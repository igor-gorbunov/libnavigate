#include "zda.h"
#include "common.h"

#include <navigate.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

#ifndef NO_GENERATOR

int navi_create_zda(const struct zda_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	const char *talkerid;
	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], utc[32], day[3],
		month[3], year[5], lzhours[4], lzmins[3], cs[3];

	msglength = strlen(talkerid = navi_talkerid_to_string(msg->tid));

	msglength += IecPrint_Utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & ZDA_VALID_UTC);
	msglength += snprintf(day, sizeof(day),
		(msg->vfields & ZDA_VALID_DAY) ? "%02u" : "", msg->day);
	msglength += snprintf(month, sizeof(month),
		(msg->vfields & ZDA_VALID_MONTH) ? "%02u" : "", msg->month);
	msglength += snprintf(year, sizeof(year),
		(msg->vfields & ZDA_VALID_YEAR) ? "%04u" : "", msg->year);

	memset(lzhours, 0, sizeof(lzhours));
	memset(lzmins, 0, sizeof(lzmins));

	// Local zone hours (00 h to +/-13 h), Local zone minutes (00 to +59)
	if (msg->vfields & ZDA_VALID_LOCALZONE)
	{
		char sign[2];
		int lz = msg->lzoffset;

		snprintf(sign, sizeof(sign), lz >= 0 ? "" : "-");
		if (lz < 0)
		{
			lz = -lz;
		}

		msglength += snprintf(lzhours, sizeof(lzhours), "%s%02d", sign, lz / 60);
		msglength += snprintf(lzmins, sizeof(lzmins), "%02u", lz % 60);
	}

	msglength += 15;
	if (msglength > NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg), "$%sZDA,%s,%s,%s,%s,%s,%s*%s\r\n",
		talkerid, utc, day, month, year, lzhours, lzmins, "%s");
	IecPrint_Checksum(iecmsg, msglength, cs);

	*nmwritten = snprintf(buffer, maxsize, iecmsg, cs);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

int navi_parse_zda(struct zda_t *msg, char *buffer)
{
	int result;
	int index = 1, nmread;

	msg->vfields = 0;

	if (navi_parse_utc(buffer + index, &msg->utc, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= ZDA_VALID_UTC;
	}
	index += nmread;

	result = IecParse_Integer(buffer + index, &msg->day, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= ZDA_VALID_DAY;
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

	result = IecParse_Integer(buffer + index, &msg->month, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= ZDA_VALID_MONTH;
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

	result = IecParse_Integer(buffer + index, &msg->year, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= ZDA_VALID_YEAR;
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

	result = IecParse_LocalZone(buffer + index, &msg->lzoffset, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= ZDA_VALID_LOCALZONE;
		break;
	case navi_NullField:
		break;
	default:
		return result;
	}

	return navi_Ok;
}

#endif // NO_PARSER