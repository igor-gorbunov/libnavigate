#include "gll.h"
#include "common.h"

#include <libnavigate/errors.h>
#include <stdio.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

int IecCompose_GLL(const struct gll_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], talkerid[3], latitude[32], latsign[2],
		longitude[32], lonsign[2], utc[32], status[2], mi[2], cs[3];

	msglength = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	msglength += IecPrint_Latitude(msg->latitude.offset, latitude, sizeof(latitude),
		msg->vfields & GLL_VALID_LATITUDE);
	msglength += IecPrint_OffsetSign(msg->latitude.sign, latsign, sizeof(latsign),
		msg->vfields & GLL_VALID_LATITUDE);
	msglength += IecPrint_Longitude(msg->longitude.offset, longitude,
		sizeof(longitude), msg->vfields & GLL_VALID_LONGITUDE);
	msglength += IecPrint_OffsetSign(msg->longitude.sign, lonsign,
		sizeof(lonsign), msg->vfields & GLL_VALID_LONGITUDE);
	msglength += IecPrint_Utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & GLL_VALID_UTC);
	msglength += IecPrint_Status(msg->status, status, sizeof(status));
	msglength += IecPrint_ModeIndicator(msg->mi, mi, sizeof(mi));

	msglength += 16;
	if (msglength > NAVI_SENTENCE_MAXSIZE)
	{
		return navi_MsgExceedsMaxSize;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg), "$%sGLL,%s,%s,%s,%s,%s,%s,%s*%s\r\n",
		talkerid, latitude, latsign, longitude, lonsign, utc, status, mi, "%s");
	IecPrint_Checksum(iecmsg, msglength, cs);

	*nmwritten = snprintf(buffer, maxsize, iecmsg, cs);
	return navi_Ok;
}

int IecParse_GLL(struct gll_t *msg, char *buffer, int maxsize)
{
	int result;
	int index = 1, nmread;

	msg->vfields = 0;

	result = IecParse_Latitude(buffer + index, &msg->latitude, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= GLL_VALID_LATITUDE;
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

	result = IecParse_Longitude(buffer + index, &msg->longitude, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= GLL_VALID_LONGITUDE;
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

