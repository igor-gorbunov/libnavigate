/*
 * check_mla.c - MLA messages generating/parsing tests and usage examples.
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

#include <navigate.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	navierr_status_t result;
	size_t msglength, nmwritten, nmread, parsed;
	int finished;

	char inbuffer[1024], outbuffer[256];
	struct navi_gloalm_t almanaclist[8];

	navi_addrfield_t msgtype;
	const navi_error_t *lasterr;

	msglength = 0;

	// MLA
	almanaclist[0].vfields = GLOALM_VALID_DAYCOUNT | GLOALM_VALID_SVHEALTH | GLOALM_VALID_E |
		GLOALM_VALID_DOT | GLOALM_VALID_OMEGA | GLOALM_VALID_TAUC | GLOALM_VALID_DELTAT |
		GLOALM_VALID_T | GLOALM_VALID_LAMBDA | GLOALM_VALID_DELTAI | GLOALM_VALID_TAUN;
	almanaclist[0].satslot = 4;
	almanaclist[0].daycount = 3400;
	almanaclist[0].svhealth = 0x44;
	almanaclist[0].e = 0x0011;
	almanaclist[0].dot = 0x09;
	almanaclist[0].omega = 0x8a14;
	almanaclist[0].tauc_high = 0x7f01;
	almanaclist[0].deltat = 0x780012;
	almanaclist[0].t = 0x00dd01;
	almanaclist[0].lambda = 0x000000;
	almanaclist[0].deltai = 0x920f15;
	almanaclist[0].tauc_low = 0x115;
	almanaclist[0].taun = 0x023;

	almanaclist[1].vfields =  GLOALM_VALID_DAYCOUNT | GLOALM_VALID_SVHEALTH | GLOALM_VALID_E |
		GLOALM_VALID_DOT | GLOALM_VALID_OMEGA | GLOALM_VALID_TAUC | GLOALM_VALID_DELTAT |
		GLOALM_VALID_T;
	almanaclist[1].satslot = 14;
	almanaclist[1].daycount = 400;
	almanaclist[1].svhealth = 0x44;
	almanaclist[1].e = 0x0111;
	almanaclist[1].dot = 0x09;
	almanaclist[1].omega = 0x8a14;
	almanaclist[1].tauc_high = 0x7f01;
	almanaclist[1].deltat = 0x780012;
	almanaclist[1].t = 0x00dd01;
	almanaclist[1].tauc_low = 0x115;

	almanaclist[2].vfields = GLOALM_VALID_DAYCOUNT | GLOALM_VALID_SVHEALTH;
	almanaclist[2].satslot = 11;
	almanaclist[2].daycount = 400;
	almanaclist[2].svhealth = 0;

	result = navi_create_mla_sequence(navi_GL, 3, almanaclist, inbuffer, sizeof(inbuffer), &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
	}
	else
	{
		printf("Composition of MLA failed (%d)\n", navierr_get_last()->errclass);
	}

	printf("msglength = %d\n", msglength);
	printf("message = '%s'\n", inbuffer);

	finished = 0;
	parsed = 0;
	nmread = 0;

	do
	{
		while ((result = navi_parse_msg(inbuffer + parsed, sizeof(inbuffer) - parsed,
			sizeof(outbuffer), &msgtype, outbuffer, &nmread)) == navi_Ok)
		{
			parsed += nmread;

			if (msgtype == navi_af_Approved)
			{
				struct approved_field_t s;
				memmove(&s, outbuffer, sizeof(s));

				switch (s.afmt)
				{
				case navi_MLA:
					{
						struct mla_t *mla = (struct mla_t *)((char *)outbuffer + sizeof(s));

						printf("Received MLA:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);
						printf("\tTotal nm of messages: %i\n", mla->totalnm);
						printf("\tMessage number: %i\n", mla->msgnm);

						printf("\tSatellite slot number: %u\n", mla->alm.satslot);
						if (mla->alm.vfields & GLOALM_VALID_DAYCOUNT)
							printf("\tDays count: %u\n", mla->alm.daycount);
						if (mla->alm.vfields & GLOALM_VALID_SVHEALTH)
							printf("\tSV health: 0x%x\n", mla->alm.svhealth);
						if (mla->alm.vfields & GLOALM_VALID_E)
							printf("\tEccentricity: 0x%x\n", mla->alm.e);
						if (mla->alm.vfields & GLOALM_VALID_DOT)
							printf("\tDOT: 0x%x\n", mla->alm.dot);
						if (mla->alm.vfields & GLOALM_VALID_OMEGA)
							printf("\tOmega n: 0x%x\n", mla->alm.omega);
						if (mla->alm.vfields & GLOALM_VALID_TAUC)
							printf("\tTau c (high): 0x%x\n", mla->alm.tauc_high);
						if (mla->alm.vfields & GLOALM_VALID_DELTAT)
						{
							printf("\tDelta T n: 0x%x\n",
								mla->alm.deltat);
						}
						if (mla->alm.vfields & GLOALM_VALID_T)
							printf("\tt n: 0x%x\n", mla->alm.t);
						if (mla->alm.vfields & GLOALM_VALID_LAMBDA)
							printf("\tLambda n: 0x%x\n", mla->alm.lambda);
						if (mla->alm.vfields & GLOALM_VALID_DELTAI)
							printf("\tDelta i n: 0x%x\n", mla->alm.deltai);
						if (mla->alm.vfields & GLOALM_VALID_TAUC)
							printf("\tTau c (low): 0x%x\n", mla->alm.tauc_low);
						if (mla->alm.vfields & GLOALM_VALID_TAUN)
							printf("\tTau n: 0x%x\n", mla->alm.taun);
					}
					break;
				default:
					break;
				}
			}
		}

		lasterr = navierr_get_last();

		if (lasterr->errclass == navi_CrcEror)
		{
			printf("CRC error\n");
			parsed += nmread;	// advance to parse next message
		}
		else if (lasterr->errclass == navi_MsgNotSupported)
		{
			parsed += nmread;	// advance to parse next message

			switch (msgtype)
			{
			case navi_MLA:
				printf("Could not parse MLA\n");
				break;
			default:
				break;
			}
		}
		else if (lasterr->errclass == navi_NoValidMessage)
		{
			printf("Buffer emptied (%d)\n", lasterr->errclass);
			finished = 1;
		}
		else
		{
			printf("Parsing result = %d\n", lasterr->errclass);
			finished = 1;
		}
	} while (!finished);

#ifdef _MSC_VER
	printf("Size of struct mla_t = %Iu\n", sizeof(struct mla_t));
#else
	printf("Size of struct mla_t = %zu\n", sizeof(struct mla_t));
#endif // MSVC_VER

	return 0;
}
