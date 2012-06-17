/*
 * entry.c - IEC messages generating/parsing tests and usage examples.
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

#include <libnavi/iecgenerator.h>
#include <libnavi/iecparser.h>

#include <stdio.h>
#include <errno.h>

int main()
{
	char buffer[1024];
	struct zda_t zda;
	struct dtm_t dtm;
	struct gll_t gll;
	struct gns_t gns;
	struct rmc_t rmc;
	struct vtg_t vtg;
	int result, msglength;

	msglength = 0;

	zda.tid = _GL;
	zda.vfields = ZDA_VALID_UTC | ZDA_VALID_DAY | ZDA_VALID_MONTH |
		ZDA_VALID_YEAR | ZDA_VALID_LOCALZONE;
	zda.utc.hour = 8;
	zda.utc.min = 12;
	zda.utc.sec = 38;
	zda.utc.msec = 56;
	zda.day = 25;
	zda.month = 5;
	zda.year = 1982;
	zda.lzoffset = -240;

	result = IecComposeMessage(_ZDA, &zda, buffer, sizeof(buffer));
	if (result >= 0)
	{
		msglength += result;
	}
	else
	{
		printf("result = %d\n", result);
		result = 0;
	}

	dtm.tid = _GP;
	dtm.vfields = DTM_VALID_LOCALDATUM | DTM_VALID_LATOFFSET |
		DTM_VALID_LONOFFSET | DTM_VALID_ALTITUDEOFFSET |
		DTM_VALID_REFERENCEDATUM;
	dtm.ld = _UserDefined;
	dtm.latofs.offset = 2.4366;
	dtm.latofs.offsign = _North;
	dtm.lonofs.offset = 3.81825;
	dtm.lonofs.offsign = _West;
	dtm.altoffset = 3.446;
	dtm.rd = _WGS84;

	result = IecComposeMessage(_DTM, &dtm, buffer + msglength,
		sizeof(buffer) - msglength);
	if (result >= 0)
	{
		msglength += result;
	}
	else
	{
		printf("result = %d\n", result);
		result = 0;
	}

	gll.tid = _SN;
	gll.vfields = GLL_VALID_LATITUDE | GLL_VALID_LONGITUDE | GLL_VALID_UTC;
	gll.latitude.offset = 0.02;
	gll.latitude.offsign = _North;
	gll.longitude.offset = 0.00000000999;
	gll.longitude.offsign = _East;
	gll.utc.hour = 4;
	gll.utc.min = 34;
	gll.utc.sec = 18;
	gll.utc.msec = 4;
	gll.status = _DataValid;
	gll.mi = _Autonomous;

	result = IecComposeMessage(_GLL, &gll, buffer + msglength,
		sizeof(buffer) - msglength);
	if (result >= 0)
	{
		msglength += result;
	}
	else
	{
		printf("result = %d\n", result);
		result = 0;
	}

	gns.tid = _GL;
	gns.vfields = GNS_VALID_UTC | GNS_VALID_LATITUDE | GNS_VALID_LONGITUDE |
		GNS_VALID_MODEINDICATOR | GNS_VALID_TOTALNMOFSATELLITES |
		GNS_VALID_HDOP  | GNS_VALID_ANTENNAALTITUDE | GNS_VALID_GEOIDALSEP |
		GNS_VALID_AGEOFDIFFDATA | GNS_VALID_DIFFREFSTATIONID;
	gns.utc.hour = 20;
	gns.utc.min = 0;
	gns.utc.sec = 0;
	gns.utc.msec = 0;
	gns.latitude.offset = 60.;
	gns.latitude.offsign = _North;
	gns.longitude.offset = 30.;
	gns.longitude.offsign = _East;
	gns.mi[0] = _Autonomous;
	gns.mi[1] = _Differential;
	gns.totalsats = 4;
	gns.hdop = 2.3;
	gns.antaltitude = 2.003;
	gns.geoidalsep = 18.2;
	gns.diffage = 4;
	gns.id = 13;

	result = IecComposeMessage(_GNS, &gns, buffer + msglength,
		sizeof(buffer) - msglength);
	if (result >= 0)
	{
		msglength += result;
	}
	else
	{
		printf("result = %d\n", result);
		result = 0;
	}

	rmc.tid = _GL;
	rmc.vfields = RMC_VALID_UTC | RMC_VALID_LATITUDE |
		RMC_VALID_LONGITUDE | RMC_VALID_DATE;
	rmc.utc.hour = 9;
	rmc.utc.min = 19;
	rmc.utc.sec = 39;
	rmc.utc.msec = 980;
	rmc.status = _DataInvalid;
	rmc.latitude.offset = 74.64772882;
	rmc.latitude.offsign = _South;
	rmc.longitude.offset = 132.0000333;
	rmc.longitude.offsign = _East;
	rmc.speed = 1.03553;
	rmc.courseTrue = 180.2112;
	rmc.day = 18;
	rmc.month = 3;
	rmc.year = 2012;
	rmc.magnetic.offset = 23.011;
	rmc.magnetic.offsign = _East;
	rmc.mi = _Estimated;

	result = IecComposeMessage(_RMC, &rmc, buffer + msglength,
		sizeof(buffer) - msglength);
	if (result >= 0)
	{
		msglength += result;
	}
	else
	{
		printf("result = %d\n", result);
		result = 0;
	}

	rmc.vfields = RMC_VALID_UTC | RMC_VALID_SPEED | RMC_VALID_COURSETRUE |
		RMC_VALID_DATE | RMC_VALID_MAGNVARIATION;

	result = IecComposeMessage(_RMC, &rmc, buffer + msglength,
		sizeof(buffer) - msglength);
	if (result >= 0)
	{
		msglength += result;
	}
	else
	{
		printf("result = %d\n", result);
		result = 0;
	}

	vtg.tid = _VW;
	vtg.vfields = VTG_VALID_COURSETRUE  | VTG_VALID_COURSEMAGN | VTG_VALID_SPEED;
	vtg.courseTrue = 0.223;
	vtg.courseMagn = 22.203;
	vtg.speed = 1.023;
	vtg.mi = _Simulator;

	result = IecComposeMessage(_VTG, &vtg, buffer + msglength,
		sizeof(buffer) - msglength);
	if (result >= 0)
	{
		msglength += result;
	}
	else
	{
		printf("result = %d\n", result);
		result = 0;
	}

	printf("msglength = %d\n", msglength);
	printf("message = %s\n", buffer);

	char parsedbuffer[1024];
	int finished, parsed;
	enum naviSentence_t msgtype;

	finished = 0;
	parsed = 0;

	do
	{
		while ((result = IecParseMessage(buffer + parsed, sizeof(buffer) - parsed,
			sizeof(parsedbuffer), parsedbuffer, &msgtype)) > 0)
		{
			parsed += result;

			switch (msgtype)
			{
			case _DTM:
				{
					struct dtm_t *dtm = (struct dtm_t *)parsedbuffer;
					printf("Received DTM: \n");
				}
				break;
			case _GLL:
				{
					struct gll_t *gll = (struct gll_t *)parsedbuffer;
					printf("Received GLL: \n");
				}
				break;
			case _GNS:
				{
					struct gns_t *gns = (struct gns_t *)parsedbuffer;
					printf("Received GNS: \n");
				}
				break;
			case _RMC:
				{
					struct rmc_t *rmc = (struct rmc_t *)parsedbuffer;
					printf("Received RMC: \n");
				}
				break;
			case _VTG:
				{
					struct vtg_t *vtg = (struct vtg_t *)parsedbuffer;
					printf("Received VTG: \n");
				}
				break;
			case _ZDA:
				{
					struct zda_t *zda = (struct zda_t *)parsedbuffer;
					printf("Received ZDA: \n");
				}
				break;
			}
		}
		if (result == -EPROTO)
		{
			printf("CRC error\n");
			parsed += 1;	// advance one character to parse next message
		}
		else if (result == -ENOSYS)
		{
			parsed += 1;	// advance one character to parse next message

			switch (msgtype)
			{
			case _DTM:
				{
					struct dtm_t *dtm = (struct dtm_t *)parsedbuffer;
					printf("Received DTM: \n");
				}
				break;
			case _GLL:
				{
					struct gll_t *gll = (struct gll_t *)parsedbuffer;
					printf("Received GLL: \n");
				}
				break;
			case _GNS:
				{
					struct gns_t *gns = (struct gns_t *)parsedbuffer;
					printf("Received GNS: \n");
				}
				break;
			case _RMC:
				{
					struct rmc_t *rmc = (struct rmc_t *)parsedbuffer;
					printf("Received RMC: \n");
				}
				break;
			case _VTG:
				{
					struct vtg_t *vtg = (struct vtg_t *)parsedbuffer;
					printf("Received VTG: \n");
				}
				break;
			case _ZDA:
				{
					struct zda_t *zda = (struct zda_t *)parsedbuffer;
					printf("Received ZDA: \n");
				}
				break;
			}
		}
		else
		{
			printf("Parsing result = %d\n", result);
			finished = 1;
		}
	} while (!finished);

	return 0;
}

