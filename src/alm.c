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

//
// Initializes ALM sentence structure with default values
navierr_status_t navi_init_alm(struct alm_t *msg, navi_talkerid_t tid)
{
	assert(msg != NULL);

	msg->tid = tid;
	msg->totalnm = 1;
	msg->msgnm = 1;
	memset(&msg->alm, 0, sizeof(msg->alm));

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates ALM message
navierr_status_t navi_create_alm(const struct alm_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	size_t msglength;

	char totalnm[32], msgnm[32], prnnm[4], weeknm[32], svhealth[4],
		e[8], toa[4], sigmai[8], omegadot[8], sqrtsemi[8], omega[8],
		omega0[8], m0[8], af0[4], af1[4];
	char bytes[8];

	msglength = navi_print_number(msg->totalnm, totalnm, sizeof(totalnm));
	msglength += navi_print_number(msg->msgnm, msgnm, sizeof(msgnm));

	(void)navi_split_integer(msg->alm.satelliteprn, bytes, 2, 10);
	msglength += navi_print_decfield(bytes, 2, prnnm, sizeof(prnnm));

	msglength += navi_print_number(msg->alm.gpsweek, weeknm, sizeof(weeknm));

	(void)navi_split_integer(msg->alm.svhealth, bytes, 2, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GPSALM_VALID_SVHEALTH ? 2 : 0,
		svhealth, sizeof(svhealth));

	(void)navi_split_integer(msg->alm.e, bytes, 4, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GPSALM_VALID_E ? 4 : 0, e, sizeof(e));

	(void)navi_split_integer(msg->alm.toa, bytes, 2, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GPSALM_VALID_TOA ? 2 : 0,
		toa, sizeof(toa));

	(void)navi_split_integer(msg->alm.sigmai, bytes, 4, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GPSALM_VALID_SIGMAI ? 4 : 0,
		sigmai, sizeof(sigmai));

	(void)navi_split_integer(msg->alm.omegadot, bytes, 4, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GPSALM_VALID_OMEGADOT ? 4 : 0,
		omegadot, sizeof(omegadot));

	(void)navi_split_integer(msg->alm.sqrtsemiaxis, bytes, 6, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GPSALM_VALID_SQRTSEMIAXIS ? 6 : 0,
		sqrtsemi, sizeof(sqrtsemi));

	(void)navi_split_integer(msg->alm.omega, bytes, 6, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GPSALM_VALID_OMEGA ? 6 : 0,
		omega, sizeof(omega));

	(void)navi_split_integer(msg->alm.omega0, bytes, 6, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GPSALM_VALID_OMEGA0 ? 6 : 0,
		omega0, sizeof(omega0));

	(void)navi_split_integer(msg->alm.m0, bytes, 6, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GPSALM_VALID_M0 ? 6 : 0,
		m0, sizeof(m0));

	(void)navi_split_integer(msg->alm.af0, bytes, 3, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GPSALM_VALID_AF0 ? 3 : 0,
		af0, sizeof(af0));

	(void)navi_split_integer(msg->alm.af1, bytes, 3, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GPSALM_VALID_AF1 ? 3 : 0,
		af1, sizeof(af1));

	if (msglength + 26 > NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
			totalnm, msgnm, prnnm, weeknm, svhealth, e, toa, sigmai, omegadot, sqrtsemi,
			omega, omega0, m0, af0, af1);
	return navi_Ok;
}

//
// Creates ALM message sequence from satellites array
navierr_status_t navi_create_alm_sequence(navi_talkerid_t tid, int nmofsatellites,
	const struct navi_gpsalm_t almanaclist[], char *buffer, size_t maxsize, size_t *nmwritten)
{
	int messagenm;
	size_t offset = 0, nmofcharswritten = 0;

	struct alm_t alm;

	assert((nmofsatellites > 0) && (nmofsatellites <= ALM_MAX_SATELLITES));
	assert(buffer != NULL);

	for (messagenm = 1; messagenm <= nmofsatellites; messagenm++)
	{
		navi_init_alm(&alm, tid);
		alm.totalnm = nmofsatellites;
		alm.msgnm = messagenm;
		memmove(&alm.alm, &almanaclist[messagenm - 1], sizeof(alm.alm));

		if (navi_create_msg(navi_ALM, &alm, buffer + offset, maxsize - offset, &nmofcharswritten) != navi_Ok)
			return navi_Error;
		offset += nmofcharswritten;
	}

	*nmwritten = offset;
	return navi_Ok;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

//
// Parses ALM message
navierr_status_t navi_parse_alm(struct alm_t *msg, char *buffer)
{
	size_t i = 0, nmread;
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

	if (navi_parse_decfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		navierr_set_last(navi_NullField);
		return navi_Error;	// without satellite number, an invalid message
	}
	else
	{
		msg->alm.satelliteprn = navi_compose_integer(bytes, 2, 10);
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.gpsweek = (int)round(d);
		msg->alm.vfields |= GPSALM_VALID_GPSWEEK;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.svhealth = navi_compose_integer(bytes, 2, 16);
		msg->alm.vfields |= GPSALM_VALID_SVHEALTH;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 4, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.e = navi_compose_integer(bytes, 4, 16);
		msg->alm.vfields |= GPSALM_VALID_E;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.toa = navi_compose_integer(bytes, 2, 16);
		msg->alm.vfields |= GPSALM_VALID_TOA;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 4, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.sigmai = navi_compose_integer(bytes, 4, 16);
		msg->alm.vfields |= GPSALM_VALID_SIGMAI;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 4, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.omegadot = navi_compose_integer(bytes, 4, 16);
		msg->alm.vfields |= GPSALM_VALID_OMEGADOT;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.sqrtsemiaxis = navi_compose_integer(bytes, 6, 16);
		msg->alm.vfields |= GPSALM_VALID_SQRTSEMIAXIS;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.omega = navi_compose_integer(bytes, 6, 16);
		msg->alm.vfields |= GPSALM_VALID_OMEGA;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.omega0 = navi_compose_integer(bytes, 6, 16);
		msg->alm.vfields |= GPSALM_VALID_OMEGA0;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.m0 = navi_compose_integer(bytes, 6, 16);
		msg->alm.vfields |= GPSALM_VALID_M0;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 3, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.af0 = navi_compose_integer(bytes, 3, 16);
		msg->alm.vfields |= GPSALM_VALID_AF0;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 3, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.af1 = navi_compose_integer(bytes, 3, 16);
		msg->alm.vfields |= GPSALM_VALID_AF1;
	}

	return navi_Ok;
}

#endif // NO_PARSER
