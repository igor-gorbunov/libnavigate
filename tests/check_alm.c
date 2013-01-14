/*
 * check_alm.c - ALM messages generating/parsing tests and usage examples.
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
	struct navi_gpsalm_t almanaclist[8];

	navi_addrfield_t msgtype;
	const navi_error_t *lasterr;

	msglength = 0;

	// ALM
	almanaclist[0].vfields = GPSALM_VALID_GPSWEEK | GPSALM_VALID_SVHEALTH | GPSALM_VALID_E |
		GPSALM_VALID_TOA | GPSALM_VALID_SIGMAI | GPSALM_VALID_OMEGADOT | GPSALM_VALID_SQRTSEMIAXIS |
		GPSALM_VALID_OMEGA | GPSALM_VALID_OMEGA0 | GPSALM_VALID_M0 | GPSALM_VALID_AF0 | GPSALM_VALID_AF1;
	almanaclist[0].satelliteprn = 4;
	almanaclist[0].gpsweek = 3400;
	almanaclist[0].svhealth = 0x44;
	almanaclist[0].e = 0x0011;
	almanaclist[0].toa = 0x09;
	almanaclist[0].sigmai = 0x8a14;
	almanaclist[0].omegadot = 0x7f01;
	almanaclist[0].sqrtsemiaxis = 0x780012;
	almanaclist[0].omega = 0x00dd01;
	almanaclist[0].omega0 = 0x000000;
	almanaclist[0].m0 = 0x920f15;
	almanaclist[0].af0 = 0x115;
	almanaclist[0].af1 = 0x023;

	almanaclist[1].vfields = GPSALM_VALID_GPSWEEK | GPSALM_VALID_SVHEALTH | GPSALM_VALID_E |
		GPSALM_VALID_TOA | GPSALM_VALID_SIGMAI | GPSALM_VALID_OMEGADOT | GPSALM_VALID_SQRTSEMIAXIS |
		GPSALM_VALID_OMEGA | GPSALM_VALID_OMEGA0 | GPSALM_VALID_M0;
	almanaclist[1].satelliteprn = 14;
	almanaclist[1].gpsweek = 3400;
	almanaclist[1].svhealth = 0xaf;
	almanaclist[1].e = 0x0011;
	almanaclist[1].toa = 0x00;
	almanaclist[1].sigmai = 0x8114;
	almanaclist[1].omegadot = 0x7701;
	almanaclist[1].sqrtsemiaxis = 0x000012;
	almanaclist[1].omega = 0x002201;
	almanaclist[1].omega0 = 0x000000;
	almanaclist[1].m0 = 0x920115;

	almanaclist[2].vfields = GPSALM_VALID_GPSWEEK | GPSALM_VALID_SVHEALTH;
	almanaclist[2].satelliteprn = 32;
	almanaclist[2].gpsweek = 3400;
	almanaclist[2].svhealth = 0x00;

	result = navi_create_alm_sequence(navi_GP, 3, almanaclist, inbuffer, sizeof(inbuffer), &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
	}
	else
	{
		printf("Composition of ALM failed (%d)\n", navierr_get_last()->errclass);
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
				case navi_ALM:
					{
						struct alm_t *alm = (struct alm_t *)((char *)outbuffer + sizeof(s));

						printf("Received ALM:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);
						printf("\tTotal nm of messages: %i\n", alm->totalnm);
						printf("\tMessage number: %i\n", alm->msgnm);

						printf("\tSatellite PRN number: %u\n", alm->alm.satelliteprn);
						if (alm->alm.vfields & GPSALM_VALID_GPSWEEK)
							printf("\tGPS week number: %u\n", alm->alm.gpsweek);
						if (alm->alm.vfields & GPSALM_VALID_SVHEALTH)
							printf("\tSV health: 0x%x\n", alm->alm.svhealth);
						if (alm->alm.vfields & GPSALM_VALID_E)
							printf("\tEccentricity: 0x%x\n", alm->alm.e);
						if (alm->alm.vfields & GPSALM_VALID_TOA)
							printf("\tAlmanac reference time: 0x%x\n", alm->alm.toa);
						if (alm->alm.vfields & GPSALM_VALID_SIGMAI)
							printf("\tInclination angle: 0x%x\n", alm->alm.sigmai);
						if (alm->alm.vfields & GPSALM_VALID_OMEGADOT)
							printf("\tRate of ascension: 0x%x\n", alm->alm.omegadot);
						if (alm->alm.vfields & GPSALM_VALID_SQRTSEMIAXIS)
						{
							printf("\tRoot of semi-major axis: 0x%x\n",
								alm->alm.sqrtsemiaxis);
						}
						if (alm->alm.vfields & GPSALM_VALID_OMEGA)
							printf("\tArgument of perigee: 0x%x\n", alm->alm.omega);
						if (alm->alm.vfields & GPSALM_VALID_OMEGA0)
							printf("\tLongitude of ascension: 0x%x\n", alm->alm.omega0);
						if (alm->alm.vfields & GPSALM_VALID_M0)
							printf("\tMean anomaly: 0x%x\n", alm->alm.m0);
						if (alm->alm.vfields & GPSALM_VALID_AF0)
							printf("\tClock parameter 1: 0x%x\n", alm->alm.af0);
						if (alm->alm.vfields & GPSALM_VALID_AF1)
							printf("\tClock parameter 2: 0x%x\n", alm->alm.af1);
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
			case navi_ALM:
				printf("Could not parse ALM\n");
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
	printf("Size of struct alm_t = %Iu\n", sizeof(struct alm_t));
#else
	printf("Size of struct alm_t = %zu\n", sizeof(struct alm_t));
#endif // MSVC_VER

	return 0;
}
