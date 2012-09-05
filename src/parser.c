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

#include <libnavigate/parser.h>
#include <libnavigate/errors.h>

#include "common.h"
#include "dtm.h"
#include "gll.h"
#include "gns.h"
#include "rmc.h"
#include "vtg.h"
#include "zda.h"

//
// Parser of IEC 61162-1 (2000-07) messages
int navi_msg_parse(char *buffer, int maxsize, int msgsize,
	void *msg, int *msgtype, int *nmread)
{
	int result;
	int tid;	// talker id

	int som;	// start of message index
	int eom;	// end of message index

	//
	//	Determine the borders of message in buffer
	//

	// Skip up to beginning of the next message
	for (som = 0; buffer[som] != '$' && som < maxsize; som++) { }
	if (som >= maxsize)
	{	// No valid message
		return navi_NoValidMessage;
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
		return navi_NoValidMessage;
	}

	// At least read a message
	*nmread = eom;

	//
	// Check that the message is not broken
	//
	if ((result = IecScan_CheckSum(buffer + som, maxsize - (som + eom))) < 0)
	{
		return navi_CrcEror;
	}

	//
	// Determine the talker ID and message type
	//
	if (IecScan_AdressField(buffer + som + 1, maxsize - (som + eom + 1),
			&tid, msgtype) < 0)
	{
		return navi_Undefined;
	}

	//
	// Parse the message fields
	//
	switch (*msgtype)
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
		if (maxsize < sizeof(struct dtm_t))
		{
			return navi_NotEnoughBuffer;
		}
		((struct dtm_t *)msg)->tid = tid;
		return navi_msg_parse_dtm((struct dtm_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case navi_FSI:
	case navi_GBS:
	case navi_GGA:
	case navi_GLC:
		break;
	case navi_GLL:
		if (maxsize < sizeof(struct gll_t))
		{
			return navi_NotEnoughBuffer;
		}
		((struct gll_t *)msg)->tid = tid;
		return IecParse_GLL((struct gll_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case navi_GNS:
		if (maxsize < sizeof(struct gns_t))
		{
			return navi_NotEnoughBuffer;
		}
		((struct gns_t *)msg)->tid = tid;
		return IecParse_GNS((struct gns_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
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
		if (maxsize < sizeof(struct rmc_t))
		{
			return navi_NotEnoughBuffer;
		}
		((struct rmc_t *)msg)->tid = tid;
		return IecParse_RMC((struct rmc_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
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
		if (maxsize < sizeof(struct vtg_t))
		{
			return navi_NotEnoughBuffer;
		}
		((struct vtg_t *)msg)->tid = tid;
		return IecParse_VTG((struct vtg_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case navi_WCV:
	case navi_WNC:
	case navi_WPL:
	case navi_XDR:
	case navi_XTE:
	case navi_XTR:
		break;
	case navi_ZDA:
		if (maxsize < sizeof(struct zda_t))
		{
			return navi_NotEnoughBuffer;
		}
		((struct zda_t *)msg)->tid = tid;
		return IecParse_ZDA((struct zda_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case navi_ZDL:
	case navi_ZFO:
	case navi_ZTG:
		break;
	default:
		break;
	}

	return navi_MsgNotSupported;
}

