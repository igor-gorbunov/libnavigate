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

#ifndef NO_GENERATOR

#include "dtm.h"
#include "gll.h"
#include "gns.h"
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

	switch (type)
	{
	case navi_AAM:
	case navi_ACK:
	case navi_ALM:
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
		break;
	case navi_DTM:
		return navi_create_dtm((const struct dtm_t *)msg, buffer, maxsize, nmwritten);
	case navi_FSI:
	case navi_GBS:
	case navi_GGA:
	case navi_GLC:
		break;
	case navi_GLL:
		return navi_create_gll((const struct gll_t *)msg, buffer, maxsize, nmwritten);
	case navi_GNS:
		return navi_create_gns((const struct gns_t *)msg, buffer, maxsize, nmwritten);
	case navi_GRS:
	case navi_GSA:
	case navi_GST:
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
		break;
	case navi_RMC:
		return navi_create_rmc((const struct rmc_t *)msg, buffer, maxsize, nmwritten);
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
		break;
	case navi_VTG:
		return navi_create_vtg((const struct vtg_t *)msg, buffer, maxsize, nmwritten);
	case navi_WCV:
	case navi_WNC:
	case navi_WPL:
	case navi_XDR:
	case navi_XTE:
	case navi_XTR:
		break;
	case navi_ZDA:
		return navi_create_zda((const struct zda_t *)msg, buffer, maxsize, nmwritten);
	case navi_ZDL:
	case navi_ZFO:
	case navi_ZTG:
		break;
	default:
		break;
	}

	navierr_set_last(navi_MsgNotSupported);

#else

	navierr_set_last(navi_NotImplemented);

#endif // NO_GENERATOR

	return -1;
}

//
//	navi_create_talkerid
//
const char *navi_talkerid_str(int tid)
{
	switch (tid)
	{
	case navi_AG:
		return "AG";
	case navi_AP:
		return "AP";
	case navi_AI:
		return "AI";
	case navi_CD:
		return "CD";
	case navi_CR:
		return "CR";
	case navi_CS:
		return "CS";
	case navi_CT:
		return "CT";
	case navi_CV:
		return "CV";
	case navi_CX:
		return "CX";
	case navi_DE:
		return "DE";
	case navi_DF:
		return "DF";
	case navi_EC:
		return "EC";
	case navi_EI:
		return "EI";
	case navi_EP:
		return "EP";
	case navi_ER:
		return "ER";
	case navi_GA:
		return "GA";
	case navi_GP:
		return "GP";
	case navi_GL:
		return "GL";
	case navi_GN:
		return "GN";
	case navi_GW:
		return "GW";
	case navi_HC:
		return "HC";
	case navi_HE:
		return "HE";
	case navi_HN:
		return "HN";
	case navi_II:
		return "II";
	case navi_IN:
		return "IN";
	case navi_LC:
		return "LC";
	case navi_P:
		return "P";
	case navi_RA:
		return "RA";
	case navi_SD:
		return "SD";
	case navi_SN:
		return "SN";
	case navi_SS:
		return "SS";
	case navi_TI:
		return "TI";
	case navi_VD:
		return "VD";
	case navi_VM:
		return "VM";
	case navi_VW:
		return "VW";
	case navi_VR:
		return "VR";
	case navi_YX:
		return "YX";
	case navi_ZA:
		return "ZA";
	case navi_ZC:
		return "ZC";
	case navi_ZQ:
		return "ZQ";
	case navi_ZV:
		return "ZV";
	case navi_WI:
		return "WI";
	default:
		return NULL;
	}
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
// navi_print_position_fix
//
int navi_print_position_fix(const struct navi_position_t *fix,
	char *buffer, int maxsize, int notnull)
{
	if (notnull)
	{
		int nmwritten;
		double degrees, fraction;

		const char *s;

		nmwritten = 0;

		// extract and print latitude
		fraction = modf(fix->latitude, &degrees);
		degrees = degrees * 100.;
		fraction = fraction * 60.;
		fraction = fraction + degrees;

		nmwritten += snprintf(buffer + nmwritten, maxsize, "%013.8f", fraction);
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

		nmwritten += snprintf(buffer + nmwritten, maxsize, "%014.8f", fraction);
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
// navi_print_double
//
int navi_print_number(double value, char *buffer, int maxsize, int notnull)
{
	if (notnull)
	{
		int result;

		result = snprintf(buffer, maxsize, "%f", value);
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
		int result = snprintf(buffer, maxsize, "%02u%02u%06.3f",
			utc->hour % 24, utc->min % 60, utc->sec);
		return remove_trailing_zeroes(buffer, result);
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}
