/*
 * apb.h - generator and parser of APB message
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

#ifndef INCLUDE_navi_apb_h
#define INCLUDE_navi_apb_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// APB - Heading/Track controller (autopilot) sentence B
// Navigation receiver warning flag status, cross-track-error, waypoint
// arrival status, initial bearing from origin waypoint to the destination,
// continuous bearing from present position to destination and recommended
// heading to steer to destination waypoint for the active navigation leg
// of the journey.
// $--APB,A,A,x.x,a,N,A,A,x.x,a,c--c,x.x,a,x.x,a,a*hh<cr><lf>
//
struct apb_t
{
	// A = Data Valid, V = LORAN-C blink or SNR warning,
	// V = genearl warning flag for other navigation systems
	// when a reliable fix is not available
	navi_status_t status_0;

	// A = OK or not used, V = LORAN-C cycle lock warning flag
	navi_status_t status_1;

	// Magnitude of XTE (cross-track-error) and
	// direction to steer, L/R
	struct navi_offset_t xte_magnitude;

	// A = arrival circle entered, V = not entered
	navi_status_t arrival_circle;

	// A = perpendicular passed at waypoint, V = not passed
	navi_status_t perpendicular;

	// Bearing origin to destination, M/T
	struct navi_offset_t bearing_origin;

	// Destination waipoint ID
	char waypoint_id[21];

	// Bearing, present position to destination, M/T
	struct navi_offset_t bearing_present;

	// Heading to steer to destination waypoint, M/T
	struct navi_offset_t heading;

	// Mode indicator
	navi_modeindicator_t mode_indicator;
};

NAVI_BEGIN_DECL

//
// Initializes APB sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_apb(struct apb_t *msg);

//
// Creates APB message
NAVI_EXTERN(navierr_status_t) navi_create_apb(const struct apb_t *msg,
	char *buffer, size_t maxsize, size_t *nmwritten);

//
// Parses APB message
NAVI_EXTERN(navierr_status_t) navi_parse_apb(struct apb_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_apb_h
