/*
 * gga.h - generator and parser of GGA message
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

#ifndef INCLUDE_navi_gga_h
#define INCLUDE_navi_gga_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// GGA - Global positioning system (GPS) fix data
// Time, position and fix-related data for a GPS receiver.
// $--GGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh<cr><lf>
//

struct gga_t
{
	// UTC time
	struct navi_utc_t utc;

	// latitude, longitude fix
	struct navi_position_t fix;

	// GPS quality indicator
	navi_gpsindicator_t gpsindicator;

	// Number of satellites in use (00-12)
	// -1, if null field
	int nmsatellites;

	// Horizontal dilution of precision
	double hdop;

	// Antenna altitude above/below mean sea level (geoid)
	double antaltitude;

	// Geoidal separation
	double geoidalsep;

	// Age of differential GPS data, seconds
	// -1, if null field
	int diffdata_age;

	// Differential reference station ID, 1-1023
	// -1, if null field
	int station_id;
};

NAVI_BEGIN_DECL

//
// Initializes GGA sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_gga(struct gga_t *msg);

//
// Creates GGA message
NAVI_EXTERN(navierr_status_t) navi_create_gga(const struct gga_t *msg,
	char *buffer, size_t maxsize, size_t *nmwritten);

//
// Parses GGA message
NAVI_EXTERN(navierr_status_t) navi_parse_gga(struct gga_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gga_h
