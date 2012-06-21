/*
 * parser.c - IEC messages parsing utilities
 *
 * Copyright (C) 2012 I. S. Gorbunov <igor.genius at gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libnavigate/iecparser.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>

//
// Knots (nautical mile per hour) to meters per second
#define KNOTS_TO_MPS		0.514444445

//
// km/h to meters per second convertion coefficient
#define KMH_TO_MPS			0.277777777777777778

//
// Determines the talker id and sentence formatter
static size_t IecScan_AdressField(char *buffer, size_t maxsize,
	enum naviTalkerId_t *tid, enum naviSentence_t *msgtype);

//
// Checks that the message is not broken
// Returns 0, if the checksum is correct, -EPROTO otherwise
static size_t IecScan_CheckSum(char *buffer, size_t maxsize);

//
// Looks up Talker ID
static enum naviTalkerId_t IecLookupTalkerId(char *buffer, size_t *nmread);

//
// Looks up sentence formatter
static enum naviSentence_t IecLookupSentenceFormatter(char *buffer, size_t *nmread);

//
// Parses DTM message
static enum naviError_t IecParse_DTM(struct dtm_t *msg, char *buffer, size_t maxsize);

//
// Parses GLL message
static enum naviError_t IecParse_GLL(struct gll_t *msg, char *buffer, size_t maxsize);

//
// Parses GNS message
static enum naviError_t IecParse_GNS(struct gns_t *msg, char *buffer, size_t maxsize);

//
// Parses RMC message
static enum naviError_t IecParse_RMC(struct rmc_t *msg, char *buffer, size_t maxsize);

//
// Parses VTG message
static enum naviError_t IecParse_VTG(struct vtg_t *msg, char *buffer, size_t maxsize);

//
// Parses ZDA message
static enum naviError_t IecParse_ZDA(struct zda_t *msg, char *buffer, size_t maxsize);

//
// Parser of IEC 61162-1 (2000-07) messages
enum naviError_t IecParseMessage(char *buffer, size_t maxsize, size_t msgsize,
	void *msg, enum naviSentence_t *msgtype, size_t *nmread)
{
	int som;	// start of message index
	int eom;	// end of message index

	//
	//	Determine the borders of message in buffer
	//

	// Skip up to beginning of the next message
	for (som = 0; buffer[som] != '$' && som < maxsize; som++) { }
	if (som >= maxsize)
	{	// No valid message
		return naviError_NoValidMessage;
	}

	// Skip up to end of the message
	for (eom = som + 1; eom < maxsize; eom++)
	{
		if (buffer[eom - 1] == '\r' && buffer[eom] == '\n')
		{
			break;
		}
	}
	if (eom >= maxsize)
	{	// No valid message
		return naviError_NoValidMessage;
	}

	// At least read a message
	*nmread = eom;

	size_t result;

	//
	// Check that the message is not broken
	//
	if ((result = IecScan_CheckSum(buffer + som, maxsize - (som + eom))) < 0)
	{
		return naviError_CrcEror;
	}

	//
	// Determine the talker ID and message type
	//
	enum naviTalkerId_t tid;

	if (IecScan_AdressField(buffer + som + 1, maxsize - (som + eom + 1),
			&tid, msgtype) < 0)
	{
		return naviError_Undefined;
	}

	//
	// Parse the message fields
	//
	switch (*msgtype)
	{
	case naviSentence_AAM:
	case naviSentence_ACK:
	case naviSentence_ALM:
	case naviSentence_ALR:
	case naviSentence_APB:
	case naviSentence_BEC:
	case naviSentence_BOD:
	case naviSentence_BWC:
	case naviSentence_BWR:
	case naviSentence_BWW:
	case naviSentence_DBT:
	case naviSentence_DCN:
	case naviSentence_DPT:
	case naviSentence_DSC:
	case naviSentence_DSE:
	case naviSentence_DSI:
	case naviSentence_DSR:
		break;
	case naviSentence_DTM:
		if (maxsize < sizeof(struct dtm_t))
		{
			return naviError_NotEnoughBuffer;
		}
		((struct dtm_t *)msg)->tid = tid;
		return IecParse_DTM((struct dtm_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case naviSentence_FSI:
	case naviSentence_GBS:
	case naviSentence_GGA:
	case naviSentence_GLC:
		break;
	case naviSentence_GLL:
		if (maxsize < sizeof(struct gll_t))
		{
			return naviError_NotEnoughBuffer;
		}
		((struct gll_t *)msg)->tid = tid;
		return IecParse_GLL((struct gll_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case naviSentence_GNS:
		if (maxsize < sizeof(struct gns_t))
		{
			return naviError_NotEnoughBuffer;
		}
		((struct gns_t *)msg)->tid = tid;
		return IecParse_GNS((struct gns_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case naviSentence_GRS:
	case naviSentence_GSA:
	case naviSentence_GST:
	case naviSentence_GSV:
	case naviSentence_HDG:
	case naviSentence_HDT:
	case naviSentence_HMR:
	case naviSentence_HMS:
	case naviSentence_HSC:
	case naviSentence_HTC:
	case naviSentence_HTD:
	case naviSentence_LCD:
	case naviSentence_MLA:
	case naviSentence_MSK:
	case naviSentence_MSS:
	case naviSentence_MTW:
	case naviSentence_MWD:
	case naviSentence_MWV:
	case naviSentence_OSD:
	case naviSentence_RMA:
	case naviSentence_RMB:
		break;
	case naviSentence_RMC:
		if (maxsize < sizeof(struct rmc_t))
		{
			return naviError_NotEnoughBuffer;
		}
		((struct rmc_t *)msg)->tid = tid;
		return IecParse_RMC((struct rmc_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case naviSentence_ROT:
	case naviSentence_RPM:
	case naviSentence_RSA:
	case naviSentence_RSD:
	case naviSentence_RTE:
	case naviSentence_SFI:
	case naviSentence_STN:
	case naviSentence_TLB:
	case naviSentence_TLL:
	case naviSentence_TTM:
	case naviSentence_TXT:
	case naviSentence_VBW:
	case naviSentence_VDR:
	case naviSentence_VHW:
	case naviSentence_VLW:
	case naviSentence_VPW:
		break;
	case naviSentence_VTG:
		if (maxsize < sizeof(struct vtg_t))
		{
			return naviError_NotEnoughBuffer;
		}
		((struct vtg_t *)msg)->tid = tid;
		return IecParse_VTG((struct vtg_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case naviSentence_WCV:
	case naviSentence_WNC:
	case naviSentence_WPL:
	case naviSentence_XDR:
	case naviSentence_XTE:
	case naviSentence_XTR:
		break;
	case naviSentence_ZDA:
		if (maxsize < sizeof(struct zda_t))
		{
			return naviError_NotEnoughBuffer;
		}
		((struct zda_t *)msg)->tid = tid;
		return IecParse_ZDA((struct zda_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case naviSentence_ZDL:
	case naviSentence_ZFO:
	case naviSentence_ZTG:
		break;
	default:
		break;
	}

	return naviError_MsgNotSupported;
}

// Talker identifier and sentence formatter
static size_t IecScan_AdressField(char *buffer, size_t maxsize,
	enum naviTalkerId_t *tid, enum naviSentence_t *msgtype)
{
	size_t result, nmread;

	*tid = IecLookupTalkerId(buffer, &nmread);
	result = nmread;
	*msgtype = IecLookupSentenceFormatter(buffer + result, &nmread);
	result += nmread;

	return result;
}

//
// Parses datum field
static enum naviError_t IecParse_Datum(char *buffer, enum naviDatum_t *datum,
	size_t *nmread);

//
// Parses datum subdivision code field
static enum naviError_t IecParse_DatumSub(char *buffer,
	enum naviLocalDatumSub_t *datumsub, size_t *nmread);

//
// Parses floating point value
static enum naviError_t IecParse_Double(char *buffer, double *value, size_t *nmread);

//
// Parses latitude/longitude/offset sign
static enum naviError_t IecParse_OffsetSign(char *buffer, enum naviOfsSign_t *sign,
	size_t *nmread);

//
// Parses latitude
static enum naviError_t IecParse_Latitude(char *buffer, struct naviOffset_t *latitude,
	size_t *nmread);

//
// Parses longitude sign
static enum naviError_t IecParse_Longitude(char *buffer, struct naviOffset_t *longitude,
	size_t *nmread);

//
// Parses time
static enum naviError_t IecParse_Time(char *buffer, struct naviUtc_t *utc,
	size_t *nmread);

//
// Parses status
static enum naviError_t IecParse_Status(char *buffer, enum naviStatus_t *status,
	size_t *nmread);

//
// Parses mode indicator
static enum naviError_t IecParse_ModeIndicator(char *buffer, enum naviModeIndicator_t *mi,
	size_t *nmread);

//
// Parses mode indicator array
static enum naviError_t IecParse_ModeIndicatorArray(char *buffer,
	enum naviModeIndicator_t mi[], size_t *nmread);

//
// Parses integer value
static enum naviError_t IecParse_Integer(char *buffer, int *value, size_t *nmread);

//
// Parses date (ddmmyy or ddmmyyyy)
static enum naviError_t IecParse_Date(char *buffer, struct naviDate_t *date,
	size_t *nmread);

//
// Parses local zone (sxx,xx)
static enum naviError_t IecParse_LocalZone(char *buffer, int *offset,
	size_t *nmread);

// DTM
static enum naviError_t IecParse_DTM(struct dtm_t *msg, char *buffer, size_t maxsize)
{
	enum naviError_t result;
	size_t index = 1, nmread;

	msg->vfields = 0;

	result = IecParse_Datum(buffer + index, &msg->ld, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= DTM_VALID_LOCALDATUM;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_DatumSub(buffer + index, &msg->lds, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= DTM_VALID_LOCALDATUMSUB;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->latofs.offset, &nmread);
	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;
	switch (result)
	{
	case naviError_OK:
		// next field must not be null too
		result = IecParse_OffsetSign(buffer + index, &msg->latofs.sign, &nmread);
		if (result == naviError_OK)
		{
			msg->vfields |= DTM_VALID_LATOFFSET;
		}
		else
		{
			return naviError_InvalidMessage;
		}
		break;
	case naviError_NullField:
		// next field must be null too
		result = IecParse_OffsetSign(buffer + index, &msg->latofs.sign, &nmread);
		if (result != naviError_NullField)
		{
			return naviError_InvalidMessage;
		}
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->lonofs.offset, &nmread);
	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;
	switch (result)
	{
	case naviError_OK:
		// next field must not be null too
		result = IecParse_OffsetSign(buffer + index, &msg->lonofs.sign, &nmread);
		if (result == naviError_OK)
		{
			msg->vfields |= DTM_VALID_LONOFFSET;
		}
		else
		{
			return naviError_InvalidMessage;
		}
		break;
	case naviError_NullField:
		// next field must be null too
		result = IecParse_OffsetSign(buffer + index, &msg->latofs.sign, &nmread);
		if (result != naviError_NullField)
		{
			return naviError_InvalidMessage;
		}
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->altoffset, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= DTM_VALID_ALTITUDEOFFSET;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Datum(buffer + index, &msg->rd, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= DTM_VALID_REFERENCEDATUM;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != '*')
	{
		return naviError_InvalidMessage;
	}

	return naviError_OK;
}

// GLL
static enum naviError_t IecParse_GLL(struct gll_t *msg, char *buffer, size_t maxsize)
{
	enum naviError_t result;
	size_t index = 1, nmread;

	msg->vfields = 0;

	result = IecParse_Latitude(buffer + index, &msg->latitude, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= GLL_VALID_LATITUDE;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Longitude(buffer + index, &msg->longitude, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= GLL_VALID_LONGITUDE;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Time(buffer + index, &msg->utc, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= GLL_VALID_UTC;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Status(buffer + index, &msg->status, &nmread);
	if (result != naviError_OK)
	{
		return naviError_InvalidMessage;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_ModeIndicator(buffer + index, &msg->mi, &nmread);
	if (result != naviError_OK)
	{
		return naviError_InvalidMessage;
	}

	index += nmread;

	if (buffer[index] != '*')
	{
		return naviError_InvalidMessage;
	}

	return naviError_OK;
}

// GNS
static enum naviError_t IecParse_GNS(struct gns_t *msg, char *buffer, size_t maxsize)
{
	enum naviError_t result;
	size_t index = 1, nmread;

	msg->vfields = 0;

	result = IecParse_Time(buffer + index, &msg->utc, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= GNS_VALID_UTC;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Latitude(buffer + index, &msg->latitude, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= GNS_VALID_LATITUDE;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Longitude(buffer + index, &msg->longitude, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= GNS_VALID_LONGITUDE;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_ModeIndicatorArray(buffer + index, msg->mi, &nmread);
	if (result != naviError_OK)
	{
		return naviError_InvalidMessage;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Integer(buffer + index, &msg->totalsats, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= GNS_VALID_TOTALNMOFSATELLITES;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->hdop, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= GNS_VALID_HDOP;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->antaltitude, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= GNS_VALID_ANTENNAALTITUDE;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->geoidalsep, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= GNS_VALID_GEOIDALSEP;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->diffage, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= GNS_VALID_AGEOFDIFFDATA;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Integer(buffer + index, &msg->id, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= GNS_VALID_DIFFREFSTATIONID;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != '*')
	{
		return naviError_InvalidMessage;
	}

	return naviError_OK;
}

// RMC
static enum naviError_t IecParse_RMC(struct rmc_t *msg, char *buffer, size_t maxsize)
{
	enum naviError_t result;
	size_t index = 1, nmread;
	struct naviDate_t date;

	msg->vfields = 0;

	result = IecParse_Time(buffer + index, &msg->utc, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= RMC_VALID_UTC;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Status(buffer + index, &msg->status, &nmread);
	if (result != naviError_OK)
	{
		return naviError_InvalidMessage;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Latitude(buffer + index, &msg->latitude, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= RMC_VALID_LATITUDE;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Longitude(buffer + index, &msg->longitude, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= RMC_VALID_LONGITUDE;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->speed, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= RMC_VALID_SPEED;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->courseTrue, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= RMC_VALID_COURSETRUE;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Date(buffer + index, &date, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->day = date.day;
		msg->month = date.month;
		msg->year = date.year;
		msg->vfields |= RMC_VALID_DATE;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->magnetic.offset, &nmread);
	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;
	switch (result)
	{
	case naviError_OK:
		// next field must not be null too
		result = IecParse_OffsetSign(buffer + index, &msg->magnetic.sign, &nmread);
		if (result == naviError_OK)
		{
			msg->vfields |= RMC_VALID_MAGNVARIATION;
		}
		else
		{
			return naviError_InvalidMessage;
		}
		break;
	case naviError_NullField:
		// next field must be null too
		result = IecParse_OffsetSign(buffer + index, &msg->magnetic.sign, &nmread);
		if (result != naviError_NullField)
		{
			return naviError_InvalidMessage;
		}
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_ModeIndicator(buffer + index, &msg->mi, &nmread);
	if (result != naviError_OK)
	{
		return naviError_InvalidMessage;
	}

	index += nmread;

	if (buffer[index] != '*')
	{
		return naviError_InvalidMessage;
	}

	return naviError_OK;
}

// VTG
static enum naviError_t IecParse_VTG(struct vtg_t *msg, char *buffer, size_t maxsize)
{
	enum naviError_t result;
	size_t index = 1, nmread;
	double speedknots, speedkmph;

	msg->vfields = 0;

	result = IecParse_Double(buffer + index, &msg->courseTrue, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= VTG_VALID_COURSETRUE;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;
	if (buffer[index] == 'T')
	{
		index += 1;
	}
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->courseMagn, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= VTG_VALID_COURSEMAGN;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;
	if (buffer[index] == 'M')
	{
		index += 1;
	}
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &speedknots, &nmread);
	switch (result)
	{
	case naviError_OK:
		break;
	case naviError_NullField:
		speedknots = -1.0;
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;
	if (buffer[index] == 'N')
	{
		index += 1;
	}
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &speedkmph, &nmread);
	switch (result)
	{
	case naviError_OK:
		break;
	case naviError_NullField:
		speedkmph = -1.0;
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;
	if (buffer[index] == 'K')
	{
		index += 1;
	}
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	if (speedkmph > -1.0)
	{
		msg->speed = speedkmph * KMH_TO_MPS;
		msg->vfields |= VTG_VALID_SPEED;
	}
	else if (speedknots > -1.0)
	{
		msg->speed = speedknots * KNOTS_TO_MPS;
		msg->vfields |= VTG_VALID_SPEED;
	}

	result = IecParse_ModeIndicator(buffer + index, &msg->mi, &nmread);
	if (result != naviError_OK)
	{
		return naviError_InvalidMessage;
	}

	index += nmread;

	if (buffer[index] != '*')
	{
		return naviError_InvalidMessage;
	}

	return naviError_OK;
}

// ZDA
static enum naviError_t IecParse_ZDA(struct zda_t *msg, char *buffer, size_t maxsize)
{
	enum naviError_t result;
	size_t index = 1, nmread;

	msg->vfields = 0;

	result = IecParse_Time(buffer + index, &msg->utc, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= ZDA_VALID_UTC;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Integer(buffer + index, &msg->day, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= ZDA_VALID_DAY;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Integer(buffer + index, &msg->month, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= ZDA_VALID_MONTH;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_Integer(buffer + index, &msg->year, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= ZDA_VALID_YEAR;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return naviError_InvalidMessage;
	}
	index += 1;

	result = IecParse_LocalZone(buffer + index, &msg->lzoffset, &nmread);
	switch (result)
	{
	case naviError_OK:
		msg->vfields |= ZDA_VALID_LOCALZONE;
		break;
	case naviError_NullField:
		break;
	default:
		return result;
	}

	return naviError_OK;
}

// Scan checksum
static size_t IecScan_CheckSum(char *buffer, size_t maxsize)
{
	int r;
	unsigned i;
	unsigned long cs, ucs = 0;

	r = -EPROTO;	// suppose the CRC error

	// Skip up to next character after '$'
	for (i = 0; buffer[i] != '$' && i < maxsize; i++) { }
	if (i >= maxsize)
	{
		return -EPROTO;
	}
	for (i += 1; buffer[i] != '*' && i < maxsize; i++)
	{
		ucs = ucs ^ buffer[i];
	}
	if (i >= maxsize)
	{
		return -EPROTO;
	}

	cs = strtoul(buffer + i + 1, NULL, 16);
	if (ucs == cs)
	{
		r = 0;
	}

	return r;
}

// Looks up Talker ID
static enum naviTalkerId_t IecLookupTalkerId(char *buffer, size_t *nmread)
{
	*nmread = 2;

	if (strncmp("AG", buffer, 2) == 0)
	{
		return naviTalkerId_AG;
	}
	else if (strncmp("AP", buffer, 2) == 0)
	{
		return naviTalkerId_AP;
	}
	else if (strncmp("AI", buffer, 2) == 0)
	{
		return naviTalkerId_AI;
	}
	else if (strncmp("CD", buffer, 2) == 0)
	{
		return naviTalkerId_CD;
	}
	else if (strncmp("CR", buffer, 2) == 0)
	{
		return naviTalkerId_CR;
	}
	else if (strncmp("CS", buffer, 2) == 0)
	{
		return naviTalkerId_CS;
	}
	else if (strncmp("CT", buffer, 2) == 0)
	{
		return naviTalkerId_CT;
	}
	else if (strncmp("CV", buffer, 2) == 0)
	{
		return naviTalkerId_CV;
	}
	else if (strncmp("CX", buffer, 2) == 0)
	{
		return naviTalkerId_CX;
	}
	else if (strncmp("DE", buffer, 2) == 0)
	{
		return naviTalkerId_DE;
	}
	else if (strncmp("DF", buffer, 2) == 0)
	{
		return naviTalkerId_DF;
	}
	else if (strncmp("EC", buffer, 2) == 0)
	{
		return naviTalkerId_EC;
	}
	else if (strncmp("EI", buffer, 2) == 0)
	{
		return naviTalkerId_EI;
	}
	else if (strncmp("EP", buffer, 2) == 0)
	{
		return naviTalkerId_EP;
	}
	else if (strncmp("ER", buffer, 2) == 0)
	{
		return naviTalkerId_ER;
	}
	else if (strncmp("GA", buffer, 2) == 0)
	{
		return naviTalkerId_GA;
	}
	else if (strncmp("GP", buffer, 2) == 0)
	{
		return naviTalkerId_GP;
	}
	else if (strncmp("GL", buffer, 2) == 0)
	{
		return naviTalkerId_GL;
	}
	else if (strncmp("GN", buffer, 2) == 0)
	{
		return naviTalkerId_GN;
	}
	else if (strncmp("GW", buffer, 2) == 0)
	{
		return naviTalkerId_GW;
	}
	else if (strncmp("HC", buffer, 2) == 0)
	{
		return naviTalkerId_HC;
	}
	else if (strncmp("HE", buffer, 2) == 0)
	{
		return naviTalkerId_HE;
	}
	else if (strncmp("HN", buffer, 2) == 0)
	{
		return naviTalkerId_HN;
	}
	else if (strncmp("II", buffer, 2) == 0)
	{
		return naviTalkerId_II;
	}
	else if (strncmp("IN", buffer, 2) == 0)
	{
		return naviTalkerId_IN;
	}
	else if (strncmp("LC", buffer, 2) == 0)
	{
		return naviTalkerId_LC;
	}
	else if (strncmp("P", buffer, 1) == 0)
	{
		*nmread = 1;
		return naviTalkerId_P;
	}
	else if (strncmp("RA", buffer, 2) == 0)
	{
		return naviTalkerId_RA;
	}
	else if (strncmp("SD", buffer, 2) == 0)
	{
		return naviTalkerId_SD;
	}
	else if (strncmp("SN", buffer, 2) == 0)
	{
		return naviTalkerId_SN;
	}
	else if (strncmp("SS", buffer, 2) == 0)
	{
		return naviTalkerId_SS;
	}
	else if (strncmp("TI", buffer, 2) == 0)
	{
		return naviTalkerId_TI;
	}
	else if (strncmp("VD", buffer, 2) == 0)
	{
		return naviTalkerId_VD;
	}
	else if (strncmp("VM", buffer, 2) == 0)
	{
		return naviTalkerId_VM;
	}
	else if (strncmp("VW", buffer, 2) == 0)
	{
		return naviTalkerId_VW;
	}
	else if (strncmp("VR", buffer, 2) == 0)
	{
		return naviTalkerId_VR;
	}
	else if (strncmp("YX", buffer, 2) == 0)
	{
		return naviTalkerId_YX;
	}
	else if (strncmp("ZA", buffer, 2) == 0)
	{
		return naviTalkerId_ZA;
	}
	else if (strncmp("ZC", buffer, 2) == 0)
	{
		return naviTalkerId_ZC;
	}
	else if (strncmp("ZQ", buffer, 2) == 0)
	{
		return naviTalkerId_ZQ;
	}
	else if (strncmp("ZV", buffer, 2) == 0)
	{
		return naviTalkerId_ZV;
	}
	else if (strncmp("WI", buffer, 2) == 0)
	{
		return naviTalkerId_WI;
	}
	else
	{
		return naviTalkerId_Undefined;
	}
}

// Looks up sentence formatter
static enum naviSentence_t IecLookupSentenceFormatter(char *buffer, size_t *nmread)
{
	*nmread = 3;

	if (strncmp("AAM", buffer, 3) == 0)
	{
		return naviSentence_AAM;
	}
	else if (strncmp("ACK", buffer, 3) == 0)
	{
		return naviSentence_ACK;
	}
	else if (strncmp("ALM", buffer, 3) == 0)
	{
		return naviSentence_ALM;
	}
	else if (strncmp("ALR", buffer, 3) == 0)
	{
		return naviSentence_ALR;
	}
	else if (strncmp("APB", buffer, 3) == 0)
	{
		return naviSentence_APB;
	}
	else if (strncmp("BEC", buffer, 3) == 0)
	{
		return naviSentence_BEC;
	}
	else if (strncmp("BOD", buffer, 3) == 0)
	{
		return naviSentence_BOD;
	}
	else if (strncmp("BWC", buffer, 3) == 0)
	{
		return naviSentence_BWC;
	}
	else if (strncmp("BWR", buffer, 3) == 0)
	{
		return naviSentence_BWR;
	}
	else if (strncmp("BWW", buffer, 3) == 0)
	{
		return naviSentence_BWW;
	}
	else if (strncmp("DBT", buffer, 3) == 0)
	{
		return naviSentence_DBT;
	}
	else if (strncmp("DCN", buffer, 3) == 0)
	{
		return naviSentence_DCN;
	}
	else if (strncmp("DPT", buffer, 3) == 0)
	{
		return naviSentence_DPT;
	}
	else if (strncmp("DSC", buffer, 3) == 0)
	{
		return naviSentence_DSC;
	}
	else if (strncmp("DSE", buffer, 3) == 0)
	{
		return naviSentence_DSE;
	}
	else if (strncmp("DSI", buffer, 3) == 0)
	{
		return naviSentence_DSI;
	}
	else if (strncmp("DSR", buffer, 3) == 0)
	{
		return naviSentence_DSR;
	}
	else if (strncmp("DTM", buffer, 3) == 0)
	{
		return naviSentence_DTM;
	}
	else if (strncmp("FSI", buffer, 3) == 0)
	{
		return naviSentence_FSI;
	}
	else if (strncmp("GBS", buffer, 3) == 0)
	{
		return naviSentence_GBS;
	}
	else if (strncmp("GGA", buffer, 3) == 0)
	{
		return naviSentence_GGA;
	}
	else if (strncmp("GLC", buffer, 3) == 0)
	{
		return naviSentence_GLC;
	}
	else if (strncmp("GLL", buffer, 3) == 0)
	{
		return naviSentence_GLL;
	}
	else if (strncmp("GNS", buffer, 3) == 0)
	{
		return naviSentence_GNS;
	}
	else if (strncmp("GRS", buffer, 3) == 0)
	{
		return naviSentence_GRS;
	}
	else if (strncmp("GSA", buffer, 3) == 0)
	{
		return naviSentence_GSA;
	}
	else if (strncmp("GST", buffer, 3) == 0)
	{
		return naviSentence_GST;
	}
	else if (strncmp("GSV", buffer, 3) == 0)
	{
		return naviSentence_GSV;
	}
	else if (strncmp("HDG", buffer, 3) == 0)
	{
		return naviSentence_HDG;
	}
	else if (strncmp("HDT", buffer, 3) == 0)
	{
		return naviSentence_HDT;
	}
	else if (strncmp("HMR", buffer, 3) == 0)
	{
		return naviSentence_HMR;
	}
	else if (strncmp("HMS", buffer, 3) == 0)
	{
		return naviSentence_HMS;
	}
	else if (strncmp("HSC", buffer, 3) == 0)
	{
		return naviSentence_HSC;
	}
	else if (strncmp("HTC", buffer, 3) == 0)
	{
		return naviSentence_HTC;
	}
	else if (strncmp("HTD", buffer, 3) == 0)
	{
		return naviSentence_HTD;
	}
	else if (strncmp("LCD", buffer, 3) == 0)
	{
		return naviSentence_LCD;
	}
	else if (strncmp("MLA", buffer, 3) == 0)
	{
		return naviSentence_MLA;
	}
	else if (strncmp("MSK", buffer, 3) == 0)
	{
		return naviSentence_MSK;
	}
	else if (strncmp("MSS", buffer, 3) == 0)
	{
		return naviSentence_MSS;
	}
	else if (strncmp("MTW", buffer, 3) == 0)
	{
		return naviSentence_MTW;
	}
	else if (strncmp("MWD", buffer, 3) == 0)
	{
		return naviSentence_MWD;
	}
	else if (strncmp("MWV", buffer, 3) == 0)
	{
		return naviSentence_MWV;
	}
	else if (strncmp("OSD", buffer, 3) == 0)
	{
		return naviSentence_OSD;
	}
	else if (strncmp("RMA", buffer, 3) == 0)
	{
		return naviSentence_RMA;
	}
	else if (strncmp("RMB", buffer, 3) == 0)
	{
		return naviSentence_RMB;
	}
	else if (strncmp("RMC", buffer, 3) == 0)
	{
		return naviSentence_RMC;
	}
	else if (strncmp("ROT", buffer, 3) == 0)
	{
		return naviSentence_ROT;
	}
	else if (strncmp("RPM", buffer, 3) == 0)
	{
		return naviSentence_RPM;
	}
	else if (strncmp("RSA", buffer, 3) == 0)
	{
		return naviSentence_RSA;
	}
	else if (strncmp("RSD", buffer, 3) == 0)
	{
		return naviSentence_RSD;
	}
	else if (strncmp("RTE", buffer, 3) == 0)
	{
		return naviSentence_RTE;
	}
	else if (strncmp("SFI", buffer, 3) == 0)
	{
		return naviSentence_SFI;
	}
	else if (strncmp("STN", buffer, 3) == 0)
	{
		return naviSentence_STN;
	}
	else if (strncmp("TLB", buffer, 3) == 0)
	{
		return naviSentence_TLB;
	}
	else if (strncmp("TLL", buffer, 3) == 0)
	{
		return naviSentence_TLL;
	}
	else if (strncmp("TTM", buffer, 3) == 0)
	{
		return naviSentence_TTM;
	}
	else if (strncmp("TXT", buffer, 3) == 0)
	{
		return naviSentence_TXT;
	}
	else if (strncmp("VBW", buffer, 3) == 0)
	{
		return naviSentence_VBW;
	}
	else if (strncmp("VDR", buffer, 3) == 0)
	{
		return naviSentence_VDR;
	}
	else if (strncmp("VHW", buffer, 3) == 0)
	{
		return naviSentence_VHW;
	}
	else if (strncmp("VLW", buffer, 3) == 0)
	{
		return naviSentence_VLW;
	}
	else if (strncmp("VPW", buffer, 3) == 0)
	{
		return naviSentence_VPW;
	}
	else if (strncmp("VTG", buffer, 3) == 0)
	{
		return naviSentence_VTG;
	}
	else if (strncmp("WCV", buffer, 3) == 0)
	{
		return naviSentence_WCV;
	}
	else if (strncmp("WNC", buffer, 3) == 0)
	{
		return naviSentence_WNC;
	}
	else if (strncmp("WPL", buffer, 3) == 0)
	{
		return naviSentence_WPL;
	}
	else if (strncmp("XDR", buffer, 3) == 0)
	{
		return naviSentence_XDR;
	}
	else if (strncmp("XTE", buffer, 3) == 0)
	{
		return naviSentence_XTE;
	}
	else if (strncmp("XTR", buffer, 3) == 0)
	{
		return naviSentence_XTR;
	}
	else if (strncmp("ZDA", buffer, 3) == 0)
	{
		return naviSentence_ZDA;
	}
	else if (strncmp("ZDL", buffer, 3) == 0)
	{
		return naviSentence_ZDL;
	}
	else if (strncmp("ZFO", buffer, 3) == 0)
	{
		return naviSentence_ZFO;
	}
	else if (strncmp("ZTG", buffer, 3) == 0)
	{
		return naviSentence_ZTG;
	}
	else
	{
		return naviSentence_Undefined;
	}
}

// Looks up datum code
static enum naviError_t IecParse_Datum(char *buffer, enum naviDatum_t *datum,
	size_t *nmread)
{
	*nmread = 3;

	if (strncmp("W84", buffer, 3) == 0)
	{
		*datum = naviDatum_WGS84;
		return naviError_OK;
	}
	else if (strncmp("W72", buffer, 3) == 0)
	{
		*datum = naviDatum_WGS72;
		return naviError_OK;
	}
	else if (strncmp("S85", buffer, 3) == 0)
	{
		*datum = naviDatum_SGS85;
		return naviError_OK;
	}
	else if (strncmp("P90", buffer, 3) == 0)
	{
		*datum = naviDatum_PE90;
		return naviError_OK;
	}
	else if (strncmp("999", buffer, 3) == 0)
	{
		*datum = naviDatum_UserDefined;
		return naviError_OK;
	}
	else if ((strncmp(",", buffer, 1) == 0) || (strncmp("*", buffer, 1) == 0))
	{
		*nmread = 0;
		*datum = naviDatum_Undefined;
		return naviError_NullField;
	}
	else
	{
		*nmread = 0;
		return naviError_MsgNotSupported;
	}
}

// Looks up datum subdivision code
static enum naviError_t IecParse_DatumSub(char *buffer,
	enum naviLocalDatumSub_t *datumsub, size_t *nmread)
{
	if (strncmp(",", buffer, 1) == 0)
	{
		*nmread = 0;
		*datumsub = naviLocalDatumSub_Undefined;
		return naviError_NullField;
	}
	else
	{
		*nmread = 0;
		return naviError_MsgNotSupported;
	}
}

// Parses floating point value
static enum naviError_t IecParse_Double(char *buffer, double *value, size_t *nmread)
{
	char *endptr = NULL;

	errno = 0;
	*value = strtod(buffer, &endptr);
	*nmread = endptr - buffer;
	if (errno != 0)
	{
		return naviError_MsgNotSupported;
	}
	else if (*nmread == 0)
	{
		return naviError_NullField;
	}
	else
	{
		return naviError_OK;
	}
}

// Parses latitude/longitude/offset sign
static enum naviError_t IecParse_OffsetSign(char *buffer, enum naviOfsSign_t *sign,
	size_t *nmread)
{
	*nmread = 1;

	if (strncmp("N", buffer, 1) == 0)
	{
		*sign = naviOfsSign_North;
		return naviError_OK;
	}
	else if (strncmp("S", buffer, 1) == 0)
	{
		*sign = naviOfsSign_South;
		return naviError_OK;
	}
	else if (strncmp("E", buffer, 1) == 0)
	{
		*sign = naviOfsSign_East;
		return naviError_OK;
	}
	else if (strncmp("W", buffer, 1) == 0)
	{
		*sign = naviOfsSign_West;
		return naviError_OK;
	}
	else
	{
		*nmread = 0;
		return naviError_NullField;
	}
}

// Parses latitude
static enum naviError_t IecParse_Latitude(char *buffer, struct naviOffset_t *latitude,
	size_t *nmread)
{
	size_t idx = 0;
	char *endptr = NULL;
	char degrees[4];
	double deg, min;

	// TODO Implement a method for checking sentence field
	// enum naviError_t IecParse_CheckField(char *buffer, enum naviFieldType_t type,
	//     size_t *nmread);
	// if ((result = IecParse_CheckField(buffer, type, &nmread)) != naviError_OK)
	//     return result;

	if ((buffer[idx] == ',') && ((buffer[idx + 1] == ',') ||
		(buffer[idx + 1] == '*')))
	{
		*nmread = 1;
		return naviError_NullField;
	}
	else if ((buffer[idx] == ',') && !((buffer[idx + 1] == ',') ||
		(buffer[idx + 1] == '*')))
	{
		*nmread = 1;
		return naviError_InvalidMessage;
	}

	degrees[0] = buffer[0];
	degrees[1] = buffer[1];
	degrees[2] = '\0';

	idx = 2;

	errno = 0;
	deg = strtod(degrees, &endptr);
	*nmread = endptr - degrees;
	if (errno != 0)
	{
		return naviError_InvalidMessage;
	}
	else if (*nmread < idx)
	{
		return naviError_InvalidMessage;
	}

	errno = 0;
	min = strtod(buffer + idx, &endptr);
	*nmread = endptr - buffer;
	if (errno != 0)
	{
		return naviError_InvalidMessage;
	}
	else
	{
		latitude->offset = deg + min / 60.;

		enum naviError_t result = IecParse_OffsetSign(buffer + *nmread + 1,
			&latitude->sign, &idx);
		if (result != naviError_OK)
		{
			return result;
		}

		*nmread += idx + 1;

		return naviError_OK;
	}
}

// Parses longitude sign
static enum naviError_t IecParse_Longitude(char *buffer, struct naviOffset_t *longitude,
	size_t *nmread)
{
	size_t idx = 0;
	char *endptr = NULL;
	char degrees[4];
	double deg, min;

	if ((buffer[idx] == ',') && ((buffer[idx + 1] == ',') ||
		(buffer[idx + 1] == '*')))
	{
		*nmread = 1;
		return naviError_NullField;
	}
	else if ((buffer[idx] == ',') && !((buffer[idx + 1] == ',') ||
		(buffer[idx + 1] == '*')))
	{
		*nmread = 1;
		return naviError_InvalidMessage;
	}

	degrees[0] = buffer[0];
	degrees[1] = buffer[1];
	degrees[2] = buffer[2];
	degrees[3] = '\0';

	idx = 3;

	errno = 0;
	deg = strtod(degrees, &endptr);
	*nmread = endptr - degrees;
	if (errno != 0)
	{
		return naviError_InvalidMessage;
	}
	else if (*nmread < idx)
	{
		return naviError_InvalidMessage;
	}

	errno = 0;
	min = strtod(buffer + idx, &endptr);
	*nmread = endptr - buffer;
	if (errno != 0)
	{
		return naviError_InvalidMessage;
	}
	else
	{
		longitude->offset = deg + min / 60.;

		enum naviError_t result = IecParse_OffsetSign(buffer + *nmread + 1,
			&longitude->sign, &idx);
		if (result != naviError_OK)
		{
			return result;
		}

		*nmread += idx + 1;

		return naviError_OK;
	}
}

// Parses time
static enum naviError_t IecParse_Time(char *buffer, struct naviUtc_t *utc,
	size_t *nmread)
{
	size_t idx;

	utc->msec = 0;

	for (idx = 0; ; idx++)
	{
		if (isdigit(buffer[idx]))
		{
			if (idx == 0)
			{
				utc->hour = buffer[idx] - '0';
			}
			else if (idx == 1)
			{
				utc->hour = utc->hour * 10 + (buffer[idx] - '0');
			}
			else if (idx == 2)
			{
				utc->min = buffer[idx] - '0';
			}
			else if (idx == 3)
			{
				utc->min = utc->min * 10 + (buffer[idx] - '0');
			}
			else if (idx == 4)
			{
				utc->sec = buffer[idx] - '0';
			}
			else if (idx == 5)
			{
				utc->sec = utc->sec * 10 + (buffer[idx] - '0');
			}
			else
			{
				utc->msec = utc->msec * 10 + (buffer[idx] - '0');
			}
		}
		else if (buffer[idx] == '.')
		{
			continue;
		}
		else if ((buffer[idx] == ',') || (buffer[idx] == '*'))
		{
			break;
		}
		else
		{
			*nmread = idx;
			return naviError_InvalidMessage;
		}
	}

	*nmread = idx;

	if (idx == 0)
	{
		return naviError_NullField;
	}
	else if (idx < 6)
	{
		return naviError_InvalidMessage;
	}
	else
	{
		return naviError_OK;
	}
}

// Parses status
static enum naviError_t IecParse_Status(char *buffer, enum naviStatus_t *status,
	size_t *nmread)
{
	*nmread = 1;

	if (strncmp("A", buffer, 1) == 0)
	{
		*status = naviStatus_DataValid;
		return naviError_OK;
	}
	else if (strncmp("V", buffer, 1) == 0)
	{
		*status = naviStatus_DataInvalid;
		return naviError_OK;
	}
	else
	{
		*nmread = 0;
		*status = naviStatus_Undefined;
		return naviError_NullField;
	}
}

// Parses mode indicator
static enum naviError_t IecParse_ModeIndicator(char *buffer, enum naviModeIndicator_t *mi,
	size_t *nmread)
{
	*nmread = 1;

	if (strncmp("A", buffer, 1) == 0)
	{
		*mi = naviModeIndicator_Autonomous;
		return naviError_OK;
	}
	else if (strncmp("D", buffer, 1) == 0)
	{
		*mi = naviModeIndicator_Differential;
		return naviError_OK;
	}
	else if (strncmp("E", buffer, 1) == 0)
	{
		*mi = naviModeIndicator_Estimated;
		return naviError_OK;
	}
	else if (strncmp("M", buffer, 1) == 0)
	{
		*mi = naviModeIndicator_ManualInput;
		return naviError_OK;
	}
	else if (strncmp("S", buffer, 1) == 0)
	{
		*mi = naviModeIndicator_Simulator;
		return naviError_OK;
	}
	else if (strncmp("N", buffer, 1) == 0)
	{
		*mi = naviModeIndicator_DataNotValid;
		return naviError_OK;
	}
	else
	{
		*nmread = 0;
		*mi = naviModeIndicator_Undefined;
		return naviError_NullField;
	}
}

// Parses mode indicator array
static enum naviError_t IecParse_ModeIndicatorArray(char *buffer,
	enum naviModeIndicator_t mi[], size_t *nmread)
{
	size_t idx = 0;

	while (buffer[idx] != ',')
	{
		if (idx < 2)
		{
			if (strncmp("A", buffer + idx, 1) == 0)
			{
				mi[idx] = naviModeIndicator_Autonomous;
			}
			else if (strncmp("D", buffer + idx, 1) == 0)
			{
				mi[idx] = naviModeIndicator_Differential;
			}
			else if (strncmp("E", buffer + idx, 1) == 0)
			{
				mi[idx] = naviModeIndicator_Estimated;
			}
			else if (strncmp("M", buffer + idx, 1) == 0)
			{
				mi[idx] = naviModeIndicator_ManualInput;
			}
			else if (strncmp("S", buffer + idx, 1) == 0)
			{
				mi[idx] = naviModeIndicator_Simulator;
			}
			else if (strncmp("N", buffer + idx, 1) == 0)
			{
				mi[idx] = naviModeIndicator_DataNotValid;
			}
			else if (strncmp("P", buffer + idx, 1) == 0)
			{
				mi[idx] = naviModeIndicator_Precise;
			}
			else if (strncmp("R", buffer + idx, 1) == 0)
			{
				mi[idx] = naviModeIndicator_RTKinematic;
			}
			else if (strncmp("F", buffer + idx, 1) == 0)
			{
				mi[idx] = naviModeIndicator_FloatRTK;
			}
			else
			{
				mi[idx] = naviModeIndicator_Undefined;
			}
		}
		idx += 1;
	}

	*nmread = idx;
	return idx == 0 ? naviError_InvalidMessage : naviError_OK;
}

// Parses integer value
static enum naviError_t IecParse_Integer(char *buffer, int *value, size_t *nmread)
{
	char *endptr = NULL;
	double tmp;

	errno = 0;
	tmp = strtod(buffer, &endptr);
	*value = (int)round(tmp);
	*nmread = endptr - buffer;
	if (errno != 0)
	{
		return naviError_MsgNotSupported;
	}
	else if (*nmread == 0)
	{
		return naviError_NullField;
	}
	else
	{
		return naviError_OK;
	}
}

// Parses date
static enum naviError_t IecParse_Date(char *buffer, struct naviDate_t *date,
	size_t *nmread)
{
	size_t idx;

	for (idx = 0; ; idx++)
	{
		if (isdigit(buffer[idx]))
		{
			if (idx == 0)
			{
				date->day = buffer[idx] - '0';
			}
			else if (idx == 1)
			{
				date->day = date->day * 10 + (buffer[idx] - '0');
			}
			else if (idx == 2)
			{
				date->month = buffer[idx] - '0';
			}
			else if (idx == 3)
			{
				date->month = date->month * 10 + (buffer[idx] - '0');
			}
			else if (idx == 4)
			{
				date->year = buffer[idx] - '0';
			}
			else if (idx == 5)
			{
				date->year = date->year * 10 + (buffer[idx] - '0');
			}
			else if (idx == 6)
			{
				date->year = date->year * 10 + (buffer[idx] - '0');
			}
			else
			{
				date->year = date->year * 10 + (buffer[idx] - '0');
			}
		}
		else if (buffer[idx] == '.')
		{
			continue;
		}
		else if ((buffer[idx] == ',') || (buffer[idx] == '*'))
		{
			break;
		}
		else
		{
			*nmread = idx;
			return naviError_InvalidMessage;
		}
	}

	*nmread = idx;

	if (idx == 0)
	{
		return naviError_NullField;
	}
	else if (idx < 6)
	{
		return naviError_InvalidMessage;
	}
	else
	{
		return naviError_OK;
	}
}

//
// Finite-state machine for parsing local time zone int the form of:
// {[+|-]dd,dd*|,*}
#define PARSE_LOCALZONE_INITIAL		0
#define PARSE_LOCALZONE_SIGN		1
#define PARSE_LOCALZONE_HOURS		2
#define PARSE_LOCALZONE_MINUTES		3
#define PARSE_LOCALZONE_FINAL		4

// Parses local zone (sxx,xx)
static enum naviError_t IecParse_LocalZone(char *buffer, int *offset,
	size_t *nmread)
{
	size_t idx = 0;
	int state = PARSE_LOCALZONE_INITIAL, sign = 1, hours = 0, minutes = 0;

	do
	{
		switch (buffer[idx])
		{
		case '+':
			switch (state)
			{
			case PARSE_LOCALZONE_INITIAL:
				state = PARSE_LOCALZONE_SIGN;
				sign = 1;
				break;
			default:
				return naviError_InvalidMessage;
			}
			break;
		case '-':
			switch (state)
			{
			case PARSE_LOCALZONE_INITIAL:
				state = PARSE_LOCALZONE_SIGN;
				sign = -1;
				break;
			default:
				return naviError_InvalidMessage;
			}
			break;
		case ',':
			switch (state)
			{
			case PARSE_LOCALZONE_INITIAL:
			case PARSE_LOCALZONE_HOURS:
				state = PARSE_LOCALZONE_MINUTES;
				break;
			case PARSE_LOCALZONE_MINUTES:
				state = PARSE_LOCALZONE_FINAL;
				break;
			default:
				return naviError_InvalidMessage;
			}
			break;
		case '*':
			switch (state)
			{
			case PARSE_LOCALZONE_MINUTES:
				state = PARSE_LOCALZONE_FINAL;
				break;
			default:
				return naviError_InvalidMessage;
			}
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			switch (state)
			{
			case PARSE_LOCALZONE_INITIAL:
			case PARSE_LOCALZONE_SIGN:
				state = PARSE_LOCALZONE_HOURS;
			// Fall through
			case PARSE_LOCALZONE_HOURS:
				hours = hours * 10 + (buffer[idx] - '0');
				break;
			case PARSE_LOCALZONE_MINUTES:
				minutes = minutes * 10 + (buffer[idx] - '0');
				break;
			default:
				return naviError_InvalidMessage;
			}
			break;
		default:
			return naviError_InvalidMessage;
		}

		idx++;
	} while (state != PARSE_LOCALZONE_FINAL);

	*offset = sign * (hours * 60 + minutes);

	*nmread = idx;
	return naviError_OK;
}

