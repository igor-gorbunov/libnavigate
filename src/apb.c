/*
 * apb.c - generator and parser of APB message
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

#include <libnavigate/apb.h>
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
// Initializes APB sentence structure with default values
navierr_status_t navi_init_apb(struct apb_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;

	msg->status_0 = navi_status_V;
	msg->status_1 = navi_status_V;
	navi_init_offset(&msg->xte_magnitude);
	msg->arrival_circle = navi_status_NULL;
	msg->perpendicular = navi_status_NULL;
	navi_init_offset(&msg->bearing_origin);
	memset(msg->waypoint_id, 0, sizeof(msg->waypoint_id));
	navi_init_offset(&msg->bearing_present);
	navi_init_offset(&msg->heading);
	msg->mode_indicator = navi_DataNotValid;

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates APB message
navierr_status_t navi_create_apb(const struct apb_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten)
{
	size_t msglength;

	const char *const_str;
	char local_str[NAVI_SENTENCE_MAXSIZE];

	assert(msg != NULL);
	assert(buffer != NULL);
	assert(maxsize > 0);

	msglength = strlen(const_str = navi_status_str(msg->status_0));
	if (msglength + 2 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcpy(local_str, const_str);
	(void)strcat(local_str, ",");
	msglength += 1;

	msglength += strlen(const_str = navi_status_str(msg->status_1));
	if (msglength + 2 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, const_str);
	(void)strcat(local_str, ",");
	msglength += 1;

	msglength += navi_print_offset(&msg->xte_magnitude, local_str + msglength,
		sizeof(local_str) - msglength);
	if (msglength + 2 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, ",N,");
	msglength += 3;

	msglength = strlen(const_str = navi_status_str(msg->arrival_circle));
	if (msglength + 2 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, const_str);
	(void)strcat(local_str, ",");
	msglength += 1;

	msglength = strlen(const_str = navi_status_str(msg->perpendicular));
	if (msglength + 2 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, const_str);
	(void)strcat(local_str, ",");
	msglength += 1;

	msglength += navi_print_offset(&msg->bearing_origin, local_str + msglength,
		sizeof(local_str) - msglength);
	if (msglength + 2 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, ",");
	msglength += 1;

	if (navi_print_character_field(msg->waypoint_id, local_str + msglength,
		sizeof(local_str) - msglength) != navi_Ok)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, ",");
	msglength = strlen(local_str);

	msglength += navi_print_offset(&msg->bearing_present, local_str + msglength,
		sizeof(local_str) - msglength);
	if (msglength + 2 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, ",");
	msglength += 1;

	msglength += navi_print_offset(&msg->heading, local_str + msglength,
		sizeof(local_str) - msglength);
	if (msglength + 2 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, ",");
	msglength += 1;

	msglength += strlen(const_str = navi_modeindicator_str(msg->mode_indicator));
	if (msglength + 1 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, const_str);

	msglength = snprintf(buffer, maxsize, "%s", local_str);
	if (nmwritten != NULL)
		*nmwritten = msglength;

	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses APB message
navierr_status_t navi_parse_apb(struct apb_t *msg, char *buffer)
{
	size_t i = 0, nmread;
	char tmp[4];

	if (navi_parse_status(buffer + i, &msg->status_0, &nmread) != navi_Ok)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_status(buffer + i, &msg->status_1, &nmread) != navi_Ok)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_offset(buffer + i, &msg->xte_magnitude, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass == navi_NullField)
			(void)navi_init_offset(&msg->xte_magnitude);
		else
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_character_field(buffer + i, tmp, sizeof(tmp), &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_status(buffer + i, &msg->arrival_circle, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass == navi_NullField)
			msg->arrival_circle = navi_status_NULL;
		else
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_status(buffer + i, &msg->perpendicular, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass == navi_NullField)
			msg->perpendicular = navi_status_NULL;
		else
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_offset(buffer + i, &msg->bearing_origin, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass == navi_NullField)
			(void)navi_init_offset(&msg->bearing_origin);
		else
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_character_field(buffer + i, msg->waypoint_id, sizeof(msg->waypoint_id), &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_offset(buffer + i, &msg->bearing_present, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass == navi_NullField)
			(void)navi_init_offset(&msg->bearing_present);
		else
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_offset(buffer + i, &msg->heading, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass == navi_NullField)
			(void)navi_init_offset(&msg->heading);
		else
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_modeindicator(buffer + i, &msg->mode_indicator, &nmread) != 0)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}

	return navi_Ok;
}

#endif // NO_PARSER
