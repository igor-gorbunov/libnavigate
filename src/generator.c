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

//
// Meters per second to knots (nautical mile per hour)
#define MPS_TO_KNOTS		1.94384449

//
// Meters per second to km/h convertion coefficient
#define MPS_TO_KMH			3.600

// DTM - Datum reference
// Local geodetic datum and datum offsets from a reference datum. This sentence
// is used to define the datum to which a position location, and geographic
// locations in subsequent sentences, are referenced. Lattitude, longitude and
// altitude offsets from the reference datum, and the selection of the reference
// datum, are also provided.
// $--DTM,ccc,a,x.x,a,x.x,a,x.x,ccc*hh<cr><lf>
static int IecCompose_DTM(const struct dtm_t *msg, char *buffer, size_t maxsize);

// GLL - Geographic position - latitude/longitude
// Latitude and longitude of vessel position, time of position fix and status.
// $--GLL,llll.ll,a,yyyyy.yy,a,hhmmss.ss,A,a*hh<cr><lf>
static int IecCompose_GLL(const struct gll_t *msg, char *buffer, size_t maxsize);

// GNS - GNSS fix data
// Fix data for single or combined sattelite navigation systems (GNSS).
// $--GNS,hhmmss.ss,llll.ll,a,yyyyy.yy,a,c--c,xx,x.x,x.x,x.x,x.x,x.x*hh<cr><lf>
static int IecCompose_GNS(const struct gns_t *msg, char *buffer, size_t maxsize);

// RMC - Recommended minimum specific GNSS data
// Time, date, position, course and speed data provided by a GNSS navigation
// receiver. This sentence is transmitted at intervals not exceeding 2 s and is
// always accompanied by RMB when a destination waypoint is active. RMC and RMB
// are the recommended minimum data to be provided by a GNSS receiver. All data
// fields must be provided, null fields used only when data is temporarily
// unavailable.
// $--RMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxxxx,x.x,a,a*hh<cr><lf>
static int IecCompose_RMC(const struct rmc_t *msg, char *buffer, size_t maxsize);

// VTG - Course over ground and ground speed
// The actual course and speed relative to the ground.
// $--VTG,x.x,T,x.x,M,x.x,N,x.x,K,a*hh<cr><lf>
static int IecCompose_VTG(const struct vtg_t *msg, char *buffer, size_t maxsize);

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
		break;
	case _GLL:
		return IecCompose_GLL((const struct gll_t *)msg, buffer, maxsize);
	case _GNS:
		return IecCompose_GNS((const struct gns_t *)msg, buffer, maxsize);
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
		break;
	case _RMC:
		return IecCompose_RMC((const struct rmc_t *)msg, buffer, maxsize);
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
		break;
	case _VTG:
		return IecCompose_VTG((const struct vtg_t *)msg, buffer, maxsize);
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
static int IecPrint_ModeIndicatorArray(const enum naviModeIndicator_t mi[],
	char *buffer, size_t maxsize, int notnull);

//
// Removes trailing zeroes of a floating point zeroes
static int RemoveTrailingZeroes(char *buffer, size_t maxsize);

//
// DTM
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

//
// GLL
static int IecCompose_GLL(const struct gll_t *msg, char *buffer, size_t maxsize)
{
	int result;
	char iecmsg[IEC_MESSAGE_MAXSIZE + 1], talkerid[3], latitude[32], latsign[2],
		longitude[32], lonsign[2], utc[32], status[2], mi[2], cs[3];

	result = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	result += IecPrint_Latitude(msg->latitude.offset, latitude, sizeof(latitude),
		msg->vfields & GLL_VALID_LATITUDE);
	result += IecPrint_OffsetSign(msg->latitude.offsign, latsign, sizeof(latsign),
		msg->vfields & GLL_VALID_LATITUDE);
	result += IecPrint_Longitude(msg->longitude.offset, longitude,
		sizeof(longitude), msg->vfields & GLL_VALID_LONGITUDE);
	result += IecPrint_OffsetSign(msg->longitude.offsign, lonsign,
		sizeof(lonsign), msg->vfields & GLL_VALID_LONGITUDE);
	result += IecPrint_Utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & GLL_VALID_UTC);
	result += IecPrint_Status(msg->status, status, sizeof(status));
	result += IecPrint_ModeIndicator(msg->mi, mi, sizeof(mi));

	result += 16;
	if (result > IEC_MESSAGE_MAXSIZE)
	{
		printf("IecCompose_GLL : Message length exceeds maximum allowed.\n");
		return -EMSGSIZE;
	}

	result = snprintf(iecmsg, sizeof(iecmsg), "$%sGLL,%s,%s,%s,%s,%s,%s,%s*%s\r\n",
		talkerid, latitude, latsign, longitude, lonsign, utc, status, mi, "%s");
	IecPrint_Checksum(iecmsg, result, cs);

	return snprintf(buffer, maxsize, iecmsg, cs);
}

//
// GNS
static int IecCompose_GNS(const struct gns_t *msg, char *buffer, size_t maxsize)
{
	int result;

	char iecmsg[IEC_MESSAGE_MAXSIZE + 1], talkerid[3], utc[32], latitude[32],
		latsign[2], longitude[32], lonsign[2], mi[3], totalsats[3], hdop[32],
		antalt[32], geoidsep[32], ddage[32], drsid[32], cs[3];

	result = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	result += IecPrint_Utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & GNS_VALID_UTC);
	result += IecPrint_Latitude(msg->latitude.offset, latitude, sizeof(latitude),
		msg->vfields & GNS_VALID_LATITUDE);
	result += IecPrint_OffsetSign(msg->latitude.offsign, latsign, sizeof(latsign),
		msg->vfields & GNS_VALID_LATITUDE);
	result += IecPrint_Longitude(msg->longitude.offset, longitude, sizeof(longitude),
		msg->vfields & GNS_VALID_LONGITUDE);
	result += IecPrint_OffsetSign(msg->longitude.offsign, lonsign, sizeof(lonsign),
		msg->vfields & GNS_VALID_LONGITUDE);
	result += IecPrint_ModeIndicatorArray(msg->mi, mi, sizeof(mi),
		msg->vfields & GNS_VALID_MODEINDICATOR);
	result += snprintf(totalsats, sizeof(totalsats),
		(msg->vfields & GNS_VALID_TOTALNMOFSATELLITES) ? "%02u" : "",
		msg->totalsats);
	result += IecPrint_Double(msg->hdop, hdop, sizeof(hdop),
		msg->vfields & GNS_VALID_HDOP);
	result += IecPrint_Double(msg->antaltitude, antalt, sizeof(antalt),
		msg->vfields & GNS_VALID_ANTENNAALTITUDE);
	result += IecPrint_Double(msg->geoidalsep, geoidsep, sizeof(geoidsep),
		msg->vfields & GNS_VALID_GEOIDALSEP);
	result += IecPrint_Double(msg->diffage, ddage, sizeof(ddage),
		msg->vfields & GNS_VALID_AGEOFDIFFDATA);
	result += snprintf(drsid, sizeof(drsid),
		(msg->vfields & GNS_VALID_DIFFREFSTATIONID) ? "%i" : "", msg->id);

	result += 23;
	if (result > IEC_MESSAGE_MAXSIZE)
	{
		printf("IecCompose_GNS : Message length exceeds maximum allowed.\n");
		return -EMSGSIZE;
	}

	result = snprintf(iecmsg, sizeof(iecmsg),
		"$%sGNS,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s*%s\r\n", talkerid, utc,
		latitude, latsign, longitude, lonsign, mi, totalsats, hdop, antalt,
		geoidsep, ddage, drsid, "%s");
	IecPrint_Checksum(iecmsg, result, cs);

	return snprintf(buffer, maxsize, iecmsg, cs);
}

//
// RMC
static int IecCompose_RMC(const struct rmc_t *msg, char *buffer, size_t maxsize)
{
	size_t result;

	char iecmsg[IEC_MESSAGE_MAXSIZE + 1], talkerid[3], utc[32], status[2],
		latitude[32], latsign[2], longitude[32], lonsign[2], snots[32],
		ctrue[32], day[3], month[3], year[3], magnetic[32], magsign[2],
		mi[2], cs[3];

	result = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	result += IecPrint_Utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & RMC_VALID_UTC);
	result += IecPrint_Status(msg->status, status, sizeof(status));
	result += IecPrint_Latitude(msg->latitude.offset, latitude, sizeof(latitude),
		msg->vfields & RMC_VALID_LATITUDE);
	result += IecPrint_OffsetSign(msg->latitude.offsign, latsign, sizeof(latsign),
		msg->vfields & RMC_VALID_LATITUDE);
	result += IecPrint_Longitude(msg->longitude.offset, longitude, sizeof(longitude),
		msg->vfields & RMC_VALID_LONGITUDE);
	result += IecPrint_OffsetSign(msg->longitude.offsign, lonsign, sizeof(lonsign),
		msg->vfields & RMC_VALID_LONGITUDE);
	result += IecPrint_Double(msg->speed * MPS_TO_KNOTS, snots, sizeof(snots),
		msg->vfields & RMC_VALID_SPEED);
	result += IecPrint_Double(msg->courseTrue, ctrue, sizeof(ctrue),
		msg->vfields & RMC_VALID_COURSETRUE);
	result += snprintf(day, sizeof(day),
		(msg->vfields & RMC_VALID_DATE) ? "%02u" : "", msg->day);
	result += snprintf(month, sizeof(month),
		(msg->vfields & RMC_VALID_DATE) ? "%02u" : "", msg->month);
	result += snprintf(year, sizeof(year),
		(msg->vfields & RMC_VALID_DATE) ? "%02u" : "", msg->year % 100);
	result += IecPrint_Double(msg->magnetic.offset, magnetic, sizeof(magnetic),
		(msg->vfields & RMC_VALID_MAGNVARIATION));
	result += IecPrint_OffsetSign(msg->magnetic.offsign, magsign, sizeof(magsign),
		(msg->vfields & RMC_VALID_MAGNVARIATION));
	result += IecPrint_ModeIndicator(msg->mi, mi, sizeof(mi));

	result += 17;
	if (result > IEC_MESSAGE_MAXSIZE)
	{
		printf("IecCompose_RMC : Message length exceeds maximum allowed.\n");
		return -EMSGSIZE;
	}

	result = snprintf(iecmsg, sizeof(iecmsg),
		"$%sRMC,%s,%s,%s,%s,%s,%s,%s,%s,%s%s%s,%s,%s,%s*%s\r\n", talkerid, utc,
		status, latitude, latsign, longitude, lonsign, snots, ctrue, day, month,
		year, magnetic, magsign, mi, "%s");
	IecPrint_Checksum(iecmsg, result, cs);

	return snprintf(buffer, maxsize, iecmsg, cs);
}

//
// VTG
static int IecCompose_VTG(const struct vtg_t *msg, char *buffer, size_t maxsize)
{
	int result;

	char iecmsg[IEC_MESSAGE_MAXSIZE + 1], talkerid[3], ctrue[32], courseT[2],
		cmagn[32], courseM[2], snots[32], speedN[4], skmph[32], speedK[2],
		mi[2], cs[3];

	result = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	result += IecPrint_Double(msg->courseTrue, ctrue, sizeof(ctrue),
		msg->vfields & VTG_VALID_COURSETRUE);
	result += snprintf(courseT, sizeof(courseT),
		(msg->vfields & VTG_VALID_COURSETRUE) ? "T" : "");
	result += IecPrint_Double(msg->courseMagn, cmagn, sizeof(cmagn),
		msg->vfields & VTG_VALID_COURSEMAGN);
	result += snprintf(courseM, sizeof(courseM),
		(msg->vfields & VTG_VALID_COURSEMAGN) ? "M" : "");
	result += IecPrint_Double(msg->speed * MPS_TO_KNOTS, snots, sizeof(snots),
		msg->vfields & VTG_VALID_SPEED);
	result += snprintf(speedN, sizeof(speedN),
		(msg->vfields & VTG_VALID_SPEED) ? "N" : "");
	result += IecPrint_Double(msg->speed * MPS_TO_KMH, skmph, sizeof(skmph),
		msg->vfields & VTG_VALID_SPEED);
	result += snprintf(speedK, sizeof(speedK),
		(msg->vfields & VTG_VALID_SPEED) ? "K" : "");
	result += IecPrint_ModeIndicator(msg->mi, mi, sizeof(mi));

	result += 18;
	if (result > IEC_MESSAGE_MAXSIZE)
	{
		printf("IecCompose_VTG : Message length exceeds maximum allowed.\n");
		return -EMSGSIZE;
	}

	result = snprintf(iecmsg, sizeof(iecmsg),
		"$%sVTG,%s,%s,%s,%s,%s,%s,%s,%s,%s*%s\r\n", talkerid, ctrue, courseT,
		cmagn, courseM, snots, speedN, skmph, speedK, mi, "%s");
	IecPrint_Checksum(iecmsg, result, cs);

	return snprintf(buffer, maxsize, iecmsg, cs);
}

//
// ZDA
static int IecCompose_ZDA(const struct zda_t *msg, char *buffer, size_t maxsize)
{
	int result;

	char iecmsg[IEC_MESSAGE_MAXSIZE + 1], talkerid[3], utc[32], day[3],
		month[3], year[5], lzhours[4], lzmins[3], cs[3];

	result = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	result += IecPrint_Utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & ZDA_VALID_UTC);
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

		value = value * 100000000.0;
		value = round(value);
		value = value / 100000000.0;

		result = snprintf(buffer, maxsize, "%.8f", value);
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

static int IecPrint_Latitude(double value, char *buffer,
	size_t maxsize, int notnull)
{
	if (notnull)
	{
		int result;
		double degrees;

		value = value * 100000000.;
		value = round(value);
		value = value / 100000000.;

		value = modf(value, &degrees);
		degrees = degrees * 100.;
		value = value * 60.;
		value = value + degrees;

		result = snprintf(buffer, maxsize, "%013.8f", value);
		return RemoveTrailingZeroes(buffer, result);
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

static int IecPrint_Longitude(double value, char *buffer,
	size_t maxsize, int notnull)
{
	if (notnull)
	{
		int result;
		double degrees;

		value = value * 100000000.;
		value = round(value);
		value = value / 100000000.;

		value = modf(value, &degrees);
		degrees = degrees * 100.;
		value = value * 60.;
		value = value + degrees;

		result = snprintf(buffer, maxsize, "%014.8f", value);
		return RemoveTrailingZeroes(buffer, result);
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

static int IecPrint_Status(enum naviStatus_t status, char *buffer,
	size_t maxsize)
{
	switch (status)
	{
	case _DataValid:
		return snprintf(buffer, maxsize, "A");
	case _DataInvalid:
		return snprintf(buffer, maxsize, "V");
	}

	return -EPROTOTYPE;
}

static int IecPrint_ModeIndicator(enum naviModeIndicator_t mi, char *buffer,
	size_t maxsize)
{
	switch (mi)
	{
	case _Autonomous:
		return snprintf(buffer, maxsize, "A");
	case _Differential:
		return snprintf(buffer, maxsize, "D");
	case _Estimated:
		return snprintf(buffer, maxsize, "E");
	case _ManualInput:
		return snprintf(buffer, maxsize, "M");
	case _Simulator:
		return snprintf(buffer, maxsize, "S");
	case _DataNotValid:
		return snprintf(buffer, maxsize, "N");
	}

	return -EPROTOTYPE;
}

static int IecPrint_ModeIndicatorArray(const enum naviModeIndicator_t mi[],
	char *buffer, size_t maxsize, int notnull)
{
	int result = 0;

	(void)strncpy(buffer, "", maxsize);

	if (notnull)
	{
		int i;
		for (i = 0; i < 2; i++, result++)
		{
			switch (mi[i])
			{
			case _Autonomous:
				(void)strncat(buffer, "A", maxsize);
				break;
			case _Differential:
				(void)strncat(buffer, "D", maxsize);
				break;
			case _Estimated:
				(void)strncat(buffer, "E", maxsize);
				break;
			case _ManualInput:
				(void)strncat(buffer, "M", maxsize);
				break;
			case _Simulator:
				(void)strncat(buffer, "S", maxsize);
				break;
			case _DataNotValid:
				(void)strncat(buffer, "N", maxsize);
				break;
			case _Precise:
				(void)strncat(buffer, "P", maxsize);
				break;
			case _RTKinematic:
				(void)strncat(buffer, "R", maxsize);
				break;
			case _FloatRTK:
				(void)strncat(buffer, "F", maxsize);
				break;
			default:
				return -EPROTOTYPE;
			}
		}
	}

	return result;
}

