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

#include <iecparser.h>
#include <errno.h>

//
// Determines the talker id and sentence formatter
static int IecScan_AdressField(char *buffer, size_t maxsize,
	enum naviTalkerId_t *tid, enum naviSentence_t *msgtype);

//
// Checks that the message is not broken
static int IecScan_CheckSum(char *buffer, size_t maxsize);

//
// Parses DTM message
static int IecParse_DTM(struct dtm_t *msg, char *buffer, size_t maxsize);

//
// Parses GLL message
static int IecParse_GLL(struct gll_t *msg, char *buffer, size_t maxsize);

//
// Parses GNS message
static int IecParse_GNS(struct gns_t *msg, char *buffer, size_t maxsize);

//
// Parses RMC message
static int IecParse_RMC(struct rmc_t *msg, char *buffer, size_t maxsize);

//
// Parses VTG message
static int IecParse_VTG(struct vtg_t *msg, char *buffer, size_t maxsize);

//
// Parses ZDA message
static int IecParse_ZDA(struct zda_t *msg, char *buffer, size_t maxsize);

//
// Parser of IEC 61162-1 (2000-07) messages
int IecParseMessage(char *buffer, size_t maxsize, size_t msgsize,
	void *msg, enum naviSentence_t *msgtype)
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
		return -EBADMSG;
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
		return -EBADMSG;
	}

	int r;

	//
	// Check that the message is not broken
	//
	if ((r = IecScan_CheckSum(buffer + som, maxsize - (som + eom))) < 0)
	{
		return r;
	}

	//
	// Determine the talker ID and message type
	//
	enum naviTalkerId_t tid;

	if ((r = IecScan_AdressField(buffer + som + 1, maxsize - (som + eom + 1),
		&tid, msgtype)) < 0)
	{
		return r;
	}

	//
	// Parse the message fields
	//
	switch (*msgtype)
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
		break;
	case _DTM:
		if (maxsize < sizeof(struct dtm_t))
		{
			return -EMSGSIZE;
		}
		((struct dtm_t *)msg)->tid = tid;
		return IecParse_DTM((struct dtm_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case _FSI:
	case _GBS:
	case _GGA:
	case _GLC:
		break;
	case _GLL:
		if (maxsize < sizeof(struct gll_t))
		{
			return -EMSGSIZE;
		}
		((struct gll_t *)msg)->tid = tid;
		return IecParse_GLL((struct gll_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case _GNS:
		if (maxsize < sizeof(struct gns_t))
		{
			return -EMSGSIZE;
		}
		((struct gns_t *)msg)->tid = tid;
		return IecParse_GNS((struct gns_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
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
		if (maxsize < sizeof(struct rmc_t))
		{
			return -EMSGSIZE;
		}
		((struct rmc_t *)msg)->tid = tid;
		return IecParse_RMC((struct rmc_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
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
		if (maxsize < sizeof(struct vtg_t))
		{
			return -EMSGSIZE;
		}
		((struct vtg_t *)msg)->tid = tid;
		return IecParse_VTG((struct vtg_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case _WCV:
	case _WNC:
	case _WPL:
	case _XDR:
	case _XTE:
	case _XTR:
		break;
	case _ZDA:
		if (maxsize < sizeof(struct zda_t))
		{
			return -EMSGSIZE;
		}
		((struct zda_t *)msg)->tid = tid;
		return IecParse_ZDA((struct zda_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case _ZDL:
	case _ZFO:
	case _ZTG:
		break;
	}

	return -ENOSYS;
}

// Talker identifier and sentence formatter
static int IecScan_AdressField(char *buffer, size_t maxsize,
	enum naviTalkerId_t *tid, enum naviSentence_t *msgtype)
{
	if (maxsize < 5)
	{
		return -EMSGSIZE;
	}

	return -ENOSYS;
}

// DTM
static int IecParse_DTM(struct dtm_t *msg, char *buffer, size_t maxsize)
{
	return -ENOSYS;
}

// GLL
static int IecParse_GLL(struct gll_t *msg, char *buffer, size_t maxsize)
{
	return -ENOSYS;
}

// GNS
static int IecParse_GNS(struct gns_t *msg, char *buffer, size_t maxsize)
{
	return -ENOSYS;
}

// RMC
static int IecParse_RMC(struct rmc_t *msg, char *buffer, size_t maxsize)
{
	return -ENOSYS;
}

// VTG
static int IecParse_VTG(struct vtg_t *msg, char *buffer, size_t maxsize)
{
	return -ENOSYS;
}

// ZDA
static int IecParse_ZDA(struct zda_t *msg, char *buffer, size_t maxsize)
{
	return -ENOSYS;
}

// Scan checksum
static int IecScan_CheckSum(char *buffer, size_t maxsize)
{
	return -ENOSYS;
}

