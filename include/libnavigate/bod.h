/*
 * bod.h - generator and parser of BOD message
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

/*! @file bod.h
 *  @brief Declares the structure and handling utilities for BOD sentence.
 *
 *  Contains declarations for structure, initilizer, generator and parser
 *  of BOD sentence.
 */

#ifndef INCLUDE_navi_bod_h
#define INCLUDE_navi_bod_h

#include "sentence.h"

/*! @brief BOD - Bearing origin to destination
 *
 *  Bearing angle of the line, calculated at the origin waypont, extending
 *  to the destination waypoint from the origin waypoint for the active
 *  navigation leg ot the journey.
 *  $--BOD,x.x,T,x.x,M,c--c,c--c*hh[cr][lf]
 */
struct bod_t
{
	struct navi_offset_t bearingT;	//!< Bearing, degrees true
	struct navi_offset_t bearingM;	//!< Bearing, degrees magnetic
	char dest_waypoint[21];			//!< Destination waypoint ID
	char orig_waypoint[21];			//!< Origin waypoint ID
};

NAVI_BEGIN_DECL

//! @brief Initializes BOD sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_bod(struct bod_t *msg);

//! @brief Creates BOD message
NAVI_EXTERN(navierr_status_t) navi_create_bod(const struct bod_t *msg,
	char *buffer, size_t maxsize, size_t *nmwritten);

//! @brief Parses BOD message
NAVI_EXTERN(navierr_status_t) navi_parse_bod(struct bod_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_bod_h
