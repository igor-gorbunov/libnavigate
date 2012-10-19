/*
 * gga.c - generator and parser of GGA message
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

#include <libnavigate/gga.h>
#include <libnavigate/common.h>

#include <navigate.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

//
// Initializes GGA sentence structure with default values
navierr_status_t navi_init_gga(struct gga_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;
	msg->vfields = 0;
	navi_init_utc(&msg->utc);
	navi_init_position(&msg->fix);
	msg->gpsindicator = navi_gps_Invalid;
	msg->nmsatellites = 0;
	msg->hdop = 0.0;
	msg->antaltitude = 0.0;
	msg->geoidalsep = 0.0;
	msg->diffage = 0;
	msg->id = 0;

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates GGA message
navierr_status_t navi_create_gga(const struct gga_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	size_t msglength;

	char bytes[4];
	char utc[32], fix[64], qi[2], nmsats[3], hdop[32], antalt[32],
		geoidsep[32], ddage[32], id[32];

	msglength = navi_print_utc(&msg->utc, utc, sizeof(utc));
	msglength += navi_print_position_fix(&msg->fix, fix, sizeof(fix));

	(void)navi_split_integer(msg->gpsindicator, bytes, 1, 10);
	msglength += navi_print_decfield(bytes, 1, qi, sizeof(qi));

	(void)navi_split_integer(msg->nmsatellites, bytes, 2, 10);
	msglength += navi_print_decfield(bytes,
		msg->vfields & GGA_VALID_NMSATELLITES ? 2 : 0, nmsats, sizeof(nmsats));

	msglength += navi_print_number(msg->hdop, hdop, sizeof(hdop),
		msg->vfields & GGA_VALID_HDOP);
	msglength += navi_print_number(msg->antaltitude, antalt, sizeof(antalt),
		msg->vfields & GGA_VALID_ANTALTITUDE);
	msglength += navi_print_number(msg->geoidalsep, geoidsep, sizeof(geoidsep),
		msg->vfields & GGA_VALID_GEOIDALSEP);
	msglength += navi_print_number(msg->diffage, ddage, sizeof(ddage),
		msg->vfields & GGA_VALID_DIFFAGE);

	(void)navi_split_integer(msg->id, bytes, 4, 10);
	msglength += navi_print_decfield(bytes,
		msg->vfields & GGA_VALID_ID ? 4 : 0, id, sizeof(id));

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
		utc, fix, qi, nmsats, hdop, antalt, "M", geoidsep, "M", ddage, id);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses GGA message
navierr_status_t navi_parse_gga(struct gga_t *msg, char *buffer)
{
	size_t i = 0, nmread;
	double d;
	char bytes[4];

	msg->vfields = 0;

	if (navi_parse_utc(buffer + i, &msg->utc, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GGA_VALID_UTC;
	}
	i += nmread;

	if (navi_parse_position_fix(buffer + i, &msg->fix, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_decfield(buffer + i, 1, bytes, &nmread) != 0)
		return navi_Error;
	else
		msg->gpsindicator = navi_compose_integer(bytes, 1, 10);
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->nmsatellites = navi_compose_integer(bytes, 2, 10);
		msg->vfields |= GGA_VALID_NMSATELLITES;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->hdop, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GGA_VALID_HDOP;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->antaltitude, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GGA_VALID_ANTALTITUDE;
	}
	i += nmread + 2;	// skip 'M,'

	if (navi_parse_number(buffer + i, &msg->geoidalsep, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GGA_VALID_GEOIDALSEP;
	}
	i += nmread + 2;	// skip 'M,'

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->diffage = (int)round(d);
		msg->vfields |= GGA_VALID_DIFFAGE;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->id = (int)round(d);
		msg->vfields |= GGA_VALID_ID;
	}

	return navi_Ok;
}

#endif // NO_PARSER
