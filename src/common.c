/*
 * common.c - common utilities for generator and parser
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

#include "common.h"
#include <libnavigate/generator.h>
#include <libnavigate/errors.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif // MSVC_VER

#include <math.h>
#include <ctype.h>
#include <assert.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
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
		*status = (c == 'A') ? navi_status_A : navi_status_V;
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

//
// navi_set_position
//
int navi_set_position(double latitude, double longitude,
	struct navi_position_t *out)
{
	assert((latitude >= -M_PI) && (latitude <= M_PI));
	assert((longitude >= -M_PI) && (longitude < 2. * M_PI));
	assert(out != NULL);

	if (latitude >= 0.)
	{
		out->latitude = latitude * 180. / M_PI;
		out->latsign = navi_North;
	}
	else
	{
		out->latitude = fabs(latitude) * 180. / M_PI;
		out->latsign = navi_South;
	}

	if ((longitude >= 0.) && (longitude < M_PI))
	{
		out->longitude = longitude * 180. / M_PI;
		out->lonsign = navi_East;
	}
	else if (longitude >= M_PI)
	{
		out->longitude = (longitude - M_PI) * 180. / M_PI;
		out->lonsign = navi_West;
	}
	else
	{
		out->latitude = fabs(latitude) * 180. / M_PI;
		out->latsign = navi_West;
	}

	return navi_Ok;
}

//
// navi_get_position
//
int navi_get_position(const struct navi_position_t *in, double *latitude,
	double *longitude)
{
	double d;

	assert(in != NULL);
	assert(latitude != NULL);
	assert(longitude != NULL);

	d = in->latitude * M_PI / 180.;
	if (in->latsign == navi_North)
		*latitude = d;
	else
		*latitude = -d;

	d = in->longitude * M_PI / 180.;
	if (in->latsign == navi_East)
		*longitude = d;
	else
		*longitude = 2 * M_PI - d;

	return navi_Ok;
}

//
// navi_split_integer
//
int navi_split_integer(unsigned int value, char bytes[], int width, int radix)
{
	int i;

	if ((radix != 10) && (radix != 16))
	{
		navierr_set_last(navi_InvalidParameter);
		return navi_Error;
	}

	for (i = width - 1; i >= 0; i--)
	{
		bytes[i] = (char)(value % radix);
		value /= radix;
	}

	return navi_Ok;
}

//
// navi_compose_integer
//
unsigned int navi_compose_integer(char bytes[], int width, int radix)
{
	int i;
	unsigned result = 0;

	for (i = 0; i < width; i++)
		result = result * radix + bytes[i];

	return result;
}

//
// navi_checksum
//
int navi_checksum(char *msg, int maxsize, char *csstr, unsigned *cs)
{
	int i;
	unsigned ucs = 0;

	assert(msg != NULL);
	assert(maxsize > 0);

	// Skip up to next character after '$'
	for (i = 0; msg[i] != '$' && i < maxsize; i++);

	if (i >= maxsize)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	for (i += 1; msg[i] != '*' && i < maxsize; i++)
		ucs = ucs ^ msg[i];

	if (i >= maxsize)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	if (cs)
		*cs = ucs;

	if (csstr)
		snprintf(csstr, 3, "%1X%1X", (ucs & 0xf0) >> 4, ucs & 0x0f);

	return navi_Ok;
}

//
// navi_get_character_type
//
navi_char_type_t navi_get_character_type(int c)
{
	if ((c < 0x20) || (c > 0x7f))
		return navi_char_Undefined;
	else if ((c == 0x21) || (c == 0x24) || (c == 0x2a) || (c == 0x2c) ||
		(c == 0x5c) || (c == 0x5e) || (c == 0x7e) || (c == 0x7f))
		return navi_char_Reserved;
	else
		return navi_char_Valid;
}

const char *navi_fmtlist[] =
{
	"AAM", "ACK", "ALM", "ALR", "APB", "BEC", "BOD", "BWC", "BWR",
	"BWW", "DBT", "DCN", "DPT", "DSC", "DSE", "DSI", "DSR", "DTM",
	"FSI", "GBS", "GGA", "GLC", "GLL", "GNS", "GRS", "GSA", "GST",
	"GSV", "HDG", "HDT", "HMR", "HMS", "HSC", "HTC", "HTD", "LCD",
	"MLA", "MSK", "MSS", "MTW", "MWD", "MWV", "OSD", "RMA", "RMB",
	"RMC", "ROT", "RPM", "RSA", "RSD", "RTE", "SFI", "STN", "TLB",
	"TLL", "TTM", "TXT", "VBW", "VDR", "VHW", "VLW", "VPW", "VTG",
	"WCV", "WNC", "WPL", "XDR", "XTE", "XTR", "ZDA", "ZDL", "ZFO",
	"ZTG", NULL
};

const char *navi_tidlist[] =
{
	"AG", "AP", "AI", "CD", "CR", "CS", "CT", "CV", "CX", "DE", "DF",
	"EC", "EI", "EP", "ER", "GA", "GP", "GL", "GN", "GW", "HC", "HE",
	"HN", "II", "IN", "LC", "RA", "SD", "SN", "SS", "TI", "VD", "VM",
	"VW", "VR", "YX", "ZA", "ZC", "ZQ", "ZV", "WI", "P", NULL
};
