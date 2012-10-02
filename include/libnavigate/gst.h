/*
 * gst.h - generator and parser of GST message
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

#ifndef INCLUDE_navi_gst_h
#define INCLUDE_navi_gst_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// GST - GNSS pseudorange noise statistics
// This message is used to support RAIM.
// $--GST,hhmmss.ss,x.x,x.x,x.x,x.x,x.x,x.x,x.x*hh<cr><lf>
//

struct gst_t
{
	navi_talkerid_t tid;	// talker id
	unsigned int vfields;	// valid fields, bitwise or of GST_VALID_xxx
	struct navi_utc_t utc;	// UTC time
	double rms;			// RMS value of the standard deviation
	double devmajor;	// Standard deviation of semi-major axis of error ellipse, m
	double devminor;	// Standard deviation of semi-minor axis of error ellipse, m
	double orientmajor;	// Orientation of semi-major axis of error ellipse,
						// degrees from true north
	double devlaterr;	// Standard deviation of latitude error, m
	double devlonerr;	// Standard deviation of longitude error, m
	double devalterr;	// Standard deviation of altitude error, m
};

#define GST_VALID_RMS				0x1
#define GST_VALID_STDDEVELLIPSE		0x2
#define GST_VALID_DEVLATLONERR		0x4
#define GST_VALID_DEVALTERR			0x8

NAVI_BEGIN_DECL

//
// Initializes GST sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_gst(struct gst_t *msg, navi_talkerid_t tid);

//
// Creates GST message
NAVI_EXTERN(navierr_status_t) navi_create_gst(const struct gst_t *msg, char *buffer,
	int maxsize, int *nmwritten);

//
// Parses GST message
NAVI_EXTERN(navierr_status_t) navi_parse_gst(struct gst_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gst_h
