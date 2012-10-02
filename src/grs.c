/*
 * grs.c - generator and parser of GRS message
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

#include <libnavigate/grs.h>
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
// Initializes GRS sentence structure with default values
navierr_status_t navi_init_grs(struct grs_t *msg, navi_talkerid_t tid)
{
	int i;

	assert(msg != NULL);

	msg->tid;
	navi_init_utc(0, 0, 0.0, &msg->utc);
	msg->mode = 0;
	for (i = 0; i < GRS_MAX_SATELLITES; i++)
		msg->residuals[i].notnull = 0,
		msg->residuals[i].residual = 0.0;

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates GRS message
navierr_status_t navi_create_grs(const struct grs_t *msg, char *buffer, int maxsize, int *nmwritten)
{
	int msglength, i;

	char bytes[2];
	char utc[32], mode[2], residuals[12][32];

	msglength = navi_print_utc(&msg->utc, utc, sizeof(utc), 1);

	(void)navi_split_integer(msg->mode, bytes, 1, 10);
	msglength += navi_print_decfield(bytes, 1, mode, sizeof(mode));

	for (i = 0; i < GRS_MAX_SATELLITES; i++)
	{
		if (msg->residuals[i].notnull && (fabs(msg->residuals[i].residual) > 99.9))
		{
			msglength += navi_print_number((int)msg->residuals[i].residual, residuals[i],
				sizeof(residuals[i]), msg->residuals[i].notnull);
		}
		else
		{
			msglength += navi_print_number(msg->residuals[i].residual, residuals[i],
				sizeof(residuals[i]), msg->residuals[i].notnull);
		}
	}

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
		utc, mode, residuals[0], residuals[1], residuals[2], residuals[3],
		residuals[4], residuals[5], residuals[6], residuals[7], residuals[8],
		residuals[9], residuals[10], residuals[11]);

	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses GRS message
navierr_status_t navi_parse_grs(struct grs_t *msg, char *buffer)
{
	int i = 0, j, nmread;
	char bytes[2];

	if (navi_parse_utc(buffer + i, &msg->utc, &nmread) != 0)
		return navi_Error;
	i += nmread;

	if (navi_parse_decfield(buffer + i, 1, bytes, &nmread) != 0)
		return navi_Error;
	else
		msg->mode = navi_compose_integer(bytes, 1, 10);
	i += nmread;

	for (j = 0; j < GRS_MAX_SATELLITES; j++)
	{
		msg->residuals[j].notnull = 0;

		if (navi_parse_number(buffer + i, &msg->residuals[j].residual, &nmread) != 0)
		{
			if (navierr_get_last()->errclass != navi_NullField)
				return navi_Error;
		}
		else
		{
			msg->residuals[j].notnull = 1;
		}
		i += nmread;
	}

	return navi_Ok;
}

#endif // NO_PARSER
