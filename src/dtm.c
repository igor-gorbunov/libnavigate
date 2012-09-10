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

	const char *talkerid, *ldatum, *rdatum, *datumsd,
		*latsign, *lonsign;
	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], latofs[32],
		lonofs[32], altofs[32], cs[3];

	msglength = strlen(talkerid = navi_talkerid_str(msg->tid));
	msglength += strlen(ldatum = navi_datum_str(msg->ld,
		msg->vfields & DTM_VALID_LOCALDATUM));
	msglength += strlen(datumsd = navi_datumsubdiv_str(msg->lds,
		msg->vfields & DTM_VALID_LOCALDATUMSUB));
	msglength += navi_print_number(msg->latofs.offset, latofs,
		sizeof(latofs), msg->vfields & DTM_VALID_LATOFFSET);
	msglength += strlen(latsign = navi_fixsign_str(msg->latofs.sign,
		msg->vfields & DTM_VALID_LATOFFSET));
	msglength += navi_print_number(msg->lonofs.offset, lonofs,
		sizeof(lonofs), msg->vfields & DTM_VALID_LONOFFSET);
	msglength += strlen(lonsign = navi_fixsign_str(msg->lonofs.sign,
		msg->vfields & DTM_VALID_LONOFFSET));
	msglength += navi_print_number(msg->altoffset, altofs,
		sizeof(altofs), msg->vfields & DTM_VALID_ALTITUDEOFFSET);
	msglength += strlen(rdatum = navi_datum_str(msg->rd,
		msg->vfields & DTM_VALID_REFERENCEDATUM));

	msglength += 17;
	if (msglength > NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return -1;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg),
		"$%sDTM,%s,%s,%s,%s,%s,%s,%s,%s*%s\r\n", talkerid, ldatum,
		datumsd, latofs, latsign, lonofs, lonsign, altofs, rdatum, "%s");
	IecPrint_Checksum(iecmsg, msglength, cs);

	*nmwritten = snprintf(buffer, maxsize, iecmsg, cs);
	return 0;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

int navi_msg_parse_dtm(struct dtm_t *msg, char *buffer)
{
	int index = 1, nmread;

	msg->vfields = 0;

	if (navi_parse_datum(buffer + index, &msg->ld, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_LOCALDATUM;
	}
	index += nmread;

	if (navi_parse_datumsub(buffer + index, &msg->lds, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_LOCALDATUMSUB;
	}
	index += nmread;

	if (navi_parse_offset(buffer + index, &msg->latofs, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_LATOFFSET;
	}
	index += nmread;

	if (navi_parse_offset(buffer + index, &msg->lonofs, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_LONOFFSET;
	}
	index += nmread;

	if (navi_parse_number(buffer + index, &msg->altoffset, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_ALTITUDEOFFSET;
	}
	index += nmread;

	if (navi_parse_datum(buffer + index, &msg->rd, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_REFERENCEDATUM;
	}
	index += nmread;

	return 0;
}

#endif // NO_PARSER
