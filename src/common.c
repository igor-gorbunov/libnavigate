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
#include <string.h>
#include <errno.h>
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

extern const char *navi_tidlist[] =
{
	"AG", "AP", "AI", "CD", "CR", "CS", "CT", "CV", "CX", "DE", "DF",
	"EC", "EI", "EP", "ER", "GA", "GP", "GL", "GN", "GW", "HC", "HE",
	"HN", "II", "IN", "LC", "RA", "SD", "SN", "SS", "TI", "VD", "VM",
	"VW", "VR", "YX", "ZA", "ZC", "ZQ", "ZV", "WI", "P", NULL
};
