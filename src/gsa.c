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

#include "gsa.h"
#include "common.h"

#include <navigate.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

#ifndef NO_GENERATOR

int navi_create_gsa(const struct gsa_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength, i;

	const char *swmode;
	char bytes[2];
	char fixmode[2], satellites[12][4], pdop[16], hdop[16], vdop[16];

	msglength = strlen(swmode = navi_gsamode_str(msg->switchmode,
		msg->vfields & GSA_VALID_SWITCHMODE));

	(void)navi_split_integer(msg->fixmode, bytes, 1, 10);
	msglength += navi_print_decfield(bytes,
		msg->vfields & GSA_VALID_SWITCHMODE ? 1 : 0, fixmode, sizeof(fixmode));

	for (i = 0; i < 12; i++)
	{
		(void)navi_split_integer(msg->satellites[i].id, bytes, 2, 10);
		msglength += navi_print_decfield(bytes,
			msg->satellites[i].notnull ? 2 : 0, satellites[i], sizeof(satellites[i]));
	}

	msglength += navi_print_number(msg->pdop, pdop, sizeof(pdop),
		msg->vfields & GSA_VALID_PDOP);
	msglength += navi_print_number(msg->hdop, hdop, sizeof(hdop),
		msg->vfields & GSA_VALID_HDOP);
	msglength += navi_print_number(msg->vdop, vdop, sizeof(vdop),
		msg->vfields & GSA_VALID_VDOP);

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

int navi_parse_gsa(struct gsa_t *msg, char *buffer)
{
	int i = 0, j, nmread;
	char bytes[2];

	msg->vfields = 0;

	if (navi_parse_gsamode(buffer + i, &msg->switchmode, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GSA_VALID_SWITCHMODE;
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
		msg->vfields |= GSA_VALID_FIXMODE;
	}
	i += nmread;

	for (j = 0; j < 12; j++)
	{
		msg->satellites[j].notnull = 0;

		if (navi_parse_decfield(buffer + i, 2, bytes, &nmread) != 0)
		{
			if (navierr_get_last()->errclass != navi_NullField)
				return navi_Error;
		}
		else
		{
			msg->satellites[j].notnull = 1;
			msg->satellites[j].id = navi_compose_integer(bytes, 2, 10);
		}
		i += nmread;
	}

	if (navi_parse_number(buffer + i, &msg->pdop, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GSA_VALID_PDOP;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->hdop, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GSA_VALID_HDOP;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->vdop, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= GSA_VALID_VDOP;
	}

	return navi_Ok;
}

#endif // NO_PARSER

