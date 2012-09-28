/*
 * rmc.h - generator and parser of RMS message
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

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// RMC - Recommended minimum specific GNSS data
// Time, date, position, course and speed data provided by a GNSS navigation
// receiver. This sentence is transmitted at intervals not exceeding 2 s and is
// always accompanied by RMB when a destination waypoint is active. RMC and RMB
// are the recommended minimum data to be provided by a GNSS receiver. All data
// fields must be provided, null fields used only when data is temporarily
// unavailable.
// $--RMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxxxx,x.x,a,a*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_rmc(const struct rmc_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_rmc(struct rmc_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_rmc_h
