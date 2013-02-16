/*
 * grs.h - generator and parser of GRS message
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

/*! @file grs.h
 *  @brief Declares the structure and handling utilities for GRS sentence.
 *
 *  Contains declarations for structure, initilizer, generator and parser
 *  of GRS sentence.
 */

#ifndef INCLUDE_navi_grs_h
#define INCLUDE_navi_grs_h

#include "sentence.h"

//! @brief Maximum satellites per message
#define GRS_MAX_SATELLITES	12

/*! @brief GRS - GNSS range residuals
 *
 * This message is used to support receiver autonomous integrity monitoring (RAIM).
 * $--GRS,hhmmss.ss,x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x*hh[cr][lf]
 */
struct grs_t
{
	struct navi_utc_t utc;	//!< UTC time

	/*! @brief Mode
	 *
	 *  0 = residuals were used to calculate the position
	 *  given in the matching GGA or GNS sentence
	 *  1 = residuals were recomputed after the GGA or GNS
	 *  position was computed
	 */
	int mode;

	double residuals[GRS_MAX_SATELLITES];	//!< range residuals array
};

NAVI_BEGIN_DECL

//! @brief Initializes GRS sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_grs(struct grs_t *msg);

//! @brief Creates GRS message
NAVI_EXTERN(navierr_status_t) navi_create_grs(const struct grs_t *msg,
	char *buffer, size_t maxsize, size_t *nmwritten);

//! @brief Parses GRS message
NAVI_EXTERN(navierr_status_t) navi_parse_grs(struct grs_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_grs_h
