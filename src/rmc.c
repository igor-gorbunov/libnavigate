/*
 * rmc.c - generator and parser of RMC message
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

#include <libnavigate/rmc.h>
#include <libnavigate/common.h>
#include <libnavigate/generator.h>
#include <libnavigate/parser.h>

#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

//
// Initializes RMC sentence structure with default values
navierr_status_t navi_init_rmc(struct rmc_t *msg)
{
	assert(msg != NULL);

	msg->vfields = 0;
	navi_init_utc(&msg->utc);
	msg->status = navi_status_V;
	navi_init_position(&msg->fix);
	navi_init_number(&msg->speedN);
	navi_init_number(&msg->courseT);
	navi_init_date(2000, 1, 1, &msg->date);
	navi_init_offset(&msg->magnVariation);
	msg->mi = navi_DataNotValid;

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates RMC message
navierr_status_t navi_create_rmc(const struct rmc_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	size_t msglength;

	const char *status, *mi;
	char utc[32], fix[64], snots[32], ctrue[32], day[3],
		month[3], year[3], magnetic[32];

	msglength = navi_print_utc(&msg->utc, utc, sizeof(utc));
	msglength += strlen(status = navi_status_str(msg->status));
	msglength += navi_print_position_fix(&msg->fix, fix, sizeof(fix));
	msglength += navi_print_number(msg->speedN, snots, sizeof(snots));
	msglength += navi_print_number(msg->courseT, ctrue, sizeof(ctrue));
	msglength += snprintf(day, sizeof(day),
		(msg->vfields & RMC_VALID_DATE) ? "%02u" : "", msg->date.day);
	msglength += snprintf(month, sizeof(month),
		(msg->vfields & RMC_VALID_DATE) ? "%02u" : "", msg->date.month);
	msglength += snprintf(year, sizeof(year),
		(msg->vfields & RMC_VALID_DATE) ? "%02u" : "", msg->date.year % 100);
	msglength += navi_print_offset(&msg->magnVariation, magnetic, sizeof(magnetic));
	msglength += strlen(mi = navi_modeindicator_str(msg->mi));

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s%s%s,%s,%s",
		utc, status, fix, snots, ctrue, day, month, year, magnetic, mi);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses RMC message
navierr_status_t navi_parse_rmc(struct rmc_t *msg, char *buffer)
{
	size_t i = 0, nmread;

	msg->vfields = 0;

	if (navi_parse_utc(buffer + i, &msg->utc, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_status(buffer + i, &msg->status, &nmread) != navi_Ok)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}
	i += nmread;

	if (navi_parse_position_fix(buffer + i, &msg->fix, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->speedN, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->courseT, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_date(buffer + i, &msg->date, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= RMC_VALID_DATE;
	}
	i += nmread;

	if (navi_parse_offset(buffer + i, &msg->magnVariation, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_modeindicator(buffer + i, &msg->mi, &nmread) != navi_Ok)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return navi_Error;
	}

	return navi_Ok;
}

#endif // NO_PARSER
