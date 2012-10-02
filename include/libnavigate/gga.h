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
	navi_talkerid_t tid;	// talker id
	unsigned int vfields;	// valid fields, bitwise or of GGA_VALID_xxx
	struct navi_utc_t utc;	// UTC time
	struct navi_position_t fix;	// latitude, longitude fix
	navi_gpsindicator_t gpsindicator;	// GPS quality indicator
	int nmsatellites;		// Number of satellites in use (00-12)
	double hdop;			// Horizontal dilution of precision
	double antaltitude;		// Antenna altitude above/below mean sea level (geoid)
	double geoidalsep;		// Geoidal separation
	int diffage;			// Age of differential GPS data, seconds
	int id;					// Differential reference station ID, 1-1023
};

#define GGA_VALID_UTC				0x01
#define GGA_VALID_FIX				0x02
#define GGA_VALID_NMSATELLITES		0x04
#define GGA_VALID_HDOP				0x08
#define GGA_VALID_ANTALTITUDE		0x10
#define GGA_VALID_GEOIDALSEP		0x20
#define GGA_VALID_DIFFAGE			0x40
#define GGA_VALID_ID				0x80

NAVI_BEGIN_DECL

//
// Initializes GGA sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_gga(struct gga_t *msg, navi_talkerid_t tid);

//
// Creates GGA message
NAVI_EXTERN(navierr_status_t) navi_create_gga(const struct gga_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten);

//
// Parses GGA message
NAVI_EXTERN(navierr_status_t) navi_parse_gga(struct gga_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gga_h
