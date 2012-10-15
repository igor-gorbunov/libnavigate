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

#include <libnavigate/errors.h>
#include <libnavigate/common.h>

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
navierr_status_t navi_parse_status(char *buffer, int *status, int *nmread)
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
navierr_status_t navi_parse_modeindicator(char *buffer, int *mi, int *nmread)
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
size_t remove_trailing_zeroes(char *buffer, size_t length)
{
	size_t i;

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
// Fills position fix structure with null value.
navierr_status_t navi_init_position(struct navi_position_t *fix)
{
	assert(fix != NULL);

	fix->latitude.offset = fix->longitude.offset = 0.0;
	fix->latitude.sign = fix->longitude.sign = navi_offset_NULL;

	return navi_Ok;
}

//
// Fills position fix structure with given values in degrees.
navierr_status_t navi_init_position_from_degrees(double latitude,
	double longitude, struct navi_position_t *fix)
{
	assert((latitude >= -90.0) && (latitude <= +90.0));
	assert((longitude >= -180.0) && (longitude < +2. * 180.0));
	assert(fix != NULL);

	if (latitude >= 0.0)
		fix->latitude.sign = navi_North;
	else
		fix->latitude.sign = navi_South;
	fix->latitude.offset = fabs(latitude);

	if ((longitude >= 0.0) && (longitude <= +180.0))
	{
		fix->longitude.offset = longitude;
		fix->longitude.sign = navi_East;
	}
	else if (longitude > +180.0)
	{
		fix->longitude.offset = longitude - 180.0;
		fix->longitude.sign = navi_West;
	}
	else
	{
		fix->longitude.offset = fabs(longitude);
		fix->longitude.sign = navi_West;
	}

	return navi_Ok;
}

//
// Fills position fix structure with given values in radians.
navierr_status_t navi_init_position_from_radians(double latitude,
	double longitude, struct navi_position_t *fix)
{
	assert((latitude >= -M_PI) && (latitude <= +M_PI));
	assert((longitude >= -M_PI) && (longitude < +2.0 * M_PI));
	assert(fix != NULL);

	if (latitude >= 0.0)
		fix->latitude.sign = navi_North;
	else
		fix->latitude.sign = navi_South;
	fix->latitude.offset = fabs(latitude) * 180.0 / M_PI;

	if ((longitude >= 0.0) && (longitude <= M_PI))
	{
		fix->longitude.offset = longitude * 180.0 / M_PI;
		fix->longitude.sign = navi_East;
	}
	else if (longitude > M_PI)
	{
		fix->longitude.offset = (longitude - M_PI) * 180.0 / M_PI;
		fix->longitude.sign = navi_West;
	}
	else
	{
		fix->longitude.offset = fabs(latitude) * 180.0 / M_PI;
		fix->longitude.sign = navi_West;
	}

	return navi_Ok;
}

//
// Fills offset structure with given values in degrees.
navierr_status_t navi_init_offset_from_degrees(double offset,
	navi_offset_sign_t sign, struct navi_offset_t *ofs)
{
	assert(ofs != NULL);

	ofs->offset = fabs(offset);
	ofs->sign = sign;

	return navi_Ok;
}

//
// Fills position fix structure with given values in radians.
navierr_status_t navi_init_offset_from_radians(double offset,
	navi_offset_sign_t sign, struct navi_offset_t *ofs)
{
	assert(ofs != NULL);

	ofs->offset = fabs(offset) * 180.0 / M_PI;
	ofs->sign = sign;

	return navi_Ok;
}

//
// navi_get_position
//
navierr_status_t navi_get_position(const struct navi_position_t *in,
	double *latitude, double *longitude)
{
	double d;

	assert(in != NULL);
	assert(latitude != NULL);
	assert(longitude != NULL);

	d = in->latitude.offset;
	if (in->latitude.sign == navi_North)
		*latitude = d;
	else
		*latitude = -d;

	d = in->longitude.offset;
	if (in->longitude.sign == navi_East)
		*longitude = d;
	else
		*longitude = -d;

	return navi_Ok;
}

//
// navi_split_integer
//
navierr_status_t navi_split_integer(unsigned int value, char bytes[], int width, int radix)
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
navierr_status_t navi_checksum(char *msg, size_t maxsize, char *csstr, unsigned int *cs)
{
	size_t i;
	unsigned int ucs = 0;

	assert(msg != NULL);
	assert(maxsize > 0);

	// Skip up to next character after '$'
	for (i = 0; msg[i] != '$' && i < maxsize; i++) { }

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
		(void)snprintf(csstr, 3, "%1X%1X", (ucs & 0xf0) >> 4, ucs & 0x0f);

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

//
// Fills utc structure with given values
navierr_status_t navi_init_utc(int hh, int mm, double ss, struct navi_utc_t *utc)
{
	assert(utc != NULL);

	utc->hour = hh;
	utc->min = mm;
	utc->sec = ss;

	return navi_Ok;
}

//
// Fills date structure with given values
navierr_status_t navi_init_date(int yy, int mm, int dd, struct navi_date_t *date)
{
	assert(date != NULL);

	date->year = yy;
	date->month = mm;
	date->day = dd;

	return navi_Ok;
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
