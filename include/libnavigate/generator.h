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

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

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
NAVI_EXTERN(navierr_status_t) navi_create_msg(navi_approved_fmt_t type,
	const void *msg, char *buffer, size_t maxsize, size_t *nmwritten);

//
// Returns the string representation of talker identifier
NAVI_EXTERN(const char *) navi_talkerid_str(navi_talkerid_t tid);

//
// Returns the string representation of approved sentence
NAVI_EXTERN(const char *) navi_sentencefmt_str(navi_approved_fmt_t fmt);

//
// Returns the string representation of geodetic datum
NAVI_EXTERN(const char *) navi_datum_str(navi_datum_t datum);

//
// Returns the string representation of geodetic datum subdivision code
NAVI_EXTERN(const char *) navi_datumsubdiv_str(navi_datum_subdivision_t datumsub);

//
// Returns the offset or position fix sign
NAVI_EXTERN(const char *) navi_fixsign_str(navi_offset_sign_t fixsign);

//
// Returns the status
NAVI_EXTERN(const char *) navi_status_str(navi_status_t status);

//
// Returns the mode indicator
NAVI_EXTERN(const char *) navi_modeindicator_str(navi_modeindicator_t mi);

//
// Returns the extended mode indicator
NAVI_EXTERN(const char *) navi_modeindicator_extended_str(navi_modeindicator_t mi);

//
// Returns the GSA 2D/3D switching mode
NAVI_EXTERN(const char *) navi_gsamode_str(navi_gsaswitchmode_t mode);

//
// Prints offset 'x.x,a', or null fields
// Returns the number of printed characters
NAVI_EXTERN(size_t) navi_print_offset(const struct navi_offset_t *offset,
	char *buffer, size_t maxsize);

//
// Prints position fix 'llll.ll,a,yyyyy.yy,a', or null fields
// Returns the number of printed characters
NAVI_EXTERN(size_t) navi_print_position_fix(const struct navi_position_t *fix,
	char *buffer, size_t maxsize, int notnull);

//
// Prints variable numbers
// Returns the number of printed characters
NAVI_EXTERN(size_t) navi_print_number(double value, char *buffer,
	size_t maxsize, int notnull);

//
// Prints fixed length hexadecimal numbers, MSB on the left.
// If fieldwidth equals 0, the field is considered to be null.
// Returns the number of printed characters
NAVI_EXTERN(size_t) navi_print_hexfield(const char bytes[], int fieldwidth,
	char *buffer, size_t maxsize);

//
// Prints fixed length decimal numbers
// If fieldwidth equals 0, the field is considered to be null.
// Returns the number of printed characters
NAVI_EXTERN(size_t) navi_print_decfield(const char bytes[], int fieldwidth,
	char *buffer, size_t maxsize);

//
// Print fixed length field with given radix
NAVI_EXTERN(size_t) navi_print_fixedfield(const char bytes[], int fieldwidth, int radix,
	char *buffer, size_t maxsize);

//
// Prints UTC time
// Returns the number of printed characters
NAVI_EXTERN(size_t) navi_print_utc(const struct navi_utc_t *utc, char *buffer,
	size_t maxsize, int notnull);

//
// Prints array of mode indicators
// Returns the number of printed characters
NAVI_EXTERN(size_t) navi_print_miarray(const navi_modeindicator_t mi[], int miquant,
	char *buffer);

//
// Fills a buffer with valid characters from the given string,
// translating reserved characters to triples '^xx'.
// Returns navi_Error, if the conversion is not possible
NAVI_EXTERN(navierr_status_t) navi_print_character_field(const char *from,
	char *to, size_t maxsize);

NAVI_END_DECL

#endif // INCLUDE_navi_generator_h
