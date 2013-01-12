/*
 * gll.h - generator and parser of GLL message
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

#ifndef INCLUDE_navi_gll_h
#define INCLUDE_navi_gll_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// GLL - Geographic position - latitude/longitude
// Latitude and longitude of vessel position, time of
// position fix and status.
// $--GLL,llll.ll,a,yyyyy.yy,a,hhmmss.ss,A,a*hh<cr><lf>
//

struct gll_t
{
	// talker id
	navi_talkerid_t tid;

	// latitude, longitude fix
	struct navi_position_t fix;

	// UTC time
	struct navi_utc_t utc;

	// status
	navi_status_t status;

	// mode indicator
	navi_modeindicator_t mi;
};

NAVI_BEGIN_DECL

//
// Initializes GLL sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_gll(struct gll_t *msg, navi_talkerid_t tid);

//
// Creates GLL message
NAVI_EXTERN(navierr_status_t) navi_create_gll(const struct gll_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten);

//
// Parses GLL message
NAVI_EXTERN(navierr_status_t) navi_parse_gll(struct gll_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gll_h
