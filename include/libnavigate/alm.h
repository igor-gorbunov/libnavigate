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

/*! @file alm.h
 *  @brief Declares the structure and handling utilities for ALM sentence.
 *
 *  Contains declarations for structure, initilizer, generator and parser
 *  of ALM sentence.
 */

#ifndef INCLUDE_navi_alm_h
#define INCLUDE_navi_alm_h

#include "sentence.h"

#define ALM_MAX_SATELLITES		32

/*! @brief ALM - GPS almanac data
 *
 * Contains GPS week number, satellite health and the complete almanac data
 * for one satellite. Multiple messages may be transmitted, one for each
 * satellite in the GPS constellation, up to a maximum of 32 messages.
 * $--ALM,x.x,x.x,xx,x.x,hh,hhhh,hh,hhhh,hhhh,hhhhhh,hhhhhh,hhhhhh,hhhhhh,hhh,hhh*hh[cr][lf]
 */
struct navi_gpsalm_t
{
	unsigned int vfields;		//!< valid fields, bitwise or of GPSALM_VALID_xxx
	unsigned int satelliteprn;	//!< 01 to 32
	unsigned int gpsweek;		//!< 0 to 9999
	unsigned int svhealth;		//!< sattelite in view health
	unsigned int e;				//!< eccentricity
	unsigned int toa;			//!< almanac reference time
	unsigned int sigmai;		//!< inclination angle
	unsigned int omegadot;		//!< rate of right ascension
	unsigned int sqrtsemiaxis;	//!< root of semi-major axis
	unsigned int omega;			//!< argument of perigee
	unsigned int omega0;		//!< longitude of ascension node
	unsigned int m0;			//!< mean anomaly
	unsigned int af0;			//!< clock parameter
	unsigned int af1;			//!< clock parameter
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

/*! @brief Holds information for all the almanacs
 *
 */
struct alm_t
{
	int totalnm;		//!< total number of messages
	int msgnm;			//!< number of received message
	struct navi_gpsalm_t alm;	//!< almanacs of a GPS satellite
};

NAVI_BEGIN_DECL

//
// Initializes ALM sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_alm(struct alm_t *msg);

#ifndef NO_GENERATOR

//
// Creates ALM message
NAVI_EXTERN(navierr_status_t) navi_create_alm(const struct alm_t *msg,
	char *buffer, size_t maxsize, size_t *nmwritten);

//
// Creates ALM message sequence from satellites array
NAVI_EXTERN(navierr_status_t) navi_create_alm_sequence(navi_talkerid_t tid,
	int nmofsatellites, const struct navi_gpsalm_t almanaclist[],
	char *buffer, size_t maxsize, size_t *nmwritten);

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses ALM message
NAVI_EXTERN(navierr_status_t) navi_parse_alm(struct alm_t *msg, char *buffer);

#endif // NO_PARSER

NAVI_END_DECL

#endif // INCLUDE_navi_alm_h
