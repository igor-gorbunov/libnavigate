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

#include "dtm.h"
#include "common.h"

#include <navigate.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

#ifndef NO_GENERATOR

int navi_create_dtm(const struct dtm_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	const char *ldatum, *rdatum, *datumsd, *latsign, *lonsign;
	char latofs[32], lonofs[32], altofs[32];

	msglength = strlen(ldatum = navi_datum_str(msg->locdatum,
		msg->vfields & DTM_VALID_LOCALDATUM));
	msglength += strlen(datumsd = navi_datumsubdiv_str(msg->locdatumsub,
		msg->vfields & DTM_VALID_LOCALDATUMSUB));
	msglength += navi_print_number(msg->latofs.offset, latofs,
		sizeof(latofs), msg->vfields & DTM_VALID_OFFSET);
	msglength += strlen(latsign = navi_fixsign_str(msg->latofs.sign,
		msg->vfields & DTM_VALID_OFFSET));
	msglength += navi_print_number(msg->lonofs.offset, lonofs,
		sizeof(lonofs), msg->vfields & DTM_VALID_OFFSET);
	msglength += strlen(lonsign = navi_fixsign_str(msg->lonofs.sign,
		msg->vfields & DTM_VALID_OFFSET));
	msglength += navi_print_number(msg->altoffset, altofs,
		sizeof(altofs), msg->vfields & DTM_VALID_ALTOFFSET);
	msglength += strlen(rdatum = navi_datum_str(msg->refdatum,
		msg->vfields & DTM_VALID_REFDATUM));

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

int navi_parse_dtm(struct dtm_t *msg, char *buffer)
{
	int i = 0, nmread;

	msg->vfields = 0;

	if (navi_parse_datum(buffer + i, &msg->locdatum, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_LOCALDATUM;
	}
	i += nmread;

	if (navi_parse_datumsub(buffer + i, &msg->locdatumsub, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_LOCALDATUMSUB;
	}
	i += nmread;

	if (navi_parse_offset(buffer + i, &msg->latofs, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_OFFSET;
	}
	i += nmread;

	if (navi_parse_offset(buffer + i, &msg->lonofs, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_OFFSET;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &msg->altoffset, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_ALTOFFSET;
	}
	i += nmread;

	if (navi_parse_datum(buffer + i, &msg->refdatum, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_REFDATUM;
	}

	return 0;
}

#endif // NO_PARSER
