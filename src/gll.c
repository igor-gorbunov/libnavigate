/*
 * gll.c - generator and parser of GLL message
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

#include "gll.h"
#include "common.h"

#include <navigate.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

#ifndef NO_GENERATOR

int navi_create_gll(const struct gll_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	const char *status, *mi;
	char fix[64], utc[32];

	msglength = navi_print_position_fix(&msg->fix, fix, sizeof(fix),
		msg->vfields & GLL_VALID_POSITION_FIX);
	msglength += navi_print_utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & GLL_VALID_UTC);
	msglength += strlen(status = navi_status_str(msg->status));
	msglength += strlen(mi = navi_modeindicator_str(msg->mi));

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s",
		fix, utc, status, mi);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

int navi_parse_gll(struct gll_t *msg, char *buffer)
{
	int i = 0, nmread;

	msg->vfields = 0;

	if (navi_parse_position_fix(buffer + i, &msg->fix, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= GLL_VALID_POSITION_FIX;
	}
	i += nmread;

	if (navi_parse_utc(buffer + i, &msg->utc, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= GLL_VALID_UTC;
	}
	i += nmread;

	if (navi_parse_status(buffer + i, &msg->status, &nmread) != 0)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}
	i += nmread;

	if (navi_parse_modeindicator(buffer + i, &msg->mi, &nmread) != 0)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}

	return navi_Ok;
}

#endif // NO_PARSER
