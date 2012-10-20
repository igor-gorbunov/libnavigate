/*
 * rmc.h - generator and parser of RMC message
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

#ifndef INCLUDE_navi_rmc_h
#define INCLUDE_navi_rmc_h

#include <libnavigate/errors.h>
#include <libnavigate/sentence.h>

//
// RMC - Recommended minimum specific GNSS data
// Time, date, position, course and speed data provided by a GNSS navigation
// receiver.
// $--RMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxxxx,x.x,a,a*hh<cr><lf>
//
struct rmc_t
{
	// talker id
	navi_talkerid_t tid;

	unsigned int vfields;

	// UTC time
	struct navi_utc_t utc;

	// status
	navi_status_t status;

	// latitude, longitude fix
	struct navi_position_t fix;

	// Speed over ground, knots
	double speedN;

	// Course over ground, degrees true
	double courseT;

	// Day (01 to 31), Month (01 to 12), Year (UTC)
	struct navi_date_t date;

	// Magnetic variation, degrees,E/W
	struct navi_offset_t magnVariation;

	// mode indicator
	navi_modeindicator_t mi;
};

#define RMC_VALID_DATE				0x10

NAVI_BEGIN_DECL

//
// Initializes RMC sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_rmc(struct rmc_t *msg, navi_talkerid_t tid);

//
// Creates RMC message
NAVI_EXTERN(navierr_status_t) navi_create_rmc(const struct rmc_t *msg, char *buffer,
	size_t maxsize, size_t *nmwritten);

//
// Parses RMC message
NAVI_EXTERN(navierr_status_t) navi_parse_rmc(struct rmc_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_rmc_h
