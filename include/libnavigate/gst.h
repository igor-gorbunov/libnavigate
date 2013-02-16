/*
 * gst.h - generator and parser of GST message
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

/*! @file gst.h
 *  @brief Declares the structure and handling utilities for GST sentence.
 *
 *  Contains declarations for structure, initilizer, generator and parser
 *  of GST sentence.
 */

#ifndef INCLUDE_navi_gst_h
#define INCLUDE_navi_gst_h

#include "sentence.h"

/*! @brief GST - GNSS pseudorange noise statistics
 *
 *  This message is used to support RAIM.
 *  $--GST,hhmmss.ss,x.x,x.x,x.x,x.x,x.x,x.x,x.x*hh[cr][lf]
 */
struct gst_t
{
	struct navi_utc_t utc;		//!< UTC time
	double rms;					//!< RMS value of the standard deviation

	//! @brief Standard deviation of semi-major axis of error ellipse, m
	double devmajor;

	//! @brief Standard deviation of semi-minor axis of error ellipse, m
	double devminor;

	//! @brief Orientation of semi-major axis of error ellipse,
	//! degrees from true north
	double orientmajor;

	double devlaterr;	//!< Standard deviation of latitude error, m
	double devlonerr;	//!< Standard deviation of longitude error, m
	double devalterr;	//!< Standard deviation of altitude error, m
};

NAVI_BEGIN_DECL

//! @brief Initializes GST sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_gst(struct gst_t *msg);

//! @brief Creates GST message
NAVI_EXTERN(navierr_status_t) navi_create_gst(const struct gst_t *msg,
	char *buffer, size_t maxsize, size_t *nmwritten);

//! @brief Parses GST message
NAVI_EXTERN(navierr_status_t) navi_parse_gst(struct gst_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gst_h
