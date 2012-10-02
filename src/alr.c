/*
 * alr.c - generator and parser of ALR message
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

#include <libnavigate/alr.h>
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
// Initializes ALR sentence structure with default values
navierr_status_t navi_init_alr(struct alr_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;
	navi_init_utc(0, 0, 0.0, &msg->utc);
	msg->alarmid = 0;
	msg->condition = navi_status_V;
	msg->ackstate = navi_status_V;
	memset(msg->description, 0, sizeof(msg->description));

	return navi_Ok;
}

//
// Creates ALR message
navierr_status_t navi_create_alr(const struct alr_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	size_t msglength;

	const char *condition, *ackstate;
	char bytes[4];
	char utc[32], alarmid[4], description[80];

	msglength = navi_print_utc(&msg->utc, utc, sizeof(utc), 1);

	navi_split_integer(msg->alarmid, bytes, 3, 10);
	msglength += navi_print_decfield(bytes, 3, alarmid, sizeof(alarmid));

	msglength += strlen(condition = navi_status_str(msg->condition));
	msglength += strlen(ackstate = navi_status_str(msg->ackstate));

	if (navi_print_character_field(msg->description, description,
		sizeof(description)) != navi_Ok)
		return navi_Error;
	msglength += strlen(description);

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s", utc, alarmid,
		condition, ackstate, description);
	return navi_Ok;
}

//
// Parses ALR message
navierr_status_t navi_parse_alr(struct alr_t *msg, char *buffer)
{
	size_t i = 0, nmread;
	char bytes[4];

	if (navi_parse_utc(buffer + i, &msg->utc, &nmread) != 0)
		return navi_Error;
	i += nmread;

	if (navi_parse_decfield(buffer + i, 3, bytes, &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	msg->alarmid = navi_compose_integer(bytes, 3, 10);
	i += nmread;

	if (navi_parse_status(buffer + i, &msg->condition, &nmread) != 0)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_status(buffer + i, &msg->ackstate, &nmread) != 0)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_character_field(buffer + i, msg->description,
		sizeof(msg->description), &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}

	return navi_Ok;
}
