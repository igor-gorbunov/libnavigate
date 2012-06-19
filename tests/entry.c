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

#include <libnavigate/iecgenerator.h>
#include <libnavigate/iecparser.h>

#include <stdio.h>
#include <errno.h>

int main()
{
	enum naviError_t result;
	size_t msglength, nmwritten, nmread;
	size_t remain;

	char buffer[1024];
	struct dtm_t dtm;
	struct gll_t gll;
	struct gns_t gns;
	struct rmc_t rmc;
	struct vtg_t vtg;
	struct zda_t zda;

	msglength = 0;
	remain = sizeof(buffer);

	// ZDA
	zda.tid = naviTalkerId_GL;
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

	nmwritten = 0;
	result = IecComposeMessage(naviSentence_ZDA, &zda, buffer + msglength,
		remain, &nmwritten);
	if (result == naviError_OK)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of ZDA failed (%d)\n", result);
	}

	// DTM
	dtm.tid = naviTalkerId_GP;
	dtm.vfields = DTM_VALID_LOCALDATUM | DTM_VALID_LATOFFSET |
		DTM_VALID_LONOFFSET | DTM_VALID_ALTITUDEOFFSET |
		DTM_VALID_REFERENCEDATUM;
	dtm.ld = naviDatum_UserDefined;
	dtm.latofs.offset = 2.4366;
	dtm.latofs.sign = naviOfsSign_North;
	dtm.lonofs.offset = 3.81825;
	dtm.lonofs.sign = naviOfsSign_West;
	dtm.altoffset = 3.446;
	dtm.rd = naviDatum_WGS84;

	result = IecComposeMessage(naviSentence_DTM, &dtm, buffer + msglength,
		remain, &nmwritten);
	if (result == naviError_OK)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of DTM failed (%d)\n", result);
	}

	// GLL
	gll.tid = naviTalkerId_SN;
	gll.vfields = GLL_VALID_LATITUDE | GLL_VALID_LONGITUDE | GLL_VALID_UTC;
	gll.latitude.offset = 0.02;
	gll.latitude.sign = naviOfsSign_North;
	gll.longitude.offset = 0.00000000999;
	gll.longitude.sign = naviOfsSign_East;
	gll.utc.hour = 4;
	gll.utc.min = 34;
	gll.utc.sec = 18;
	gll.utc.msec = 4;
	gll.status = naviStatus_DataValid;
	gll.mi = naviModeIndicator_Autonomous;

	result = IecComposeMessage(naviSentence_GLL, &gll, buffer + msglength,
		remain, &nmwritten);
	if (result == naviError_OK)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GLL failed (%d)\n", result);
	}

	// GNS
	gns.tid = naviTalkerId_GL;
	gns.vfields = GNS_VALID_UTC | GNS_VALID_LATITUDE | GNS_VALID_LONGITUDE |
		GNS_VALID_MODEINDICATOR | GNS_VALID_TOTALNMOFSATELLITES |
		GNS_VALID_HDOP  | GNS_VALID_ANTENNAALTITUDE | GNS_VALID_GEOIDALSEP |
		GNS_VALID_AGEOFDIFFDATA | GNS_VALID_DIFFREFSTATIONID;
	gns.utc.hour = 20;
	gns.utc.min = 0;
	gns.utc.sec = 0;
	gns.utc.msec = 0;
	gns.latitude.offset = 60.;
	gns.latitude.sign = naviOfsSign_North;
	gns.longitude.offset = 30.;
	gns.longitude.sign = naviOfsSign_East;
	gns.mi[0] = naviModeIndicator_Autonomous;
	gns.mi[1] = naviModeIndicator_Differential;
	gns.totalsats = 4;
	gns.hdop = 2.3;
	gns.antaltitude = 2.003;
	gns.geoidalsep = 18.2;
	gns.diffage = 4;
	gns.id = 13;

	result = IecComposeMessage(naviSentence_GNS, &gns, buffer + msglength,
		remain, &nmwritten);
	if (result == naviError_OK)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GNS failed (%d)\n", result);
	}

	// RMC
	rmc.tid = naviTalkerId_GL;
	rmc.vfields = RMC_VALID_UTC | RMC_VALID_LATITUDE |
		RMC_VALID_LONGITUDE | RMC_VALID_DATE;
	rmc.utc.hour = 9;
	rmc.utc.min = 19;
	rmc.utc.sec = 39;
	rmc.utc.msec = 980;
	rmc.status = naviStatus_DataInvalid;
	rmc.latitude.offset = 74.64772882;
	rmc.latitude.sign = naviOfsSign_South;
	rmc.longitude.offset = 132.0000333;
	rmc.longitude.sign = naviOfsSign_East;
	rmc.speed = 1.03553;
	rmc.courseTrue = 180.2112;
	rmc.day = 18;
	rmc.month = 3;
	rmc.year = 2012;
	rmc.magnetic.offset = 23.011;
	rmc.magnetic.sign = naviOfsSign_East;
	rmc.mi = naviModeIndicator_Estimated;
	// Part 1
	result = IecComposeMessage(naviSentence_RMC, &rmc, buffer + msglength,
		remain, &nmwritten);
	if (result == naviError_OK)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of RMC failed (%d)\n", result);
	}
	// Part 2
	rmc.vfields = RMC_VALID_UTC | RMC_VALID_SPEED | RMC_VALID_COURSETRUE |
		RMC_VALID_DATE | RMC_VALID_MAGNVARIATION;
	result = IecComposeMessage(naviSentence_RMC, &rmc, buffer + msglength,
		remain, &nmwritten);
	if (result == naviError_OK)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of RMC failed (%d)\n", result);
	}

	// VTG
	vtg.tid = naviTalkerId_VW;
	vtg.vfields = VTG_VALID_COURSETRUE  | VTG_VALID_COURSEMAGN | VTG_VALID_SPEED;
	vtg.courseTrue = 0.223;
	vtg.courseMagn = 22.203;
	vtg.speed = 1.023;
	vtg.mi = naviModeIndicator_Simulator;

	result = IecComposeMessage(naviSentence_VTG, &vtg, buffer + msglength,
		remain, &nmwritten);
	if (result == naviError_OK)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of VTG failed (%d)\n", result);
	}

	printf("msglength = %zu\n", msglength);
	printf("message = '%s'\n", buffer);

	char parsedbuffer[1024];
	int finished, parsed;
	enum naviSentence_t msgtype;

	finished = 0;
	parsed = 0;
	nmread = 0;

	do
	{
		while ((result = IecParseMessage(buffer + parsed, sizeof(buffer) - parsed,
			sizeof(parsedbuffer), parsedbuffer, &msgtype, &nmread)) == naviError_OK)
		{
			parsed += nmread;

			switch (msgtype)
			{
			case naviSentence_DTM:
				{
					struct dtm_t *dtm = (struct dtm_t *)parsedbuffer;
					printf("Received DTM: talker id = %d\n", dtm->tid);

					if (dtm->vfields & DTM_VALID_LOCALDATUM)
					{
						printf("\tlocal datum = %d\n", dtm->ld);
					}
					if (dtm->vfields & DTM_VALID_LOCALDATUMSUB)
					{
						printf("\tlocal datum subdivision = %d\n", dtm->lds);
					}
					if (dtm->vfields & DTM_VALID_LATOFFSET)
					{
						printf("\tlatitude offset = %.8f (%d)\n",
							dtm->latofs.offset, dtm->latofs.sign);
					}
					if (dtm->vfields & DTM_VALID_LONOFFSET)
					{
						printf("\tlongitude offset = %.8f (%d)\n",
							dtm->lonofs.offset, dtm->lonofs.sign);
					}
					if (dtm->vfields & DTM_VALID_ALTITUDEOFFSET)
					{
						printf("\taltitude offset = %.8f\n", dtm->altoffset);
					}
					if (dtm->vfields & DTM_VALID_REFERENCEDATUM)
					{
						printf("\treference datum = %d\n", dtm->rd);
					}
				}
				break;
			case naviSentence_GLL:
				{
					struct gll_t *gll = (struct gll_t *)parsedbuffer;
					printf("Received GLL: talker id = %d\n", gll->tid);

					if (gll->vfields & GLL_VALID_LATITUDE)
					{
						printf("\tlatitude = %.12f (%d)\n", gll->latitude.offset,
							gll->latitude.sign);
					}
					if (gll->vfields & GLL_VALID_LONGITUDE)
					{
						printf("\tlongitude = %.12f (%d)\n", gll->longitude.offset,
							gll->longitude.sign);
					}
					if (gll->vfields & GLL_VALID_UTC)
					{
						printf("\tutc = %d %d %d %d\n", gll->utc.hour,
							gll->utc.min, gll->utc.sec, gll->utc.msec);
					}

					printf("\tstatus = %d\n", gll->status);
					printf("\tmode indicator = %d\n", gll->mi);
				}
				break;
			case naviSentence_GNS:
				{
					struct gns_t *gns = (struct gns_t *)parsedbuffer;
					printf("Received GNS: talker id = %d\n", gns->tid);

					if (gns->vfields & GNS_VALID_UTC)
					{
						printf("\tutc = %d %d %d %d\n", gns->utc.hour,
							gns->utc.min, gns->utc.sec, gns->utc.msec);
					}
					if (gns->vfields & GNS_VALID_LATITUDE)
					{
						printf("\tlatitude = %.12f (%d)\n", gns->latitude.offset,
							gns->latitude.sign);
					}
					if (gns->vfields & GNS_VALID_LONGITUDE)
					{
						printf("\tlongitude = %.12f (%d)\n", gns->longitude.offset,
							gns->longitude.sign);
					}
					printf("\tmode indicator = %d %d\n", gns->mi[0], gns->mi[1]);
					if (gns->vfields & GNS_VALID_TOTALNMOFSATELLITES)
					{
						printf("\tsatellites = %d\n", gns->totalsats);
					}
					if (gns->vfields & GNS_VALID_HDOP)
					{
						printf("\thdop = %.12f\n", gns->hdop);
					}
					if (gns->vfields & GNS_VALID_ANTENNAALTITUDE)
					{
						printf("\tantenna altitude = %.12f\n", gns->antaltitude);
					}
					if (gns->vfields & GNS_VALID_GEOIDALSEP)
					{
						printf("\tgeoidal separation = %.12f\n", gns->geoidalsep);
					}
					if (gns->vfields & GNS_VALID_AGEOFDIFFDATA)
					{
						printf("\tage of dd = %.12f\n", gns->diffage);
					}
					if (gns->vfields & GNS_VALID_DIFFREFSTATIONID)
					{
						printf("\tid = %d\n", gns->id);
					}
				}
				break;
			case naviSentence_RMC:
				{
					struct rmc_t *rmc = (struct rmc_t *)parsedbuffer;
					printf("Received RMC: talker id = %d\n", rmc->tid);

					if (rmc->vfields & RMC_VALID_UTC)
					{
						printf("\tutc = %d %d %d %d\n", rmc->utc.hour,
							rmc->utc.min, rmc->utc.sec, rmc->utc.msec);
					}
					printf("\tstatus = %d\n", rmc->status);
					if (rmc->vfields & RMC_VALID_LATITUDE)
					{
						printf("\tlatitude = %.12f (%d)\n", rmc->latitude.offset,
							rmc->latitude.sign);
					}
					if (rmc->vfields & RMC_VALID_LONGITUDE)
					{
						printf("\tlongitude = %.12f (%d)\n", rmc->longitude.offset,
							rmc->longitude.sign);
					}
					if (rmc->vfields & RMC_VALID_SPEED)
					{
						printf("\tspeed = %.12f\n", rmc->speed);
					}
					if (rmc->vfields & RMC_VALID_COURSETRUE)
					{
						printf("\tcourse, true = %.12f\n", rmc->courseTrue);
					}
					if (rmc->vfields & RMC_VALID_DATE)
					{
						printf("\tdate = %d %d %d\n", rmc->day,
							rmc->month, rmc->year);
					}
					if (rmc->vfields & RMC_VALID_MAGNVARIATION)
					{
						printf("\tmagnetic variation = %.12f (%d)\n",
							rmc->magnetic.offset, rmc->magnetic.sign);
					}
					printf("\tmode indicator = %d\n", rmc->mi);
				}
				break;
			case naviSentence_VTG:
				{
					struct vtg_t *vtg = (struct vtg_t *)parsedbuffer;
					printf("Received VTG: talker id = %d\n", vtg->tid);

					if (vtg->vfields & VTG_VALID_COURSETRUE)
					{
						printf("\tcource, true = %.12f\n", vtg->courseTrue);
					}
					if (vtg->vfields & VTG_VALID_COURSEMAGN)
					{
						printf("\tcourse, magnetic = %.12f\n", vtg->courseMagn);
					}
					if (vtg->vfields & VTG_VALID_SPEED)
					{
						printf("\tspeed = %.12f\n", vtg->speed);
					}
					printf("\tmode indicator = %d\n", vtg->mi);
				}
				break;
			case naviSentence_ZDA:
				{
//					struct zda_t *zda = (struct zda_t *)parsedbuffer;
					printf("Received ZDA: \n");
				}
				break;
			default:
				break;
			}
		}
		if (result == naviError_CrcEror)
		{
			printf("CRC error\n");
			parsed += nmread;	// advance to parse next message
		}
		else if (result == naviError_MsgNotSupported)
		{
			parsed += nmread;	// advance to parse next message

			switch (msgtype)
			{
			case naviSentence_DTM:
				{
					printf("Could not parse DTM\n");
				}
				break;
			case naviSentence_GLL:
				{
					printf("Could not parse GLL\n");
				}
				break;
			case naviSentence_GNS:
				{
					printf("Could not parse GNS\n");
				}
				break;
			case naviSentence_RMC:
				{
					printf("Could not parse RMC\n");
				}
				break;
			case naviSentence_VTG:
				{
					printf("Could not parse VTG\n");
				}
				break;
			case naviSentence_ZDA:
				{
					printf("Could not parse ZDA\n");
				}
				break;
			default:
				break;
			}
		}
		else if (result == naviError_NoValidMessage)
		{
			printf("Buffer emptied (%d)\n", result);
			finished = 1;
		}
		else
		{
			printf("Parsing result = %d\n", result);
			finished = 1;
		}
	} while (!finished);

	return 0;
}

