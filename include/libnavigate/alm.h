/*
 * alm.h - generator and parser of ALM message
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

#ifndef INCLUDE_navi_alm_h
#define INCLUDE_navi_alm_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// ALM - GPS almanac data
// Contains GPS week number, satellite health and the complete almanac data
// for one satellite. Multiple messages may be transmitted, one for each
// satellite in the GPS constellation, up to a maximum of 32 messages.
// $--ALM,x.x,x.x,xx,x.x,hh,hhhh,hh,hhhh,hhhh,hhhhhh,hhhhhh,hhhhhh,hhhhhh,hhh,hhh*hh<cr><lf>
//

#define ALM_MAX_SATELLITES		32

//
// Holds GPS almanac data for one satellite
struct navi_gpsalm_t
{
	// valid fields, bitwise or of GPSALM_VALID_xxx
	unsigned int vfields;
	// 01 to 32
	unsigned int satelliteprn;
	// 0 to 9999
	unsigned int gpsweek;
	// SV health
	unsigned int svhealth;
	// eccentricity
	unsigned int e;
	// almanac reference time
	unsigned int toa;
	// inclination angle
	unsigned int sigmai;
	// rate of right ascension
	unsigned int omegadot;
	// root of semi-major axis
	unsigned int sqrtsemiaxis;
	// argument of perigee
	unsigned int omega;
	// longitude of ascension node
	unsigned int omega0;
	// mean anomaly
	unsigned int m0;
	// clock parameter
	unsigned int af0;
	// clock parameter
	unsigned int af1;
};

#define GPSALM_VALID_GPSWEEK			0x001
#define GPSALM_VALID_SVHEALTH			0x002
#define GPSALM_VALID_E					0x004
#define GPSALM_VALID_TOA				0x008
#define GPSALM_VALID_SIGMAI				0x010
#define GPSALM_VALID_OMEGADOT			0x020
#define GPSALM_VALID_SQRTSEMIAXIS		0x040
#define GPSALM_VALID_OMEGA				0x080
#define GPSALM_VALID_OMEGA0				0x100
#define GPSALM_VALID_M0					0x200
#define GPSALM_VALID_AF0				0x400
#define GPSALM_VALID_AF1				0x800

//
// Holder of information for all the almanacs
struct alm_t
{
	// talker id
	navi_talkerid_t tid;

	// total number of messages
	int totalnm;

	// number of received message
	int msgnm;

	// almanacs of a GPS satellite
	struct navi_gpsalm_t alm;
};

NAVI_BEGIN_DECL

//
// Initializes ALM sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_alm(struct alm_t *msg, navi_talkerid_t tid);

#ifndef NO_GENERATOR

//
// Creates ALM message
NAVI_EXTERN(navierr_status_t) navi_create_alm(const struct alm_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten);

//
// Creates ALM message sequence from satellites array
NAVI_EXTERN(navierr_status_t) navi_create_alm_sequence(navi_talkerid_t tid, int nmofsatellites,
	const struct navi_gpsalm_t almanaclist[], char *buffer, size_t maxsize, size_t *nmwritten);

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses ALM message
NAVI_EXTERN(navierr_status_t) navi_parse_alm(struct alm_t *msg, char *buffer);

#endif // NO_PARSER

NAVI_END_DECL

#endif // INCLUDE_navi_alm_h
