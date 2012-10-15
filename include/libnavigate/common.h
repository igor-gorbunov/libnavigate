/*
 * common.h - common utilities for generator and parser
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

#ifndef INCLUDE_navi_common_h
#define INCLUDE_navi_common_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

NAVI_BEGIN_DECL

//
// Meters per second to knots (nautical mile per hour)
#define MPS_TO_KNOTS(mps)		(mps * 1.94384449)

//
// Meters per second to km/h convertion coefficient
#define MPS_TO_KMPH(mps)		(mps * 3.600)

//
// Knots (nautical mile per hour) to meters per second
#define KNOTS_TO_MPS(knots)		(knots * 0.514444445)

//
// km/h to meters per second convertion coefficient
#define KMPH_TO_MPS(kmph)		(kmph * 0.277777777777777778)


//
// Transmitted data consists of ASCII characters.
// There are several groups of characters.
enum _navi_char_type_t
{
	// these characters shall not be transmitted at any time
	navi_char_Undefined = -1,

	// these characters are used for specific formatting
	// purposes and shall not be used in data fields
	navi_char_Reserved = 0,

	// this set consists of all printable ASCII characters,
	// except those marked as reserved
	navi_char_Valid = 1
};

typedef int navi_char_type_t;

//
// Checks and returns the type of given character
NAVI_EXTERN(navi_char_type_t) navi_get_character_type(int c);

//
// Fills utc structure with given values
NAVI_EXTERN(navierr_status_t) navi_init_utc(int hh, int mm, double ss,
	struct navi_utc_t *utc);

//
// Fills date structure with given values
NAVI_EXTERN(navierr_status_t) navi_init_date(int yy, int mm, int dd,
	struct navi_date_t *date);

//
// Fills position fix structure with null value.
NAVI_EXTERN(navierr_status_t) navi_init_position(struct navi_position_t *fix);

//
// Fills position fix structure with given values in degrees.
// Latitude is provided in the range of [-pi/2, +pi/2] and the result is within
// [90°S, 90°N].
// The longitude is provided in the range of [-pi, +2pi) and result is within
// [180°W, 180°E). Thus, the input range of [0, +pi) is treated as [0, 180°E)
// and the ranges of [-pi, 0) or [+pi, +2pi] are [180°W, 0].
NAVI_EXTERN(navierr_status_t) navi_init_position_from_degrees(double latitude,
	double longitude, struct navi_position_t *fix);

//
// Fills position fix structure with given values in radians.
// Latitude is provided in the range of [-pi/2, +pi/2] and the result is within
// [90°S, 90°N].
// The longitude is provided in the range of [-pi, +2pi) and result is within
// [180°W, 180°E). Thus, the input range of [0, +pi) is treated as [0, 180°E)
// and the ranges of [-pi, 0) or [+pi, +2pi] are [180°W, 0].
NAVI_EXTERN(navierr_status_t) navi_init_position_from_radians(double latitude,
	double longitude, struct navi_position_t *fix);

//
// Fills offset structure with given values in degrees.
NAVI_EXTERN(navierr_status_t) navi_init_offset_from_degrees(double offset,
	navi_offset_sign_t sign, struct navi_offset_t *ofs);

//
// Fills position fix structure with given values in radians.
NAVI_EXTERN(navierr_status_t) navi_init_offset_from_radians(double offset,
	navi_offset_sign_t sign, struct navi_offset_t *ofs);

//
// Removes trailing zeroes in a variable length value
// string representation up to and including decimal point
// Returns the remaining string length
NAVI_EXTERN(size_t) remove_trailing_zeroes(char *buffer, size_t length);

//
// Splits an integer into array of digits. Radix may be 10 or 16.
// Most significant digit is put at bytes[0]
NAVI_EXTERN(navierr_status_t) navi_split_integer(unsigned int value, char bytes[], int width, int radix);

//
// Composes an integer from array of digits. Radix may be 10 or 16.
// Most significant digit is taken from bytes[0]
//
// Returns the combined value
NAVI_EXTERN(unsigned int) navi_compose_integer(char bytes[], int width, int radix);

//
// Calculates the checksum of a message between the '$' and
// '*' characters. Returns both string and binary representation.
// Either csstr or cs may be NULL, if the return value is not
// used.
//
// @returns 0 if parsed successfully, or navi_Error in the case of an error
//
NAVI_EXTERN(navierr_status_t) navi_checksum(char *msg, size_t maxsize,
	char *csstr, unsigned int *cs);

NAVI_END_DECL

#endif // INCLUDE_navi_common_h
