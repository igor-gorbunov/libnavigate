/*
 * gst.c - generator and parser of GST message
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

#include <libnavigate/gst.h>
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
// Initializes GST sentence structure with default values
navierr_status_t navi_init_gst(struct gst_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;
	navi_init_utc(&msg->utc);
	navi_init_number(&msg->rms);
	navi_init_number(&msg->devmajor);
	navi_init_number(&msg->devminor);
	navi_init_number(&msg->orientmajor);
	navi_init_number(&msg->devlaterr);
	navi_init_number(&msg->devlonerr);
	navi_init_number(&msg->devalterr);

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates GST message
navierr_status_t navi_create_gst(const struct gst_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	size_t msglength;

	char utc[32], rms[16], devmajor[16], devminor[16], orientmajor[16],
		devlaterr[16], devlonerr[16], devalterr[16];

	msglength = navi_print_utc(&msg->utc, utc, sizeof(utc));
	msglength += navi_print_number(msg->rms, rms, sizeof(rms));
	msglength += navi_print_number(msg->devmajor, devmajor, sizeof(devmajor));
	msglength += navi_print_number(msg->devminor, devminor, sizeof(devminor));
	msglength += navi_print_number(msg->orientmajor, orientmajor, sizeof(orientmajor));
	msglength += navi_print_number(msg->devlaterr, devlaterr, sizeof(devlaterr));
	msglength += navi_print_number(msg->devlonerr, devlonerr, sizeof(devlonerr));
	msglength += navi_print_number(msg->devalterr, devalterr, sizeof(devalterr));

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s,%s,%s",
		utc, rms, devmajor, devminor, orientmajor, devlaterr, devlonerr, devalterr);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses GST message
navierr_status_t navi_parse_gst(struct gst_t *msg, char *buffer)
{
	size_t i = 0, nmread;

	if (navi_parse_utc(buffer + i, &msg->utc, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->rms, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->devmajor, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->devminor, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->orientmajor, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->devlaterr, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->devlonerr, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->devalterr, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}

	return navi_Ok;
}

#endif // NO_PARSER
