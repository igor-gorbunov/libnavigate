#include "rmc.h"
#include "common.h"

#include <libnavigate/errors.h>
#include <stdio.h>

int IecCompose_RMC(const struct rmc_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], talkerid[3], utc[32], status[2],
		latitude[32], latsign[2], longitude[32], lonsign[2], snots[32],
		ctrue[32], day[3], month[3], year[3], magnetic[32], magsign[2],
		mi[2], cs[3];

	msglength = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	msglength += IecPrint_Utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & RMC_VALID_UTC);
	msglength += IecPrint_Status(msg->status, status, sizeof(status));
	msglength += IecPrint_Latitude(msg->latitude.offset, latitude, sizeof(latitude),
		msg->vfields & RMC_VALID_LATITUDE);
	msglength += IecPrint_OffsetSign(msg->latitude.sign, latsign, sizeof(latsign),
		msg->vfields & RMC_VALID_LATITUDE);
	msglength += IecPrint_Longitude(msg->longitude.offset, longitude, sizeof(longitude),
		msg->vfields & RMC_VALID_LONGITUDE);
	msglength += IecPrint_OffsetSign(msg->longitude.sign, lonsign, sizeof(lonsign),
		msg->vfields & RMC_VALID_LONGITUDE);
	msglength += IecPrint_Double(msg->speed * MPS_TO_KNOTS, snots, sizeof(snots),
		msg->vfields & RMC_VALID_SPEED);
	msglength += IecPrint_Double(msg->courseTrue, ctrue, sizeof(ctrue),
		msg->vfields & RMC_VALID_COURSETRUE);
	msglength += snprintf(day, sizeof(day),
		(msg->vfields & RMC_VALID_DATE) ? "%02u" : "", msg->day);
	msglength += snprintf(month, sizeof(month),
		(msg->vfields & RMC_VALID_DATE) ? "%02u" : "", msg->month);
	msglength += snprintf(year, sizeof(year),
		(msg->vfields & RMC_VALID_DATE) ? "%02u" : "", msg->year % 100);
	msglength += IecPrint_Double(msg->magnetic.offset, magnetic, sizeof(magnetic),
		(msg->vfields & RMC_VALID_MAGNVARIATION));
	msglength += IecPrint_OffsetSign(msg->magnetic.sign, magsign, sizeof(magsign),
		(msg->vfields & RMC_VALID_MAGNVARIATION));
	msglength += IecPrint_ModeIndicator(msg->mi, mi, sizeof(mi));

	msglength += 17;
	if (msglength > NAVI_SENTENCE_MAXSIZE)
	{
		return navi_MsgExceedsMaxSize;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg),
		"$%sRMC,%s,%s,%s,%s,%s,%s,%s,%s,%s%s%s,%s,%s,%s*%s\r\n", talkerid, utc,
		status, latitude, latsign, longitude, lonsign, snots, ctrue, day, month,
		year, magnetic, magsign, mi, "%s");
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

	result = IecParse_Latitude(buffer + index, &msg->latitude, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= RMC_VALID_LATITUDE;
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
		msg->vfields |= RMC_VALID_LONGITUDE;
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

