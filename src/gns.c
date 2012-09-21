/*
 * gns.c - generator and parser of GNS message
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

#include "gns.h"
#include "common.h"

#include <navigate.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

#ifndef NO_GENERATOR

int navi_create_gns(const struct gns_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	char utc[32], fix[64], mi[3], totalsats[3], hdop[32], antalt[32],
		geoidsep[32], ddage[32], drsid[32];

	msglength = navi_print_utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & GNS_VALID_UTC);
	msglength += navi_print_position_fix(&msg->fix, fix, sizeof(fix),
		msg->vfields & GNS_VALID_POSITION_FIX);
	msglength += navi_print_miarray(msg->mi,
		sizeof(msg->mi) / sizeof(msg->mi[0]), mi);
	msglength += snprintf(totalsats, sizeof(totalsats),
		(msg->vfields & GNS_VALID_TOTALNMOFSATELLITES) ? "%02u" : "",
		msg->totalsats);
	msglength += navi_print_number(msg->hdop, hdop, sizeof(hdop),
		msg->vfields & GNS_VALID_HDOP);
	msglength += navi_print_number(msg->antaltitude, antalt, sizeof(antalt),
		msg->vfields & GNS_VALID_ANTENNAALTITUDE);
	msglength += navi_print_number(msg->geoidalsep, geoidsep, sizeof(geoidsep),
		msg->vfields & GNS_VALID_GEOIDALSEP);
	msglength += navi_print_number(msg->diffage, ddage, sizeof(ddage),
		msg->vfields & GNS_VALID_AGEOFDIFFDATA);
	msglength += snprintf(drsid, sizeof(drsid),
		(msg->vfields & GNS_VALID_DIFFREFSTATIONID) ? "%i" : "", msg->id);

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s,%s,%s,%s",
		utc, fix, mi, totalsats, hdop, antalt, geoidsep, ddage, drsid);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

int navi_parse_gns(struct gns_t *msg, char *buffer)
{
	int i = 0, j, nmread;
	double d;

	msg->vfields = 0;

	if (navi_parse_utc(buffer + i, &msg->utc, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GNS_VALID_UTC;
	}
	i += nmread;

	if (navi_parse_position_fix(buffer + i, &msg->fix, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GNS_VALID_POSITION_FIX;
	}
	i += nmread;

	j = sizeof(msg->mi) / sizeof(msg->mi[0]);
	if (navi_parse_miarray(buffer + i, msg->mi, &j, &nmread) != 0)
	{
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->totalsats = (int)round(d);
		msg->vfields |= GNS_VALID_TOTALNMOFSATELLITES;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->hdop, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GNS_VALID_HDOP;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->antaltitude, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GNS_VALID_ANTENNAALTITUDE;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->geoidalsep, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GNS_VALID_GEOIDALSEP;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->diffage = (int)round(d);
		msg->vfields |= GNS_VALID_AGEOFDIFFDATA;
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
		msg->vfields |= GNS_VALID_DIFFREFSTATIONID;
	}

	return navi_Ok;
}

#endif // NO_PARSER
