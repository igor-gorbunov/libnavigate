/*
 * gns.h - generator and parser of GNS message
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

#ifndef INCLUDE_navi_gns_h
#define INCLUDE_navi_gns_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// GNS - GNSS fix data
// Fix data for single or combined sattelite navigation systems (GNSS).
// $--GNS,hhmmss.ss,llll.ll,a,yyyyy.yy,a,c--c,xx,x.x,x.x,x.x,x.x,x.x*hh<cr><lf>
//

#define GNS_MODEINDICATOR_SIZE		2

struct gns_t
{
	// talker id
	navi_talkerid_t tid;

	// UTC time
	struct navi_utc_t utc;

	// latitude, longitude fix
	struct navi_position_t fix;

	// GPS, GLONASS
	int mi[GNS_MODEINDICATOR_SIZE];

	// Total number of satellites in use, 00-99
	// -1, if null field
	int nmsatellites;

	// Horizontal Dilution of Precision
	double hdop;

	// Antenna altitude, m, re:mean-sea-level (geoid)
	double antaltitude;

	// Geoidal separation, m
	double geoidalsep;

	// Age of differential data, seconds
	// -1, if null field
	int diffdata_age;

	// Differential reference station ID, 1-1023
	// -1, if null field
	int station_id;
};

NAVI_BEGIN_DECL

//
// Initializes GNS sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_gns(struct gns_t *msg, navi_talkerid_t tid);

//
// Creates GNS message
NAVI_EXTERN(navierr_status_t) navi_create_gns(const struct gns_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten);

//
// Parses GNS message
NAVI_EXTERN(navierr_status_t) navi_parse_gns(struct gns_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gns_h
