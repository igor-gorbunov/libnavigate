#include "gll.h"
#include "common.h"

#include <libnavigate/errors.h>
#include <libnavigate/parser.h>
#include <stdio.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

int navi_msg_create_gll(const struct gll_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], talkerid[3], fix[64],
		utc[32], status[2], mi[2], cs[3];

	msglength = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));

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

int navi_msg_parse_gll(struct gll_t *msg, char *buffer, int maxsize)
{
	int result;
	int index = 1, nmread;

	msg->vfields = 0;

	if (navi_msg_parse_position_fix(buffer + index, &msg->fix, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= GLL_VALID_POSITION_FIX;
	}

	index += nmread;

	result = IecParse_Time(buffer + index, &msg->utc, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= GLL_VALID_UTC;
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

