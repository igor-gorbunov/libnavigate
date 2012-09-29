/*
 * gbs.c - generator and parser of GBS message
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

#include "libnavigate/gbs.h"
#include "libnavigate/common.h"

#include <navigate.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

#ifndef NO_GENERATOR

int navi_create_gbs(const struct gbs_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	char bytes[2];
	char utc[32], experrlat[32], experrlon[32], experralt[32],
		id[4], probability[32], estimate[32], deviation[32];

	msglength = navi_print_utc(&msg->utc, utc, sizeof(utc), 1);
	msglength += navi_print_number(msg->experrlat, experrlat, sizeof(experrlat),
		msg->vfields & GBS_VALID_EXPERRLATLON);
	msglength += navi_print_number(msg->experrlon, experrlon, sizeof(experrlon),
		msg->vfields & GBS_VALID_EXPERRLATLON);
	msglength += navi_print_number(msg->experralt, experralt, sizeof(experralt),
		msg->vfields & GBS_VALID_EXPERRALT);

	(void)navi_split_integer(msg->id, bytes, 2, 10);
	msglength += navi_print_decfield(bytes, msg->vfields & GBS_VALID_ID ? 2 : 0,
		id, sizeof(id));

	msglength += navi_print_number(msg->probability, probability, sizeof(probability),
		msg->vfields & GBS_VALID_PROBABILITY);
	msglength += navi_print_number(msg->estimate, estimate, sizeof(estimate),
		msg->vfields & GBS_VALID_ESTIMATE);
	msglength += navi_print_number(msg->deviation, deviation, sizeof(deviation),
		msg->vfields & GBS_VALID_DEVIATION);

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s,%s,%s", utc,
		experrlat, experrlon, experralt, id, probability, estimate, deviation);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

int navi_parse_gbs(struct gbs_t *msg, char *buffer)
{
	int i = 0, nmread;
	char bytes[4];

	msg->vfields = 0;

	if (navi_parse_utc(buffer + i, &msg->utc, &nmread) != 0)
	{
		return navi_Error;
	}
	i += nmread;

	msg->experrlat = 0.;
	if (navi_parse_number(buffer + i, &msg->experrlat, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GBS_VALID_EXPERRLATLON;
	}
	i += nmread;

	msg->experrlon = 0.;
	if (navi_parse_number(buffer + i, &msg->experrlon, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GBS_VALID_EXPERRLATLON;
	}
	i += nmread;

	msg->experralt = 0.;
	if (navi_parse_number(buffer + i, &msg->experralt, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GBS_VALID_EXPERRALT;
	}
	i += nmread;

	if (navi_parse_decfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->id = navi_compose_integer(bytes, 2, 10);
		msg->vfields |= GBS_VALID_ID;
	}
	i += nmread;

	msg->probability = 0.;
	if (navi_parse_number(buffer + i, &msg->probability, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GBS_VALID_PROBABILITY;
	}
	i += nmread;

	msg->estimate = 0.;
	if (navi_parse_number(buffer + i, &msg->estimate, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GBS_VALID_ESTIMATE;
	}
	i += nmread;

	msg->deviation = 0.;
	if (navi_parse_number(buffer + i, &msg->deviation, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GBS_VALID_DEVIATION;
	}

	return navi_Ok;
}

#endif // NO_PARSER

