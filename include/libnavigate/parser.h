/*
 * parser.h - interface to IEC message parser
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

#ifndef INCLUDE_navi_parser_h
#define INCLUDE_navi_parser_h

#include "generic.h"
#include "sentence.h"

NAVI_BEGIN_DECL

//
// Parser of IEC 61162-1 (2000-07) messages
//
// Parses the next IEC sentence up to <cr><lf> read from buffer.
// Stores the result to msg which has the maximum size of msgsize.
// The type of parsed message is stored to msgtype and the number of
// parsed characters is put to nmread.
// Returns the analysis status
//
NAVI_EXTERN(int) navi_parse_msg(char *buffer, int maxsize, int msgsize,
		void *msg, int *msgtype, int *nmread);

//
// Parses offset field in the form of 'x.x,a | ,'.
// The field must end with ',' or '*'
//
// @param pointer to the first byte of field
// @param out pointer to structure where the result is stored
// @param pointer to variable where the number of read bytes is stored
// @return 0 on success, or navi_Error if it's null or an error occured. Call
// navierr_get_last() to check the error
//
NAVI_EXTERN(int) navi_parse_offset(char *buffer,
		struct navi_offset_t *offset, int *nmread);

//
// Parses position fix in the form of 'llll.ll,a,yyyyy.yy,a | ,,,'.
// The field must end with ',' or '*'
//
// @returns 0 if parsed successfully, or navi_Error in the case of an error
//
NAVI_EXTERN(int) navi_parse_position_fix(char *buffer,
		struct navi_position_t *fix, int *nmread);

//
// Parses UTC time in the form of 'hhmmss.ss' of null field.
// The field must end with ',' or '*'
//
// @returns 0 if parsed successfully, or navi_Error in the case of an error
//
NAVI_EXTERN(int) navi_parse_utc(char *buffer, struct navi_utc_t *utc,
		int *nmread);

//
// Parses status in the form of 'A | V'. Shall not be null field.
// The field must end with ',' or '*'
//
// @returns 0 if parsed successfully, or navi_Error in the case of an error
//
NAVI_EXTERN(int) navi_parse_status(char *buffer, int *status, int *nmread);

//
// Parses mode indicator in the form of 'A | D | E | M | S | N'.
// Shall not be null field. The field must end with ',' or '*'
//
// @returns 0 if parsed successfully, or navi_Error in the case of an error
//
NAVI_EXTERN(int) navi_parse_modeindicator(char *buffer, int *mi, int *nmread);

//
// Parses variable numbers in the form of '[+|-]x[.x]'.
// May be null field. The field must end with ',' or '*'
//
// @returns 0 if parsed successfully, or navi_Error in the case of an error
//
NAVI_EXTERN(int) navi_parse_number(char *buffer, double *parsed, int *nmread);

//
// Parses datum field in the form of 'ccc'
// May be null field. The field must end with ',' or '*'
//
// @returns 0 if parsed successfully, or navi_Error in the case of an error
//
NAVI_EXTERN(int) navi_parse_datum(char *buffer, int *datum, int *nmread);

//
// Parses datum subdivision code field in the form of 'a'.
// May be null field. The field must end with ',' or '*'
//
// @returns 0 if parsed successfully, or navi_Error in the case of an error
//
NAVI_EXTERN(int) navi_parse_datumsub(char *buffer, int *datumsub, int *nmread);

//
// Parses mode indicator array in the form of 'c--c'.
// May not be null field. The field must end with ',' or '*'
//
// @returns 0 if parsed successfully, or navi_Error in the case of an error
//
NAVI_EXTERN(int) navi_parse_miarray(char *buffer, int mi[], int *misize, int *nmread);

//
// Parses date in the form of 'ddmmyy | ddmmyyyy'
// May be null field. The field must end with ',' or '*'
//
// @returns 0 if parsed successfully, or navi_Error in the case of an error
//
NAVI_EXTERN(int) navi_parse_date(char *buffer, struct navi_date_t *date, int *nmread);

//
// Parses local zone in the form of '[+|-]dd,dd'.
// May be null field. The field must end with ',' or '*'
//
// @returns 0 if parsed successfully, or navi_Error in the case of an error
//
NAVI_EXTERN(int) navi_parse_localzone(char *buffer, int *offset, int *nmread);

//
// Calculates the checksum of a message between the '$' and
// '*' characters. Returns both string and binary representation.
// Either csstr or cs may be NULL, if the return value is not
// used.
//
// @returns 0 if parsed successfully, or navi_Error in the case of an error
//
NAVI_EXTERN(int) navi_checksum(char *msg, int maxsize, char *csstr, unsigned *cs);

//
// Determines the talker id and sentence formatter
NAVI_EXTERN(int) navi_parse_address(char *buffer, int *tid, int *msgtype);

//
// Looks up Talker ID
NAVI_EXTERN(int) navi_parse_talkerid(char *buffer, int *nmread);

//
// Looks up sentence formatter
NAVI_EXTERN(int) navi_parse_sentencefmt(char *buffer, int *nmread);

NAVI_END_DECL

#endif // INCLUDE_navi_parser_h
