/*
 * gsv.h - generator and parser of GSV message
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

#ifndef INCLUDE_navi_gsv_h
#define INCLUDE_navi_gsv_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// GSV - GNSS satellites in view
// Number of satellites in view, satellite ID numbers, elevation, azimuth and
// SNR value. Four satellites maximum per transmission. Null fields are not
// required for unused sets when less than four sets are transmitted.
// $--GSV,x,x,xx,xx,xx,xxx,xx......,xx,xx,xxx,xx*hh<cr><lf>
//

#define GSV_MAX_SATELLITES_PER_MESSAGE	4
#define GSV_MAX_SATELLITES				(9 * GSV_MAX_SATELLITES_PER_MESSAGE)

//
// Holds satellite information for one satellite
//
struct navi_satinfo_t
{
	unsigned int vfields;	// valid fields, bitwise or of SATINFO_VALID_xxx
	unsigned int id;		// satellite ID number (if id == 0, the structure is empty)
	unsigned int elevation;	// degrees 00-90
	unsigned int azimuth;	// degrees true, 000-359
	unsigned int snr;		// signal-to-noise ratio, 00-99 dB-Hz, null if not tracking
};

#define SATINFO_VALID_ORIENTATION	0x1
#define SATINFO_VALID_SNR			0x2

struct gsv_t
{
	navi_talkerid_t tid;	// talker id
	int totalnm;		// total number of messages
	int msgnm;			// number of received message
	int nmsatellites;	// total number of satellites in view, -1 if null

	// satellite info array
	struct navi_satinfo_t info[GSV_MAX_SATELLITES_PER_MESSAGE];
};

NAVI_BEGIN_DECL

#ifndef NO_GENERATOR

//
// Initializes GSV sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_gsv(struct gsv_t *msg, navi_talkerid_t tid);

//
// Creates GSV message
NAVI_EXTERN(navierr_status_t) navi_create_gsv(const struct gsv_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten);

//
// Creates GSV message sequence from satellites array
NAVI_EXTERN(navierr_status_t) navi_create_gsv_sequence(navi_talkerid_t tid, int nmofsatellites,
	const struct navi_satinfo_t satlist[], char *buffer, size_t maxsize, size_t *nmwritten);

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses GSV message
NAVI_EXTERN(navierr_status_t) navi_parse_gsv(struct gsv_t *msg, char *buffer);

#endif // NO_PARSER

NAVI_END_DECL

#endif // INCLUDE_navi_gsv_h
