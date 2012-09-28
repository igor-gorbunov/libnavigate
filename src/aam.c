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

#include "libnavigate/aam.h"
#include "libnavigate/generator.h"
#include "libnavigate/parser.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

#ifdef _MSC_VER
	#define snprintf	_snprintf
#endif // MSVC_VER

//
// Initializes AAM sentence structure with default values
navierr_status_t navi_init_aam(struct aam_t *aam, navi_talkerid_t tid)
{
	assert(aam != NULL);

	aam->tid = tid;
	aam->circle = navi_status_V;
	aam->perp = navi_status_V;
	aam->radius = 0.0;
	memset(aam->wpid, 0, sizeof(aam->wpid));

	return navi_Ok;
}

//
// Creates AAM message
navierr_status_t navi_create_aam(const struct aam_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	const char *circle, *perp;
	char radius[20], waypointid[80];

	msglength = strlen(circle = navi_status_str(msg->circle));
	msglength += strlen(perp = navi_status_str(msg->perp));
	msglength += navi_print_number(msg->radius, radius, sizeof(radius), 1);

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
	int i = 0, nmread;
	char tmp[4];

	if (navi_parse_status(buffer + i, &msg->circle, &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}
	i += nmread;

	if (navi_parse_status(buffer + i, &msg->perp, &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->radius, &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}
	i += nmread;

	if (navi_parse_character_field(buffer + i, tmp, sizeof(tmp), &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}
	i += nmread;

	if (navi_parse_character_field(buffer + i, msg->wpid, sizeof(msg->wpid), &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}

	return navi_Ok;
}
