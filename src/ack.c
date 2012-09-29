/*
 * ack.c - generator and parser of ACK message
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

#include <libnavigate/ack.h>
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
// Initializes ACK sentence structure with default values
navierr_status_t navi_init_ack(struct ack_t *ack, navi_talkerid_t tid)
{
	assert(ack != NULL);

	ack->tid = tid;
	ack->alarmid = 0;

	return navi_Ok;
}

//
// Creates ACK message
navierr_status_t navi_create_ack(const struct ack_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	char bytes[4], alarmid[4];

	navi_split_integer(msg->alarmid, bytes, 3, 10);
	navi_print_decfield(bytes, 3, alarmid, sizeof(alarmid));

	*nmwritten = snprintf(buffer, maxsize, "%s", alarmid);
	return navi_Ok;
}

//
// Parses ACK message
navierr_status_t navi_parse_ack(struct ack_t *msg, char *buffer)
{
	int nmread;
	char bytes[4];

	if (navi_parse_decfield(buffer, 3, bytes, &nmread) != 0)
	{
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}

	msg->alarmid = navi_compose_integer(bytes, 3, 10);

	return navi_Ok;
}
