#include "rmc.h"
#include "common.h"

#include <navigate.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

#ifndef NO_GENERATOR

int navi_create_rmc(const struct rmc_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	const char *talkerid, *status, *magsign, *mi;
	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], utc[32], fix[64], snots[32],
		ctrue[32], day[3], month[3], year[3], magnetic[32], cs[3];

	msglength = strlen(talkerid = navi_talkerid_str(msg->tid));

	msglength += IecPrint_Utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & RMC_VALID_UTC);

	msglength += strlen(status = navi_status_str(msg->status));

	msglength += navi_msg_create_position_fix(&msg->fix, fix, sizeof(fix),
		msg->vfields & RMC_VALID_POSITION_FIX);

	msglength += navi_msg_create_double(msg->speed * MPS_TO_KNOTS, snots, sizeof(snots),
		msg->vfields & RMC_VALID_SPEED);
	msglength += navi_msg_create_double(msg->courseTrue, ctrue, sizeof(ctrue),
		msg->vfields & RMC_VALID_COURSETRUE);
	msglength += snprintf(day, sizeof(day),
		(msg->vfields & RMC_VALID_DATE) ? "%02u" : "", msg->day);
	msglength += snprintf(month, sizeof(month),
		(msg->vfields & RMC_VALID_DATE) ? "%02u" : "", msg->month);
	msglength += snprintf(year, sizeof(year),
		(msg->vfields & RMC_VALID_DATE) ? "%02u" : "", msg->year % 100);
	msglength += navi_msg_create_double(msg->magnetic.offset, magnetic, sizeof(magnetic),
		(msg->vfields & RMC_VALID_MAGNVARIATION));

	msglength += strlen(magsign = navi_fixsign_str(msg->magnetic.sign,
		msg->vfields & RMC_VALID_MAGNVARIATION));
	msglength += strlen(mi = navi_modeindicator_str(msg->mi));

	msglength += 17;
	if (msglength > NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg),
		"$%sRMC,%s,%s,%s,%s,%s,%s%s%s,%s,%s,%s*%s\r\n", talkerid, utc, status,
		fix, snots, ctrue, day, month, year, magnetic, magsign, mi, "%s");
	IecPrint_Checksum(iecmsg, msglength, cs);

	*nmwritten = snprintf(buffer, maxsize, iecmsg, cs);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

int IecParse_RMC(struct rmc_t *msg, char *buffer)
{
	int result;
	int index = 1, nmread;
	struct naviDate_t date;

	msg->vfields = 0;

	if (navi_parse_utc(buffer + index, &msg->utc, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= RMC_VALID_UTC;
	}
	index += nmread;

	if (navi_parse_status(buffer + index, &msg->status, &nmread) != 0)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}
	index += nmread;

	if (navi_parse_position_fix(buffer + index, &msg->fix, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= RMC_VALID_POSITION_FIX;
	}

	index += nmread;

	if (navi_parse_number(buffer + index, &msg->speed, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= RMC_VALID_SPEED;
	}
	index += nmread;

	if (navi_parse_number(buffer + index, &msg->courseTrue, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= RMC_VALID_COURSETRUE;
	}
	index += nmread;

	result = IecParse_Date(buffer + index, &date, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->day = date.day;
		msg->month = date.month;
		msg->year = date.year;
		msg->vfields |= RMC_VALID_DATE;
		break;
	case navi_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;

	if (navi_parse_offset(buffer + index, &msg->magnetic, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= RMC_VALID_MAGNVARIATION;
	}
	index += nmread;

	if (navi_parse_modeindicator(buffer + index, &msg->mi, &nmread) != 0)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}

	return navi_Ok;
}

#endif // NO_PARSER
