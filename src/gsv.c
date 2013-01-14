/*
 * gsv.c - generator and parser of GSV message
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

#include <libnavigate/gsv.h>
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
// Initializes GSV sentence structure with default values
navierr_status_t navi_init_gsv(struct gsv_t *msg)
{
	assert(msg != NULL);

	msg->totalnm = 1;
	msg->msgnm = 1;
	msg->nmsatellites = -1;
	memset(msg->info, 0, sizeof(msg->info));

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates GSV message
navierr_status_t navi_create_gsv(const struct gsv_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	int i;
	size_t msglength;

	char totalnm[2], msgnm[2], nmsatellites[4], id[4], elevation[4], azimuth[4], snr[4];
	char bytes[4];

	if (maxsize < NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_NotEnoughBuffer);
		return navi_Error;
	}

	(void)navi_split_integer(msg->totalnm, bytes, 1, 10);
	msglength = navi_print_decfield(bytes, 1, totalnm, sizeof(totalnm));

	(void)navi_split_integer(msg->msgnm, bytes, 1, 10);
	msglength += navi_print_decfield(bytes, 1, msgnm, sizeof(msgnm));

	if (msg->nmsatellites != -1)
	{
		(void)navi_split_integer(msg->nmsatellites, bytes, 2, 10);
		msglength += navi_print_decfield(bytes, 2, nmsatellites, sizeof(nmsatellites));
	}
	else
	{
		strcpy(nmsatellites, "");
	}

	(void)strcpy(buffer, totalnm);
	(void)strcat(buffer, ",");
	(void)strcat(buffer, msgnm);
	(void)strcat(buffer, ",");
	(void)strcat(buffer, nmsatellites);

	for (i = 0; i < GSV_MAX_SATELLITES_PER_MESSAGE && msg->info[i].id != 0; i++)
	{
		strcat(buffer, ",");

		(void)navi_split_integer(msg->info[i].id, bytes, 2, 10);
		msglength += navi_print_decfield(bytes, 2, id, sizeof(id));
		strcat(buffer, id);

		strcat(buffer, ",");
		msglength += 1;

		(void)navi_split_integer(msg->info[i].elevation, bytes, 2, 10);
		msglength += navi_print_decfield(bytes,
			msg->info[i].vfields & SATINFO_VALID_ORIENTATION ? 2 : 0,
			elevation, sizeof(elevation));
		strcat(buffer, elevation);

		strcat(buffer, ",");
		msglength += 1;

		(void)navi_split_integer(msg->info[i].azimuth, bytes, 3, 10);
		msglength += navi_print_decfield(bytes,
			msg->info[i].vfields & SATINFO_VALID_ORIENTATION ? 3 : 0,
			azimuth, sizeof(azimuth));
		strcat(buffer, azimuth);

		strcat(buffer, ",");
		msglength += 1;

		(void)navi_split_integer(msg->info[i].snr, bytes, 2, 10);
		msglength += navi_print_decfield(bytes,
			msg->info[i].vfields & SATINFO_VALID_SNR ? 2 : 0,
			snr, sizeof(snr));
		strcat(buffer, snr);
	}

	*nmwritten = msglength;
	return navi_Ok;
}

//
// Creates GSV message sequence from satellites array
navierr_status_t navi_create_gsv_sequence(navi_talkerid_t tid, int nmofsatellites,
	const struct navi_satinfo_t satlist[], char *buffer, size_t maxsize, size_t *nmwritten)
{
	int i, j;
	int messagenm, totalmsgnm;
	size_t offset = 0, nmofcharswritten = 0;

	struct gsv_t gsv;
	struct approved_field_t s;

	totalmsgnm = nmofsatellites / GSV_MAX_SATELLITES_PER_MESSAGE +
		(nmofsatellites % GSV_MAX_SATELLITES_PER_MESSAGE ? 1 : 0);

	j = 0;
	s.afmt = navi_GSV;
	s.tid = tid;

	for (messagenm = 1; messagenm <= totalmsgnm; messagenm++)
	{
		navi_init_gsv(&gsv);
		gsv.totalnm = totalmsgnm;
		gsv.msgnm = messagenm;
		gsv.nmsatellites = messagenm == 1 ? nmofsatellites : -1;

		i = 0;
		while (i < GSV_MAX_SATELLITES_PER_MESSAGE && j < nmofsatellites)
		{
			memmove(&gsv.info[i++], &satlist[j++], sizeof(gsv.info[0]));
		}

		if (navi_create_msg(navi_af_Approved, &s, &gsv, buffer + offset,
			maxsize - offset, &nmofcharswritten) != navi_Ok)
		{
			return navi_Error;
		}
		offset += nmofcharswritten;
	}

	*nmwritten = offset;
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses GSV message
navierr_status_t navi_parse_gsv(struct gsv_t *msg, char *buffer)
{
	size_t i = 0, j, nmread;
	double d;
	char bytes[8];

	if (navi_parse_number(buffer + i, &d, &nmread) != navi_Ok)
		return navi_Error;
	else
		msg->totalnm = (int)round(d);
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != navi_Ok)
		return navi_Error;
	else
		msg->msgnm = (int)round(d);
	i += nmread;

	if (navi_parse_decfield(buffer + i, 2, bytes, &nmread) != navi_Ok)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->nmsatellites = navi_compose_integer(bytes, 2, 10);
	}
	i += nmread;

	for (j = 0; j < 4; j++)
	{
		msg->info[j].vfields = 0;

		if (navi_parse_number(buffer + i, &d, &nmread) != 0)
		{
			if (navierr_get_last()->errclass == navi_NullField)
				break;
			else
				return navi_Error;
		}
		else
		{
			msg->info[j].id = (int)round(d);
		}
		i += nmread;

		if (navi_parse_number(buffer + i, &d, &nmread) != 0)
		{
			if (navierr_get_last()->errclass != navi_NullField)
				return navi_Error;
		}
		else
		{
			msg->info[j].elevation = (int)round(d);
			msg->info[j].vfields |= SATINFO_VALID_ORIENTATION;
		}
		i += nmread;

		if (navi_parse_number(buffer + i, &d, &nmread) != 0)
		{
			if (navierr_get_last()->errclass != navi_NullField)
				return navi_Error;
		}
		else
		{
			msg->info[j].azimuth = (int)round(d);
			msg->info[j].vfields |= SATINFO_VALID_ORIENTATION;
		}
		i += nmread;

		if (navi_parse_number(buffer + i, &d, &nmread) != 0)
		{
			if (navierr_get_last()->errclass != navi_NullField)
				return navi_Error;
		}
		else
		{
			msg->info[j].snr = (int)round(d);
			msg->info[j].vfields |= SATINFO_VALID_SNR;
		}
		i += nmread;

		if (*(buffer + i - 1) == '*')
			break;
	}

	return navi_Ok;
}

#endif // NO_PARSER
