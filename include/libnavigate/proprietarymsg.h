/*
 * proprietarymsg.h - proprietary messages handling utilities
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

#ifndef INCLUDE_navi_proprietarymsg_h
#define INCLUDE_navi_proprietarymsg_h

#include "errors.h"

NAVI_BEGIN_DECL

typedef navierr_status_t (*proprietary_msg_generator_t)
	(const void *msg, char *buffer, size_t maxsize, size_t *nmwritten);

typedef navierr_status_t (*proprietary_msg_parser_t)
	(void *msg, char *buffer);

//
// Registers proprietary message generator
//
NAVI_EXTERN(navierr_status_t) navi_register_proprietary_generator(proprietary_msg_generator_t callback);

//
// Unregisters proprietary message generator
//
NAVI_EXTERN(navierr_status_t) navi_unregister_proprietary_generator();

//
// Registers proprietary message parser
//
NAVI_EXTERN(navierr_status_t) navi_register_proprietary_parser(proprietary_msg_parser_t callback);

//
// Unregisters proprietary message parser
//
NAVI_EXTERN(navierr_status_t) navi_unregister_proprietary_parser();

//
// Creates proprietary message, if the user proprietary message generator is registered
//
NAVI_EXTERN(navierr_status_t) navi_create_proprietary(const void *msg, char *buffer, size_t maxsize, size_t *nmwritten);

//
// Parses proprietary message, if the user proprietary message parser is registered
//
NAVI_EXTERN(navierr_status_t) navi_parse_proprietary(void *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_proprietarymsg_h
