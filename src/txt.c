/*
 * txt.c - generator and parser of TXT message
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

#include <libnavigate/txt.h>
#include <libnavigate/common.h>
#include <libnavigate/generator.h>
#include <libnavigate/parser.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

//
// Initializes TXT sentence structure with default values
navierr_status_t navi_init_txt(struct txt_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;
	msg->totalnm = msg->msgnm = msg->textid = 1;
	memset(msg->textmsg, 0, sizeof(msg->textmsg));

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates TXT message
navierr_status_t navi_create_txt(const struct txt_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	size_t msglength;

	char bytes[4];
	char totalnm[4], msgnm[4], textid[4], textmsg[80];

	navi_split_integer(msg->totalnm, bytes, 2, 10);
	msglength = navi_print_decfield(bytes, 2, totalnm, sizeof(totalnm));

	navi_split_integer(msg->msgnm, bytes, 2, 10);
	msglength += navi_print_decfield(bytes, 2, msgnm, sizeof(msgnm));

	navi_split_integer(msg->textid, bytes, 2, 10);
	msglength += navi_print_decfield(bytes, 2, textid, sizeof(textid));

	if (navi_print_character_field(msg->textmsg, textmsg, sizeof(textmsg)) != navi_Ok)
		return navi_Error;
	msglength += strlen(textmsg);

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s", totalnm, msgnm,
		textid, textmsg);
	return navi_Ok;
}

//
// Creates TXT message sequence rom text string
navierr_status_t navi_create_txt_sequence(navi_talkerid_t tid, int textid,
	const char *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	int i, j, k;
	int totalnm, messagenm;
	size_t offset = 0, nmofcharswritten = 0;

	struct txt_t txt;

	i = 0, j = 0;
	while (i < MAX_TEXT_SIZE && msg[i] != '\0')
	{
		switch (navi_get_character_type(msg[i++]))
		{
		case navi_char_Valid:
			j += 1;
			break;
		default:
			j += 3;
			break;
		}
	}

	if (j >= MAX_TEXT_SIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	i = 0;
	totalnm = j / MAX_TEXT_MESSAGE_SIZE + (j % MAX_TEXT_MESSAGE_SIZE ? 1 : 0);
	for (messagenm = 1; messagenm <= totalnm; messagenm++)
	{
		navi_init_txt(&txt, tid);
		txt.totalnm = totalnm;
		txt.msgnm = messagenm;
		txt.textid = textid;

		j = k = 0;
		while (j < MAX_TEXT_MESSAGE_SIZE && msg[i] != '\0')
		{
			j += navi_get_character_type(msg[i]) == navi_char_Valid ? 1 : 3;
			txt.textmsg[k++] = msg[i++];
		}

		if (navi_create_msg(navi_TXT, &txt, buffer + offset, maxsize - offset, &nmofcharswritten) != navi_Ok)
			return navi_Error;
		offset += nmofcharswritten;
	}

	*nmwritten = offset;
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses TXT message
navierr_status_t navi_parse_txt(struct txt_t *msg, char *buffer)
{
	size_t i = 0, nmread;
	char bytes[4];

	if (navi_parse_decfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	msg->totalnm = navi_compose_integer(bytes, 2, 10);
	i += nmread;

	if (navi_parse_decfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	msg->msgnm = navi_compose_integer(bytes, 2, 10);
	i += nmread;

	if (navi_parse_decfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	msg->textid = navi_compose_integer(bytes, 2, 10);
	i += nmread;

	if (navi_parse_character_field(buffer + i, msg->textmsg,
		sizeof(msg->textmsg), &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}

	return navi_Ok;
}

#endif // NO_PARSER
