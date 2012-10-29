/*
 * bwr.h - generator and parser of BWR message
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

#ifndef INCLUDE_navi_bwr_h
#define INCLUDE_navi_bwr_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// BWR - Bearing and distance to waypoint - rhumb line
// Time (UTC) and distance and bearing to, and location of,
// a specified waypoint from present position. BWR data is calculated
// along the rhumb line from present position rather than along the
// great circle path.
// $--BWR,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x.x,T,x.x,M,x.x,N,c--c,a*hh<cr><lf>
//
struct bwr_t
{
	// Talker id
	navi_talkerid_t tid;

	// UTC of observation
	struct navi_utc_t utc;

	// Waypoint coordinates
	struct navi_position_t waypointfix;

	// Bearing, degrees true
	struct navi_offset_t bearingT;

	// Bearing, degrees magnetic
	struct navi_offset_t bearingM;

	// Distance, nautical miles
	double distance;

	// Waypoint ID
	char waypoint_id[21];

	// Mode indicator
	navi_modeindicator_t mi;
};

NAVI_BEGIN_DECL

//
// Initializes BWR sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_bwr(struct bwr_t *msg, navi_talkerid_t tid);

//
// Creates BWR message
NAVI_EXTERN(navierr_status_t) navi_create_bwr(const struct bwr_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten);

//
// Parses BWR message
NAVI_EXTERN(navierr_status_t) navi_parse_bwr(struct bwr_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_bwr_h
