/*
 * vtg.c - generator and parser of VTG message
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

#include "libnavigate/vtg.h"
#include "libnavigate/common.h"
#include "libnavigate/generator.h"
#include "libnavigate/parser.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

//
// Initializes VTG sentence structure with default values
NAVI_EXTERN(navierr_status_t) navi_init_vtg(struct vtg_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;
	msg->vfields = 0;
	msg->courseTrue = 0.;
	msg->courseMagn = 0.;
	msg->speed = 0.;
	msg->mi = navi_DataNotValid;

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates ZDA message
navierr_status_t navi_create_vtg(const struct vtg_t *msg, char *buffer, int maxsize,
	int *nmwritten)
{
	int msglength;

	const char *mi;
	char ctrue[32], courseT[2], cmagn[32], courseM[2], snots[32],
		speedN[4], skmph[32], speedK[2];

	msglength = navi_print_number(msg->courseTrue, ctrue, sizeof(ctrue),
		msg->vfields & VTG_VALID_COURSETRUE);
	msglength += snprintf(courseT, sizeof(courseT),
		(msg->vfields & VTG_VALID_COURSETRUE) ? "T" : "");
	msglength += navi_print_number(msg->courseMagn, cmagn, sizeof(cmagn),
		msg->vfields & VTG_VALID_COURSEMAGN);
	msglength += snprintf(courseM, sizeof(courseM),
		(msg->vfields & VTG_VALID_COURSEMAGN) ? "M" : "");
	msglength += navi_print_number(MPS_TO_KNOTS(msg->speed), snots,
		sizeof(snots), msg->vfields & VTG_VALID_SPEED);
	msglength += snprintf(speedN, sizeof(speedN),
		(msg->vfields & VTG_VALID_SPEED) ? "N" : "");
	msglength += navi_print_number(MPS_TO_KMPH(msg->speed), skmph,
		sizeof(skmph), msg->vfields & VTG_VALID_SPEED);
	msglength += snprintf(speedK, sizeof(speedK),
		(msg->vfields & VTG_VALID_SPEED) ? "K" : "");

	msglength += strlen(mi = navi_modeindicator_str(msg->mi));

	if (msglength > maxsize)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s,%s,%s,%s",
		ctrue, courseT, cmagn, courseM, snots, speedN, skmph, speedK, mi);
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses VTG message
navierr_status_t navi_parse_vtg(struct vtg_t *msg, char *buffer)
{
	int i = 0, nmread;
	double speedknots, speedkmph;

	msg->vfields = 0;

	if (navi_parse_number(buffer + i, &msg->courseTrue, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= VTG_VALID_COURSETRUE;
	}
	i += nmread;

	if (buffer[i] == 'T')
	{
		i += 1;
	}
	if (buffer[i] != ',')
	{
		return navi_InvalidMessage;
	}
	i += 1;

	if (navi_parse_number(buffer + i, &msg->courseMagn, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= VTG_VALID_COURSEMAGN;
	}
	i += nmread;

	if (buffer[i] == 'M')
	{
		i += 1;
	}
	if (buffer[i] != ',')
	{
		return navi_InvalidMessage;
	}
	i += 1;

	speedknots = -1.0;
	if (navi_parse_number(buffer + i, &speedknots, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	i += nmread;

	if (buffer[i] == 'N')
	{
		i += 1;
	}
	if (buffer[i] != ',')
	{
		return navi_InvalidMessage;
	}
	i += 1;

	speedkmph = -1.0;
	if (navi_parse_number(buffer + i, &speedkmph, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	i += nmread;

	if (buffer[i] == 'K')
	{
		i += 1;
	}
	if (buffer[i] != ',')
	{
		return navi_InvalidMessage;
	}
	i += 1;

	if (speedkmph > -1.0)
	{
		msg->speed = KMPH_TO_MPS(speedkmph);
		msg->vfields |= VTG_VALID_SPEED;
	}
	else if (speedknots > -1.0)
	{
		msg->speed = KNOTS_TO_MPS(speedknots);
		msg->vfields |= VTG_VALID_SPEED;
	}

	if (navi_parse_modeindicator(buffer + i, &msg->mi, &nmread) != 0)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}

	return navi_Ok;
}

#endif // NO_PARSER
