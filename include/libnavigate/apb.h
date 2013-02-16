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

/*! @file apb.h
 *  @brief Declares the structure and handling utilities for APB sentence.
 *
 *  Contains declarations for structure, initilizer, generator and parser
 *  of APB sentence.
 */

#ifndef INCLUDE_navi_apb_h
#define INCLUDE_navi_apb_h

#include "sentence.h"

/*! @brief APB - Heading/Track controller (autopilot) sentence B
 *
 * Navigation receiver warning flag status, cross-track-error, waypoint
 * arrival status, initial bearing from origin waypoint to the destination,
 * continuous bearing from present position to destination and recommended
 * heading to steer to destination waypoint for the active navigation leg
 * of the journey.
 * $--APB,A,A,x.x,a,N,A,A,x.x,a,c--c,x.x,a,x.x,a,a*hh[cr][lf]
 */
struct apb_t
{
	/*! @brief Fix status
	 *
	 *  A = Data Valid, V = LORAN-C blink or SNR warning,
	 *  V = general warning flag for other navigation systems
	 *  when a reliable fix is not available
	 */
	navi_status_t status_0;

	/*! @brief LORAN-C cycle lock status
	 *
	 *  A = OK or not used, V = LORAN-C cycle lock warning flag
	 */
	navi_status_t status_1;

	/*! @brief Magnitude of XTE (cross-track-error) and
	 *  direction to steer, L/R
	 */
	struct navi_offset_t xte_magnitude;

	/*! @brief Status of arrival
	 *
	 *  A = arrival circle entered, V = not entered
	 */
	navi_status_t arrival_circle;

	/*! @brief Status of perpendicular
	 *
	 *  A = perpendicular passed at waypoint, V = not passed
	 */
	navi_status_t perpendicular;

	/*! @brief Bearing origin to destination, M/T
	 */
	struct navi_offset_t bearing_origin;

	/*! @brief Destination waipoint ID
	 */
	char waypoint_id[21];

	/*! @brief Bearing, present position to destination, M/T
	 */
	struct navi_offset_t bearing_present;

	/*! @brief Heading to steer to destination waypoint, M/T
	 */
	struct navi_offset_t heading;

	/*! @brief Mode indicator
	 */
	navi_modeindicator_t mode_indicator;
};

NAVI_BEGIN_DECL

//! @brief Initializes APB sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_apb(struct apb_t *msg);

//! @brief Creates APB message
NAVI_EXTERN(navierr_status_t) navi_create_apb(const struct apb_t *msg,
	char *buffer, size_t maxsize, size_t *nmwritten);

//! @brief Parses APB message
NAVI_EXTERN(navierr_status_t) navi_parse_apb(struct apb_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_apb_h
