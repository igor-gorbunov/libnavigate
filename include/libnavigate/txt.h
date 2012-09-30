/*
 * txt.h - generator and parser of TXT message
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

#ifndef INCLUDE_navi_txt_h
#define INCLUDE_navi_txt_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// TXT - Text transmission
//
// For the transmission of short messages.
// $--TXT,xx,xx,xx,c--c*hh<cr><lf>
//

struct txt_t
{
	navi_talkerid_t tid;	// talker identifier
	int totalnm;		// total number of messages (01-99)
	int msgnm;			// message number (01-99)
	int textid;			// text identifier (01-99)
	char textmsg[62];	// text message
};

NAVI_BEGIN_DECL

//
// Initializes TXT sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_txt(struct txt_t *msg, navi_talkerid_t tid);

//
// Creates TXT message
NAVI_EXTERN(navierr_status_t) navi_create_txt(const struct txt_t *msg, char *buffer,
	int maxsize, int *nmwritten);

//
// Parses TXT message
NAVI_EXTERN(navierr_status_t) navi_parse_txt(struct txt_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_txt_h
