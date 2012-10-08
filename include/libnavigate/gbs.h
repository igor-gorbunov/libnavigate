/*
 * gbs.h - generator and parser of GBS message
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

#ifndef INCLUDE_navi_gbs_h
#define INCLUDE_navi_gbs_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// GBS - GNSS satellite fault detection
// This message shall be used for reporting RAIM information.
// $--GBS,hhmmss.ss,x.x,x.x,x.x,xx,x.x,x.x,x.x*hh<cr><lf>
//

struct gbs_t
{
	navi_talkerid_t tid;	// talker id
	unsigned int vfields;	// valid fields, bitwise or of GBS_VALID_xxx
	struct navi_utc_t utc;	// UTC time
	double experrlat;		// expected error in latitude
	double experrlon;		// expected error in longitude
	double experralt;		// expected error in altitude
	int id;					// ID number of most likely failed satellite
	double probability;		// probability of missed detection for most likely
							// failed satellite
	double estimate;		// estimate of bias on most likely failed satellite
	double deviation;		// standard deviation of bias estimate
};

#define GBS_VALID_EXPERRLATLON	0x01
#define GBS_VALID_EXPERRALT		0x02
#define GBS_VALID_ID			0x04
#define GBS_VALID_PROBABILITY	0x08
#define GBS_VALID_ESTIMATE		0x10
#define GBS_VALID_DEVIATION		0x20

NAVI_BEGIN_DECL

//
// Initializes GBS sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_gbs(struct gbs_t *msg, navi_talkerid_t tid);

//
// Creates GBS message
NAVI_EXTERN(navierr_status_t) navi_create_gbs(const struct gbs_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten);

//
// Parses GBS message
NAVI_EXTERN(navierr_status_t) navi_parse_gbs(struct gbs_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gbs_h
