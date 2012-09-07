#include "common.h"
#include <libnavigate/errors.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#define EPROTO 100
#endif // MSVC_VER

//
// navi_parse_status
//

int navi_parse_status(char *buffer, int *status, int *nmread)
{

#ifndef NO_PARSER

	int i = 0, c, error = 0;

	assert(buffer != NULL);
	assert(status != NULL);
	assert(nmread != NULL);

	c = buffer[i++];
	if ((c == 'A') || (c == 'V'))
	{
		*status = (c == 'A') ? navi_DataValid : navi_DataInvalid;
		c = buffer[i++];
		if ((c != ',') && (c != '*'))
		{
			error = navi_InvalidMessage;
		}
	}
	else if ((c == ',') || (c == '*'))
	{
		error = navi_NullField;
	}
	else
	{
		error = navi_InvalidMessage;
	}

	*nmread = i;

	if (error)
	{
		navierr_set_last(error);
		return navi_Error;
	}

	return navi_Ok;

#else

	navierr_set_last(navi_NotImplemented);
	return -1;

#endif // NO_PARSER

}

//
// navi_parse_modeindicator
//

int navi_parse_modeindicator(char *buffer, int *mi, int *nmread)
{

#ifndef NO_PARSER

	int i = 0, c, error = 0;

	assert(buffer != NULL);
	assert(mi != NULL);
	assert(nmread != NULL);

	c = buffer[i++];

	if ((c == 'A') || (c == 'D') || (c == 'E') ||
		(c == 'M') || (c == 'S') || (c == 'N'))
	{
		switch (c)
		{
		case 'A':
			*mi = navi_Autonomous;
			break;
		case 'D':
			*mi = navi_Differential;
			break;
		case 'E':
			*mi = navi_Estimated;
			break;
		case 'M':
			*mi = navi_ManualInput;
			break;
		case 'S':
			*mi = navi_Simulator;
			break;
		case 'N':
			*mi = navi_DataNotValid;
			break;
		}

		c = buffer[i++];
		if ((c != ',') && (c != '*'))
		{
			error = navi_InvalidMessage;
		}
	}
	else if ((c == ',') || (c == '*'))
	{
		error = navi_NullField;
	}
	else
	{
		error = navi_InvalidMessage;
	}

	*nmread = i;

	if (error)
	{
		navierr_set_last(error);
		return navi_Error;
	}

	return navi_Ok;

#else

	navierr_set_last(navi_NotImplemented);
	return -1;

#endif // NO_PARSER

}

//
// remove_trailing_zeroes
//

int remove_trailing_zeroes(char *buffer, int length)
{
	int i;

	for (i = length - 1; ; i--)
	{
		if (buffer[i] == '0')
		{
			buffer[i] = '\0';
			length--;
		}
		else if (buffer[i] == '.')
		{
			buffer[i] = '\0';
			length--;
			break;
		}
		else
		{
			break;
		}
	}

	return length;
}


/////////////////////
int IecPrint_Utc(const struct navi_utc_t *utc, char *buffer,
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

int IecPrint_Checksum(char *msg, int maxsize, char *cs)
{
	int i;
	unsigned ucs = 0;

	if ((msg == NULL) || (maxsize <= 0) || (cs == NULL))
	{
		return -EINVAL;
	}

	// Skip up to next character after '$'
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

int IecPrint_Datum(int datum, char *buffer, int maxsize, int notnull)
{
	if (notnull)
	{
		switch (datum)
		{
		case naviDatum_WGS84:
			return snprintf(buffer, maxsize, "W84");
		case naviDatum_WGS72:
			return snprintf(buffer, maxsize, "W72");
		case naviDatum_SGS85:
			return snprintf(buffer, maxsize, "S85");
		case naviDatum_PE90:
			return snprintf(buffer, maxsize, "P90");
		case naviDatum_UserDefined:
			return snprintf(buffer, maxsize, "999");
		default:
			break;
		}

		return 0;
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

int IecPrint_DatumSubdivision(int lds, char *buffer, int maxsize, int notnull)
{
	if (notnull)
	{
		switch (lds)
		{
		default:
			return 0;
		}
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

int IecPrint_Latitude(double value, char *buffer, int maxsize, int notnull)
{
	if (notnull)
	{
		int result;
		double degrees;

		value = modf(value, &degrees);
		degrees = degrees * 100.;
		value = value * 60.;
		value = value + degrees;

		result = snprintf(buffer, maxsize, "%013.8f", value);
		return remove_trailing_zeroes(buffer, result);
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

int IecPrint_Longitude(double value, char *buffer,
	int maxsize, int notnull)
{
	if (notnull)
	{
		int result;
		double degrees;

		value = modf(value, &degrees);
		degrees = degrees * 100.;
		value = value * 60.;
		value = value + degrees;

		result = snprintf(buffer, maxsize, "%014.8f", value);
		return remove_trailing_zeroes(buffer, result);
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
		return 0;
	}
}

int IecPrint_Status(int status, char *buffer, int maxsize)
{
	switch (status)
	{
	case navi_DataValid:
		return snprintf(buffer, maxsize, "A");
	case navi_DataInvalid:
		return snprintf(buffer, maxsize, "V");
	default:
		break;
	}

	return 0;
}

int IecPrint_ModeIndicator(int mi, char *buffer, int maxsize)
{
	switch (mi)
	{
	case navi_Autonomous:
		return snprintf(buffer, maxsize, "A");
	case navi_Differential:
		return snprintf(buffer, maxsize, "D");
	case navi_Estimated:
		return snprintf(buffer, maxsize, "E");
	case navi_ManualInput:
		return snprintf(buffer, maxsize, "M");
	case navi_Simulator:
		return snprintf(buffer, maxsize, "S");
	case navi_DataNotValid:
		return snprintf(buffer, maxsize, "N");
	default:
		break;
	}

	return 0;
}

int IecPrint_ModeIndicatorArray(const int mi[], char *buffer, int maxsize,
		int notnull)
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
			case navi_Autonomous:
				(void)strncat(buffer, "A", maxsize);
				break;
			case navi_Differential:
				(void)strncat(buffer, "D", maxsize);
				break;
			case navi_Estimated:
				(void)strncat(buffer, "E", maxsize);
				break;
			case navi_ManualInput:
				(void)strncat(buffer, "M", maxsize);
				break;
			case navi_Simulator:
				(void)strncat(buffer, "S", maxsize);
				break;
			case navi_DataNotValid:
				(void)strncat(buffer, "N", maxsize);
				break;
			case navi_Precise:
				(void)strncat(buffer, "P", maxsize);
				break;
			case navi_RTKinematic:
				(void)strncat(buffer, "R", maxsize);
				break;
			case navi_FloatRTK:
				(void)strncat(buffer, "F", maxsize);
				break;
			default:
				return 0;
			}
		}
	}

	return result;
}

// Talker identifier and sentence formatter
int IecScan_AdressField(char *buffer, int maxsize, int *tid, int *msgtype)
{
	int result, nmread;

	*tid = IecLookupTalkerId(buffer, &nmread);
	result = nmread;
	*msgtype = IecLookupSentenceFormatter(buffer + result, &nmread);
	result += nmread;

	return result;
}

// Scan checksum
int IecScan_CheckSum(char *buffer, int maxsize)
{
	int r, i;
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
int IecLookupTalkerId(char *buffer, int *nmread)
{
	*nmread = 2;

	if (strncmp("AG", buffer, 2) == 0)
		return navi_AG;
	else if (strncmp("AP", buffer, 2) == 0)
		return navi_AP;
	else if (strncmp("AI", buffer, 2) == 0)
		return navi_AI;
	else if (strncmp("CD", buffer, 2) == 0)
		return navi_CD;
	else if (strncmp("CR", buffer, 2) == 0)
		return navi_CR;
	else if (strncmp("CS", buffer, 2) == 0)
		return navi_CS;
	else if (strncmp("CT", buffer, 2) == 0)
		return navi_CT;
	else if (strncmp("CV", buffer, 2) == 0)
		return navi_CV;
	else if (strncmp("CX", buffer, 2) == 0)
		return navi_CX;
	else if (strncmp("DE", buffer, 2) == 0)
		return navi_DE;
	else if (strncmp("DF", buffer, 2) == 0)
		return navi_DF;
	else if (strncmp("EC", buffer, 2) == 0)
		return navi_EC;
	else if (strncmp("EI", buffer, 2) == 0)
		return navi_EI;
	else if (strncmp("EP", buffer, 2) == 0)
		return navi_EP;
	else if (strncmp("ER", buffer, 2) == 0)
		return navi_ER;
	else if (strncmp("GA", buffer, 2) == 0)
		return navi_GA;
	else if (strncmp("GP", buffer, 2) == 0)
		return navi_GP;
	else if (strncmp("GL", buffer, 2) == 0)
		return navi_GL;
	else if (strncmp("GN", buffer, 2) == 0)
		return navi_GN;
	else if (strncmp("GW", buffer, 2) == 0)
		return navi_GW;
	else if (strncmp("HC", buffer, 2) == 0)
		return navi_HC;
	else if (strncmp("HE", buffer, 2) == 0)
		return navi_HE;
	else if (strncmp("HN", buffer, 2) == 0)
		return navi_HN;
	else if (strncmp("II", buffer, 2) == 0)
		return navi_II;
	else if (strncmp("IN", buffer, 2) == 0)
		return navi_IN;
	else if (strncmp("LC", buffer, 2) == 0)
		return navi_LC;
	else if (strncmp("P", buffer, 1) == 0)
	{
		*nmread = 1;
		return navi_P;
	}
	else if (strncmp("RA", buffer, 2) == 0)
		return navi_RA;
	else if (strncmp("SD", buffer, 2) == 0)
		return navi_SD;
	else if (strncmp("SN", buffer, 2) == 0)
		return navi_SN;
	else if (strncmp("SS", buffer, 2) == 0)
		return navi_SS;
	else if (strncmp("TI", buffer, 2) == 0)
		return navi_TI;
	else if (strncmp("VD", buffer, 2) == 0)
		return navi_VD;
	else if (strncmp("VM", buffer, 2) == 0)
		return navi_VM;
	else if (strncmp("VW", buffer, 2) == 0)
		return navi_VW;
	else if (strncmp("VR", buffer, 2) == 0)
		return navi_VR;
	else if (strncmp("YX", buffer, 2) == 0)
		return navi_YX;
	else if (strncmp("ZA", buffer, 2) == 0)
		return navi_ZA;
	else if (strncmp("ZC", buffer, 2) == 0)
		return navi_ZC;
	else if (strncmp("ZQ", buffer, 2) == 0)
		return navi_ZQ;
	else if (strncmp("ZV", buffer, 2) == 0)
		return navi_ZV;
	else if (strncmp("WI", buffer, 2) == 0)
		return navi_WI;
	else
		return -1;
}

// Looks up sentence formatter
int IecLookupSentenceFormatter(char *buffer, int *nmread)
{
	*nmread = 3;

	if (strncmp("AAM", buffer, 3) == 0)
	{
		return navi_AAM;
	}
	else if (strncmp("ACK", buffer, 3) == 0)
	{
		return navi_ACK;
	}
	else if (strncmp("ALM", buffer, 3) == 0)
	{
		return navi_ALM;
	}
	else if (strncmp("ALR", buffer, 3) == 0)
	{
		return navi_ALR;
	}
	else if (strncmp("APB", buffer, 3) == 0)
	{
		return navi_APB;
	}
	else if (strncmp("BEC", buffer, 3) == 0)
	{
		return navi_BEC;
	}
	else if (strncmp("BOD", buffer, 3) == 0)
	{
		return navi_BOD;
	}
	else if (strncmp("BWC", buffer, 3) == 0)
	{
		return navi_BWC;
	}
	else if (strncmp("BWR", buffer, 3) == 0)
	{
		return navi_BWR;
	}
	else if (strncmp("BWW", buffer, 3) == 0)
	{
		return navi_BWW;
	}
	else if (strncmp("DBT", buffer, 3) == 0)
	{
		return navi_DBT;
	}
	else if (strncmp("DCN", buffer, 3) == 0)
	{
		return navi_DCN;
	}
	else if (strncmp("DPT", buffer, 3) == 0)
	{
		return navi_DPT;
	}
	else if (strncmp("DSC", buffer, 3) == 0)
	{
		return navi_DSC;
	}
	else if (strncmp("DSE", buffer, 3) == 0)
	{
		return navi_DSE;
	}
	else if (strncmp("DSI", buffer, 3) == 0)
	{
		return navi_DSI;
	}
	else if (strncmp("DSR", buffer, 3) == 0)
	{
		return navi_DSR;
	}
	else if (strncmp("DTM", buffer, 3) == 0)
	{
		return navi_DTM;
	}
	else if (strncmp("FSI", buffer, 3) == 0)
	{
		return navi_FSI;
	}
	else if (strncmp("GBS", buffer, 3) == 0)
	{
		return navi_GBS;
	}
	else if (strncmp("GGA", buffer, 3) == 0)
	{
		return navi_GGA;
	}
	else if (strncmp("GLC", buffer, 3) == 0)
	{
		return navi_GLC;
	}
	else if (strncmp("GLL", buffer, 3) == 0)
	{
		return navi_GLL;
	}
	else if (strncmp("GNS", buffer, 3) == 0)
	{
		return navi_GNS;
	}
	else if (strncmp("GRS", buffer, 3) == 0)
	{
		return navi_GRS;
	}
	else if (strncmp("GSA", buffer, 3) == 0)
	{
		return navi_GSA;
	}
	else if (strncmp("GST", buffer, 3) == 0)
	{
		return navi_GST;
	}
	else if (strncmp("GSV", buffer, 3) == 0)
	{
		return navi_GSV;
	}
	else if (strncmp("HDG", buffer, 3) == 0)
	{
		return navi_HDG;
	}
	else if (strncmp("HDT", buffer, 3) == 0)
	{
		return navi_HDT;
	}
	else if (strncmp("HMR", buffer, 3) == 0)
	{
		return navi_HMR;
	}
	else if (strncmp("HMS", buffer, 3) == 0)
	{
		return navi_HMS;
	}
	else if (strncmp("HSC", buffer, 3) == 0)
	{
		return navi_HSC;
	}
	else if (strncmp("HTC", buffer, 3) == 0)
	{
		return navi_HTC;
	}
	else if (strncmp("HTD", buffer, 3) == 0)
	{
		return navi_HTD;
	}
	else if (strncmp("LCD", buffer, 3) == 0)
	{
		return navi_LCD;
	}
	else if (strncmp("MLA", buffer, 3) == 0)
	{
		return navi_MLA;
	}
	else if (strncmp("MSK", buffer, 3) == 0)
	{
		return navi_MSK;
	}
	else if (strncmp("MSS", buffer, 3) == 0)
	{
		return navi_MSS;
	}
	else if (strncmp("MTW", buffer, 3) == 0)
	{
		return navi_MTW;
	}
	else if (strncmp("MWD", buffer, 3) == 0)
	{
		return navi_MWD;
	}
	else if (strncmp("MWV", buffer, 3) == 0)
	{
		return navi_MWV;
	}
	else if (strncmp("OSD", buffer, 3) == 0)
	{
		return navi_OSD;
	}
	else if (strncmp("RMA", buffer, 3) == 0)
	{
		return navi_RMA;
	}
	else if (strncmp("RMB", buffer, 3) == 0)
	{
		return navi_RMB;
	}
	else if (strncmp("RMC", buffer, 3) == 0)
	{
		return navi_RMC;
	}
	else if (strncmp("ROT", buffer, 3) == 0)
	{
		return navi_ROT;
	}
	else if (strncmp("RPM", buffer, 3) == 0)
	{
		return navi_RPM;
	}
	else if (strncmp("RSA", buffer, 3) == 0)
	{
		return navi_RSA;
	}
	else if (strncmp("RSD", buffer, 3) == 0)
	{
		return navi_RSD;
	}
	else if (strncmp("RTE", buffer, 3) == 0)
	{
		return navi_RTE;
	}
	else if (strncmp("SFI", buffer, 3) == 0)
	{
		return navi_SFI;
	}
	else if (strncmp("STN", buffer, 3) == 0)
	{
		return navi_STN;
	}
	else if (strncmp("TLB", buffer, 3) == 0)
	{
		return navi_TLB;
	}
	else if (strncmp("TLL", buffer, 3) == 0)
	{
		return navi_TLL;
	}
	else if (strncmp("TTM", buffer, 3) == 0)
	{
		return navi_TTM;
	}
	else if (strncmp("TXT", buffer, 3) == 0)
	{
		return navi_TXT;
	}
	else if (strncmp("VBW", buffer, 3) == 0)
	{
		return navi_VBW;
	}
	else if (strncmp("VDR", buffer, 3) == 0)
	{
		return navi_VDR;
	}
	else if (strncmp("VHW", buffer, 3) == 0)
	{
		return navi_VHW;
	}
	else if (strncmp("VLW", buffer, 3) == 0)
	{
		return navi_VLW;
	}
	else if (strncmp("VPW", buffer, 3) == 0)
	{
		return navi_VPW;
	}
	else if (strncmp("VTG", buffer, 3) == 0)
	{
		return navi_VTG;
	}
	else if (strncmp("WCV", buffer, 3) == 0)
	{
		return navi_WCV;
	}
	else if (strncmp("WNC", buffer, 3) == 0)
	{
		return navi_WNC;
	}
	else if (strncmp("WPL", buffer, 3) == 0)
	{
		return navi_WPL;
	}
	else if (strncmp("XDR", buffer, 3) == 0)
	{
		return navi_XDR;
	}
	else if (strncmp("XTE", buffer, 3) == 0)
	{
		return navi_XTE;
	}
	else if (strncmp("XTR", buffer, 3) == 0)
	{
		return navi_XTR;
	}
	else if (strncmp("ZDA", buffer, 3) == 0)
	{
		return navi_ZDA;
	}
	else if (strncmp("ZDL", buffer, 3) == 0)
	{
		return navi_ZDL;
	}
	else if (strncmp("ZFO", buffer, 3) == 0)
	{
		return navi_ZFO;
	}
	else if (strncmp("ZTG", buffer, 3) == 0)
	{
		return navi_ZTG;
	}
	else
	{
		return navi_Error;
	}
}

// Looks up datum code
int IecParse_Datum(char *buffer, int *datum, int *nmread)
{
	*nmread = 3;

	if (strncmp("W84", buffer, 3) == 0)
	{
		*datum = naviDatum_WGS84;
		return navi_Ok;
	}
	else if (strncmp("W72", buffer, 3) == 0)
	{
		*datum = naviDatum_WGS72;
		return navi_Ok;
	}
	else if (strncmp("S85", buffer, 3) == 0)
	{
		*datum = naviDatum_SGS85;
		return navi_Ok;
	}
	else if (strncmp("P90", buffer, 3) == 0)
	{
		*datum = naviDatum_PE90;
		return navi_Ok;
	}
	else if (strncmp("999", buffer, 3) == 0)
	{
		*datum = naviDatum_UserDefined;
		return navi_Ok;
	}
	else if ((strncmp(",", buffer, 1) == 0) || (strncmp("*", buffer, 1) == 0))
	{
		*nmread = 0;
		*datum = navi_Undefined;
		return navi_NullField;
	}
	else
	{
		*nmread = 0;
		return navi_MsgNotSupported;
	}
}

// Looks up datum subdivision code
int IecParse_DatumSub(char *buffer, int *datumsub, int *nmread)
{
	if (strncmp(",", buffer, 1) == 0)
	{
		*nmread = 0;
		*datumsub = naviLocalDatumSub_Undefined;

		navierr_set_last(navi_NullField);
		return navi_Error;
	}
	else
	{
		*nmread = 0;

		navierr_set_last(navi_MsgNotSupported);
		return navi_Error;
	}
}

// Parses floating point value
int IecParse_Double(char *buffer, double *value, int *nmread)
{
	char *endptr = NULL;

	errno = 0;
	*value = strtod(buffer, &endptr);
	*nmread = endptr - buffer;
	if (errno != 0)
	{
		return navi_MsgNotSupported;
	}
	else if (*nmread == 0)
	{
		return navi_NullField;
	}
	else
	{
		return navi_Ok;
	}
}

// Parses mode indicator array
int IecParse_ModeIndicatorArray(char *buffer, int mi[], int *nmread)
{
	int idx = 0;

	while (buffer[idx] != ',')
	{
		if (idx < 2)
		{
			if (strncmp("A", buffer + idx, 1) == 0)
			{
				mi[idx] = navi_Autonomous;
			}
			else if (strncmp("D", buffer + idx, 1) == 0)
			{
				mi[idx] = navi_Differential;
			}
			else if (strncmp("E", buffer + idx, 1) == 0)
			{
				mi[idx] = navi_Estimated;
			}
			else if (strncmp("M", buffer + idx, 1) == 0)
			{
				mi[idx] = navi_ManualInput;
			}
			else if (strncmp("S", buffer + idx, 1) == 0)
			{
				mi[idx] = navi_Simulator;
			}
			else if (strncmp("N", buffer + idx, 1) == 0)
			{
				mi[idx] = navi_DataNotValid;
			}
			else if (strncmp("P", buffer + idx, 1) == 0)
			{
				mi[idx] = navi_Precise;
			}
			else if (strncmp("R", buffer + idx, 1) == 0)
			{
				mi[idx] = navi_RTKinematic;
			}
			else if (strncmp("F", buffer + idx, 1) == 0)
			{
				mi[idx] = navi_FloatRTK;
			}
			else
			{
				mi[idx] = navi_Undefined;
			}
		}
		idx += 1;
	}

	*nmread = idx;
	return idx == 0 ? navi_InvalidMessage : navi_Ok;
}

// Parses integer value
int IecParse_Integer(char *buffer, int *value, int *nmread)
{
	char *endptr = NULL;
	double tmp;

	errno = 0;
	tmp = strtod(buffer, &endptr);
	*value = (int)tmp;
	*nmread = endptr - buffer;
	if (errno != 0)
	{
		return navi_MsgNotSupported;
	}
	else if (*nmread == 0)
	{
		return navi_NullField;
	}
	else
	{
		return navi_Ok;
	}
}

// Parses date
int IecParse_Date(char *buffer, struct naviDate_t *date,
	int *nmread)
{
	int idx;

	for (idx = 0; ; idx++)
	{
		if (isdigit(buffer[idx]))
		{
			if (idx == 0)
			{
				date->day = buffer[idx] - '0';
			}
			else if (idx == 1)
			{
				date->day = date->day * 10 + (buffer[idx] - '0');
			}
			else if (idx == 2)
			{
				date->month = buffer[idx] - '0';
			}
			else if (idx == 3)
			{
				date->month = date->month * 10 + (buffer[idx] - '0');
			}
			else if (idx == 4)
			{
				date->year = buffer[idx] - '0';
			}
			else if (idx == 5)
			{
				date->year = date->year * 10 + (buffer[idx] - '0');
			}
			else if (idx == 6)
			{
				date->year = date->year * 10 + (buffer[idx] - '0');
			}
			else
			{
				date->year = date->year * 10 + (buffer[idx] - '0');
			}
		}
		else if (buffer[idx] == '.')
		{
			continue;
		}
		else if ((buffer[idx] == ',') || (buffer[idx] == '*'))
		{
			break;
		}
		else
		{
			*nmread = idx;
			return navi_InvalidMessage;
		}
	}

	*nmread = idx;

	if (idx == 0)
	{
		return navi_NullField;
	}
	else if (idx < 6)
	{
		return navi_InvalidMessage;
	}
	else
	{
		return navi_Ok;
	}
}

//
// Finite-state machine for parsing local time zone int the form of:
// {[+|-]dd,dd*|,*}
#define PARSE_LOCALZONE_INITIAL		0
#define PARSE_LOCALZONE_SIGN		1
#define PARSE_LOCALZONE_HOURS		2
#define PARSE_LOCALZONE_MINUTES		3
#define PARSE_LOCALZONE_FINAL		4

// Parses local zone (sxx,xx)
int IecParse_LocalZone(char *buffer, int *offset,
	int *nmread)
{
	int idx = 0;
	int state = PARSE_LOCALZONE_INITIAL, sign = 1, hours = 0, minutes = 0;

	do
	{
		switch (buffer[idx])
		{
		case '+':
			switch (state)
			{
			case PARSE_LOCALZONE_INITIAL:
				state = PARSE_LOCALZONE_SIGN;
				sign = 1;
				break;
			default:
				return navi_InvalidMessage;
			}
			break;
		case '-':
			switch (state)
			{
			case PARSE_LOCALZONE_INITIAL:
				state = PARSE_LOCALZONE_SIGN;
				sign = -1;
				break;
			default:
				return navi_InvalidMessage;
			}
			break;
		case ',':
			switch (state)
			{
			case PARSE_LOCALZONE_INITIAL:
			case PARSE_LOCALZONE_HOURS:
				state = PARSE_LOCALZONE_MINUTES;
				break;
			case PARSE_LOCALZONE_MINUTES:
				state = PARSE_LOCALZONE_FINAL;
				break;
			default:
				return navi_InvalidMessage;
			}
			break;
		case '*':
			switch (state)
			{
			case PARSE_LOCALZONE_MINUTES:
				state = PARSE_LOCALZONE_FINAL;
				break;
			default:
				return navi_InvalidMessage;
			}
			break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			switch (state)
			{
			case PARSE_LOCALZONE_INITIAL:
			case PARSE_LOCALZONE_SIGN:
				state = PARSE_LOCALZONE_HOURS;
			// Fall through
			case PARSE_LOCALZONE_HOURS:
				hours = hours * 10 + (buffer[idx] - '0');
				break;
			case PARSE_LOCALZONE_MINUTES:
				minutes = minutes * 10 + (buffer[idx] - '0');
				break;
			default:
				return navi_InvalidMessage;
			}
			break;
		default:
			return navi_InvalidMessage;
		}

		idx++;
	} while (state != PARSE_LOCALZONE_FINAL);

	*offset = sign * (hours * 60 + minutes);

	*nmread = idx;
	return navi_Ok;
}

//
// Prints position fix `llll.ll,a,yyyyy.yy,a`, or null fields
// Returns the number of printed characters
int navi_msg_create_position_fix(const struct navi_position_t *fix,
	char *buffer, int maxsize, int notnull)
{
	if (notnull)
	{
		int nmwritten;
		double degrees, fraction;

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

		nmwritten += navi_msg_create_sign(fix->latsign, buffer + nmwritten,
			maxsize, notnull);

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

		nmwritten += navi_msg_create_sign(fix->lonsign, buffer + nmwritten,
			maxsize, notnull);

		return nmwritten;
	}
	else
	{
		(void)strncpy(buffer, ",,,", maxsize);
		return 3;
	}
}

int navi_msg_create_double(double value, char *buffer, int maxsize, int notnull)
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

int navi_msg_create_sign(int sign, char *buffer, int maxsize, int notnull)
{
	if (notnull)
	{
		switch (sign)
		{
		case navi_North:
			return snprintf(buffer, maxsize, "N");
		case navi_South:
			return snprintf(buffer, maxsize, "S");
		case navi_East:
			return snprintf(buffer, maxsize, "E");
		case navi_West:
			return snprintf(buffer, maxsize, "W");
		default:
			break;
		}
	}
	else
	{
		(void)strncpy(buffer, "", maxsize);
	}

	return 0;
}
