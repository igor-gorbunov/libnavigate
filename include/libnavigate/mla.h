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

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// MLA - GLONASS almanac data
// Contains complete almanac data for one GLONASS satellite.
// $--MLA,x.x,x.x,xx,x.x,hh,hhhh,hh,hhhh,hhhh,hhhhhh,hhhhhh,hhhhhh,hhhhhh,hhh,hhh*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_mla(const struct mla_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_mla(struct mla_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_mla_h

