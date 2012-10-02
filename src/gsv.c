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
navierr_status_t navi_init_gsv(struct gsv_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;
	msg->nmsatellites = 0;
	memset(msg->info, 0, sizeof(msg->info));
	msg->totalnm = msg->msgnm = 1;

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates GSV message
navierr_status_t navi_create_gsv(const struct gsv_t *msg, char *buffer, int maxsize, int *nmwritten)
{
	int i, j, msglength, total = 0, nmoffullmsg;
	const char *tid = NULL, *sfmt = NULL;
	char csstr[3];

	char totalnm[2], msgnm[2], nmsatellites[4], id[4][4], elevation[4][4],
		azimuth[4][4], snr[4][4];
	char bytes[4];

	tid = navi_talkerid_str(msg->tid);
	sfmt = navi_sentencefmt_str(navi_GSV);

	nmoffullmsg = msg->nmsatellites / 4;

	if (msg->nmsatellites % 4)
		(void)navi_split_integer(nmoffullmsg + 1, bytes, 1, 10);
	else
		(void)navi_split_integer(nmoffullmsg, bytes, 1, 10);
	(void)navi_print_decfield(bytes, 1, totalnm, sizeof(totalnm));

	(void)navi_split_integer(msg->nmsatellites, bytes, 2, 10);
	(void)navi_print_decfield(bytes, 2, nmsatellites, sizeof(nmsatellites));

	for (i = 0; i < nmoffullmsg; i++)
	{	// compose all the messages, where all four satellites are used
		msglength = strlen(totalnm);
		msglength += strlen(nmsatellites);

		(void)navi_split_integer(i + 1, bytes, 1, 10);
		msglength += navi_print_decfield(bytes, 1, msgnm, sizeof(msgnm));

		for (j = 0; j < 4; j++)
		{
			(void)navi_split_integer(msg->info[i * 4 + j].id, bytes, 2, 10);
			msglength += navi_print_decfield(bytes, 2, id[j], sizeof(id[0]));

			(void)navi_split_integer(msg->info[i * 4 + j].elevation, bytes, 2, 10);
			msglength += navi_print_decfield(bytes,
				msg->info[i * 4 + j].vfields & SATINFO_VALID_ORIENTATION ? 2 : 0,
				elevation[j], sizeof(elevation[0]));

			(void)navi_split_integer(msg->info[i * 4 + j].azimuth, bytes, 3, 10);
			msglength += navi_print_decfield(bytes,
				msg->info[i * 4 + j].vfields & SATINFO_VALID_ORIENTATION ? 3 : 0,
				azimuth[j], sizeof(azimuth[0]));

			(void)navi_split_integer(msg->info[i * 4 + j].snr, bytes, 2, 10);
			msglength += navi_print_decfield(bytes,
				msg->info[i * 4 + j].vfields & SATINFO_VALID_SNR ? 2 : 0,
				snr[j], sizeof(snr[0]));
		}

		if (msglength + 30 > NAVI_SENTENCE_MAXSIZE)
		{
			navierr_set_last(navi_MsgExceedsMaxSize);
			return navi_Error;
		}

		msglength = snprintf(buffer + total, maxsize - total,
			"$%s%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s*",
			tid, sfmt, totalnm, msgnm, nmsatellites, id[0], elevation[0], azimuth[0],
			snr[0], id[1], elevation[1], azimuth[1], snr[1], id[2], elevation[2],
			azimuth[2], snr[2], id[3], elevation[3], azimuth[3], snr[3]);

		if (navi_checksum(buffer + total, msglength, csstr, NULL) != navi_Ok)
			return navi_Error;
		strcat(buffer, csstr);
		strcat(buffer, "\r\n");
		total = total + msglength + 4;
	}

	if (msg->nmsatellites % 4)
	{	// compose the last message
		msglength = strlen(totalnm);
		msglength += strlen(nmsatellites);

		(void)navi_split_integer(i + 1, bytes, 1, 10);
		msglength += navi_print_decfield(bytes, 1, msgnm, sizeof(msgnm));

		strcat(buffer, "$");
		strcat(buffer, tid);
		strcat(buffer, sfmt);
		strcat(buffer, ",");

		msglength += 7;

		strcat(buffer, totalnm);
		strcat(buffer, ",");
		strcat(buffer, msgnm);
		strcat(buffer, ",");
		strcat(buffer, nmsatellites);

		msglength += 2;
		
		nmoffullmsg = msg->nmsatellites % 4;
		for (j = 0; j < nmoffullmsg; j++)
		{
			(void)navi_split_integer(msg->info[i * 4 + j].id, bytes, 2, 10);
			msglength += navi_print_decfield(bytes, 2, id[j], sizeof(id[0]));

			strcat(buffer, ",");
			msglength += 1;
			strcat(buffer, id[j]);

			(void)navi_split_integer(msg->info[i * 4 + j].elevation, bytes, 2, 10);
			msglength += navi_print_decfield(bytes,
				msg->info[i * 4 + j].vfields & SATINFO_VALID_ORIENTATION ? 2 : 0,
				elevation[j], sizeof(elevation[0]));

			strcat(buffer, ",");
			msglength += 1;
			strcat(buffer, elevation[j]);

			(void)navi_split_integer(msg->info[i * 4 + j].azimuth, bytes, 3, 10);
			msglength += navi_print_decfield(bytes,
				msg->info[i * 4 + j].vfields & SATINFO_VALID_ORIENTATION ? 3 : 0,
				azimuth[j], sizeof(azimuth[0]));

			strcat(buffer, ",");
			msglength += 1;
			strcat(buffer, azimuth[j]);

			(void)navi_split_integer(msg->info[i * 4 + j].snr, bytes, 2, 10);
			msglength += navi_print_decfield(bytes,
				msg->info[i * 4 + j].vfields & SATINFO_VALID_SNR ? 2 : 0,
				snr[j], sizeof(snr[0]));

			strcat(buffer, ",");
			msglength += 1;
			strcat(buffer, snr[j]);
		}

		strcat(buffer, "*");
		msglength += 1;

		if (navi_checksum(buffer + total, msglength, csstr, NULL) != navi_Ok)
			return navi_Error;
		strcat(buffer, csstr);
		strcat(buffer, "\r\n");
		total = total + msglength + 4;
	}

	*nmwritten = total;
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses GSV message
navierr_status_t navi_parse_gsv(struct gsv_t *msg, char *buffer)
{
	int i = 0, j, nmread;
	double d;
	char bytes[8];

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
		return navi_Error;
	else
		msg->totalnm = (int)round(d);
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
		return navi_Error;
	else
		msg->msgnm = (int)round(d);
	i += nmread;

	msg->nmsatellites = 0;
	if (navi_parse_decfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->nmsatellites = navi_compose_integer(bytes, 2, 10);
	}
	i += nmread;

	msg->nmsatellites = 0;
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
			msg->nmsatellites += 1;
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
