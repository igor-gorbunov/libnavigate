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

const char *navi_talkerid_to_string(int tid)
{
	switch (tid)
	{
	case navi_AG: return "AG";
	case navi_AP: return "AP";
	case navi_AI: return "AI";
	case navi_CD: return "CD";
	case navi_CR: return "CR";
	case navi_CS: return "CS";
	case navi_CT: return "CT";
	case navi_CV: return "CV";
	case navi_CX: return "CX";
	case navi_DE: return "DE";
	case navi_DF: return "DF";
	case navi_EC: return "EC";
	case navi_EI: return "EI";
	case navi_EP: return "EP";
	case navi_ER: return "ER";
	case navi_GA: return "GA";
	case navi_GP: return "GP";
	case navi_GL: return "GL";
	case navi_GN: return "GN";
	case navi_GW: return "GW";
	case navi_HC: return "HC";
	case navi_HE: return "HE";
	case navi_HN: return "HN";
	case navi_II: return "II";
	case navi_IN: return "IN";
	case navi_LC: return "LC";
	case navi_P:  return "P";
	case navi_RA: return "RA";
	case navi_SD: return "SD";
	case navi_SN: return "SN";
	case navi_SS: return "SS";
	case navi_TI: return "TI";
	case navi_VD: return "VD";
	case navi_VM: return "VM";
	case navi_VW: return "VW";
	case navi_VR: return "VR";
	case navi_YX: return "YX";
	case navi_ZA: return "ZA";
	case navi_ZC: return "ZC";
	case navi_ZQ: return "ZQ";
	case navi_ZV: return "ZV";
	case navi_WI: return "WI";
	default: return NULL;
	}
}
