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
			return -EMSGSIZE;
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
			return -EMSGSIZE;
		}
		((struct gll_t *)msg)->tid = tid;
		return IecParse_GLL((struct gll_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case naviSentence_GNS:
		if (maxsize < sizeof(struct gns_t))
		{
			return -EMSGSIZE;
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
			return -EMSGSIZE;
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
			return -EMSGSIZE;
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
			return -EMSGSIZE;
		}
		((struct zda_t *)msg)->tid = tid;
		return IecParse_ZDA((struct zda_t *)msg, buffer + som + 6,
			maxsize - (som + eom + 11));
	case naviSentence_ZDL:
	case naviSentence_ZFO:
	case naviSentence_ZTG:
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
		*tid = naviTalkerId_AG;
		return 0;
	}
	else if (strncmp("AP", stid, 2) == 0)
	{
		*tid = naviTalkerId_AP;
		return 0;
	}
	else if (strncmp("AI", stid, 2) == 0)
	{
		*tid = naviTalkerId_AI;
		return 0;
	}
	else if (strncmp("CD", stid, 2) == 0)
	{
		*tid = naviTalkerId_CD;
		return 0;
	}
	else if (strncmp("CR", stid, 2) == 0)
	{
		*tid = naviTalkerId_CR;
		return 0;
	}
	else if (strncmp("CS", stid, 2) == 0)
	{
		*tid = naviTalkerId_CS;
		return 0;
	}
	else if (strncmp("CT", stid, 2) == 0)
	{
		*tid = naviTalkerId_CT;
		return 0;
	}
	else if (strncmp("CV", stid, 2) == 0)
	{
		*tid = naviTalkerId_CV;
		return 0;
	}
	else if (strncmp("CX", stid, 2) == 0)
	{
		*tid = naviTalkerId_CX;
		return 0;
	}
	else if (strncmp("DE", stid, 2) == 0)
	{
		*tid = naviTalkerId_DE;
		return 0;
	}
	else if (strncmp("DF", stid, 2) == 0)
	{
		*tid = naviTalkerId_DF;
		return 0;
	}
	else if (strncmp("EC", stid, 2) == 0)
	{
		*tid = naviTalkerId_EC;
		return 0;
	}
	else if (strncmp("EI", stid, 2) == 0)
	{
		*tid = naviTalkerId_EI;
		return 0;
	}
	else if (strncmp("EP", stid, 2) == 0)
	{
		*tid = naviTalkerId_EP;
		return 0;
	}
	else if (strncmp("ER", stid, 2) == 0)
	{
		*tid = naviTalkerId_ER;
		return 0;
	}
	else if (strncmp("GA", stid, 2) == 0)
	{
		*tid = naviTalkerId_GA;
		return 0;
	}
	else if (strncmp("GP", stid, 2) == 0)
	{
		*tid = naviTalkerId_GP;
		return 0;
	}
	else if (strncmp("GL", stid, 2) == 0)
	{
		*tid = naviTalkerId_GL;
		return 0;
	}
	else if (strncmp("GN", stid, 2) == 0)
	{
		*tid = naviTalkerId_GN;
		return 0;
	}
	else if (strncmp("GW", stid, 2) == 0)
	{
		*tid = naviTalkerId_GW;
		return 0;
	}
	else if (strncmp("HC", stid, 2) == 0)
	{
		*tid = naviTalkerId_HC;
		return 0;
	}
	else if (strncmp("HE", stid, 2) == 0)
	{
		*tid = naviTalkerId_HE;
		return 0;
	}
	else if (strncmp("HN", stid, 2) == 0)
	{
		*tid = naviTalkerId_HN;
		return 0;
	}
	else if (strncmp("II", stid, 2) == 0)
	{
		*tid = naviTalkerId_II;
		return 0;
	}
	else if (strncmp("IN", stid, 2) == 0)
	{
		*tid = naviTalkerId_IN;
		return 0;
	}
	else if (strncmp("LC", stid, 2) == 0)
	{
		*tid = naviTalkerId_LC;
		return 0;
	}
	else if (strncmp("P", stid, 1) == 0)
	{
		*tid = naviTalkerId_P;
		return 0;
	}
	else if (strncmp("RA", stid, 2) == 0)
	{
		*tid = naviTalkerId_RA;
		return 0;
	}
	else if (strncmp("SD", stid, 2) == 0)
	{
		*tid = naviTalkerId_SD;
		return 0;
	}
	else if (strncmp("SN", stid, 2) == 0)
	{
		*tid = naviTalkerId_SN;
		return 0;
	}
	else if (strncmp("SS", stid, 2) == 0)
	{
		*tid = naviTalkerId_SS;
		return 0;
	}
	else if (strncmp("TI", stid, 2) == 0)
	{
		*tid = naviTalkerId_TI;
		return 0;
	}
	else if (strncmp("VD", stid, 2) == 0)
	{
		*tid = naviTalkerId_VD;
		return 0;
	}
	else if (strncmp("VM", stid, 2) == 0)
	{
		*tid = naviTalkerId_VM;
		return 0;
	}
	else if (strncmp("VW", stid, 2) == 0)
	{
		*tid = naviTalkerId_VW;
		return 0;
	}
	else if (strncmp("VR", stid, 2) == 0)
	{
		*tid = naviTalkerId_VR;
		return 0;
	}
	else if (strncmp("YX", stid, 2) == 0)
	{
		*tid = naviTalkerId_YX;
		return 0;
	}
	else if (strncmp("ZA", stid, 2) == 0)
	{
		*tid = naviTalkerId_ZA;
		return 0;
	}
	else if (strncmp("ZC", stid, 2) == 0)
	{
		*tid = naviTalkerId_ZC;
		return 0;
	}
	else if (strncmp("ZQ", stid, 2) == 0)
	{
		*tid = naviTalkerId_ZQ;
		return 0;
	}
	else if (strncmp("ZV", stid, 2) == 0)
	{
		*tid = naviTalkerId_ZV;
		return 0;
	}
	else if (strncmp("WI", stid, 2) == 0)
	{
		*tid = naviTalkerId_WI;
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
		*msgtype = naviSentence_AAM;
		return 0;
	}
	else if (strncmp("ACK", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_ACK;
		return 0;
	}
	else if (strncmp("ALM", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_ALM;
		return 0;
	}
	else if (strncmp("ALR", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_ALR;
		return 0;
	}
	else if (strncmp("APB", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_APB;
		return 0;
	}
	else if (strncmp("BEC", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_BEC;
		return 0;
	}
	else if (strncmp("BOD", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_BOD;
		return 0;
	}
	else if (strncmp("BWC", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_BWC;
		return 0;
	}
	else if (strncmp("BWR", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_BWR;
		return 0;
	}
	else if (strncmp("BWW", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_BWW;
		return 0;
	}
	else if (strncmp("DBT", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_DBT;
		return 0;
	}
	else if (strncmp("DCN", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_DCN;
		return 0;
	}
	else if (strncmp("DPT", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_DPT;
		return 0;
	}
	else if (strncmp("DSC", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_DSC;
		return 0;
	}
	else if (strncmp("DSE", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_DSE;
		return 0;
	}
	else if (strncmp("DSI", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_DSI;
		return 0;
	}
	else if (strncmp("DSR", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_DSR;
		return 0;
	}
	else if (strncmp("DTM", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_DTM;
		return 0;
	}
	else if (strncmp("FSI", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_FSI;
		return 0;
	}
	else if (strncmp("GBS", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_GBS;
		return 0;
	}
	else if (strncmp("GGA", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_GGA;
		return 0;
	}
	else if (strncmp("GLC", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_GLC;
		return 0;
	}
	else if (strncmp("GLC", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_GLC;
		return 0;
	}
	else if (strncmp("GNS", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_GNS;
		return 0;
	}
	else if (strncmp("GRS", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_GRS;
		return 0;
	}
	else if (strncmp("GSA", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_GSA;
		return 0;
	}
	else if (strncmp("GST", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_GST;
		return 0;
	}
	else if (strncmp("GSV", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_GSV;
		return 0;
	}
	else if (strncmp("HDG", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_HDG;
		return 0;
	}
	else if (strncmp("HDT", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_HDT;
		return 0;
	}
	else if (strncmp("HMR", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_HMR;
		return 0;
	}
	else if (strncmp("HMS", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_HMS;
		return 0;
	}
	else if (strncmp("HSC", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_HSC;
		return 0;
	}
	else if (strncmp("HTC", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_HTC;
		return 0;
	}
	else if (strncmp("HTD", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_HTD;
		return 0;
	}
	else if (strncmp("LCD", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_LCD;
		return 0;
	}
	else if (strncmp("MLA", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_MLA;
		return 0;
	}
	else if (strncmp("MSK", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_MSK;
		return 0;
	}
	else if (strncmp("MSS", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_MSS;
		return 0;
	}
	else if (strncmp("MTW", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_MTW;
		return 0;
	}
	else if (strncmp("MWD", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_MWD;
		return 0;
	}
	else if (strncmp("MWV", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_MWV;
		return 0;
	}
	else if (strncmp("OSD", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_OSD;
		return 0;
	}
	else if (strncmp("RMA", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_RMA;
		return 0;
	}
	else if (strncmp("RMB", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_RMB;
		return 0;
	}
	else if (strncmp("RMC", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_RMC;
		return 0;
	}
	else if (strncmp("ROT", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_ROT;
		return 0;
	}
	else if (strncmp("RPM", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_RPM;
		return 0;
	}
	else if (strncmp("RSA", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_RSA;
		return 0;
	}
	else if (strncmp("RSD", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_RSD;
		return 0;
	}
	else if (strncmp("RTE", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_RTE;
		return 0;
	}
	else if (strncmp("SFI", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_SFI;
		return 0;
	}
	else if (strncmp("STN", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_STN;
		return 0;
	}
	else if (strncmp("TLB", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_TLB;
		return 0;
	}
	else if (strncmp("TLL", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_TLL;
		return 0;
	}
	else if (strncmp("TTM", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_TTM;
		return 0;
	}
	else if (strncmp("TXT", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_TXT;
		return 0;
	}
	else if (strncmp("VBW", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_VBW;
		return 0;
	}
	else if (strncmp("VDR", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_VDR;
		return 0;
	}
	else if (strncmp("VHW", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_VHW;
		return 0;
	}
	else if (strncmp("VLW", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_VLW;
		return 0;
	}
	else if (strncmp("VPW", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_VPW;
		return 0;
	}
	else if (strncmp("VTG", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_VTG;
		return 0;
	}
	else if (strncmp("WCV", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_WCV;
		return 0;
	}
	else if (strncmp("WNC", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_WNC;
		return 0;
	}
	else if (strncmp("WPL", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_WPL;
		return 0;
	}
	else if (strncmp("XDR", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_XDR;
		return 0;
	}
	else if (strncmp("XTE", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_XTE;
		return 0;
	}
	else if (strncmp("XTR", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_XTR;
		return 0;
	}
	else if (strncmp("ZDA", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_ZDA;
		return 0;
	}
	else if (strncmp("ZDL", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_ZDL;
		return 0;
	}
	else if (strncmp("ZFO", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_ZFO;
		return 0;
	}
	else if (strncmp("ZTG", sfmt, 3) == 0)
	{
		*msgtype = naviSentence_ZTG;
		return 0;
	}
	else
	{
		return -1;
	}
}

