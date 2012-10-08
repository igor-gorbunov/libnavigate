/*
 * errors.h - library error status utilities
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

#ifndef INCLUDE_navi_errors_h
#define INCLUDE_navi_errors_h

#include <libnavigate/generic.h>

NAVI_BEGIN_DECL

//
// Return statuses for libnavigate methods
//
enum _navierr_status_t
{
	navi_Error = -1,		// error
	navi_Ok = 0				// no error
};

//
// Error classes
//
enum _navierr_class_t
{
	navi_Undefined = 0,			// undefined or no error
	navi_MsgExceedsMaxSize = 1,	// message too long
	navi_CrcEror = 2,			// crc error
	navi_NotEnoughBuffer = 3,	// not enough space in output buffer
	navi_MsgNotSupported = 4,	// message type not supported
	navi_NoValidMessage = 5,	// no valid message in buffer
	navi_NullField = 6,			// null field in a message, where it is not allowed
	navi_InvalidMessage = 7,	// message does not conform to protocol
	navi_NotImplemented = 8,	// method not implemented
	navi_InvalidParameter = 9	// invalid parameter to method
};

typedef int navierr_status_t;
typedef int navierr_class_t;

typedef struct _navi_error_t
{
	navierr_class_t errclass;
} navi_error_t;

/**
 * Return the pointer to 'navi_error_t' object that holds the last library error
 * that occurred for this thread.
 */
NAVI_EXTERN(const navi_error_t *) navierr_get_last(void);

NAVI_EXTERN(void) navierr_set_last(navierr_class_t errclass);

NAVI_END_DECL

#endif // INCLUDE_navi_errors_h
