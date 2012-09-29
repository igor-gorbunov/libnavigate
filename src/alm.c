/*
 * alm.c - generator and parser of ALM message
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

#include <libnavigate/alm.h>
#include <libnavigate/common.h>

#include <navigate.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#ifdef _MSC_VER
	#include "win32/win32navi.h"
#endif // MSVC_VER

navierr_status_t navi_init_alm(struct alm_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;
	msg->totalnm = msg->msgnm = 0;
	msg->nmsatellites = 0;
	memset(msg->almlist, 0, sizeof(msg->almlist));

	return navi_Ok;
}

#ifndef NO_GENERATOR

navierr_status_t navi_create_alm(const struct alm_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int i, msglength, total = 0;
	const char *tid = NULL, *sfmt = NULL;
	char csstr[3];

	char totalnm[32], msgnm[32], prnnm[4], weeknm[32], svhealth[4],
		e[8], toa[4], sigmai[8], omegadot[8], sqrtsemi[8], omega[8],
		omega0[8], m0[8], af0[4], af1[4];
	char bytes[8];

	tid = navi_talkerid_str(msg->tid);
	sfmt = navi_sentencefmt_str(navi_ALM);

	for (i = 0; i < msg->nmsatellites; i++)
	{
		msglength = navi_print_number(msg->nmsatellites, totalnm,
			sizeof(totalnm), 1);
		msglength += navi_print_number(i + 1, msgnm, sizeof(msgnm), 1);

		(void)navi_split_integer(msg->almlist[i].satelliteprn, bytes, 2, 10);
		msglength += navi_print_decfield(bytes,
			msg->almlist[i].vfields & GPSALM_VALID_SATELLITEPRN ? 2 : 0,
			prnnm, sizeof(prnnm));

		msglength += navi_print_number(msg->almlist[i].gpsweek, weeknm,
			sizeof(weeknm), msg->almlist[i].vfields & GPSALM_VALID_GPSWEEK);

		(void)navi_split_integer(msg->almlist[i].svhealth, bytes, 2, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GPSALM_VALID_SVHEALTH ? 2 : 0,
			svhealth, sizeof(svhealth));

		(void)navi_split_integer(msg->almlist[i].e, bytes, 4, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GPSALM_VALID_E ? 4 : 0, e, sizeof(e));

		(void)navi_split_integer(msg->almlist[i].toa, bytes, 2, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GPSALM_VALID_TOA ? 2 : 0,
			toa, sizeof(toa));

		(void)navi_split_integer(msg->almlist[i].sigmai, bytes, 4, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GPSALM_VALID_SIGMAI ? 4 : 0,
			sigmai, sizeof(sigmai));

		(void)navi_split_integer(msg->almlist[i].omegadot, bytes, 4, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GPSALM_VALID_OMEGADOT ? 4 : 0,
			omegadot, sizeof(omegadot));

		(void)navi_split_integer(msg->almlist[i].sqrtsemiaxis, bytes, 6, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GPSALM_VALID_SQRTSEMIAXIS ? 6 : 0,
			sqrtsemi, sizeof(sqrtsemi));

		(void)navi_split_integer(msg->almlist[i].omega, bytes, 6, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GPSALM_VALID_OMEGA ? 6 : 0,
			omega, sizeof(omega));

		(void)navi_split_integer(msg->almlist[i].omega0, bytes, 6, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GPSALM_VALID_OMEGA0 ? 6 : 0,
			omega0, sizeof(omega0));

		(void)navi_split_integer(msg->almlist[i].m0, bytes, 6, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GPSALM_VALID_M0 ? 6 : 0,
			m0, sizeof(m0));

		(void)navi_split_integer(msg->almlist[i].af0, bytes, 3, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GPSALM_VALID_AF0 ? 3 : 0,
			af0, sizeof(af0));

		(void)navi_split_integer(msg->almlist[i].af1, bytes, 3, 16);
		msglength += navi_print_hexfield(bytes,
			msg->almlist[i].vfields & GPSALM_VALID_AF1 ? 3 : 0,
			af1, sizeof(af1));

		if (msglength + 26 > NAVI_SENTENCE_MAXSIZE)
		{
			navierr_set_last(navi_MsgExceedsMaxSize);
			return navi_Error;
		}

		msglength = snprintf(buffer + total, maxsize - total,
			"$%s%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s*",
			tid, sfmt, totalnm, msgnm, prnnm, weeknm, svhealth, e,
			toa, sigmai, omegadot, sqrtsemi, omega, omega0, m0, af0, af1);

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

navierr_status_t navi_parse_alm(struct alm_t *msg, char *buffer)
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
		msg->almlist[0].satelliteprn = navi_compose_integer(bytes, 2, 10);
		msg->almlist[0].vfields |= GPSALM_VALID_SATELLITEPRN;
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].gpsweek = (int)round(d);
		msg->almlist[0].vfields |= GPSALM_VALID_GPSWEEK;
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
		msg->almlist[0].vfields |= GPSALM_VALID_SVHEALTH;
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
		msg->almlist[0].vfields |= GPSALM_VALID_E;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].toa = navi_compose_integer(bytes, 2, 16);
		msg->almlist[0].vfields |= GPSALM_VALID_TOA;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 4, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].sigmai = navi_compose_integer(bytes, 4, 16);
		msg->almlist[0].vfields |= GPSALM_VALID_SIGMAI;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 4, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].omegadot = navi_compose_integer(bytes, 4, 16);
		msg->almlist[0].vfields |= GPSALM_VALID_OMEGADOT;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].sqrtsemiaxis = navi_compose_integer(bytes, 6, 16);
		msg->almlist[0].vfields |= GPSALM_VALID_SQRTSEMIAXIS;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].omega = navi_compose_integer(bytes, 6, 16);
		msg->almlist[0].vfields |= GPSALM_VALID_OMEGA;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].omega0 = navi_compose_integer(bytes, 6, 16);
		msg->almlist[0].vfields |= GPSALM_VALID_OMEGA0;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].m0 = navi_compose_integer(bytes, 6, 16);
		msg->almlist[0].vfields |= GPSALM_VALID_M0;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 3, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].af0 = navi_compose_integer(bytes, 3, 16);
		msg->almlist[0].vfields |= GPSALM_VALID_AF0;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 3, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->almlist[0].af1 = navi_compose_integer(bytes, 3, 16);
		msg->almlist[0].vfields |= GPSALM_VALID_AF1;
	}

	msg->nmsatellites = 1;
	return navi_Ok;
}

#endif // NO_PARSER

