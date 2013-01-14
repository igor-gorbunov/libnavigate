/*
 * proprietarymsg.c - proprietary messages handling utilities
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

#include <stdio.h>
#include <string.h>

#include <libnavigate/proprietarymsg.h>
#include <libnavigate/common.h>
#include <libnavigate/sentence.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

static proprietary_msg_generator_t user_generator_callback = NULL;
static proprietary_msg_parser_t user_parser_callback = NULL;

//
// Registers proprietary message generator
//
navierr_status_t navi_register_proprietary_generator(proprietary_msg_generator_t callback)
{
	if (callback == NULL)
	{
		navierr_set_last(navi_InvalidParameter);
		return navi_Error;
	}
	else
	{
		user_generator_callback = callback;
		return navi_Ok;
	}
}

//
// Unregisters proprietary message generator
//
navierr_status_t navi_unregister_proprietary_generator()
{
	user_generator_callback = NULL;
	return navi_Ok;
}

//
// Registers proprietary message parser
//
navierr_status_t navi_register_proprietary_parser(proprietary_msg_parser_t callback)
{
	if (callback == NULL)
	{
		navierr_set_last(navi_InvalidParameter);
		return navi_Error;
	}
	else
	{
		user_parser_callback = callback;
		return navi_Ok;
	}
}

//
// Unregisters proprietary message parser
//
navierr_status_t navi_unregister_proprietary_parser()
{
	user_parser_callback = NULL;
	return navi_Ok;
}

//
// Creates proprietary message, if the user proprietary message generator is registered
//
navierr_status_t navi_create_proprietary(const void *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	const char *tid = "P";
	char msgbody[NAVI_SENTENCE_MAXSIZE + 1], csstr[3];

	size_t msglen = 0;

	if (user_generator_callback == NULL)
	{
		navierr_set_last(navi_MsgNotSupported);
		return navi_Error;
	}

	if (user_generator_callback(msg, msgbody, sizeof(msgbody), &msglen) != navi_Ok)
		return navi_Error;

	if (msglen + 12 > NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	if (msglen + 12 > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	msglen = snprintf(buffer, maxsize, "$%s%s*", tid, msgbody);
	if (navi_checksum(buffer, msglen, csstr, NULL) != navi_Ok)
		return navi_Error;
	strcat(buffer, csstr);
	strcat(buffer, "\r\n");

	*nmwritten = msglen + 4;

	return navi_Ok;
}

//
// Parses proprietary message, if the user proprietary message parser is registered
//
navierr_status_t navi_parse_proprietary(void *msg, char *buffer)
{
	if (user_parser_callback == NULL)
	{
		navierr_set_last(navi_MsgNotSupported);
		return navi_Error;
	}

	return user_parser_callback(msg, buffer + 1);
}
