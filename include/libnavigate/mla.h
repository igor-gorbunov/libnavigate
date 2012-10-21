/*
 * mla.h - generator and parser of MLA message
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

#ifndef INCLUDE_navi_mla_h
#define INCLUDE_navi_mla_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// MLA - GLONASS almanac data
// Contains complete almanac data for one GLONASS satellite.
// $--MLA,x.x,x.x,xx,x.x,hh,hhhh,hh,hhhh,hhhh,hhhhhh,hhhhhh,hhhhhh,hhhhhh,hhh,hhh*hh<cr><lf>
//

#define MLA_MAX_SATELLITES		32

//
// Holds GLONASS almanac data for one satellite
//
struct navi_gloalm_t
{
	unsigned vfields;	// valid fields, bitwise or of GLOALM_VALID_xxx
	unsigned satslot;	// 01 to 24
	unsigned daycount;	// calendar day count within the four-year period,
						// beginning with the previous leap year
	unsigned svhealth;	// generalized health and carrier frequency number
	unsigned e;			// eccentricity
	unsigned dot;		// rate of change of the draconic circling time
	unsigned omega;		// argument of perigee
	unsigned tauc_high;	// 16 MSB of system time scale correction
	unsigned deltat;	// correction to the average value of the
						// draconic circling time
	unsigned t;			// time of the ascension node almanac reference time
	unsigned lambda;	// Greenwich longitude of the ascension node
	unsigned deltai;	// correction to the average value of the inclination angle
	unsigned tauc_low;	// 12 LSB of system time scale correction
	unsigned taun;		// course value of the time scale shift
};

#define GLOALM_VALID_DAYCOUNT		0x001
#define GLOALM_VALID_SVHEALTH		0x002
#define GLOALM_VALID_E				0x004
#define GLOALM_VALID_DOT			0x008
#define GLOALM_VALID_OMEGA			0x010
#define GLOALM_VALID_TAUC			0x020
#define GLOALM_VALID_DELTAT			0x040
#define GLOALM_VALID_T				0x080
#define GLOALM_VALID_LAMBDA			0x100
#define GLOALM_VALID_DELTAI			0x200
#define GLOALM_VALID_TAUN			0x400

//
// Holder of information for all the almanacs
struct mla_t
{
	// talker id
	navi_talkerid_t tid;

	// total number of messages
	int totalnm;

	// number of received message
	int msgnm;

	// almanac of a GLONASS satellite
	struct navi_gloalm_t alm;
};

NAVI_BEGIN_DECL

//
// Initializes MLA sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_mla(struct mla_t *msg, navi_talkerid_t tid);

#ifndef NO_GENERATOR

//
// Creates MLA message
NAVI_EXTERN(navierr_status_t) navi_create_mla(const struct mla_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten);

//
// Creates MLA message sequence from satellites array
NAVI_EXTERN(navierr_status_t) navi_create_mla_sequence(navi_talkerid_t tid, int nmofsatellites,
	const struct navi_gloalm_t almanaclist[], char *buffer, size_t maxsize, size_t *nmwritten);

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses MLA message
NAVI_EXTERN(navierr_status_t) navi_parse_mla(struct mla_t *msg, char *buffer);

#endif // NO_PARSER

NAVI_END_DECL

#endif // INCLUDE_navi_mla_h
