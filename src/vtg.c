/*
 * vtg.c - generator and parser of VTG message
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

#include <libnavigate/vtg.h>
#include <libnavigate/common.h>
#include <libnavigate/generator.h>
#include <libnavigate/parser.h>

#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

//
// Initializes VTG sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_vtg(struct vtg_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;
	msg->courseT = nan("");
	msg->courseM = nan("");
	msg->speedN = nan("");
	msg->speedK = nan("");
	msg->mi = navi_DataNotValid;

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates VTG message
navierr_status_t navi_create_vtg(const struct vtg_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten)
{
	size_t msglength = 0;

	const char *const_str;
	char local_str[NAVI_SENTENCE_MAXSIZE];

	if (navi_check_validity_number(msg->courseT) == navi_Ok)
	{
		msglength += navi_print_number(msg->courseT, local_str + msglength,
			sizeof(local_str) - msglength);
		msglength += snprintf(local_str + msglength,
			sizeof(local_str) - msglength, ",T,");
	}
	else
	{
		msglength += snprintf(local_str + msglength,
			sizeof(local_str) - msglength, ",,");
	}

	if (navi_check_validity_number(msg->courseM) == navi_Ok)
	{
		msglength += navi_print_number(msg->courseM, local_str + msglength,
			sizeof(local_str) - msglength);
		msglength += snprintf(local_str + msglength,
			sizeof(local_str) - msglength, ",M,");
	}
	else
	{
		msglength += snprintf(local_str + msglength,
			sizeof(local_str) - msglength, ",,");
	}

	if (navi_check_validity_number(msg->speedN) == navi_Ok)
	{
		msglength += navi_print_number(msg->speedN, local_str + msglength,
			sizeof(local_str) - msglength);
		msglength += snprintf(local_str + msglength,
			sizeof(local_str) - msglength, ",N,");
	}
	else
	{
		msglength += snprintf(local_str + msglength,
			sizeof(local_str) - msglength, ",,");
	}

	if (navi_check_validity_number(msg->speedK) == navi_Ok)
	{
		msglength += navi_print_number(msg->speedK, local_str + msglength,
			sizeof(local_str) - msglength);
		msglength += snprintf(local_str + msglength,
			sizeof(local_str) - msglength, ",K,");
	}
	else
	{
		msglength += snprintf(local_str + msglength,
			sizeof(local_str) - msglength, ",,");
	}

	const_str = navi_modeindicator_str(msg->mi);
	msglength += snprintf(local_str + msglength, sizeof(local_str) - msglength,
		",%s", const_str);

	if (msglength >= maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = msglength;
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses VTG message
navierr_status_t navi_parse_vtg(struct vtg_t *msg, char *buffer)
{
	size_t i = 0, nmread;

	if (navi_parse_number(buffer + i, &msg->courseT, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (buffer[i] == 'T')
	{
		i += 1;
	}
	if (buffer[i] != ',')
	{
		return navi_InvalidMessage;
	}
	i += 1;

	if (navi_parse_number(buffer + i, &msg->courseM, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (buffer[i] == 'M')
	{
		i += 1;
	}
	if (buffer[i] != ',')
	{
		return navi_InvalidMessage;
	}
	i += 1;

	if (navi_parse_number(buffer + i, &msg->speedN, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (buffer[i] == 'N')
	{
		i += 1;
	}
	if (buffer[i] != ',')
	{
		return navi_InvalidMessage;
	}
	i += 1;

	if (navi_parse_number(buffer + i, &msg->speedK, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (buffer[i] == 'K')
	{
		i += 1;
	}
	if (buffer[i] != ',')
	{
		return navi_InvalidMessage;
	}
	i += 1;

	if (navi_parse_modeindicator(buffer + i, &msg->mi, &nmread) != navi_Ok)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}

	return navi_Ok;
}

#endif // NO_PARSER
