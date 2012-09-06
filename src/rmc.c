#include "rmc.h"
#include "common.h"

#include <libnavigate/errors.h>
#include <libnavigate/parser.h>
#include <stdio.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

int navi_create_rmc(const struct rmc_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], talkerid[3], utc[32], status[2],
		fix[64], snots[32], ctrue[32], day[3], month[3], year[3], magnetic[32],
		magsign[2], mi[2], cs[3];

	msglength = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	msglength += IecPrint_Utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & RMC_VALID_UTC);
	msglength += IecPrint_Status(msg->status, status, sizeof(status));

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
	msglength += navi_msg_create_sign(msg->magnetic.sign, magsign, sizeof(magsign),
		(msg->vfields & RMC_VALID_MAGNVARIATION));
	msglength += IecPrint_ModeIndicator(msg->mi, mi, sizeof(mi));

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

int IecParse_RMC(struct rmc_t *msg, char *buffer, int maxsize)
{
	int result;
	int index = 1, nmread;
	struct naviDate_t date;

	msg->vfields = 0;

	result = IecParse_Time(buffer + index, &msg->utc, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= RMC_VALID_UTC;
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

	result = IecParse_Status(buffer + index, &msg->status, &nmread);
	if (result != navi_Ok)
	{
		return navi_InvalidMessage;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;

	if (navi_msg_parse_position_fix(buffer + index, &msg->fix, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= RMC_VALID_POSITION_FIX;
	}

	index += nmread;

	result = IecParse_Double(buffer + index, &msg->speed, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= RMC_VALID_SPEED;
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

	result = IecParse_Double(buffer + index, &msg->courseTrue, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= RMC_VALID_COURSETRUE;
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

	result = IecParse_Double(buffer + index, &msg->magnetic.offset, &nmread);
	index += nmread;
	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;
	switch (result)
	{
	case navi_Ok:
		// next field must not be null too
		result = IecParse_OffsetSign(buffer + index, &msg->magnetic.sign, &nmread);
		if (result == navi_Ok)
		{
			msg->vfields |= RMC_VALID_MAGNVARIATION;
		}
		else
		{
			return navi_InvalidMessage;
		}
		break;
	case navi_NullField:
		// next field must be null too
		result = IecParse_OffsetSign(buffer + index, &msg->magnetic.sign, &nmread);
		if (result != navi_NullField)
		{
			return navi_InvalidMessage;
		}
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

	result = IecParse_ModeIndicator(buffer + index, &msg->mi, &nmread);
	if (result != navi_Ok)
	{
		return navi_InvalidMessage;
	}

	index += nmread;

	if (buffer[index] != '*')
	{
		return navi_InvalidMessage;
	}

	return navi_Ok;
}

