/*
 * gsa.h - generator and parser of GSA message
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

#ifndef INCLUDE_navi_gsa_h
#define INCLUDE_navi_gsa_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// GSA - GNSS DOP and active satellites
// GNSS receiver operating mode, satellites used in the navigation solution
// reported by the GGA or GNS sentences, and DOP values.
// $--GSA,a,x,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,x.x,x.x,x.x*hh<cr><lf>
//

#define GSA_MAX_SATELLITES	12

struct gsa_t
{
	navi_talkerid_t tid;	// talker id
	unsigned int vfields;	// valid fields, bitwise or of GSA_VALID_xxx
	navi_gsaswitchmode_t swmode;	// Mode: Manula or Automatic
	int fixmode;			// Mode: 1 = fix not available, 2 = 2D, 3 = 3D
	struct
	{
		int notnull;		// 0 = null field, 1 = not null
		int id;				// ID number of satellite used in solution
	} satellites[GSA_MAX_SATELLITES];	// satellites ID numbers array
	double pdop;			// Position dilution of precision
	double hdop;			// Horizontal dilution of precision
	double vdop;			// Vertical dilution of precision
};

#define GSA_VALID_SWITCHMODE	0x01
#define GSA_VALID_FIXMODE		0x02
#define GSA_VALID_PDOP			0x04
#define GSA_VALID_HDOP			0x08
#define GSA_VALID_VDOP			0x10

NAVI_BEGIN_DECL

//
// Initializes GSA sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_gsa(struct gsa_t *msg, navi_talkerid_t tid);

//
// Creates GSA message
NAVI_EXTERN(navierr_status_t) navi_create_gsa(const struct gsa_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten);

//
// Parses GSA message
NAVI_EXTERN(navierr_status_t) navi_parse_gsa(struct gsa_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gsa_h
