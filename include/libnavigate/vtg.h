/*
 * vtg.h - generator and parser of VTG message
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

/*! @file vtg.h
 *  @brief Declares the structure and handling utilities for VTG sentence.
 *
 *  Contains declarations for structure, initilizer, generator and parser
 *  of VTG sentence.
 */

#ifndef INCLUDE_navi_vtg_h
#define INCLUDE_navi_vtg_h

#include "sentence.h"

/*! @brief VTG - Course over ground and ground speed
 *
 * The actual course and speed relative to the ground.
 * $--VTG,x.x,T,x.x,M,x.x,N,x.x,K,a*hh[cr][lf]
 */
struct vtg_t
{
	double courseT;		//!< Course over ground, degrees true
	double courseM;		//!< Course over ground, degrees magnetic
	double speedN;		//!< Speed over ground, knots
	double speedK;		//!< Speed over ground, kmph
	navi_modeindicator_t mi;	//!< Mode indicator
};

NAVI_BEGIN_DECL

/*! @brief Initializes VTG sentence structure with default values
 */
NAVI_EXTERN(navierr_status_t) navi_init_vtg(struct vtg_t *msg);

/*! @brief Creates VTG message
 */
NAVI_EXTERN(navierr_status_t) navi_create_vtg(const struct vtg_t *msg,
	char *buffer, size_t maxsize, size_t *nmwritten);

/*! @brief Parses VTG message
 */
NAVI_EXTERN(navierr_status_t) navi_parse_vtg(struct vtg_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_vtg_h
