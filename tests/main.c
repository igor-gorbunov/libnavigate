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

#include <navigate.h>

#include <stdio.h>
#include <errno.h>

int main(void)
{
	int result;
	int msglength, nmwritten, nmread;
	int remain;

	char buffer[1024];
	struct dtm_t dtm;
	struct gll_t gll;
	struct gns_t gns;
	struct rmc_t rmc;
	struct vtg_t vtg;
	struct zda_t zda;

	char parsedbuffer[1024];
	int finished, parsed;
	int msgtype;

	const navi_error_t *lasterr;

	msglength = 0;
	remain = sizeof(buffer);

	// ZDA
	zda.tid = navi_GL;
	zda.vfields = ZDA_VALID_UTC | ZDA_VALID_DAY | ZDA_VALID_MONTH |
		ZDA_VALID_YEAR | ZDA_VALID_LOCALZONE;
	zda.utc.hour = 8;
	zda.utc.min = 12;
	zda.utc.sec = 38.56;
	zda.date.day = 25;
	zda.date.month = 5;
	zda.date.year = 1982;
	zda.lzoffset = -240;

	nmwritten = 0;
	result = navi_create_msg(navi_ZDA, &zda, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of ZDA failed (%d)\n", result);
	}

	// DTM
	dtm.tid = navi_GP;
	dtm.vfields = DTM_VALID_LOCALDATUM | DTM_VALID_OFFSET |
		DTM_VALID_ALTOFFSET | DTM_VALID_REFDATUM;
	dtm.locdatum = navi_UserDefined;
	dtm.latofs.offset = 2.4366;
	dtm.latofs.sign = navi_North;
	dtm.lonofs.offset = 3.81825;
	dtm.lonofs.sign = navi_West;
	dtm.altoffset = 3.446;
	dtm.refdatum = navi_WGS84;

	result = navi_create_msg(navi_DTM, &dtm, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of DTM failed (%d)\n", result);
	}

	// GLL
	gll.tid = navi_SN;
	gll.vfields = GLL_VALID_POSITION_FIX | GLL_VALID_UTC;
	gll.fix.latitude = 0.02;
	gll.fix.latsign = navi_North;
	gll.fix.longitude = 0.00000000999;
	gll.fix.lonsign = navi_East;
	gll.utc.hour = 4;
	gll.utc.min = 34;
	gll.utc.sec = 18.4;
	gll.status = navi_DataValid;
	gll.mi = navi_Autonomous;

	result = navi_create_msg(navi_GLL, &gll, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GLL failed (%d)\n", result);
	}

	// GNS
	gns.tid = navi_GL;
	gns.vfields = GNS_VALID_UTC | GNS_VALID_POSITION_FIX |
		GNS_VALID_MODEINDICATOR | GNS_VALID_TOTALNMOFSATELLITES |
		GNS_VALID_HDOP | GNS_VALID_ANTENNAALTITUDE | GNS_VALID_GEOIDALSEP |
		GNS_VALID_AGEOFDIFFDATA | GNS_VALID_DIFFREFSTATIONID;
	gns.utc.hour = 20;
	gns.utc.min = 0;
	gns.utc.sec = 0.;
	gns.fix.latitude = 60.;
	gns.fix.latsign = navi_North;
	gns.fix.longitude = 30.;
	gns.fix.lonsign = navi_East;
	gns.mi[0] = navi_Autonomous;
	gns.mi[1] = navi_Differential;
	gns.totalsats = 4;
	gns.hdop = 2.3;
	gns.antaltitude = 2.003;
	gns.geoidalsep = 18.2;
	gns.diffage = 4;
	gns.id = 13;

	result = navi_create_msg(navi_GNS, &gns, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GNS failed (%d)\n", result);
	}

	// RMC
	rmc.tid = navi_GL;
	rmc.vfields = RMC_VALID_UTC | RMC_VALID_POSITION_FIX | RMC_VALID_DATE;
	rmc.utc.hour = 9;
	rmc.utc.min = 19;
	rmc.utc.sec = 39.98;
	rmc.status = navi_DataInvalid;
	rmc.fix.latitude = 74.64772882;
	rmc.fix.latsign = navi_South;
	rmc.fix.longitude = 132.0000333;
	rmc.fix.lonsign = navi_East;
	rmc.speed = 1.03553;
	rmc.courseTrue = 180.2112;
	rmc.date.day = 18;
	rmc.date.month = 3;
	rmc.date.year = 2012;
	rmc.magnetic.offset = 23.011;
	rmc.magnetic.sign = navi_East;
	rmc.mi = navi_Estimated;
	// Part 1
	result = navi_create_msg(navi_RMC, &rmc, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
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
	result = navi_create_msg(navi_RMC, &rmc, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of RMC failed (%d)\n", result);
	}

	// VTG
	vtg.tid = navi_VW;
	vtg.vfields = VTG_VALID_COURSETRUE | VTG_VALID_COURSEMAGN | VTG_VALID_SPEED;
	vtg.courseTrue = 0.223;
	vtg.courseMagn = 22.203;
	vtg.speed = 1.023;
	vtg.mi = navi_Simulator;

	result = navi_create_msg(navi_VTG, &vtg, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of VTG failed (%d)\n", result);
	}

	printf("msglength = %d\n", msglength);
	printf("message = '%s'\n", buffer);

	finished = 0;
	parsed = 0;
	nmread = 0;

	do
	{
		while ((result = navi_parse_msg(buffer + parsed, sizeof(buffer) - parsed,
			sizeof(parsedbuffer), parsedbuffer, &msgtype, &nmread)) == navi_Ok)
		{
			parsed += nmread;

			switch (msgtype)
			{
			case navi_DTM:
				{
					struct dtm_t *dtm = (struct dtm_t *)parsedbuffer;
					printf("Received DTM:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(dtm->tid), dtm->tid);

					if (dtm->vfields & DTM_VALID_LOCALDATUM)
					{
						printf("\tlocal datum = %d\n", dtm->locdatum);
					}
					if (dtm->vfields & DTM_VALID_LOCALDATUMSUB)
					{
						printf("\tlocal datum subdivision = %d\n", dtm->locdatumsub);
					}
					if (dtm->vfields & DTM_VALID_OFFSET)
					{
						printf("\tlatitude offset = %.8f %s (%d)\n", dtm->latofs.offset,
							navi_fixsign_str(dtm->latofs.sign, 1), dtm->latofs.sign);
					}
					if (dtm->vfields & DTM_VALID_OFFSET)
					{
						printf("\tlongitude offset = %.8f %s (%d)\n", dtm->lonofs.offset,
							navi_fixsign_str(dtm->lonofs.sign, 1), dtm->lonofs.sign);
					}
					if (dtm->vfields & DTM_VALID_ALTOFFSET)
					{
						printf("\taltitude offset = %.8f\n", dtm->altoffset);
					}
					if (dtm->vfields & DTM_VALID_REFDATUM)
					{
						printf("\treference datum = %d\n", dtm->refdatum);
					}
				}
				break;
			case navi_GLL:
				{
					struct gll_t *gll = (struct gll_t *)parsedbuffer;
					printf("Received GLL:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(gll->tid), gll->tid);

					if (gll->vfields & GLL_VALID_POSITION_FIX)
					{
						printf("\tlatitude = %.12f %s (%d)\n", gll->fix.latitude,
							navi_fixsign_str(gll->fix.latsign, 1), gll->fix.latsign);
					}
					if (gll->vfields & GLL_VALID_POSITION_FIX)
					{
						printf("\tlongitude = %.12f %s (%d)\n", gll->fix.longitude,
							navi_fixsign_str(gll->fix.lonsign, 1), gll->fix.lonsign);
					}
					if (gll->vfields & GLL_VALID_UTC)
					{
						printf("\tutc = %d %d %f\n", gll->utc.hour, gll->utc.min,
							gll->utc.sec);
					}

					printf("\tstatus = %d\n", gll->status);
					printf("\tmode indicator = %d\n", gll->mi);
				}
				break;
			case navi_GNS:
				{
					struct gns_t *gns = (struct gns_t *)parsedbuffer;
					printf("Received GNS:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(gns->tid), gns->tid);

					if (gns->vfields & GNS_VALID_UTC)
					{
						printf("\tutc = %d %d %f\n", gns->utc.hour,
							gns->utc.min, gns->utc.sec);
					}
					if (gns->vfields & GNS_VALID_POSITION_FIX)
					{
						printf("\tlatitude = %.12f %s (%d)\n", gns->fix.latitude,
							navi_fixsign_str(gns->fix.latsign, 1), gns->fix.latsign);
					}
					if (gns->vfields & GNS_VALID_POSITION_FIX)
					{
						printf("\tlongitude = %.12f %s (%d)\n", gns->fix.longitude,
							navi_fixsign_str(gns->fix.lonsign, 1), gns->fix.lonsign);
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
			case navi_RMC:
				{
					struct rmc_t *rmc = (struct rmc_t *)parsedbuffer;
					printf("Received RMC:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(rmc->tid), rmc->tid);

					if (rmc->vfields & RMC_VALID_UTC)
					{
						printf("\tutc = %d %d %f\n", rmc->utc.hour,
							rmc->utc.min, rmc->utc.sec);
					}
					printf("\tstatus = %d\n", rmc->status);
					if (rmc->vfields & RMC_VALID_POSITION_FIX)
					{
						printf("\tlatitude = %.12f %s (%d)\n", rmc->fix.latitude,
							navi_fixsign_str(rmc->fix.latsign, 1), rmc->fix.latsign);
					}
					if (rmc->vfields & RMC_VALID_POSITION_FIX)
					{
						printf("\tlongitude = %.12f %s (%d)\n", rmc->fix.longitude,
							navi_fixsign_str(rmc->fix.lonsign, 1), rmc->fix.lonsign);
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
						printf("\tdate = %d %d %d\n", rmc->date.day,
							rmc->date.month, rmc->date.year);
					}
					if (rmc->vfields & RMC_VALID_MAGNVARIATION)
					{
						printf("\tmagnetic variation = %.12f (%d)\n",
							rmc->magnetic.offset, rmc->magnetic.sign);
					}
					printf("\tmode indicator = %d\n", rmc->mi);
				}
				break;
			case navi_VTG:
				{
					struct vtg_t *vtg = (struct vtg_t *)parsedbuffer;
					printf("Received VTG:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(vtg->tid), vtg->tid);

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
			case navi_ZDA:
				{
					struct zda_t *zda = (struct zda_t *)parsedbuffer;
					printf("Received ZDA:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(zda->tid), zda->tid);

					if (zda->vfields & ZDA_VALID_UTC)
					{
						printf("\tutc = %d %d %f\n", zda->utc.hour,
							zda->utc.min, zda->utc.sec);
					}
					if (zda->vfields & ZDA_VALID_DAY)
					{
						printf("\tday = %d\n", zda->date.day);
					}
					if (zda->vfields & ZDA_VALID_MONTH)
					{
						printf("\tmonth = %d\n", zda->date.month);
					}
					if (zda->vfields & ZDA_VALID_YEAR)
					{
						printf("\tyear = %d\n", zda->date.year);
					}
					if (zda->vfields & ZDA_VALID_LOCALZONE)
					{
						printf("\tlocal zone offset = %d\n", zda->lzoffset);
					}
				}
				break;
			default:
				break;
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
			case navi_DTM:
				{
					printf("Could not parse DTM\n");
				}
				break;
			case navi_GLL:
				{
					printf("Could not parse GLL\n");
				}
				break;
			case navi_GNS:
				{
					printf("Could not parse GNS\n");
				}
				break;
			case navi_RMC:
				{
					printf("Could not parse RMC\n");
				}
				break;
			case navi_VTG:
				{
					printf("Could not parse VTG\n");
				}
				break;
			case navi_ZDA:
				{
					printf("Could not parse ZDA\n");
				}
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

	return 0;
}
