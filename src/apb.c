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
	msg->vfields = 0;

	msg->status_0 = navi_status_V;
	msg->status_1 = navi_status_V;
	navi_init_offset_from_degrees(0.0, navi_Left, &msg->xte_magnitude);
	msg->arrival_circle = navi_status_V;
	msg->perpendicular = navi_status_V;
	navi_init_offset_from_degrees(0.0, navi_True, &msg->bearing_origin);
	memset(msg->waypoint_id, 0, sizeof(msg->waypoint_id));
	navi_init_offset_from_degrees(0.0, navi_True, &msg->bearing_present);
	navi_init_offset_from_degrees(0.0, navi_True, &msg->heading);
	msg->mode_indicator = navi_DataNotValid;

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates APB message
navierr_status_t navi_create_apb(const struct apb_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten)
{
	navierr_set_last(navi_NotImplemented);
	return navi_Error;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses APB message
navierr_status_t navi_parse_apb(struct apb_t *msg, char *buffer)
{
	navierr_set_last(navi_NotImplemented);
	return navi_Error;
}

#endif // NO_PARSER
