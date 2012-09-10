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

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

#ifndef NO_GENERATOR

int navi_create_gns(const struct gns_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	const char *talkerid;
	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], utc[32], fix[64], mi[3],
		totalsats[3], hdop[32], antalt[32], geoidsep[32], ddage[32],
		drsid[32], cs[3];

	msglength = strlen(talkerid = navi_talkerid_str(msg->tid));

	msglength += IecPrint_Utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & GNS_VALID_UTC);

	msglength += navi_print_position_fix(&msg->fix, fix, sizeof(fix),
		msg->vfields & GNS_VALID_POSITION_FIX);

	msglength += IecPrint_ModeIndicatorArray(msg->mi, mi, sizeof(mi),
		msg->vfields & GNS_VALID_MODEINDICATOR);
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

	msglength += 23;
	if (msglength > NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg),
		"$%sGNS,%s,%s,%s,%s,%s,%s,%s,%s,%s*%s\r\n", talkerid, utc, fix, mi,
		totalsats, hdop, antalt, geoidsep, ddage, drsid, "%s");
	IecPrint_Checksum(iecmsg, msglength, cs);

	*nmwritten = snprintf(buffer, maxsize, iecmsg, cs);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

int navi_parse_gns(struct gns_t *msg, char *buffer)
{
	int result;
	int index = 1, nmread;
	double d;

	msg->vfields = 0;

	if (navi_parse_utc(buffer + index, &msg->utc, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= GNS_VALID_UTC;
	}
	index += nmread;

	if (navi_parse_position_fix(buffer + index, &msg->fix, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= GNS_VALID_POSITION_FIX;
	}

	index += nmread;

	result = IecParse_ModeIndicatorArray(buffer + index, msg->mi, &nmread);
	if (result != navi_Ok)
	{
		return navi_InvalidMessage;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;

	if (navi_parse_number(buffer + index, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->totalsats = (int)round(d);
		msg->vfields |= GNS_VALID_TOTALNMOFSATELLITES;
	}
	index += nmread;

	if (navi_parse_number(buffer + index, &msg->hdop, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= GNS_VALID_HDOP;
	}
	index += nmread;

	if (navi_parse_number(buffer + index, &msg->antaltitude, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= GNS_VALID_ANTENNAALTITUDE;
	}
	index += nmread;

	if (navi_parse_number(buffer + index, &msg->geoidalsep, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= GNS_VALID_GEOIDALSEP;
	}
	index += nmread;

	if (navi_parse_number(buffer + index, &msg->diffage, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= GNS_VALID_AGEOFDIFFDATA;
	}
	index += nmread;

	if (navi_parse_number(buffer + index, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->id = (int)round(d);
		msg->vfields |= GNS_VALID_DIFFREFSTATIONID;
	}
	index += nmread;

	return navi_Ok;
}

#endif // NO_PARSER
