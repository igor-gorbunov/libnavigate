/*
 * dtm.h - generator and parser of DTM message
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

#ifndef INCLUDE_navi_dtm_h
#define INCLUDE_navi_dtm_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// DTM - Datum reference
// Local geodetic datum and datum offsets from a reference datum. This sentence
// is used to define the datum to which a position location, and geographic
// locations in subsequent sentences, are referenced. Lattitude, longitude and
// altitude offsets from the reference datum, and the selection of the reference
// datum, are also provided.
// $--DTM,ccc,a,x.x,a,x.x,a,x.x,ccc*hh<cr><lf>
//

struct dtm_t
{
	// talker id
	navi_talkerid_t tid;

	// local datum
	navi_datum_t local_dtm;

	// local datum subdivision code
	navi_datum_subdivision_t local_dtmsd;

	// latitude offset, min, N/S
	struct navi_offset_t lat_offset;

	// longitude offset, min, E/W
	struct navi_offset_t long_offset;

	// altitude offset, m
	double alt_offset;

	// reference datum
	navi_datum_t reference_dtm;
};

NAVI_BEGIN_DECL

//
// Initializes DTM sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_dtm(struct dtm_t *msg, navi_talkerid_t tid);

//
// Creates DTM message
NAVI_EXTERN(navierr_status_t) navi_create_dtm(const struct dtm_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten);

//
// Parses DTM message
NAVI_EXTERN(navierr_status_t) navi_parse_dtm(struct dtm_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_dtm_h
