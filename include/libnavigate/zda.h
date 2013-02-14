/*
 * zda.h - generator and parser of ZDA message
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

/*! @file zda.h
 *  @brief Declares the structure and handling utilities for ZDA sentence.
 *
 *  Contains declarations for structure, initilizer, generator and parser
 *  of ZDA sentence.
 */

#ifndef INCLUDE_navi_zda_h
#define INCLUDE_navi_zda_h

#include "sentence.h"

/*! @brief ZDA - Time and date
 *
 *  UTC, day, month, year and local time zone.
 *  $--ZDA,hhmmss.ss,xx,xx,xxxx,xx,xx*hh[cr][lf]
 */
struct zda_t
{
	unsigned int vfields;		//!< valid fields, bitwise or of ZDA_VALID_xx
	struct navi_utc_t utc;		//!< UTC time
	struct navi_date_t date;	//!< Day (01 to 31), Month (01 to 12), Year (UTC)
	int lzoffset;				//!< Local zone offset in minutes
};

//! the date field is valid
#define ZDA_VALID_DATE			0x2

//! the local zone offset field is valid
#define ZDA_VALID_LOCALZONE		0x4

NAVI_BEGIN_DECL

//
// Initializes ZDA sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_zda(struct zda_t *msg);

//
// Creates ZDA message
NAVI_EXTERN(navierr_status_t) navi_create_zda(const struct zda_t *msg,
	char *buffer, size_t maxsize, size_t *nmwritten);

//
// Parses ZDA message
NAVI_EXTERN(navierr_status_t) navi_parse_zda(struct zda_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_zda_h
