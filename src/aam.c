/*
 * aam.c - generator and parser of AAM message
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

#include "aam.h"

#include <assert.h>
#include <string.h>

//
// navi_init_aam
//
navierr_status_t navi_init_aam(struct aam_t *aam, navi_talkerid_t tid)
{
	assert(aam != NULL);

	aam->tid = tid;
	aam->circle = navi_status_V;
	aam->perp = navi_status_V;
	aam->radius = 0.;
	memset(aam->wpid, 0, sizeof(aam->wpid));

	return navi_Ok;
}
