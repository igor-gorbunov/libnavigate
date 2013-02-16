/*
 * gsa.h - generator and parser of GSA message
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

/*! @file gsa.h
 *  @brief Declares the structure and handling utilities for GSA sentence.
 *
 *  Contains declarations for structure, initilizer, generator and parser
 *  of GSA sentence.
 */

#ifndef INCLUDE_navi_gsa_h
#define INCLUDE_navi_gsa_h

#include "sentence.h"

//! @brief Maximum satellites per message
#define GSA_MAX_SATELLITES	12

/*! @brief GSA - GNSS DOP and active satellites
 *
 *  GNSS receiver operating mode, satellites used in the navigation solution
 *  reported by the GGA or GNS sentences, and DOP values.
 *  $--GSA,a,x,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,x.x,x.x,x.x*hh[cr][lf]
 */
struct gsa_t
{
	navi_gsaswitchmode_t swmode;	//!< Mode: Manual or Automatic

	//! Mode: 1 = fix not available, 2 = 2D, 3 = 3D, -1 = null field
	int fixmode;

	//! @brief satellites ID numbers array
	//!
	//! ID number of satellite used in solution,
	//! -1 if null field
	int satellites[GSA_MAX_SATELLITES];

	double pdop;	//!< Position dilution of precision
	double hdop;	//!< Horizontal dilution of precision
	double vdop;	//!< Vertical dilution of precision
};

NAVI_BEGIN_DECL

//! @brief Initializes GSA sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_gsa(struct gsa_t *msg);

//! @brief Creates GSA message
NAVI_EXTERN(navierr_status_t) navi_create_gsa(const struct gsa_t *msg,
	char *buffer, size_t maxsize, size_t *nmwritten);

//! @brief Parses GSA message
NAVI_EXTERN(navierr_status_t) navi_parse_gsa(struct gsa_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gsa_h
