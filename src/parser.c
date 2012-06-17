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

//
// Determines the talker id and sentence formatter
static int IecScan_AdressField(char *buffer, size_t maxsize,
	enum naviTalkerId_t *tid, enum naviSentence_t *msgtype);

//
// Checks that the message is not broken
// Returns 0, if the checksum is correct, -EPROTO otherwise
static int IecScan_CheckSum(char *buffer, size_t maxsize);

//
// Looks up Talker ID
static int IecLookupTalkerId(char *stid, enum naviTalkerId_t *tid);

//
// Looks up sentence formatter
static int IecLookupSentenceFormatter(char *sfmt, enum naviSentence_t *msgtype);

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
	int result;
	char stid[3], sfmt[4];

	if (maxsize < 5)
	{
		return -EMSGSIZE;
	}

	stid[0] = buffer[0];

	if (stid[0] == 'P')
	{
		stid[1] = '\0';

		sfmt[0] = buffer[1];
		sfmt[1] = buffer[2];
		sfmt[2] = buffer[3];
		sfmt[3] = '0';
	}
	else
	{
		stid[1] = buffer[1];
		stid[2] = '\0';

		sfmt[0] = buffer[2];
		sfmt[1] = buffer[3];
		sfmt[2] = buffer[4];
		sfmt[3] = '\0';
	}

	(void)IecLookupTalkerId(stid, tid);
	result = IecLookupSentenceFormatter(sfmt, msgtype);

	return result;
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
static int IecLookupTalkerId(char *stid, enum naviTalkerId_t *tid)
{
	if (strncmp("AG", stid, 2) == 0)
	{
		*tid = _AG;
		return 0;
	}
	else if (strncmp("AP", stid, 2) == 0)
	{
		*tid = _AP;
		return 0;
	}
	else if (strncmp("AI", stid, 2) == 0)
	{
		*tid = _AI;
		return 0;
	}
	else if (strncmp("CD", stid, 2) == 0)
	{
		*tid = _CD;
		return 0;
	}
	else if (strncmp("CR", stid, 2) == 0)
	{
		*tid = _CR;
		return 0;
	}
	else if (strncmp("CS", stid, 2) == 0)
	{
		*tid = _CS;
		return 0;
	}
	else if (strncmp("CT", stid, 2) == 0)
	{
		*tid = _CT;
		return 0;
	}
	else if (strncmp("CV", stid, 2) == 0)
	{
		*tid = _CV;
		return 0;
	}
	else if (strncmp("CX", stid, 2) == 0)
	{
		*tid = _CX;
		return 0;
	}
	else if (strncmp("DE", stid, 2) == 0)
	{
		*tid = _DE;
		return 0;
	}
	else if (strncmp("DF", stid, 2) == 0)
	{
		*tid = _DF;
		return 0;
	}
	else if (strncmp("EC", stid, 2) == 0)
	{
		*tid = _EC;
		return 0;
	}
	else if (strncmp("EI", stid, 2) == 0)
	{
		*tid = _EI;
		return 0;
	}
	else if (strncmp("EP", stid, 2) == 0)
	{
		*tid = _EP;
		return 0;
	}
	else if (strncmp("ER", stid, 2) == 0)
	{
		*tid = _ER;
		return 0;
	}
	else if (strncmp("GA", stid, 2) == 0)
	{
		*tid = _GA;
		return 0;
	}
	else if (strncmp("GP", stid, 2) == 0)
	{
		*tid = _GP;
		return 0;
	}
	else if (strncmp("GL", stid, 2) == 0)
	{
		*tid = _GL;
		return 0;
	}
	else if (strncmp("GN", stid, 2) == 0)
	{
		*tid = _GN;
		return 0;
	}
	else if (strncmp("GW", stid, 2) == 0)
	{
		*tid = _GW;
		return 0;
	}
	else if (strncmp("HC", stid, 2) == 0)
	{
		*tid = _HC;
		return 0;
	}
	else if (strncmp("HE", stid, 2) == 0)
	{
		*tid = _HE;
		return 0;
	}
	else if (strncmp("HN", stid, 2) == 0)
	{
		*tid = _HN;
		return 0;
	}
	else if (strncmp("II", stid, 2) == 0)
	{
		*tid = _II;
		return 0;
	}
	else if (strncmp("IN", stid, 2) == 0)
	{
		*tid = _IN;
		return 0;
	}
	else if (strncmp("LC", stid, 2) == 0)
	{
		*tid = _LC;
		return 0;
	}
	else if (strncmp("P", stid, 1) == 0)
	{
		*tid = _P;
		return 0;
	}
	else if (strncmp("RA", stid, 2) == 0)
	{
		*tid = _RA;
		return 0;
	}
	else if (strncmp("SD", stid, 2) == 0)
	{
		*tid = _SD;
		return 0;
	}
	else if (strncmp("SN", stid, 2) == 0)
	{
		*tid = _SN;
		return 0;
	}
	else if (strncmp("SS", stid, 2) == 0)
	{
		*tid = _SS;
		return 0;
	}
	else if (strncmp("TI", stid, 2) == 0)
	{
		*tid = _TI;
		return 0;
	}
	else if (strncmp("VD", stid, 2) == 0)
	{
		*tid = _VD;
		return 0;
	}
	else if (strncmp("VM", stid, 2) == 0)
	{
		*tid = _VM;
		return 0;
	}
	else if (strncmp("VW", stid, 2) == 0)
	{
		*tid = _VW;
		return 0;
	}
	else if (strncmp("VR", stid, 2) == 0)
	{
		*tid = _VR;
		return 0;
	}
	else if (strncmp("YX", stid, 2) == 0)
	{
		*tid = _YX;
		return 0;
	}
	else if (strncmp("ZA", stid, 2) == 0)
	{
		*tid = _ZA;
		return 0;
	}
	else if (strncmp("ZC", stid, 2) == 0)
	{
		*tid = _ZC;
		return 0;
	}
	else if (strncmp("ZQ", stid, 2) == 0)
	{
		*tid = _ZQ;
		return 0;
	}
	else if (strncmp("ZV", stid, 2) == 0)
	{
		*tid = _ZV;
		return 0;
	}
	else if (strncmp("WI", stid, 2) == 0)
	{
		*tid = _WI;
		return 0;
	}
	else
	{
		return -1;
	}
}

// Looks up sentence formatter
static int IecLookupSentenceFormatter(char *sfmt, enum naviSentence_t *msgtype)
{
	if (strncmp("AAM", sfmt, 3) == 0)
	{
		*msgtype = _AAM;
		return 0;
	}
	else if (strncmp("ACK", sfmt, 3) == 0)
	{
		*msgtype = _ACK;
		return 0;
	}
	else if (strncmp("ALM", sfmt, 3) == 0)
	{
		*msgtype = _ALM;
		return 0;
	}
	else if (strncmp("ALR", sfmt, 3) == 0)
	{
		*msgtype = _ALR;
		return 0;
	}
	else if (strncmp("APB", sfmt, 3) == 0)
	{
		*msgtype = _APB;
		return 0;
	}
	else if (strncmp("BEC", sfmt, 3) == 0)
	{
		*msgtype = _BEC;
		return 0;
	}
	else if (strncmp("BOD", sfmt, 3) == 0)
	{
		*msgtype = _BOD;
		return 0;
	}
	else if (strncmp("BWC", sfmt, 3) == 0)
	{
		*msgtype = _BWC;
		return 0;
	}
	else if (strncmp("BWR", sfmt, 3) == 0)
	{
		*msgtype = _BWR;
		return 0;
	}
	else if (strncmp("BWW", sfmt, 3) == 0)
	{
		*msgtype = _BWW;
		return 0;
	}
	else if (strncmp("DBT", sfmt, 3) == 0)
	{
		*msgtype = _DBT;
		return 0;
	}
	else if (strncmp("DCN", sfmt, 3) == 0)
	{
		*msgtype = _DCN;
		return 0;
	}
	else if (strncmp("DPT", sfmt, 3) == 0)
	{
		*msgtype = _DPT;
		return 0;
	}
	else if (strncmp("DSC", sfmt, 3) == 0)
	{
		*msgtype = _DSC;
		return 0;
	}
	else if (strncmp("DSE", sfmt, 3) == 0)
	{
		*msgtype = _DSE;
		return 0;
	}
	else if (strncmp("DSI", sfmt, 3) == 0)
	{
		*msgtype = _DSI;
		return 0;
	}
	else if (strncmp("DSR", sfmt, 3) == 0)
	{
		*msgtype = _DSR;
		return 0;
	}
	else if (strncmp("DTM", sfmt, 3) == 0)
	{
		*msgtype = _DTM;
		return 0;
	}
	else if (strncmp("FSI", sfmt, 3) == 0)
	{
		*msgtype = _FSI;
		return 0;
	}
	else if (strncmp("GBS", sfmt, 3) == 0)
	{
		*msgtype = _GBS;
		return 0;
	}
	else if (strncmp("GGA", sfmt, 3) == 0)
	{
		*msgtype = _GGA;
		return 0;
	}
	else if (strncmp("GLC", sfmt, 3) == 0)
	{
		*msgtype = _GLC;
		return 0;
	}
	else if (strncmp("GLC", sfmt, 3) == 0)
	{
		*msgtype = _GLC;
		return 0;
	}
	else if (strncmp("GNS", sfmt, 3) == 0)
	{
		*msgtype = _GNS;
		return 0;
	}
	else if (strncmp("GRS", sfmt, 3) == 0)
	{
		*msgtype = _GRS;
		return 0;
	}
	else if (strncmp("GSA", sfmt, 3) == 0)
	{
		*msgtype = _GSA;
		return 0;
	}
	else if (strncmp("GST", sfmt, 3) == 0)
	{
		*msgtype = _GST;
		return 0;
	}
	else if (strncmp("GSV", sfmt, 3) == 0)
	{
		*msgtype = _GSV;
		return 0;
	}
	else if (strncmp("HDG", sfmt, 3) == 0)
	{
		*msgtype = _HDG;
		return 0;
	}
	else if (strncmp("HDT", sfmt, 3) == 0)
	{
		*msgtype = _HDT;
		return 0;
	}
	else if (strncmp("HMR", sfmt, 3) == 0)
	{
		*msgtype = _HMR;
		return 0;
	}
	else if (strncmp("HMS", sfmt, 3) == 0)
	{
		*msgtype = _HMS;
		return 0;
	}
	else if (strncmp("HSC", sfmt, 3) == 0)
	{
		*msgtype = _HSC;
		return 0;
	}
	else if (strncmp("HTC", sfmt, 3) == 0)
	{
		*msgtype = _HTC;
		return 0;
	}
	else if (strncmp("HTD", sfmt, 3) == 0)
	{
		*msgtype = _HTD;
		return 0;
	}
	else if (strncmp("LCD", sfmt, 3) == 0)
	{
		*msgtype = _LCD;
		return 0;
	}
	else if (strncmp("MLA", sfmt, 3) == 0)
	{
		*msgtype = _MLA;
		return 0;
	}
	else if (strncmp("MSK", sfmt, 3) == 0)
	{
		*msgtype = _MSK;
		return 0;
	}
	else if (strncmp("MSS", sfmt, 3) == 0)
	{
		*msgtype = _MSS;
		return 0;
	}
	else if (strncmp("MTW", sfmt, 3) == 0)
	{
		*msgtype = _MTW;
		return 0;
	}
	else if (strncmp("MWD", sfmt, 3) == 0)
	{
		*msgtype = _MWD;
		return 0;
	}
	else if (strncmp("MWV", sfmt, 3) == 0)
	{
		*msgtype = _MWV;
		return 0;
	}
	else if (strncmp("OSD", sfmt, 3) == 0)
	{
		*msgtype = _OSD;
		return 0;
	}
	else if (strncmp("RMA", sfmt, 3) == 0)
	{
		*msgtype = _RMA;
		return 0;
	}
	else if (strncmp("RMB", sfmt, 3) == 0)
	{
		*msgtype = _RMB;
		return 0;
	}
	else if (strncmp("RMC", sfmt, 3) == 0)
	{
		*msgtype = _RMC;
		return 0;
	}
	else if (strncmp("ROT", sfmt, 3) == 0)
	{
		*msgtype = _ROT;
		return 0;
	}
	else if (strncmp("RPM", sfmt, 3) == 0)
	{
		*msgtype = _RPM;
		return 0;
	}
	else if (strncmp("RSA", sfmt, 3) == 0)
	{
		*msgtype = _RSA;
		return 0;
	}
	else if (strncmp("RSD", sfmt, 3) == 0)
	{
		*msgtype = _RSD;
		return 0;
	}
	else if (strncmp("RTE", sfmt, 3) == 0)
	{
		*msgtype = _RTE;
		return 0;
	}
	else if (strncmp("SFI", sfmt, 3) == 0)
	{
		*msgtype = _SFI;
		return 0;
	}
	else if (strncmp("STN", sfmt, 3) == 0)
	{
		*msgtype = _STN;
		return 0;
	}
	else if (strncmp("TLB", sfmt, 3) == 0)
	{
		*msgtype = _TLB;
		return 0;
	}
	else if (strncmp("TLL", sfmt, 3) == 0)
	{
		*msgtype = _TLL;
		return 0;
	}
	else if (strncmp("TTM", sfmt, 3) == 0)
	{
		*msgtype = _TTM;
		return 0;
	}
	else if (strncmp("TXT", sfmt, 3) == 0)
	{
		*msgtype = _TXT;
		return 0;
	}
	else if (strncmp("VBW", sfmt, 3) == 0)
	{
		*msgtype = _VBW;
		return 0;
	}
	else if (strncmp("VDR", sfmt, 3) == 0)
	{
		*msgtype = _VDR;
		return 0;
	}
	else if (strncmp("VHW", sfmt, 3) == 0)
	{
		*msgtype = _VHW;
		return 0;
	}
	else if (strncmp("VLW", sfmt, 3) == 0)
	{
		*msgtype = _VLW;
		return 0;
	}
	else if (strncmp("VPW", sfmt, 3) == 0)
	{
		*msgtype = _VPW;
		return 0;
	}
	else if (strncmp("VTG", sfmt, 3) == 0)
	{
		*msgtype = _VTG;
		return 0;
	}
	else if (strncmp("WCV", sfmt, 3) == 0)
	{
		*msgtype = _WCV;
		return 0;
	}
	else if (strncmp("WNC", sfmt, 3) == 0)
	{
		*msgtype = _WNC;
		return 0;
	}
	else if (strncmp("WPL", sfmt, 3) == 0)
	{
		*msgtype = _WPL;
		return 0;
	}
	else if (strncmp("XDR", sfmt, 3) == 0)
	{
		*msgtype = _XDR;
		return 0;
	}
	else if (strncmp("XTE", sfmt, 3) == 0)
	{
		*msgtype = _XTE;
		return 0;
	}
	else if (strncmp("XTR", sfmt, 3) == 0)
	{
		*msgtype = _XTR;
		return 0;
	}
	else if (strncmp("ZDA", sfmt, 3) == 0)
	{
		*msgtype = _ZDA;
		return 0;
	}
	else if (strncmp("ZDL", sfmt, 3) == 0)
	{
		*msgtype = _ZDL;
		return 0;
	}
	else if (strncmp("ZFO", sfmt, 3) == 0)
	{
		*msgtype = _ZFO;
		return 0;
	}
	else if (strncmp("ZTG", sfmt, 3) == 0)
	{
		*msgtype = _ZTG;
		return 0;
	}
	else
	{
		return -1;
	}
}

