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

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// GGA - Global positioning system (GPS) fix data
// Time, position and fix-related data for a GPS receiver.
// $--GGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_gga(const struct gga_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_gga(struct gga_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gga_h

