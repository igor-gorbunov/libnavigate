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

#include <libnavigate/mla.h>
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
// Initializes MLA sentence structure with default values
navierr_status_t navi_init_mla(struct mla_t *msg)
{
	assert(msg != NULL);

	msg->totalnm = 1;
	msg->msgnm = 1;
	memset(&msg->alm, 0, sizeof(msg->alm));

	return navi_Ok;
}

#ifndef NO_GENERATOR

//
// Creates MLA message
navierr_status_t navi_create_mla(const struct mla_t *msg, char *buffer, size_t maxsize, size_t *nmwritten)
{
	size_t msglength;

	char totalnm[32], msgnm[32], satslot[4], daycount[32], svhealth[4],
		e[8], dot[4], omega[8], tauc_high[8], deltat[8], t[8],
		lambda[8], deltai[8], tauc_low[4], taun[4];
	char bytes[8];

	msglength = navi_print_number(msg->totalnm, totalnm, sizeof(totalnm));
	msglength += navi_print_number(msg->msgnm, msgnm, sizeof(msgnm));

	(void)navi_split_integer(msg->alm.satslot, bytes, 2, 10);
	msglength += navi_print_decfield(bytes, 2, satslot, sizeof(satslot));

	msglength += navi_print_number(msg->alm.daycount, daycount, sizeof(daycount));

	(void)navi_split_integer(msg->alm.svhealth, bytes, 2, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GLOALM_VALID_SVHEALTH ? 2 : 0,
		svhealth, sizeof(svhealth));

	(void)navi_split_integer(msg->alm.e, bytes, 4, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GLOALM_VALID_E ? 4 : 0, e, sizeof(e));

	(void)navi_split_integer(msg->alm.dot, bytes, 2, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GLOALM_VALID_DOT ? 2 : 0,
		dot, sizeof(dot));

	(void)navi_split_integer(msg->alm.omega, bytes, 4, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GLOALM_VALID_OMEGA ? 4 : 0,
		omega, sizeof(omega));

	(void)navi_split_integer(msg->alm.tauc_high, bytes, 4, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GLOALM_VALID_TAUC ? 4 : 0,
		tauc_high, sizeof(tauc_high));

	(void)navi_split_integer(msg->alm.deltat, bytes, 6, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GLOALM_VALID_DELTAT ? 6 : 0,
		deltat, sizeof(deltat));

	(void)navi_split_integer(msg->alm.t, bytes, 6, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GLOALM_VALID_T ? 6 : 0,
		t, sizeof(t));

	(void)navi_split_integer(msg->alm.lambda, bytes, 6, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GLOALM_VALID_LAMBDA ? 6 : 0,
		lambda, sizeof(lambda));

	(void)navi_split_integer(msg->alm.deltai, bytes, 6, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GLOALM_VALID_DELTAI ? 6 : 0,
		deltai, sizeof(deltai));

	(void)navi_split_integer(msg->alm.tauc_low, bytes, 3, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GLOALM_VALID_TAUC ? 3 : 0,
		tauc_low, sizeof(tauc_low));

	(void)navi_split_integer(msg->alm.taun, bytes, 3, 16);
	msglength += navi_print_hexfield(bytes,
		msg->alm.vfields & GLOALM_VALID_TAUN ? 3 : 0,
		taun, sizeof(taun));

	if (msglength + 26 > NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	*nmwritten = snprintf(buffer, maxsize, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
			totalnm, msgnm, satslot, daycount, svhealth, e, dot, omega, tauc_high, deltat,
			t, lambda, deltai, tauc_low, taun);
	return navi_Ok;
}

//
// Creates MLA message sequence from satellites array
navierr_status_t navi_create_mla_sequence(navi_talkerid_t tid, int nmofsatellites,
	const struct navi_gloalm_t almanaclist[], char *buffer, size_t maxsize, size_t *nmwritten)
{
	int messagenm;
	size_t offset = 0, nmofcharswritten = 0;

	struct mla_t mla;
	struct approved_field_t s;

	assert((nmofsatellites > 0) && (nmofsatellites <= MLA_MAX_SATELLITES));
	assert(buffer != NULL);

	s.afmt = navi_MLA;
	s.tid = tid;

	for (messagenm = 1; messagenm <= nmofsatellites; messagenm++)
	{
		navi_init_mla(&mla);
		mla.totalnm = nmofsatellites;
		mla.msgnm = messagenm;
		memmove(&mla.alm, &almanaclist[messagenm - 1], sizeof(mla.alm));

		if (navi_create_msg(navi_af_Approved, &s, &mla, buffer + offset,
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
// Parses MLA message
navierr_status_t navi_parse_mla(struct mla_t *msg, char *buffer)
{
	size_t i = 0, nmread;
	double d;
	char bytes[8];

	msg->alm.vfields = 0;

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
		msg->alm.satslot = navi_compose_integer(bytes, 2, 10);
	}
	i += nmread;

	if (navi_parse_number(buffer + i, &d, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.daycount = (int)round(d);
		msg->alm.vfields |= GLOALM_VALID_DAYCOUNT;
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
		msg->alm.vfields |= GLOALM_VALID_SVHEALTH;
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
		msg->alm.vfields |= GLOALM_VALID_E;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 2, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.dot = navi_compose_integer(bytes, 2, 16);
		msg->alm.vfields |= GLOALM_VALID_DOT;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 4, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.omega = navi_compose_integer(bytes, 4, 16);
		msg->alm.vfields |= GLOALM_VALID_OMEGA;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 4, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.tauc_high = navi_compose_integer(bytes, 4, 16);
		msg->alm.vfields |= GLOALM_VALID_TAUC;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.deltat = navi_compose_integer(bytes, 6, 16);
		msg->alm.vfields |= GLOALM_VALID_DELTAT;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.t = navi_compose_integer(bytes, 6, 16);
		msg->alm.vfields |= GLOALM_VALID_T;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.lambda = navi_compose_integer(bytes, 6, 16);
		msg->alm.vfields |= GLOALM_VALID_LAMBDA;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 6, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.deltai = navi_compose_integer(bytes, 6, 16);
		msg->alm.vfields |= GLOALM_VALID_DELTAI;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 3, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.tauc_low = navi_compose_integer(bytes, 3, 16);
		msg->alm.vfields |= GLOALM_VALID_TAUC;
	}
	i += nmread;

	if (navi_parse_hexfield(buffer + i, 3, bytes, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return navi_Error;
	}
	else
	{
		msg->alm.taun = navi_compose_integer(bytes, 3, 16);
		msg->alm.vfields |= GLOALM_VALID_TAUN;
	}

	return navi_Ok;
}

#endif // NO_PARSER
