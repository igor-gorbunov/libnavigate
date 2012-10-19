/*
 * aam.c - generator and parser of AAM message
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

#include <libnavigate/aam.h>
#include <libnavigate/generator.h>
#include <libnavigate/parser.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

//
// Initializes AAM sentence structure with default values
navierr_status_t navi_init_aam(struct aam_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;
	msg->circle = navi_status_V;
	msg->perp = navi_status_V;
	msg->radius = nan("");
	memset(msg->wpid, 0, sizeof(msg->wpid));

	return navi_Ok;
}

//
// Creates AAM message
navierr_status_t navi_create_aam(const struct aam_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	size_t msglength;

	const char *circle, *perp;
	char radius[20], waypointid[80];

	msglength = strlen(circle = navi_status_str(msg->circle));
	msglength += strlen(perp = navi_status_str(msg->perp));
	msglength += navi_print_number(msg->radius, radius, sizeof(radius));

	if (navi_print_character_field(msg->wpid, waypointid, sizeof(waypointid)) != navi_Ok)
		return navi_Error;
	msglength += strlen(waypointid);

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,N,%s",
		circle, perp, radius, waypointid);
	return navi_Ok;
}

//
// Parses AAM message
navierr_status_t navi_parse_aam(struct aam_t *msg, char *buffer)
{
	size_t i = 0, nmread;
	char tmp[4];

	if (navi_parse_status(buffer + i, &msg->circle, &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_status(buffer + i, &msg->perp, &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->radius, &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_character_field(buffer + i, tmp, sizeof(tmp), &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_character_field(buffer + i, msg->wpid, sizeof(msg->wpid), &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}

	return navi_Ok;
}
