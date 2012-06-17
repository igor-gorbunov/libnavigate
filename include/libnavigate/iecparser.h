/*
 * iecparser.h - interface to IEC message parser
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

#ifndef IEC_PARSER_H
#define IEC_PARSER_H

#include <libnavigate/iecmessage.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//
// Parser of IEC 61162-1 (2000-07) messages
//
// Parses next IEC sentence up to <cr><lf>, given in *buffer, and
// stores the result to *msg which has the maximum size of msgsize.
// The type of parsed message is stored to *msgtype.
// Returns the number of characters parsed, or -errno code in case of error
//
int IecParseMessage(char *buffer, size_t maxsize, size_t msgsize,
	void *msg, enum naviSentence_t *msgtype);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // IEC_PARSER_H

