#include "gns.h"
#include "common.h"

#include <libnavigate/errors.h>
#include <stdio.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

int IecCompose_GNS(const struct gns_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], talkerid[3], utc[32], latitude[32],
		latsign[2], longitude[32], lonsign[2], mi[3], totalsats[3], hdop[32],
		antalt[32], geoidsep[32], ddage[32], drsid[32], cs[3];

	msglength = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	msglength += IecPrint_Utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & GNS_VALID_UTC);
	msglength += IecPrint_Latitude(msg->latitude.offset, latitude, sizeof(latitude),
		msg->vfields & GNS_VALID_LATITUDE);
	msglength += IecPrint_OffsetSign(msg->latitude.sign, latsign, sizeof(latsign),
		msg->vfields & GNS_VALID_LATITUDE);
	msglength += IecPrint_Longitude(msg->longitude.offset, longitude, sizeof(longitude),
		msg->vfields & GNS_VALID_LONGITUDE);
	msglength += IecPrint_OffsetSign(msg->longitude.sign, lonsign, sizeof(lonsign),
		msg->vfields & GNS_VALID_LONGITUDE);
	msglength += IecPrint_ModeIndicatorArray(msg->mi, mi, sizeof(mi),
		msg->vfields & GNS_VALID_MODEINDICATOR);
	msglength += snprintf(totalsats, sizeof(totalsats),
		(msg->vfields & GNS_VALID_TOTALNMOFSATELLITES) ? "%02u" : "",
		msg->totalsats);
	msglength += IecPrint_Double(msg->hdop, hdop, sizeof(hdop),
		msg->vfields & GNS_VALID_HDOP);
	msglength += IecPrint_Double(msg->antaltitude, antalt, sizeof(antalt),
		msg->vfields & GNS_VALID_ANTENNAALTITUDE);
	msglength += IecPrint_Double(msg->geoidalsep, geoidsep, sizeof(geoidsep),
		msg->vfields & GNS_VALID_GEOIDALSEP);
	msglength += IecPrint_Double(msg->diffage, ddage, sizeof(ddage),
		msg->vfields & GNS_VALID_AGEOFDIFFDATA);
	msglength += snprintf(drsid, sizeof(drsid),
		(msg->vfields & GNS_VALID_DIFFREFSTATIONID) ? "%i" : "", msg->id);

	msglength += 23;
	if (msglength > NAVI_SENTENCE_MAXSIZE)
	{
		return navi_MsgExceedsMaxSize;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg),
		"$%sGNS,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s*%s\r\n", talkerid, utc,
		latitude, latsign, longitude, lonsign, mi, totalsats, hdop, antalt,
		geoidsep, ddage, drsid, "%s");
	IecPrint_Checksum(iecmsg, msglength, cs);

	*nmwritten = snprintf(buffer, maxsize, iecmsg, cs);
	return navi_Ok;
}

int IecParse_GNS(struct gns_t *msg, char *buffer, int maxsize)
{
	int result;
	int index = 1, nmread;

	msg->vfields = 0;

	result = IecParse_Time(buffer + index, &msg->utc, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= GNS_VALID_UTC;
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

	result = IecParse_Latitude(buffer + index, &msg->latitude, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= GNS_VALID_LATITUDE;
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
		msg->vfields |= GNS_VALID_LONGITUDE;
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

	result = IecParse_ModeIndicatorArray(buffer + index, msg->mi, &nmread);
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

	result = IecParse_Integer(buffer + index, &msg->totalsats, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= GNS_VALID_TOTALNMOFSATELLITES;
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

	result = IecParse_Double(buffer + index, &msg->hdop, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= GNS_VALID_HDOP;
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

	result = IecParse_Double(buffer + index, &msg->antaltitude, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= GNS_VALID_ANTENNAALTITUDE;
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

	result = IecParse_Double(buffer + index, &msg->geoidalsep, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= GNS_VALID_GEOIDALSEP;
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

	result = IecParse_Double(buffer + index, &msg->diffage, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= GNS_VALID_AGEOFDIFFDATA;
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

	result = IecParse_Integer(buffer + index, &msg->id, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= GNS_VALID_DIFFREFSTATIONID;
		break;
	case navi_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != '*')
	{
		return navi_InvalidMessage;
	}

	return navi_Ok;
}

