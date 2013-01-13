/*
 * bec.c - generator and parser of BEC message
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

#include <libnavigate/bec.h>
#include <libnavigate/generator.h>
#include <libnavigate/parser.h>

#include <string.h>
#include <assert.h>
#include <stdio.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

//
// Initializes BEC sentence structure with default values
navierr_status_t navi_init_bec(struct bec_t *msg)
{
	assert(msg != NULL);

	navi_init_utc(&msg->utc);
	navi_init_position(&msg->waypointfix);
	navi_init_offset(&msg->bearingT);
	navi_init_offset(&msg->bearingM);
	navi_init_number(&msg->distance);
	memset(msg->waypoint_id, 0, sizeof(msg->waypoint_id));

	return navi_Ok;
}

//
// Creates BEC message
navierr_status_t navi_create_bec(const struct bec_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten)
{
	size_t msglength = 0;

	char local_str[NAVI_SENTENCE_MAXSIZE];

	assert(msg != NULL);
	assert(buffer != NULL);
	assert(maxsize > 0);

	msglength = navi_print_utc(&msg->utc, local_str + msglength,
		sizeof(local_str) - msglength);
	if (msglength + 2 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, ",");
	msglength += 1;

	msglength += navi_print_position_fix(&msg->waypointfix,
		local_str + msglength, sizeof(local_str) - msglength);
	if (msglength + 2 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, ",");
	msglength += 1;

	msglength += navi_print_offset(&msg->bearingT,
		local_str + msglength, sizeof(local_str) - msglength);
	if (msglength + 2 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, ",");
	msglength += 1;

	msglength += navi_print_offset(&msg->bearingM,
		local_str + msglength, sizeof(local_str) - msglength);
	if (msglength + 2 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, ",");
	msglength += 1;

	msglength = navi_print_number(msg->distance, local_str + msglength,
		sizeof(local_str) - msglength);
	if (msglength + 4 > sizeof(local_str))
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	(void)strcat(local_str, ",N,");
	msglength += 3;

	if (navi_print_character_field(msg->waypoint_id, local_str + msglength,
		sizeof(local_str) - msglength) != navi_Ok)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}
	msglength = strlen(local_str);

	msglength = snprintf(buffer, maxsize, "%s", local_str);
	if (nmwritten != NULL)
		*nmwritten = msglength;

	return navi_Ok;
}

//
// Parses BEC message
navierr_status_t navi_parse_bec(struct bec_t *msg, char *buffer)
{
	size_t i = 0, nmread;

	if (navi_parse_utc(buffer + i, &msg->utc, &nmread) != navi_Ok)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_position_fix(buffer + i, &msg->waypointfix, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_offset(buffer + i, &msg->bearingT, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_offset(buffer + i, &msg->bearingM, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->distance, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_character_field(buffer + i, msg->waypoint_id,
		sizeof(msg->waypoint_id), &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}

	return navi_Ok;
}
