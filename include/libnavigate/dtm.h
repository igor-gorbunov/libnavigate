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
	navi_talkerid_t tid;	// talker id
	unsigned int vfields;	// valid fields, bitwise or of DTM_VALID_xxx
	navi_datum_t locdatum;	// local datum
	navi_datum_subdivision_t locdatumsub;	// local datum subdivision code
	struct navi_offset_t latofs;	// latitude offset, min, N/S
	struct navi_offset_t lonofs;	// longitude offset, min, E/W
	double altoffset;		// altitude offset, m
	navi_datum_t refdatum;	// reference datum
};

#define DTM_VALID_LOCALDATUM		0x01
#define DTM_VALID_LOCALDATUMSUB		0x02
#define DTM_VALID_OFFSET			0x04
#define DTM_VALID_ALTOFFSET			0x08
#define DTM_VALID_REFDATUM			0x10

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
