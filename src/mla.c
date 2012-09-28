/*
 * mla.c - generator and parser of MLA message
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

#include "libnavigate/mla.h"
#include "libnavigate/common.h"

#include <navigate.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef _MSC_VER

	#define snprintf	_snprintf

	extern double round(double x);

#endif // MSVC_VER

#ifndef NO_GENERATOR

int navi_create_mla(const struct mla_t *msg, char *buffer,
		int maxsize, int *nmwritten)
{
	int i, msglength, total = 0;
	const char *tid = NULL, *sfmt = NULL;
	char csstr[3];

	char totalnm[32], msgnm[32], satslot[4], daycount[32], svhealth[4],
		e[8], dot[4], omega[8], tauc_high[8], deltat[8], t[8],
		lambda[8], deltai[8], tauc_low[4], taun[4];
	char bytes[8];

	tid = navi_talkerid_str(msg->tid);
	sfmt = navi_sentencefmt_str(navi_MLA);

	for (i = 0; i < msg->nmsatellites; i++)
	{
		msglength = navi_print_number(msg->nmsatellites, totalnm,
			sizeof(totalnm), 1);
		msglength += navi_print_number(i + 1, msgnm, sizeof(msgnm), 1);

		(void)navi_split_integer(msg->almlist[i].satslot, bytes, 2, 10);
		msglength += navi_print_decfield(bytes,
			msg->almlist[i].vfields & GLOALM_VALID_SATSLOT ? 2 : 0,
			satslot, sizeof(satslot));

		msglength += navi_print_number(msg->almlist[i].daycount, daycount,
			sizeof(daycount), msg->almlist[i].vfields & GLOALM_VALID_DAYCOUNT);

		(void)navi_split_integer(msg->almlist[i].svhealth, bytes, 2, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GLOALM_VALID_SVHEALTH ? 2 : 0,
			svhealth, sizeof(svhealth));

		(void)navi_split_integer(msg->almlist[i].e, bytes, 4, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GLOALM_VALID_E ? 4 : 0, e, sizeof(e));

		(void)navi_split_integer(msg->almlist[i].dot, bytes, 2, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GLOALM_VALID_DOT ? 2 : 0,
			dot, sizeof(dot));

		(void)navi_split_integer(msg->almlist[i].omega, bytes, 4, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GLOALM_VALID_OMEGA ? 4 : 0,
			omega, sizeof(omega));

		(void)navi_split_integer(msg->almlist[i].tauc_high, bytes, 4, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GLOALM_VALID_TAUC ? 4 : 0,
			tauc_high, sizeof(tauc_high));

		(void)navi_split_integer(msg->almlist[i].deltat, bytes, 6, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GLOALM_VALID_DELTAT ? 6 : 0,
			deltat, sizeof(deltat));

		(void)navi_split_integer(msg->almlist[i].t, bytes, 6, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GLOALM_VALID_T ? 6 : 0,
			t, sizeof(t));

		(void)navi_split_integer(msg->almlist[i].lambda, bytes, 6, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GLOALM_VALID_LAMBDA ? 6 : 0,
			lambda, sizeof(lambda));

		(void)navi_split_integer(msg->almlist[i].deltai, bytes, 6, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GLOALM_VALID_DELTAI ? 6 : 0,
			deltai, sizeof(deltai));

		(void)navi_split_integer(msg->almlist[i].tauc_low, bytes, 3, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GLOALM_VALID_TAUC ? 3 : 0,
			tauc_low, sizeof(tauc_low));

		(void)navi_split_integer(msg->almlist[i].taun, bytes, 3, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GLOALM_VALID_TAUN ? 3 : 0,
			taun, sizeof(taun));

		if (msglength + 26 > NAVI_SENTENCE_MAXSIZE)
		{
			navierr_set_last(navi_MsgExceedsMaxSize);
			return navi_Error;
		}

		msglength = snprintf(buffer + total, maxsize - total,
			"$%s%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s*",
			tid, sfmt, totalnm, msgnm, satslot, daycount, svhealth, e,
			dot, omega, tauc_high, deltat, t, lambda, deltai, tauc_low, taun);

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

int navi_parse_mla(struct mla_t *msg, char *buffer)
{
	int i = 0, nmread;
	double d;
	char bytes[8];

	msg->almlist[0].vfields = 0;

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

	if (navi_parse_decfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].satslot = navi_compose_integer(bytes, 2, 10);
		msg->almlist[0].vfields |= GLOALM_VALID_SATSLOT;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].daycount = (int)round(d);
		msg->almlist[0].vfields |= GLOALM_VALID_DAYCOUNT;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].svhealth = navi_compose_integer(bytes, 2, 16);
		msg->almlist[0].vfields |= GLOALM_VALID_SVHEALTH;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 4, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].e = navi_compose_integer(bytes, 4, 16);
		msg->almlist[0].vfields |= GLOALM_VALID_E;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].dot = navi_compose_integer(bytes, 2, 16);
		msg->almlist[0].vfields |= GLOALM_VALID_DOT;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 4, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].omega = navi_compose_integer(bytes, 4, 16);
		msg->almlist[0].vfields |= GLOALM_VALID_OMEGA;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 4, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].tauc_high = navi_compose_integer(bytes, 4, 16);
		msg->almlist[0].vfields |= GLOALM_VALID_TAUC;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].deltat = navi_compose_integer(bytes, 6, 16);
		msg->almlist[0].vfields |= GLOALM_VALID_DELTAT;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].t = navi_compose_integer(bytes, 6, 16);
		msg->almlist[0].vfields |= GLOALM_VALID_T;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].lambda = navi_compose_integer(bytes, 6, 16);
		msg->almlist[0].vfields |= GLOALM_VALID_LAMBDA;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].deltai = navi_compose_integer(bytes, 6, 16);
		msg->almlist[0].vfields |= GLOALM_VALID_DELTAI;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 3, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].tauc_low = navi_compose_integer(bytes, 3, 16);
		msg->almlist[0].vfields |= GLOALM_VALID_TAUC;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 3, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].taun = navi_compose_integer(bytes, 3, 16);
		msg->almlist[0].vfields |= GLOALM_VALID_TAUN;
	}

	msg->nmsatellites = 1;
	return navi_Ok;
}

#endif // NO_PARSER

