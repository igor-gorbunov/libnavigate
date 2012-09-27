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

#include <libnavigate/generic.h>
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
navi_char_type_t navi_get_character_type(int c);

//
// Removes trailing zeroes in a variable length value
// string representation up to and including decimal point
// Returns the remaining string length
int remove_trailing_zeroes(char *buffer, int length);

#ifdef WIN32
extern double round(double x);
#endif // WIN32

//
// Print fixed length field with given radix
extern int navi_print_fixedfield(const char bytes[], int fieldwidth, int radix,
	char *buffer, int maxsize);

//
// Splits an integer into array of digits. Radix may be 10 or 16.
// Most significant digit is put at bytes[0]
extern int navi_split_integer(unsigned int value, char bytes[], int width, int radix);

//
// Composes an integer from array of digits. Radix may be 10 or 16.
// Most significant digit is taken from bytes[0]
//
// Returns the combined value
extern unsigned int navi_compose_integer(char bytes[], int width, int radix);

//
// Talker IDs list
extern const char *navi_tidlist[];

//
// Approved sentence formatters list
extern const char *navi_fmtlist[];

NAVI_END_DECL

#endif // INCLUDE_navi_common_h
