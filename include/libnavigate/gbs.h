/*
 * gbs.h - generator and parser of GBS message
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

/*! @file gbs.h
 *  @brief Declares the structure and handling utilities for GBS sentence.
 *
 *  Contains declarations for structure, initilizer, generator and parser
 *  of GBS sentence.
 */

#ifndef INCLUDE_navi_gbs_h
#define INCLUDE_navi_gbs_h

#include "sentence.h"

/*! @brief GBS - GNSS satellite fault detection
 *
 *  This message shall be used for reporting RAIM information.
 *  $--GBS,hhmmss.ss,x.x,x.x,x.x,xx,x.x,x.x,x.x*hh[cr][lf]
 */
struct gbs_t
{
	struct navi_utc_t utc;	//!< UTC time
	double experrlat;		//!< expected error in latitude
	double experrlon;		//!< expected error in longitude
	double experralt;		//!< expected error in altitude

	/*! @brief ID number of most likely failed satellite,
	 *
	 *  -1 if null field
	 */
	int failed_id;

	/*! @brief probability of missed detection for most likely
	 * failed satellite
	 */
	double probability;

	double estimate;	//!< estimate of bias on most likely failed satellite
	double deviation;	//!< standard deviation of bias estimate
};

NAVI_BEGIN_DECL

//! @brief Initializes GBS sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_gbs(struct gbs_t *msg);

//! @brief Creates GBS message
NAVI_EXTERN(navierr_status_t) navi_create_gbs(const struct gbs_t *msg,
	char *buffer, size_t maxsize, size_t *nmwritten);

//! @brief Parses GBS message
NAVI_EXTERN(navierr_status_t) navi_parse_gbs(struct gbs_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gbs_h
