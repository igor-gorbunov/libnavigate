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

#include <navigate.h>
#include "common.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#ifndef NO_GENERATOR

#include "alm.h"
#include "dtm.h"
#include "gbs.h"
#include "gga.h"
#include "gll.h"
#include "gns.h"
#include "grs.h"
#include "gsa.h"
#include "gst.h"
#include "rmc.h"
#include "vtg.h"
#include "zda.h"

#endif // NO_GENERATOR

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

int navi_create_msg(int type, void *msg, char *buffer, int maxsize, int *nmwritten)
{

#ifndef NO_GENERATOR

	const char *tid = NULL, *sfmt = NULL;
	char msgbody[NAVI_SENTENCE_MAXSIZE + 1], csstr[3];

	int msglen = 0;

	assert(msg != NULL);
	assert(buffer != NULL);
	assert(nmwritten != NULL);

	switch (type)
	{
	case navi_AAM:
	case navi_ACK:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_ALM:
		return navi_create_alm((const struct alm_t *)msg, buffer, maxsize, nmwritten);
	case navi_ALR:
	case navi_APB:
	case navi_BEC:
	case navi_BOD:
	case navi_BWC:
	case navi_BWR:
	case navi_BWW:
	case navi_DBT:
	case navi_DCN:
	case navi_DPT:
	case navi_DSC:
	case navi_DSE:
	case navi_DSI:
	case navi_DSR:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_DTM:
		{
			const struct dtm_t *pdtm = (const struct dtm_t *)msg;
			tid = navi_talkerid_str(pdtm->tid);
			sfmt = navi_sentencefmt_str(navi_DTM);

			if (navi_create_dtm(pdtm, msgbody, sizeof(msgbody), &msglen) < 0)
				return navi_Error;
		}
		break;
	case navi_FSI:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_GBS:
		{
			const struct gbs_t *pgbs = (const struct gbs_t *)msg;
			tid = navi_talkerid_str(pgbs->tid);
			sfmt = navi_sentencefmt_str(navi_GBS);

			if (navi_create_gbs(pgbs, msgbody, sizeof(msgbody), &msglen) < 0)
				return navi_Error;
		}
		break;
	case navi_GGA:
		{
			const struct gga_t *pgga = (const struct gga_t *)msg;
			tid = navi_talkerid_str(pgga->tid);
			sfmt = navi_sentencefmt_str(navi_GGA);

			if (navi_create_gga(pgga, msgbody, sizeof(msgbody), &msglen) < 0)
				return navi_Error;
		}
		break;
	case navi_GLC:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_GLL:
		{
			const struct gll_t *pgll = (const struct gll_t *)msg;
			tid = navi_talkerid_str(pgll->tid);
			sfmt = navi_sentencefmt_str(navi_GLL);

			if (navi_create_gll(pgll, msgbody, sizeof(msgbody), &msglen) < 0)
				return navi_Error;
		}
		break;
	case navi_GNS:
		{
			const struct gns_t *pgns = (const struct gns_t *)msg;
			tid = navi_talkerid_str(pgns->tid);
			sfmt = navi_sentencefmt_str(navi_GNS);

			if (navi_create_gns(pgns, msgbody, sizeof(msgbody), &msglen) < 0)
				return navi_Error;
		}
		break;
	case navi_GRS:
		{
			const struct grs_t *pgrs = (const struct grs_t *)msg;
			tid = navi_talkerid_str(pgrs->tid);
			sfmt = navi_sentencefmt_str(navi_GRS);

			if (navi_create_grs(pgrs, msgbody, sizeof(msgbody), &msglen) < 0)
				return navi_Error;
		}
		break;
	case navi_GSA:
		{
			const struct gsa_t *pgsa = (const struct gsa_t *)msg;
			tid = navi_talkerid_str(pgsa->tid);
			sfmt = navi_sentencefmt_str(navi_GSA);

			if (navi_create_gsa(pgsa, msgbody, sizeof(msgbody), &msglen) < 0)
				return navi_Error;
		}
		break;
	case navi_GST:
		{
			const struct gst_t *pgst = (const struct gst_t *)msg;
			tid = navi_talkerid_str(pgst->tid);
			sfmt = navi_sentencefmt_str(navi_GST);

			if (navi_create_gst(pgst, msgbody, sizeof(msgbody), &msglen) < 0)
				return navi_Error;
		}
		break;
	case navi_GSV:
	case navi_HDG:
	case navi_HDT:
	case navi_HMR:
	case navi_HMS:
	case navi_HSC:
	case navi_HTC:
	case navi_HTD:
	case navi_LCD:
	case navi_MLA:
	case navi_MSK:
	case navi_MSS:
	case navi_MTW:
	case navi_MWD:
	case navi_MWV:
	case navi_OSD:
	case navi_RMA:
	case navi_RMB:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_RMC:
		{
			const struct rmc_t *prmc = (const struct rmc_t *)msg;
			tid = navi_talkerid_str(prmc->tid);
			sfmt = navi_sentencefmt_str(navi_RMC);

			if (navi_create_rmc(prmc, msgbody, sizeof(msgbody), &msglen) < 0)
				return navi_Error;
		}
		break;
	case navi_ROT:
	case navi_RPM:
	case navi_RSA:
	case navi_RSD:
	case navi_RTE:
	case navi_SFI:
	case navi_STN:
	case navi_TLB:
	case navi_TLL:
	case navi_TTM:
	case navi_TXT:
	case navi_VBW:
	case navi_VDR:
	case navi_VHW:
	case navi_VLW:
	case navi_VPW:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_VTG:
		{
			const struct vtg_t *pvtg = (const struct vtg_t *)msg;
			tid = navi_talkerid_str(pvtg->tid);
			sfmt = navi_sentencefmt_str(navi_VTG);

			if (navi_create_vtg(pvtg, msgbody, sizeof(msgbody), &msglen) < 0)
				return navi_Error;
		}
		break;
	case navi_WCV:
	case navi_WNC:
	case navi_WPL:
	case navi_XDR:
	case navi_XTE:
	case navi_XTR:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	case navi_ZDA:
		{
			const struct zda_t *pzda = (const struct zda_t *)msg;
			tid = navi_talkerid_str(pzda->tid);
			sfmt = navi_sentencefmt_str(navi_ZDA);

			if (navi_create_zda(pzda, msgbody, sizeof(msgbody), &msglen) < 0)
				return navi_Error;
		}
		break;
	case navi_ZDL:
	case navi_ZFO:
	case navi_ZTG:
		navierr_set_last(navi_NotImplemented);
		return navi_Error;
	default:
		navierr_set_last(navi_MsgNotSupported);
		return navi_Error;
	}

	if (msglen + 12 > NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	if (msglen + 12 > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	msglen = snprintf(buffer, maxsize, "$%s%s,%s*", tid, sfmt, msgbody);
	if (navi_checksum(buffer, msglen, csstr, NULL) != navi_Ok)
		return navi_Error;
	strcat(buffer, csstr);
	strcat(buffer, "\r\n");

	*nmwritten = msglen + 4;

	return navi_Ok;

#else

	navierr_set_last(navi_NotImplemented);
	return navi_Error;

#endif // NO_GENERATOR

}

//
// navi_datum_to_string
//
const char *navi_datum_str(int datum, int notnull)
{
	if (!notnull)
		datum = navi_Null;

	switch (datum)
	{
	case navi_WGS84:
		return "W84";
	case navi_WGS72:
		return "W72";
	case navi_SGS85:
		return "S85";
	case navi_PE90:
		return "P90";
	case navi_UserDefined:
		return "999";
	case navi_Null:
		return "";
	default:
		return NULL;
	}
}

//
// navi_datumsubdiv_str
//
const char *navi_datumsubdiv_str(int datumsub, int notnull)
{
	if (!notnull)
		datumsub = navi_Null;

	switch (datumsub)
	{
	case navi_Null:
		return "";
	default:
		return NULL;
	}
}

//
// navi_fixsign_str
//
const char *navi_fixsign_str(int fixsign, int notnull)
{
	if (!notnull)
		fixsign = navi_Null;

	switch (fixsign)
	{
	case navi_North:
		return "N";
	case navi_South:
		return "S";
	case navi_East:
		return "E";
	case navi_West:
		return "W";
	case navi_Null:
		return "";
	default:
		return NULL;
	}
}

//
// navi_status_str
//
const char *navi_status_str(int status)
{
	switch (status)
	{
	case navi_DataValid:
		return "A";
	case navi_DataInvalid:
		return "V";
	default:
		return NULL;
	}
}

//
// navi_modeindicator_str
//
const char *navi_modeindicator_str(int mi)
{
	switch (mi)
	{
	case navi_Autonomous:
		return "A";
	case navi_Differential:
		return "D";
	case navi_Estimated:
		return "E";
	case navi_ManualInput:
		return "M";
	case navi_Simulator:
		return "S";
	case navi_DataNotValid:
		return "N";
	default:
		return NULL;
	}
}

//
// navi_modeindicator_extended_str
//
const char *navi_modeindicator_extended_str(int mi)
{
	switch (mi)
	{
	case navi_Autonomous:
		return "A";
	case navi_Differential:
		return "D";
	case navi_Estimated:
		return "E";
	case navi_ManualInput:
		return "M";
	case navi_Simulator:
		return "S";
	case navi_DataNotValid:
		return "N";
	case navi_Precise:
		return "P";
	case navi_RTKinematic:
		return "R";
	case navi_FloatRTK:
		return "F";
	default:
		return NULL;
	}
}

//
// navi_gsamode_str
//
const char *navi_gsamode_str(int mode, int notnull)
{
	if (notnull)
	{
		switch (mode)
		{
		case navi_GsaManual:
			return "M";
		case navi_GsaAutomatic:
			return "A";
		default:
			return NULL;
		}
	}
	else
	{
		return "";
	}
}

//
// navi_print_position_fix
//
int navi_print_position_fix(const struct navi_position_t *fix,
	char *buffer, int maxsize, int notnull)
{
	if (notnull)
	{
		int nmwritten, precision;
		double degrees, fraction;

		const char *s;

		nmwritten = 0;
		precision = naviconf_get_presicion();

		// extract and print latitude
		fraction = modf(fix->latitude, &degrees);
		degrees = degrees * 100.;
		fraction = fraction * 60.;
		fraction = fraction + degrees;

		nmwritten += snprintf(buffer + nmwritten, maxsize, "%0*.*f",
			precision + 5, precision, fraction);
		nmwritten = remove_trailing_zeroes(buffer, nmwritten);

		(void)strncat(buffer, ",", maxsize);
		nmwritten += 1;

		nmwritten += strlen(s = navi_fixsign_str(fix->latsign, notnull));
		(void)strncat(buffer, s, maxsize);

		(void)strncat(buffer, ",", maxsize);
		nmwritten += 1;

		// extract and print longitude
		fraction = modf(fix->longitude, &degrees);
		degrees = degrees * 100.;
		fraction = fraction * 60.;
		fraction = fraction + degrees;

		nmwritten += snprintf(buffer + nmwritten, maxsize, "%0*.*f",
			precision + 6, precision, fraction);
		nmwritten = remove_trailing_zeroes(buffer, nmwritten);

		(void)strncat(buffer, ",", maxsize);
		nmwritten += 1;

		nmwritten += strlen(s = navi_fixsign_str(fix->lonsign, notnull));
		(void)strncat(buffer, s, maxsize);

		return nmwritten;
	}
	else
	{
		(void)strncpy(buffer, ",,,", maxsize);
		return 3;
	}
}

//
// navi_print_number
//
int navi_print_number(double value, char *buffer, int maxsize, int notnull)
{
	if (notnull)
	{
		int result, precision;

		precision = naviconf_get_presicion();
		result = snprintf(buffer, maxsize, "%.*f", precision, value);
		return remove_trailing_zeroes(buffer, result);
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

//
// navi_print_utc
//
int navi_print_utc(const struct navi_utc_t *utc, char *buffer,
	int maxsize, int notnull)
{
	if (notnull)
	{
		int result, precision;

		precision = naviconf_get_presicion();
		result = snprintf(buffer, maxsize, "%02u%02u%0*.*f",
			utc->hour % 24, utc->min % 60, precision + 3, precision, utc->sec);
		return remove_trailing_zeroes(buffer, result);
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

//
// navi_print_miarray
//
int navi_print_miarray(const int mi[], int miquant, char *buffer)
{
	int i;
	const char *mistr;

	assert(buffer != NULL);

	strcpy(buffer, "");
	for (i = 0; i < miquant; i++)
	{
		mistr = navi_modeindicator_extended_str(mi[i]);
		if (strlen(mistr) == 0)
		{
			navierr_set_last(navi_InvalidParameter);
			return 0;
		}
		strcat(buffer, mistr);
	}

	return i;
}

//
// navi_sentencefmt_str
//
const char *navi_sentencefmt_str(int fmt)
{
	assert((fmt >= 0) && (fmt <= navi_ZTG));
	return navi_fmtlist[fmt];
}

//
//	navi_create_talkerid
//
const char *navi_talkerid_str(int tid)
{
	assert((tid >= 0) && (tid <= navi_P));
	return navi_tidlist[tid];
}

//
// navi_print_numfield
//
int navi_print_fixedfield(const char bytes[], int fieldwidth, int radix,
	char *buffer, int maxsize)
{
	int i;
	char str[4];

	assert(buffer != NULL);
	assert(maxsize > fieldwidth);

	(void)strncpy(buffer, "", maxsize);

	for (i = 0; i < fieldwidth; i++)
	{
		switch (radix)
		{
		case 10:
			snprintf(str, sizeof(str), "%d", bytes[i]);
			break;
		case 16:
			snprintf(str, sizeof(str), "%x", bytes[i]);
			break;
		default:
			snprintf(str, sizeof(str), "%c", bytes[i]);
			break;
		}
		(void)strncat(buffer, str, maxsize);
	}

	return i;
}

//
// navi_print_hexfield
//
int navi_print_hexfield(const char bytes[], int fieldwidth,
	char *buffer, int maxsize)
{
	return navi_print_fixedfield(bytes, fieldwidth, 16, buffer, maxsize);
}

//
// navi_print_decfield
//
int navi_print_decfield(const char bytes[], int fieldwidth,
	char *buffer, int maxsize)
{
	return navi_print_fixedfield(bytes, fieldwidth, 10, buffer, maxsize);
}

