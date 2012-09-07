#include "gll.h"
#include "common.h"

#include <navigate.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

#ifndef NO_GENERATOR

int navi_create_gll(const struct gll_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	const char *talkerid;
	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], fix[64],
		utc[32], status[2], mi[2], cs[3];

	msglength = strlen(talkerid = navi_talkerid_to_string(msg->tid));

	msglength += navi_msg_create_position_fix(&msg->fix, fix, sizeof(fix),
		msg->vfields & GLL_VALID_POSITION_FIX);

	msglength += IecPrint_Utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & GLL_VALID_UTC);
	msglength += IecPrint_Status(msg->status, status, sizeof(status));
	msglength += IecPrint_ModeIndicator(msg->mi, mi, sizeof(mi));

	msglength += 16;
	if (msglength > NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg), "$%sGLL,%s,%s,%s,%s*%s\r\n",
		talkerid, fix, utc, status, mi, "%s");
	IecPrint_Checksum(iecmsg, msglength, cs);

	*nmwritten = snprintf(buffer, maxsize, iecmsg, cs);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

int navi_parse_gll(struct gll_t *msg, char *buffer)
{
	int index = 1, nmread;

	msg->vfields = 0;

	if (navi_parse_position_fix(buffer + index, &msg->fix, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= GLL_VALID_POSITION_FIX;
	}
	index += nmread;

	if (navi_parse_utc(buffer + index, &msg->utc, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= GLL_VALID_UTC;
	}
	index += nmread;

	if (navi_parse_status(buffer + index, &msg->status, &nmread) != 0)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return -1;
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
