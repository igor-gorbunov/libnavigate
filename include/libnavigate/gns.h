/*
 * gns.h - generator and parser of GNS message
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

#ifndef INCLUDE_navi_gns_h
#define INCLUDE_navi_gns_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// GNS - GNSS fix data
// Fix data for single or combined sattelite navigation systems (GNSS).
// $--GNS,hhmmss.ss,llll.ll,a,yyyyy.yy,a,c--c,xx,x.x,x.x,x.x,x.x,x.x*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_gns(const struct gns_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_gns(struct gns_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gns_h
