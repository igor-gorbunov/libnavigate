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

#include <math.h>
#include <ctype.h>
#include <stddef.h>
#include <assert.h>

#include "common.h"
#include "dtm.h"
#include "gll.h"
#include "gns.h"
#include "rmc.h"
#include "vtg.h"
#include "zda.h"

//
// navi_msg_parse
//
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
		return navi_msg_parse_gll((struct gll_t *)msg, buffer + som + 6,
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

//
// navi_msg_parse_offset
//

#define PARSE_OFFSET_INIT		0
#define PARSE_OFFSET_INTEGRAL	1
#define PARSE_OFFSET_FRACTION	2
#define PARSE_OFFSET_SIGN		3
#define PARSE_OFFSET_FINI		4

int navi_msg_parse_offset(char *buffer, struct navi_offset_t *offset,
		int *nmread)
{
	double t;
	int i, j, state, c, s, error = 0;

	assert(buffer != NULL);
	assert(offset != NULL);
	assert(nmread != NULL);

	t = 0.;
	state = PARSE_OFFSET_INIT;

	for (i = 0, j = -1; ; i++)
	{
		c = buffer[i];

		switch (state)
		{
		case PARSE_OFFSET_INIT:
			if (isdigit(c))
			{
				state = PARSE_OFFSET_INTEGRAL;
				t = t * 10. + (c - '0');
			}
			else if (c == '.')
			{
				state = PARSE_OFFSET_FRACTION;
			}
			else if (c == ',')
			{	// null field
				state = PARSE_OFFSET_FINI;
				error = navi_NullField;
			}
			else
			{
				error = navi_InvalidMessage;
				goto _Exit;
			}
			break;
		case PARSE_OFFSET_INTEGRAL:
			if (isdigit(c))
			{
				t = t * 10. + (c - '0');
			}
			else if (c == '.')
			{
				state = PARSE_OFFSET_FRACTION;
			}
			else if (c == ',')
			{
				state = PARSE_OFFSET_SIGN;
			}
			else
			{
				error = navi_InvalidMessage;
				goto _Exit;
			}
			break;
		case PARSE_OFFSET_FRACTION:
			if (isdigit(c))
			{
				t = t + pow((c - '0'), j--);
			}
			else if (c == ',')
			{
				state = PARSE_OFFSET_SIGN;
			}
			else
			{
				error = navi_InvalidMessage;
				goto _Exit;
			}
			break;
		case PARSE_OFFSET_SIGN:
			if (c == 'N')
			{
				s = navi_North;
			}
			else if (c == 'S')
			{
				s = navi_South;
			}
			else if (c == 'E')
			{
				s = navi_East;
			}
			else if (c == 'W')
			{
				s = navi_West;
			}
			else
			{
				error = navi_InvalidMessage;
				goto _Exit;
			}
			state = PARSE_OFFSET_FINI;
			break;
		case PARSE_OFFSET_FINI:
			if (c != ',' && c != '*')
				error = navi_InvalidMessage;
			goto _Exit;
		}
	}

_Exit:

	*nmread = i;

	if (error)
	{
		navierr_set_last(error);
		return navi_Error;
	}

	return navi_Ok;
}

#undef PARSE_OFFSET_INIT
#undef PARSE_OFFSET_INTEGRAL
#undef PARSE_OFFSET_FRACTION
#undef PARSE_OFFSET_SIGN
#undef PARSE_OFFSET_FINI

//
// navi_msg_parse_position_fix
//

#define PARSE_POSITION_INIT				0
#define PARSE_POSITION_LAT_INTEGRAL		1
#define PARSE_POSITION_LAT_FRACTION		2
#define PARSE_POSITION_LAT_SIGN			3
#define PARSE_POSITION_LON_INTEGRAL		4
#define PARSE_POSITION_LON_FRACTION		5
#define PARSE_POSITION_LON_SIGN			6
#define PARSE_POSITION_NULLFIELD		7
#define PARSE_POSITION_FINI				8

int navi_msg_parse_position_fix(char *buffer, struct navi_position_t *fix,
	int *nmread)
{
	int state, i, j, k, c, error = 0;
	double deg, min;

	assert(buffer != NULL);
	assert(fix != NULL);
	assert(nmread != NULL);

	state = PARSE_POSITION_INIT;
	deg = min = 0.;

	for (i = 0; ; i++)
	{
		c = buffer[i];

		switch (state)
		{
		case PARSE_POSITION_INIT:
			if (c == ',')
			{	// check for null field
				state = PARSE_POSITION_NULLFIELD;
				j = 1;
			}
			else if (isdigit(c))
			{	// proceed latitude
				state = PARSE_POSITION_LAT_INTEGRAL;
				i--;	// one character back
			}
			else
			{
				error = navi_InvalidMessage;
				goto _Exit;
			}
			break;
		case PARSE_POSITION_LAT_INTEGRAL:
			// parse two digits of degrees
			for (k = 0; k < 2; k++, i++)
			{
				c = buffer[i];
				if (isdigit(c))
				{
					deg = deg * 10. + (c - '0');
				}
				else
				{
					error = navi_InvalidMessage;
					goto _Exit;
				}
			}
			// parse two integral digits of minutes
			for (k = 0; k < 2; k++, i++)
			{
				c = buffer[i];
				if (isdigit(c))
				{
					min = min * 10. + (c - '0');
				}
				else
				{
					error = navi_InvalidMessage;
					goto _Exit;
				}
			}
			// check if there is fractional part of latitude minutes
			c = buffer[i];
			if (c == '.')
			{	// yes, there is
				state = PARSE_POSITION_LAT_FRACTION;
				j = -1;
			}
			else if (c == ',')
			{	// no, proceed to the latitude sign
				state = PARSE_POSITION_LAT_SIGN;
				fix->latitude = deg + min / 60.;
			}
			else
			{	// invalid character
				error = navi_InvalidMessage;
				goto _Exit;
			}
			break;
		case PARSE_POSITION_LAT_FRACTION:
			if (isdigit(c))
			{
				min = min + pow((c - '0'), j--);
			}
			else if (c == ',')
			{
				state = PARSE_POSITION_LAT_SIGN;
				fix->latitude = deg + min / 60.;
			}
			else
			{
				error = navi_InvalidMessage;
				goto _Exit;
			}
			break;
		case PARSE_POSITION_LAT_SIGN:
			if (c == 'N')
			{
				fix->latsign = navi_North;
			}
			else if (c == 'S')
			{
				fix->latsign = navi_South;
			}
			else
			{
				error = navi_InvalidMessage;
				goto _Exit;
			}
			// check if this is the only character
			c = buffer[++i];
			if (c == ',')
			{
				state = PARSE_POSITION_LON_INTEGRAL;
			}
			else
			{
				error = navi_InvalidMessage;
				goto _Exit;
			}
			break;
		case PARSE_POSITION_LON_INTEGRAL:
			// parse three digits of degrees
			for (k = 0; k < 3; k++, i++)
			{
				c = buffer[i];
				if (isdigit(c))
				{
					deg = deg * 10. + (c - '0');
				}
				else
				{
					error = navi_InvalidMessage;
					goto _Exit;
				}
			}
			// parse two integral digits of minutes
			for (k = 0; k < 2; k++, i++)
			{
				c = buffer[i];
				if (isdigit(c))
				{
					min = min * 10. + (c - '0');
				}
				else
				{
					error = navi_InvalidMessage;
					goto _Exit;
				}
			}
			// check if there is fractional part of longitude minutes
			c = buffer[i];
			if (c == '.')
			{	// yes, there is
				state = PARSE_POSITION_LON_FRACTION;
				j = -1;
			}
			else if (c == ',')
			{	// no, proceed to the longitude sign
				state = PARSE_POSITION_LON_SIGN;
				fix->longitude = deg + min / 60.;
			}
			else
			{	// invalid character
				error = navi_InvalidMessage;
				goto _Exit;
			}
			break;
		case PARSE_POSITION_LON_FRACTION:
			if (isdigit(c))
			{
				min = min + pow((c - '0'), j--);
			}
			else if (c == ',')
			{
				state = PARSE_POSITION_LON_SIGN;
				fix->longitude = deg + min / 60.;
			}
			else
			{
				error = navi_InvalidMessage;
				goto _Exit;
			}
			break;
		case PARSE_POSITION_LON_SIGN:
			if (c == 'E')
			{
				fix->lonsign = navi_East;
			}
			else if (c == 'W')
			{
				fix->lonsign = navi_West;
			}
			else
			{
				error = navi_InvalidMessage;
				goto _Exit;
			}
			// check if this is the only character
			c = buffer[++i];
			if (c == ',')
			{
				state = PARSE_POSITION_FINI;
			}
			else
			{
				error = navi_InvalidMessage;
				goto _Exit;
			}
			break;
		case PARSE_POSITION_NULLFIELD:
			if (j < 3)
			{
				if (c == ',')
				{
					j++;
				}
				else
				{
					error = navi_InvalidMessage;
					goto _Exit;
				}
			}
			else
			{	// indeed null field
				state = PARSE_POSITION_FINI;
				error = navi_NullField;
			}
			break;
		case PARSE_POSITION_FINI:
			if (c != ',' && c != '*')
				error = navi_InvalidMessage;
			goto _Exit;
		}
	}

_Exit:

	*nmread = i;

	if (error)
	{
		navierr_set_last(error);
		return navi_Error;
	}

	return navi_Ok;
}

#undef PARSE_POSITION_INIT
#undef PARSE_POSITION_LAT_INTEGRAL
#undef PARSE_POSITION_LAT_FRACTION
#undef PARSE_POSITION_LAT_SIGN
#undef PARSE_POSITION_LON_INTEGRAL
#undef PARSE_POSITION_LON_FRACTION
#undef PARSE_POSITION_LON_SIGN
#undef PARSE_POSITION_NULLFIELD
#undef PARSE_POSITION_FINI

