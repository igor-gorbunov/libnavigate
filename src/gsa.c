/*
 * gsa.c - generator and parser of GSA message
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

#include <libnavigate/gsa.h>
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
// Initializes GSA sentence structure with default values
navierr_status_t navi_init_gsa(struct gsa_t *msg)
{
	size_t i;

	assert(msg != NULL);

	msg->swmode = navi_gsa_NULL;
	msg->fixmode = -1;
	for (i = 0; i < GSA_MAX_SATELLITES; i++)
		msg->satellites[i] = -1;
	navi_init_number(&msg->pdop);
	navi_init_number(&msg->hdop);
	navi_init_number(&msg->vdop);

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates GSA message
navierr_status_t navi_create_gsa(const struct gsa_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	size_t msglength, i;

	const char *swmode;
	char bytes[2];
	char fixmode[2], satellites[12][4], pdop[16], hdop[16], vdop[16];

	msglength = strlen(swmode = navi_gsamode_str(msg->swmode));

	(void)navi_split_integer(msg->fixmode, bytes, 1, 10);
	msglength += navi_print_decfield(bytes, msg->fixmode == -1 ? 0 : 1,
		fixmode, sizeof(fixmode));

	for (i = 0; i < GSA_MAX_SATELLITES; i++)
	{
		(void)navi_split_integer(msg->satellites[i], bytes, 2, 10);
		msglength += navi_print_decfield(bytes, msg->satellites[i] == -1 ? 0 : 2,
			satellites[i], sizeof(satellites[i]));
	}

	msglength += navi_print_number(msg->pdop, pdop, sizeof(pdop));
	msglength += navi_print_number(msg->hdop, hdop, sizeof(hdop));
	msglength += navi_print_number(msg->vdop, vdop, sizeof(vdop));

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
		swmode, fixmode, satellites[0], satellites[1], satellites[2], satellites[3],
		satellites[4], satellites[5], satellites[6], satellites[7], satellites[8],
		satellites[9], satellites[10], satellites[11], pdop, hdop, vdop);

	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses GSA message
navierr_status_t navi_parse_gsa(struct gsa_t *msg, char *buffer)
{
	size_t i = 0, j, nmread;
	char bytes[2];

	if (navi_parse_gsamode(buffer + i, &msg->swmode, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_decfield(buffer + i, 1, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->fixmode = navi_compose_integer(bytes, 1, 10);
	}
	i += nmread;

	for (j = 0; j < GSA_MAX_SATELLITES; j++)
	{
		if (navi_parse_decfield(buffer + i, 2, bytes, &nmread) != 0)
		{
			if (navierr_get_last()->errclass != navi_NullField)
				return navi_Error;
		}
		else
		{
			msg->satellites[j] = navi_compose_integer(bytes, 2, 10);
		}
		i += nmread;
	}

	if (navi_parse_number(buffer + i, &msg->pdop, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->hdop, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->vdop, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}

	return navi_Ok;
}

#endif // NO_PARSER
