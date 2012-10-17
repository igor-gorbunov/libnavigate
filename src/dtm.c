/*
 * dtm.c - generator and parser of DTM message
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

#include <libnavigate/dtm.h>
#include <libnavigate/common.h>

#include <navigate.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

//
// Initializes DTM sentence structure with default values
navierr_status_t navi_init_dtm(struct dtm_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;

	msg->vfields = 0;

	msg->local_dtm = navi_datum_NULL;
	msg->local_dtmsd = navi_datumsub_NULL;
	navi_init_offset(&msg->lat_offset);
	navi_init_offset(&msg->long_offset);
	msg->alt_offset = 0.0;
	msg->reference_dtm = navi_datum_NULL;

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates DTM message
navierr_status_t navi_create_dtm(const struct dtm_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	size_t msglength;

	const char *ldatum, *rdatum, *datumsd, *latsign, *lonsign;
	char latofs[32], lonofs[32], altofs[32];

	msglength = strlen(ldatum = navi_datum_str(msg->local_dtm));
	msglength += strlen(datumsd = navi_datumsubdiv_str(msg->local_dtmsd));
	msglength += navi_print_number(msg->lat_offset.offset * 60., latofs,
		sizeof(latofs), msg->lat_offset.sign != navi_offset_NULL);
	msglength += strlen(latsign = navi_fixsign_str(msg->lat_offset.sign));
	msglength += navi_print_number(msg->long_offset.offset * 60., lonofs,
		sizeof(lonofs), msg->long_offset.sign != navi_offset_NULL);
	msglength += strlen(lonsign = navi_fixsign_str(msg->long_offset.sign));
	msglength += navi_print_number(msg->alt_offset, altofs,
		sizeof(altofs), msg->vfields & DTM_VALID_ALTOFFSET);
	msglength += strlen(rdatum = navi_datum_str(msg->reference_dtm));

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s,%s,%s",
		ldatum, datumsd, latofs, latsign, lonofs, lonsign, altofs, rdatum);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses DTM message
navierr_status_t navi_parse_dtm(struct dtm_t *msg, char *buffer)
{
	size_t i = 0, nmread;

	msg->vfields = 0;

	if (navi_parse_datum(buffer + i, &msg->local_dtm, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_datumsub(buffer + i, &msg->local_dtmsd, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	i += nmread;

	if (navi_parse_offset(buffer + i, &msg->lat_offset, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->lat_offset.offset /= 60.0;
	}
	i += nmread;

	if (navi_parse_offset(buffer + i, &msg->long_offset, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->long_offset.offset /= 60.0;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->alt_offset, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->vfields |= DTM_VALID_ALTOFFSET;
	}
	i += nmread;

	if (navi_parse_datum(buffer + i, &msg->reference_dtm, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}

	return navi_Ok;
}

#endif // NO_PARSER
