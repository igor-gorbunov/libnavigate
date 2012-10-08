/*
 * ack.h - generator and parser of ACK message
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

#ifndef INCLUDE_navi_ack_h
#define INCLUDE_navi_ack_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// ACK - Acknowledge alarm
//
// Acknowledge device alarm.
// $--ACK,xxx*hh<cr><lf>
//

struct ack_t
{
	navi_talkerid_t tid;	// talker identifier
	int alarmid;			// local alarm number
};

NAVI_BEGIN_DECL

//
// Initializes ACK sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_ack(struct ack_t *msg, navi_talkerid_t tid);

//
// Creates ACK message
NAVI_EXTERN(navierr_status_t) navi_create_ack(const struct ack_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten);

//
// Parses ACK message
NAVI_EXTERN(navierr_status_t) navi_parse_ack(struct ack_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_ack_h
