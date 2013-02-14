/*
 * alr.h - generator and parser of ALR message
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

/*! @file alr.h
 *  @brief Declares the structure and handling utilities for ALR sentence.
 *
 *  Contains declarations for structure, initilizer, generator and parser
 *  of ALR sentence.
 */

#ifndef INCLUDE_navi_alr_h
#define INCLUDE_navi_alr_h

#include "sentence.h"

/*! @brief ALR - Set alarm state
 *
 * Local alarm condition and status.
 * $--ALR,hhmmss.ss,xxx,A,A,c--c*hh[cr][lf]
 */
struct alr_t
{
	struct navi_utc_t utc;		//!< time of alarm condition change
	int alarmid;				//!< local alarm number

	navi_status_t condition;	//!< alarm condition
								//!< A = threshold exceeded
								//!< V = not exceeded

	navi_status_t ackstate;		//!< alarm's acknowledge state
								//!< A = acknowledged
								//!< V = unacknowledged

	char description[60];		//!< alarm's description text
};

NAVI_BEGIN_DECL

//
// Initializes ALR sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_alr(struct alr_t *msg);

//
// Creates ALR message
NAVI_EXTERN(navierr_status_t) navi_create_alr(const struct alr_t *msg,
	char *buffer, size_t maxsize, size_t *nmwritten);

//
// Parses ALR message
NAVI_EXTERN(navierr_status_t) navi_parse_alr(struct alr_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_alr_h
