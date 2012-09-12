/*
 * generator.h - interface to IEC message generator
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

#ifndef INCLUDE_navi_generator_h
#define INCLUDE_navi_generator_h

#include "generic.h"
#include "sentence.h"

NAVI_BEGIN_DECL

//
// Generator for IEC 61162-1 (2000-07) messages
//
// Generates IEC sentence by its description given by type and msg.
// Stores the result to buffer which has the maximum size of maxsize.
// The number of stored characters is stored to nmwritten.
// Returns 0 if succeeded, -1 otherwise
// Call navierr_get_last() to get the error description
//
NAVI_EXTERN(int) navi_create_msg(int type, void *msg, char *buffer,
		int maxsize, int *nmwritten);

//
// Returns the string representation of talker identifier
NAVI_EXTERN(const char *) navi_talkerid_str(int tid);

//
// Returns the string representation of approved sentence
NAVI_EXTERN(const char *) navi_sentencefmt_str(int fmt);

//
// Returns the string representation of geodetic datum
NAVI_EXTERN(const char *) navi_datum_str(int datum, int notnull);

//
// Returns the string representation of geodetic datum
NAVI_EXTERN(const char *) navi_datumsubdiv_str(int datumsub, int notnull);

//
// Returns the offset or position fix sign
NAVI_EXTERN(const char *) navi_fixsign_str(int fixsign, int notnull);

//
// Returns the status
NAVI_EXTERN(const char *) navi_status_str(int status);

//
// Returns the mode indicator
NAVI_EXTERN(const char *) navi_modeindicator_str(int mi);

//
// Prints position fix 'llll.ll,a,yyyyy.yy,a', or null fields
// Returns the number of printed characters
NAVI_EXTERN(int) navi_print_position_fix(const struct navi_position_t *fix,
		char *buffer, int maxsize, int notnull);

//
// Prints variable numbers
// Returns the number of printed characters
NAVI_EXTERN(int) navi_print_number(double value, char *buffer,
		int maxsize, int notnull);

//
// Prints UTC time
// Returns the number of printed characters
NAVI_EXTERN(int) navi_print_utc(const struct navi_utc_t *utc, char *buffer,
		int maxsize, int notnull);

//
// Prints array of mode indicators
// Returns the number of printed characters
NAVI_EXTERN(int) navi_print_miarray(const int mi[], int miquant, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_generator_h
