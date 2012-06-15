/*
 * generator.c - IEC messages generation utilities
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

#include <iecgenerator.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// DTM - Datum reference
// Local geodetic datum and datum offsets from a reference datum. This sentence
// is used to define the datum to which a position location, and geographic
// locations in subsequent sentences, are referenced. Lattitude, longitude and
// altitude offsets from the reference datum, and the selection of the reference
// datum, are also provided.
// $--DTM,ccc,a,x.x,a,x.x,a,x.x,ccc*hh<cr><lf>
static int IecCompose_DTM(const struct dtm_t *msg, char *buffer, size_t maxsize);

//
// ZDA - Time and date
// UTC, day, month, year and local time zone.
// $--ZDA,hhmmss.ss,xx,xx,xxxx,xx,xx*hh<cr><lf>
static int IecCompose_ZDA(const struct zda_t *msg, char *buffer, size_t maxsize);

int IecComposeMessage(enum naviSentence_t msgtype, void *msg,
	char *buffer, size_t maxsize)
{
	switch (msgtype)
	{
	case _AAM:
	case _ACK:
	case _ALM:
	case _ALR:
	case _APB:
	case _BEC:
	case _BOD:
	case _BWC:
	case _BWR:
	case _BWW:
	case _DBT:
	case _DCN:
	case _DPT:
	case _DSC:
	case _DSE:
	case _DSI:
	case _DSR:
	case _DTM:
		return IecCompose_DTM((const struct dtm_t *)msg, buffer, maxsize);
	case _FSI:
	case _GBS:
	case _GGA:
	case _GLC:
	case _GLL:
	case _GNS:
	case _GRS:
	case _GSA:
	case _GST:
	case _GSV:
	case _HDG:
	case _HDT:
	case _HMR:
	case _HMS:
	case _HSC:
	case _HTC:
	case _HTD:
	case _LCD:
	case _MLA:
	case _MSK:
	case _MSS:
	case _MTW:
	case _MWD:
	case _MWV:
	case _OSD:
	case _RMA:
	case _RMB:
	case _RMC:
	case _ROT:
	case _RPM:
	case _RSA:
	case _RSD:
	case _RTE:
	case _SFI:
	case _STN:
	case _TLB:
	case _TLL:
	case _TTM:
	case _TXT:
	case _VBW:
	case _VDR:
	case _VHW:
	case _VLW:
	case _VPW:
	case _VTG:
	case _WCV:
	case _WNC:
	case _WPL:
	case _XDR:
	case _XTE:
	case _XTR:
		break;
	case _ZDA:
		return IecCompose_ZDA((const struct zda_t *)msg, buffer, maxsize);
	case _ZDL:
	case _ZFO:
	case _ZTG:
		break;
	}

	return -EAFNOSUPPORT;
}

//
// Prints talker identifier
static int IecPrint_TalkerId(enum naviTalkerId_t tid, char *buffer,
	size_t maxsize);

//
// Prints datum
static int IecPrint_Datum(enum naviDatum_t datum, char *buffer,
	size_t maxsize, int notnull);

//
// Prints local datum subdivision
static int IecPrint_DatumSubdivision(enum naviLocalDatumSub_t lds,
	char *buffer, size_t maxsize, int notnull);

//
// Prints a floating point value
static int IecPrint_Double(double value, char *buffer,
	size_t maxsize, int notnull);

//
// Prints offset sign
static int IecPrint_OffsetSign(enum naviOffsetSign_t sign, char *buffer,
	size_t maxsize, int notnull);

//
// Prints checksum of the generated message
static int IecPrint_Checksum(char *msg, size_t maxsize, char *cs);

//
// Prints latitude (llll.ll)
static int IecPrint_Latitude(double value, char *buffer,
	size_t maxsize, int notnull);

//
// Prints longitude (yyyyy.yy)
static int IecPrint_Longitude(double value, char *buffer,
	size_t maxsize, int notnull);

//
// Prints UTC
static int IecPrint_Utc(const struct naviUtc_t *utc, char *buffer,
	size_t maxsize, int notnull);

//
// Prints message status
static int IecPrint_Status(enum naviStatus_t status, char *buffer,
	size_t maxsize);

//
// Prints mode indicator
static int IecPrint_ModeIndicator(enum naviModeIndicator_t mi, char *buffer,
	size_t maxsize);

//
// Prints array of mode indicators
static int IecPrint_ModeIndicatorArray(enum naviModeIndicator_t mi[],
	char *buffer, size_t maxsize, int notnull);

//
// Removes trailing zeroes of a floating point zeroes
static int RemoveTrailingZeroes(char *buffer, size_t maxsize);

static int IecCompose_DTM(const struct dtm_t *msg, char *buffer, size_t maxsize)
{
	int result;

	char iecmsg[IEC_MESSAGE_MAXSIZE + 1], talkerid[3], locdatum[4],
		locdatumsub[2], latofs[32], latsign[2], lonofs[32], lonsign[2],
		altofs[32], refdatum[4], cs[3];

	result = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	result += IecPrint_Datum(msg->ld, locdatum, sizeof(locdatum),
		msg->vfields & DTM_VALID_LOCALDATUM);
	result += IecPrint_DatumSubdivision(msg->lds, locdatumsub,
		sizeof(locdatumsub), msg->vfields & DTM_VALID_LOCALDATUMSUB);
	result += IecPrint_Double(msg->latofs.offset, latofs, sizeof(latofs),
		msg->vfields & DTM_VALID_LATOFFSET);
	result += IecPrint_OffsetSign(msg->latofs.offsign, latsign, sizeof(latsign),
		msg->vfields & DTM_VALID_LATOFFSET);
	result += IecPrint_Double(msg->lonofs.offset, lonofs, sizeof(lonofs),
		msg->vfields & DTM_VALID_LONOFFSET);
	result += IecPrint_OffsetSign(msg->lonofs.offsign, lonsign, sizeof(lonsign),
		msg->vfields & DTM_VALID_LONOFFSET);
	result += IecPrint_Double(msg->altoffset, altofs, sizeof(altofs),
		msg->vfields & DTM_VALID_ALTITUDEOFFSET);
	result += IecPrint_Datum(msg->rd, refdatum, sizeof(refdatum),
		msg->vfields & DTM_VALID_REFERENCEDATUM);

	result += 17;
	if (result > IEC_MESSAGE_MAXSIZE)
	{
		printf("IecCompose_DTM : Message length exceeds maximum allowed.\n");
		return -EMSGSIZE;
	}

	result = snprintf(iecmsg, sizeof(iecmsg),
		"$%sDTM,%s,%s,%s,%s,%s,%s,%s,%s*%s\r\n", talkerid, locdatum, locdatumsub,
		latofs, latsign, lonofs, lonsign, altofs, refdatum, "%s");
	IecPrint_Checksum(iecmsg, result, cs);

	return snprintf(buffer, maxsize, iecmsg, cs);
}

static int IecCompose_ZDA(const struct zda_t *msg, char *buffer, size_t maxsize)
{
	int result;

	char iecmsg[IEC_MESSAGE_MAXSIZE + 1], talkerid[3], utc[32], day[3],
		month[3], year[5], lzhours[4], lzmins[3], cs[3];

	result = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	result += IecPrint_Utc((const struct naviUtc_t *)&msg->utc, utc,
		sizeof(utc), msg->vfields & ZDA_VALID_UTC);
	result += snprintf(day, sizeof(day),
		(msg->vfields & ZDA_VALID_DAY) ? "%02u" : "", msg->day);
	result += snprintf(month, sizeof(month),
		(msg->vfields & ZDA_VALID_MONTH) ? "%02u" : "", msg->month);
	result += snprintf(year, sizeof(year),
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

		result += snprintf(lzhours, sizeof(lzhours), "%s%02d", sign, lz / 60);
		result += snprintf(lzmins, sizeof(lzmins), "%02u", lz % 60);
	}

	result += 15;
	if (result > IEC_MESSAGE_MAXSIZE)
	{
		printf("IecCompose_ZDA : Message length exceeds maximum allowed.\n");
		return -EMSGSIZE;
	}

	result = snprintf(iecmsg, sizeof(iecmsg), "$%sZDA,%s,%s,%s,%s,%s,%s*%s\r\n",
		talkerid, utc, day, month, year, lzhours, lzmins, "%s");
	IecPrint_Checksum(iecmsg, result, cs);

	return snprintf(buffer, maxsize, iecmsg, cs);
}

static int IecPrint_TalkerId(enum naviTalkerId_t tid, char *buffer,
	size_t maxsize)
{
	switch (tid)
	{
	case _AG:
		return snprintf(buffer, maxsize, "AG");
	case _AP:
		return snprintf(buffer, maxsize, "AP");
	case _AI:
		return snprintf(buffer, maxsize, "AI");
	case _CD:
		return snprintf(buffer, maxsize, "CD");
	case _CR:
		return snprintf(buffer, maxsize, "CR");
	case _CS:
		return snprintf(buffer, maxsize, "CS");
	case _CT:
		return snprintf(buffer, maxsize, "CT");
	case _CV:
		return snprintf(buffer, maxsize, "CV");
	case _CX:
		return snprintf(buffer, maxsize, "CX");
	case _DE:
		return snprintf(buffer, maxsize, "DE");
	case _DF:
		return snprintf(buffer, maxsize, "DF");
	case _EC:
		return snprintf(buffer, maxsize, "EC");
	case _EI:
		return snprintf(buffer, maxsize, "EI");
	case _EP:
		return snprintf(buffer, maxsize, "EP");
	case _ER:
		return snprintf(buffer, maxsize, "ER");
	case _GA:
		return snprintf(buffer, maxsize, "GA");
	case _GP:
		return snprintf(buffer, maxsize, "GP");
	case _GL:
		return snprintf(buffer, maxsize, "GL");
	case _GN:
		return snprintf(buffer, maxsize, "GN");
	case _GW:
		return snprintf(buffer, maxsize, "GW");
	case _HC:
		return snprintf(buffer, maxsize, "HC");
	case _HE:
		return snprintf(buffer, maxsize, "HE");
	case _HN:
		return snprintf(buffer, maxsize, "HN");
	case _II:
		return snprintf(buffer, maxsize, "II");
	case _IN:
		return snprintf(buffer, maxsize, "IN");
	case _LC:
		return snprintf(buffer, maxsize, "LC");
	case _P:
		return snprintf(buffer, maxsize, "P");
	case _RA:
		return snprintf(buffer, maxsize, "RA");
	case _SD:
		return snprintf(buffer, maxsize, "SD");
	case _SN:
		return snprintf(buffer, maxsize, "SN");
	case _SS:
		return snprintf(buffer, maxsize, "SS");
	case _TI:
		return snprintf(buffer, maxsize, "TI");
	case _VD:
		return snprintf(buffer, maxsize, "VD");
	case _VM:
		return snprintf(buffer, maxsize, "VM");
	case _VW:
		return snprintf(buffer, maxsize, "VW");
	case _VR:
		return snprintf(buffer, maxsize, "VR");
	case _YX:
		return snprintf(buffer, maxsize, "YX");
	case _ZA:
		return snprintf(buffer, maxsize, "ZA");
	case _ZC:
		return snprintf(buffer, maxsize, "ZC");
	case _ZQ:
		return snprintf(buffer, maxsize, "ZQ");
	case _ZV:
		return snprintf(buffer, maxsize, "ZV");
	case _WI:
		return snprintf(buffer, maxsize, "WI");
	}

	return -EPROTOTYPE;
}

static int IecPrint_Utc(const struct naviUtc_t *utc, char *buffer,
	size_t maxsize, int notnull)
{
	if (notnull)
	{
		int result = snprintf(buffer, maxsize, "%02u%02u%02u.%03u",
			utc->hour % 24, utc->min % 60, utc->sec % 60, utc->msec % 1000);
		return RemoveTrailingZeroes(buffer, result);
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

static int IecPrint_Checksum(char *msg, size_t maxsize, char *cs)
{
	if ((msg == NULL) || (maxsize <= 0) || (cs == NULL))
	{
		return -EINVAL;
	}

	unsigned i, ucs = 0;

	// Skip up to beginning of the meassage
	for (i = 0; msg[i] != '$' && i < maxsize; i++) { }

	if (i >= maxsize)
	{
		return -EPROTO;
	}
	for (i += 1; msg[i] != '*' && i < maxsize; i++)
	{
		ucs = ucs ^ msg[i];
	}
	if (i >= maxsize)
	{
		return -EPROTO;
	}

	return snprintf(cs, 3, "%1X%1X", (ucs & 0xf0) >> 4, ucs & 0x0f);
}

static int RemoveTrailingZeroes(char *buffer, size_t maxsize)
{
	int i;

	for (i = maxsize - 1; ; i--)
	{
		if (buffer[i] == '0')
		{
			buffer[i] = '\0';
			maxsize--;
		}
		else if (buffer[i] == '.')
		{
			buffer[i] = '\0';
			maxsize--;
			break;
		}
		else
		{
			break;
		}
	}

	return maxsize;
}

static int IecPrint_Datum(enum naviDatum_t datum, char *buffer,
	size_t maxsize, int notnull)
{
	if (notnull)
	{
		switch (datum)
		{
		case _WGS84:
			return snprintf(buffer, maxsize, "W84");
		case _WGS72:
			return snprintf(buffer, maxsize, "W72");
		case _SGS85:
			return snprintf(buffer, maxsize, "S85");
		case _PE90:
			return snprintf(buffer, maxsize, "P90");
		case _UserDefined:
			return snprintf(buffer, maxsize, "999");
		}

		return -EPROTOTYPE;
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

static int IecPrint_DatumSubdivision(enum naviLocalDatumSub_t lds,
	char *buffer, size_t maxsize, int notnull)
{
	if (notnull)
	{
		switch (lds)
		{
		default:
			return -EPROTOTYPE;
		}
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

static int IecPrint_Double(double value, char *buffer, size_t maxsize, int notnull)
{
	if (notnull)
	{
		int result;

		value = value * 10000000.0;
		value = round(value);
		value = value / 10000000.0;

		result = snprintf(buffer, maxsize, "%.7f", value);
		return RemoveTrailingZeroes(buffer, result);
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

static int IecPrint_OffsetSign(enum naviOffsetSign_t sign, char *buffer,
	size_t maxsize, int notnull)
{
	if (notnull)
	{
		switch (sign)
		{
		case _North:
			return snprintf(buffer, maxsize, "N");
		case _South:
			return snprintf(buffer, maxsize, "S");
		case _East:
			return snprintf(buffer, maxsize, "E");
		case _West:
			return snprintf(buffer, maxsize, "W");
		}

		return -EPROTOTYPE;
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

