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

#include <libnavigate/gbs.h>
#include <libnavigate/common.h>

#include <navigate.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

//
// Initializes GBS sentence structure with default values
navierr_status_t navi_init_gbs(struct gbs_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;
	navi_init_utc(&msg->utc);
	navi_init_number(&msg->experrlat);
	navi_init_number(&msg->experrlon);
	navi_init_number(&msg->experralt);
	msg->failed_id = -1;
	navi_init_number(&msg->probability);
	navi_init_number(&msg->estimate);
	navi_init_number(&msg->deviation);

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates GBS message
navierr_status_t navi_create_gbs(const struct gbs_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	size_t msglength;

	char bytes[2];
	char utc[32], experrlat[32], experrlon[32], experralt[32],
		id[4], probability[32], estimate[32], deviation[32];

	msglength = navi_print_utc(&msg->utc, utc, sizeof(utc));
	msglength += navi_print_number(msg->experrlat, experrlat, sizeof(experrlat));
	msglength += navi_print_number(msg->experrlon, experrlon, sizeof(experrlon));
	msglength += navi_print_number(msg->experralt, experralt, sizeof(experralt));

	(void)navi_split_integer(msg->failed_id, bytes, 2, 10);
	msglength += navi_print_decfield(bytes, msg->failed_id == -1 ? 0 : 2,
		id, sizeof(id));

	msglength += navi_print_number(msg->probability, probability, sizeof(probability));
	msglength += navi_print_number(msg->estimate, estimate, sizeof(estimate));
	msglength += navi_print_number(msg->deviation, deviation, sizeof(deviation));

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

//
// Parses GBS message
navierr_status_t navi_parse_gbs(struct gbs_t *msg, char *buffer)
{
	size_t i = 0, nmread;
	char bytes[4];

	if (navi_parse_utc(buffer + i, &msg->utc, &nmread) != navi_Ok)
	{
		return navi_Error;
	}
	i += nmread;

	msg->experrlat = 0.;
	if (navi_parse_number(buffer + i, &msg->experrlat, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	msg->experrlon = 0.;
	if (navi_parse_number(buffer + i, &msg->experrlon, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	msg->experralt = 0.0;
	if (navi_parse_number(buffer + i, &msg->experralt, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_decfield(buffer + i, 2, bytes, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->failed_id = navi_compose_integer(bytes, 2, 10);
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->probability, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->estimate, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->deviation, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}

	return navi_Ok;
}

#endif // NO_PARSER
