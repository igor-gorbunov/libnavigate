/*
 * zda.c - generator and parser of ZDA message
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

#include <libnavigate/zda.h>
#include <libnavigate/common.h>
#include <libnavigate/generator.h>
#include <libnavigate/parser.h>

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

//
// Initializes ZDA sentence structure with default values
navierr_status_t navi_init_zda(struct zda_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;
	msg->vfields = 0;
	navi_init_utc(0, 0, 0.0, &msg->utc);
	navi_init_date(2000, 1, 1, &msg->date);
	msg->lzoffset = 0;

	return navi_Ok;
}

#ifndef NO_GENERATOR

navierr_status_t navi_create_zda(const struct zda_t *msg, char *buffer, int maxsize, int *nmwritten)
{
	int msglength;
	char utc[32], day[3], month[3], year[5], lzhours[4], lzmins[3];

	msglength = navi_print_utc(&msg->utc, utc, sizeof(utc),
		msg->vfields & ZDA_VALID_UTC);
	msglength += snprintf(day, sizeof(day),
		(msg->vfields & ZDA_VALID_DAY) ? "%02u" : "", msg->date.day);
	msglength += snprintf(month, sizeof(month),
		(msg->vfields & ZDA_VALID_MONTH) ? "%02u" : "", msg->date.month);
	msglength += snprintf(year, sizeof(year),
		(msg->vfields & ZDA_VALID_YEAR) ? "%04u" : "", msg->date.year);

	memset(lzhours, 0, sizeof(lzhours));
	memset(lzmins, 0, sizeof(lzmins));

	// Local zone hours (00 h to +/-13 h), Local zone minutes (00 to +59)
	if (msg->vfields & ZDA_VALID_LOCALZONE)
	{
		char sign[2];
		int lz = msg->lzoffset;

		snprintf(sign, sizeof(sign), lz >= 0 ? "" : "-");
		if (lz < 0)
		{
			lz = -lz;
		}

		msglength += snprintf(lzhours, sizeof(lzhours), "%s%02d", sign, lz / 60);
		msglength += snprintf(lzmins, sizeof(lzmins), "%02u", lz % 60);
	}

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s",
		utc, day, month, year, lzhours, lzmins);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

navierr_status_t navi_parse_zda(struct zda_t *msg, char *buffer)
{
	int i = 0, nmread;
	double d;

	msg->vfields = 0;

	if (navi_parse_utc(buffer + i, &msg->utc, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= ZDA_VALID_UTC;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->date.day = (int)round(d);
		msg->vfields |= ZDA_VALID_DAY;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->date.month = (int)round(d);
		msg->vfields |= ZDA_VALID_MONTH;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->date.year = (int)round(d);
		msg->vfields |= ZDA_VALID_YEAR;
	}
	i += nmread;

	if (navi_parse_localzone(buffer + i, &msg->lzoffset, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= ZDA_VALID_LOCALZONE;
	}

	return navi_Ok;
}

#endif // NO_PARSER
