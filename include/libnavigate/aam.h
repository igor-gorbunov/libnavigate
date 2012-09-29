/*
 * aam.h - generator and parser of AAM message
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

#ifndef INCLUDE_navi_aam_h
#define INCLUDE_navi_aam_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// AAM - Waypoint arrival alarm
//
// Status of arrival (entering the arrival circle, or passing the perpendicular
// of the course line) at waypoint c--c.
// $--AAM,A,A,x.x,N,c--c*hh<cr><lf>
//

struct aam_t
{
	navi_talkerid_t tid;	// talker identifier
	navi_status_t circle;	// arrival circle status
							// A = arrival circle entered
							// V = not entered
	navi_status_t perp;		// perpendicular status
							// A = perpendicular passed at waypoint
							// V = not passed
	double radius;			// arrival circle radius, nautical miles
	char wpid[60];			// waypoint id
};

NAVI_BEGIN_DECL

//
// Initializes AAM sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_aam(struct aam_t *msg, navi_talkerid_t tid);

//
// Creates AAM message
NAVI_EXTERN(navierr_status_t) navi_create_aam(const struct aam_t *msg, char *buffer,
	int maxsize, int *nmwritten);

//
// Parses AAM message
NAVI_EXTERN(navierr_status_t) navi_parse_aam(struct aam_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_aam_h
