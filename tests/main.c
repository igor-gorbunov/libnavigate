/*
 * main.c - IEC messages generating/parsing tests and usage examples.
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
	int result;
	size_t msglength, nmwritten, nmread, remain, parsed;

	char buffer[1024];
	struct aam_t aam;
	struct ack_t ack;
	struct alr_t alr;
	struct dtm_t dtm;
	struct gbs_t gbs;
	struct gga_t gga;
	struct gll_t gll;
	struct gns_t gns;
	struct grs_t grs;
	struct gsa_t gsa;
	struct gst_t gst;
	struct rmc_t rmc;
	struct txt_t txt;
	struct vtg_t vtg;
	struct zda_t zda;

	struct navi_satinfo_t gsvinfo[9];

	char parsedbuffer[4096];
	const char *longtxtmessage = "Pay big attention to the Metro stations in St.Petersburg. "
		"Some stations have correspondents on several main lines. The big problem comes this way: "
		"Even if it is the same station, it will have different names on each main line. So if you "
		"know you want to reach Gostiny Dvor on the green line, pay attention as you might be "
		"travelling on the blue line. You would have to descend at Nevski Prospekt station which is "
		"in fact the same station as Gostiny Dvor.";
	int finished;
	navi_approved_fmt_t msgtype;

	const navi_error_t *lasterr;

	msglength = 0;
	remain = sizeof(buffer);

	// ZDA
	navi_init_zda(&zda, navi_GL);
	zda.vfields = ZDA_VALID_UTC | ZDA_VALID_DATE | ZDA_VALID_LOCALZONE;
	navi_init_utc(8, 12, 38.56, &zda.utc);
	navi_init_date(1982, 5, 25, &zda.date);
	zda.lzoffset = -240;

	nmwritten = 0;
	result = navi_create_msg(navi_ZDA, &zda, buffer + msglength, remain, &nmwritten);
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
	navi_init_dtm(&dtm, navi_GP);

	dtm.vfields = DTM_VALID_ALTOFFSET;
	dtm.local_dtm = navi_UserDefined;

	navi_init_offset_from_degrees(0.2366, navi_North, &dtm.lat_offset);
	navi_init_offset_from_degrees(0.31825, navi_West, &dtm.long_offset);

	dtm.alt_offset = 3.446;
	dtm.reference_dtm = navi_WGS84;

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
	gll.fix.latitude.offset = 0.02;
	gll.fix.latitude.sign = navi_North;
	gll.fix.longitude.offset = 0.00000000999;
	gll.fix.longitude.sign = navi_East;
	gll.utc.hour = 4;
	gll.utc.min = 34;
	gll.utc.sec = 18.4;
	gll.status = navi_status_A;
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
	gns.vfields = GNS_VALID_UTC | GNS_VALID_POSITION_FIX | GNS_VALID_TOTALNMOFSATELLITES |
		GNS_VALID_HDOP | GNS_VALID_ANTENNAALTITUDE | GNS_VALID_GEOIDALSEP |
		GNS_VALID_AGEOFDIFFDATA | GNS_VALID_DIFFREFSTATIONID;
	gns.utc.hour = 20;
	gns.utc.min = 7;
	gns.utc.sec = 1.;
	gns.fix.latitude.offset = 60.;
	gns.fix.latitude.sign = navi_North;
	gns.fix.longitude.offset = 30.;
	gns.fix.longitude.sign = navi_East;
	gns.mi[0] = navi_Autonomous;
	gns.mi[1] = navi_Differential;
	gns.nmsatellites = 4;
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
	rmc.status = navi_status_V;
	rmc.fix.latitude.offset = 74.64772882;
	rmc.fix.latitude.sign = navi_South;
	rmc.fix.longitude.offset = 132.0000333;
	rmc.fix.longitude.sign = navi_East;
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
	navi_init_vtg(&vtg, navi_VW);
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

					if (dtm->local_dtm != navi_datum_NULL)
						printf("\tlocal datum = %d\n", dtm->local_dtm);
					if (dtm->local_dtmsd != navi_datumsub_NULL)
						printf("\tlocal datum subdivision = %d\n", dtm->local_dtmsd);
					if (dtm->lat_offset.sign != navi_offset_NULL)
						printf("\tlatitude offset = %.8f %s (%d)\n", dtm->lat_offset.offset,
							navi_fixsign_str(dtm->lat_offset.sign), dtm->lat_offset.sign);
					if (dtm->long_offset.sign != navi_offset_NULL)
						printf("\tlongitude offset = %.8f %s (%d)\n", dtm->long_offset.offset,
							navi_fixsign_str(dtm->long_offset.sign), dtm->long_offset.sign);
					if (dtm->vfields & DTM_VALID_ALTOFFSET)
						printf("\taltitude offset = %.8f\n", dtm->alt_offset);
					if (dtm->reference_dtm != navi_datum_NULL)
						printf("\treference datum = %d\n", dtm->reference_dtm);
				}
				break;
			case navi_GLL:
				{
					struct gll_t *gll = (struct gll_t *)parsedbuffer;
					printf("Received GLL:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(gll->tid), gll->tid);

					if (gll->vfields & GLL_VALID_POSITION_FIX)
						printf("\tlatitude = %.12f %s (%d)\n", gll->fix.latitude.offset,
							navi_fixsign_str(gll->fix.latitude.sign), gll->fix.latitude.sign);
					if (gll->vfields & GLL_VALID_POSITION_FIX)
						printf("\tlongitude = %.12f %s (%d)\n", gll->fix.longitude.offset,
							navi_fixsign_str(gll->fix.longitude.sign), gll->fix.longitude.sign);
					if (gll->vfields & GLL_VALID_UTC)
						printf("\tutc = %02u:%02u:%06.3f\n", gll->utc.hour,
							gll->utc.min, gll->utc.sec);

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
						printf("\tutc = %02u:%02u:%06.3f\n", gns->utc.hour,
							gns->utc.min, gns->utc.sec);
					if (gns->vfields & GNS_VALID_POSITION_FIX)
						printf("\tlatitude = %.12f %s (%d)\n", gns->fix.latitude.offset,
							navi_fixsign_str(gns->fix.latitude.sign), gns->fix.latitude.sign);
					if (gns->vfields & GNS_VALID_POSITION_FIX)
						printf("\tlongitude = %.12f %s (%d)\n", gns->fix.longitude.offset,
							navi_fixsign_str(gns->fix.longitude.sign), gns->fix.longitude.sign);
					printf("\tmode indicator = %d %d\n", gns->mi[0], gns->mi[1]);
					if (gns->vfields & GNS_VALID_TOTALNMOFSATELLITES)
						printf("\tsatellites = %d\n", gns->nmsatellites);
					if (gns->vfields & GNS_VALID_HDOP)
						printf("\thdop = %.12f\n", gns->hdop);
					if (gns->vfields & GNS_VALID_ANTENNAALTITUDE)
						printf("\tantenna altitude = %.12f\n", gns->antaltitude);
					if (gns->vfields & GNS_VALID_GEOIDALSEP)
						printf("\tgeoidal separation = %.12f\n", gns->geoidalsep);
					if (gns->vfields & GNS_VALID_AGEOFDIFFDATA)
						printf("\tage of dd = %if\n", gns->diffage);
					if (gns->vfields & GNS_VALID_DIFFREFSTATIONID)
						printf("\tid = %d\n", gns->id);
				}
				break;
			case navi_RMC:
				{
					struct rmc_t *rmc = (struct rmc_t *)parsedbuffer;
					printf("Received RMC:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(rmc->tid), rmc->tid);

					if (rmc->vfields & RMC_VALID_UTC)
						printf("\tutc = %02u:%02u:%06.3f\n", rmc->utc.hour,
							rmc->utc.min, rmc->utc.sec);
					printf("\tstatus = %d\n", rmc->status);
					if (rmc->vfields & RMC_VALID_POSITION_FIX)
						printf("\tlatitude = %.12f %s (%d)\n", rmc->fix.latitude.offset,
							navi_fixsign_str(rmc->fix.latitude.sign), rmc->fix.latitude.sign);
					if (rmc->vfields & RMC_VALID_POSITION_FIX)
						printf("\tlongitude = %.12f %s (%d)\n", rmc->fix.longitude.offset,
							navi_fixsign_str(rmc->fix.longitude.sign), rmc->fix.longitude.sign);
					if (rmc->vfields & RMC_VALID_SPEED)
						printf("\tspeed = %.12f\n", rmc->speed);
					if (rmc->vfields & RMC_VALID_COURSETRUE)
						printf("\tcourse, true = %.12f\n", rmc->courseTrue);
					if (rmc->vfields & RMC_VALID_DATE)
						printf("\tdate = %d %d %d\n", rmc->date.day,
							rmc->date.month, rmc->date.year);
					if (rmc->vfields & RMC_VALID_MAGNVARIATION)
						printf("\tmagnetic variation = %.12f (%d)\n",
							rmc->magnetic.offset, rmc->magnetic.sign);
					printf("\tmode indicator = %d\n", rmc->mi);
				}
				break;
			case navi_VTG:
				{
					struct vtg_t *vtg = (struct vtg_t *)parsedbuffer;
					printf("Received VTG:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(vtg->tid), vtg->tid);

					if (vtg->vfields & VTG_VALID_COURSETRUE)
						printf("\tcource, true = %.12f\n", vtg->courseTrue);
					if (vtg->vfields & VTG_VALID_COURSEMAGN)
						printf("\tcourse, magnetic = %.12f\n", vtg->courseMagn);
					if (vtg->vfields & VTG_VALID_SPEED)
						printf("\tspeed = %.12f\n", vtg->speed);
					printf("\tmode indicator = %d\n", vtg->mi);
				}
				break;
			case navi_ZDA:
				{
					struct zda_t *zda = (struct zda_t *)parsedbuffer;
					printf("Received ZDA:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(zda->tid), zda->tid);

					if (zda->vfields & ZDA_VALID_UTC)
						printf("\tutc = %02u:%02u:%06.3f\n", zda->utc.hour,
							zda->utc.min, zda->utc.sec);
					if (zda->vfields & ZDA_VALID_DATE)
						printf("\tdate = %04d-%02d-%02d\n", zda->date.year, zda->date.month,
							zda->date.day);
					if (zda->vfields & ZDA_VALID_LOCALZONE)
						printf("\tlocal zone offset = %d\n", zda->lzoffset);
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
				printf("Could not parse DTM\n");
				break;
			case navi_GLL:
				printf("Could not parse GLL\n");
				break;
			case navi_GNS:
				printf("Could not parse GNS\n");
				break;
			case navi_RMC:
				printf("Could not parse RMC\n");
				break;
			case navi_VTG:
				printf("Could not parse VTG\n");
				break;
			case navi_ZDA:
				printf("Could not parse ZDA\n");
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

	msglength = 0;
	remain = sizeof(buffer);

	// GBS
	gbs.tid = navi_GL;

	gbs.vfields = GBS_VALID_EXPERRLATLON | GBS_VALID_EXPERRALT |
		GBS_VALID_ID | GBS_VALID_PROBABILITY | GBS_VALID_ESTIMATE |
		GBS_VALID_DEVIATION;
	gbs.utc.hour = 0;
	gbs.utc.min = 34;
	gbs.utc.sec = 16.;
	gbs.experrlat = 1.4;
	gbs.experrlon = 0.12;
	gbs.experralt = 1.1;
	gbs.id = 66;
	gbs.probability = 0.12;
	gbs.estimate = 1.1;
	gbs.deviation = 1.3;

	result = navi_create_msg(navi_GBS, &gbs, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GBS failed (%d)\n", result);
	}

	// GGA
	gga.tid = navi_GP;

	gga.vfields = GGA_VALID_UTC | GGA_VALID_FIX | GGA_VALID_NMSATELLITES |
		GGA_VALID_HDOP | GGA_VALID_ANTALTITUDE | GGA_VALID_GEOIDALSEP |
		GGA_VALID_DIFFAGE | GGA_VALID_ID;
	gga.utc.hour = 0;
	gga.utc.min = 34;
	gga.utc.sec = 16.;
	gga.fix.latitude.offset = 12.0;
	gga.fix.latitude.sign = navi_South;
	gga.fix.longitude.offset = 112.01;
	gga.fix.longitude.sign = navi_West;
	gga.gpsindicator = navi_gps_Differential;
	gga.nmsatellites = 8;
	gga.hdop = 1.0;
	gga.antaltitude = 8.1;
	gga.geoidalsep = -1.2;
	gga.diffage = 21;
	gga.id = 1011;

	result = navi_create_msg(navi_GGA, &gga, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GGA failed (%d)\n", result);
	}

	// GRS
	memset(&grs, 0, sizeof(grs));
	grs.tid = navi_GP;

	grs.utc.hour = 0;
	grs.utc.min = 34;
	grs.utc.sec = 16.;

	grs.mode = 0;

	grs.residuals[0].notnull = 1;
	grs.residuals[0].residual = 1.0;

	grs.residuals[1].notnull = 1;
	grs.residuals[1].residual = 0.2;

	grs.residuals[2].notnull = 1;
	grs.residuals[2].residual = 0.34;

	grs.residuals[3].notnull = 1;
	grs.residuals[3].residual = 1.01;

	grs.residuals[4].notnull = 1;
	grs.residuals[4].residual = 0.98;

	grs.residuals[7].notnull = 1;
	grs.residuals[7].residual = 0.1;

	grs.residuals[8].notnull = 1;
	grs.residuals[8].residual = -103.7;

	result = navi_create_msg(navi_GRS, &grs, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GRS failed (%d)\n", result);
	}

	// GSA
	memset(&gsa, 0, sizeof(gsa));
	gsa.tid = navi_GP;

	gsa.swmode = navi_gsa_Automatic;
	gsa.fixmode = 3;

	gsa.satellites[0].notnull = 1;
	gsa.satellites[0].id = 1;

	gsa.satellites[1].notnull = 1;
	gsa.satellites[1].id = 12;

	gsa.satellites[2].notnull = 1;
	gsa.satellites[2].id = 3;

	gsa.satellites[3].notnull = 1;
	gsa.satellites[3].id = 2;

	gsa.satellites[4].notnull = 1;
	gsa.satellites[4].id = 18;

	gsa.satellites[7].notnull = 1;
	gsa.satellites[7].id = 24;

	gsa.satellites[8].notnull = 1;
	gsa.satellites[8].id = 14;

	gsa.hdop = 2.12;
	gsa.vdop = .012;
	gsa.pdop = 2.12003396;

	gsa.vfields = GSA_VALID_SWITCHMODE | GSA_VALID_FIXMODE | GSA_VALID_PDOP |
		GSA_VALID_HDOP | GSA_VALID_VDOP;

	result = navi_create_msg(navi_GSA, &gsa, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GSA failed (%d)\n", result);
	}

	// GST
	gst.tid = navi_GP;

	gst.vfields = GST_VALID_RMS | GST_VALID_STDDEVELLIPSE |
		GST_VALID_DEVLATLONERR | GST_VALID_DEVALTERR;

	gst.utc.hour = 14;
	gst.utc.min = 8;
	gst.utc.sec = 16;

	gst.rms = 1.4;
	gst.devmajor = .56;
	gst.devminor = 3.2;
	gst.orientmajor = 18.;
	gst.devlaterr = 0.2;
	gst.devlonerr = 0.1;
	gst.devalterr = 1.;

	result = navi_create_msg(navi_GST, &gst, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GST failed (%d)\n", result);
	}

	// GSV
	gsvinfo[0].vfields = SATINFO_VALID_ORIENTATION;
	gsvinfo[0].id = 4;
	gsvinfo[0].elevation = 12;
	gsvinfo[0].azimuth = 0;

	gsvinfo[1].vfields = SATINFO_VALID_ORIENTATION | SATINFO_VALID_SNR;
	gsvinfo[1].id = 5;
	gsvinfo[1].elevation = 18;
	gsvinfo[1].azimuth = 12;
	gsvinfo[1].snr = 45;

	gsvinfo[2].vfields = 0;
	gsvinfo[2].id = 14;

	gsvinfo[3].vfields = SATINFO_VALID_ORIENTATION | SATINFO_VALID_SNR;
	gsvinfo[3].id = 18;
	gsvinfo[3].elevation = 12;
	gsvinfo[3].azimuth = 300;
	gsvinfo[3].snr = 70;

	gsvinfo[4].vfields = 0;
	gsvinfo[4].id = 6;

	gsvinfo[5].vfields = SATINFO_VALID_SNR;
	gsvinfo[5].id = 7;
	gsvinfo[5].snr = 4;

	gsvinfo[6].vfields = SATINFO_VALID_SNR;
	gsvinfo[6].id = 8;
	gsvinfo[6].snr = 4;

	gsvinfo[7].vfields = SATINFO_VALID_SNR;
	gsvinfo[7].id = 9;
	gsvinfo[7].snr = 4;

	gsvinfo[8].vfields = SATINFO_VALID_SNR;
	gsvinfo[8].id = 10;
	gsvinfo[8].snr = 4;

	result = navi_create_gsv_sequence(navi_GL, 9, gsvinfo, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GSV failed (%d)\n", result);
	}

	// AAM
	navi_init_aam(&aam, navi_GL);
	aam.circle = navi_status_A;
	aam.perp = navi_status_V;
	aam.radius = 10.1;
	strcpy(aam.wpid, "St. Petersburg, Russia");

	result = navi_create_msg(navi_AAM, &aam, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of AAM failed (%d)\n", result);
	}

	// ACK
	navi_init_ack(&ack, navi_GL);
	ack.alarmid = 846;

	result = navi_create_msg(navi_ACK, &ack, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of ACK failed (%d)\n", result);
	}

	// ALR
	navi_init_alr(&alr, navi_GL);
	navi_init_utc(12, 8, 13, &alr.utc);
	alr.alarmid = 846;
	alr.condition = navi_status_A;
	alr.ackstate = navi_status_V;

	result = navi_create_msg(navi_ALR, &alr, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of ALR failed (%d)\n", result);
	}

	// ALR
	navi_init_alr(&alr, navi_GL);
	navi_init_utc(16, 12, 0, &alr.utc);
	alr.alarmid = 7;
	alr.condition = navi_status_V;
	alr.ackstate = navi_status_V;
	strcpy(alr.description, "Captain, take your pills.");

	result = navi_create_msg(navi_ALR, &alr, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of ALR failed (%d)\n", result);
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
			case navi_GBS:
				{
					struct gbs_t *gbs = (struct gbs_t *)parsedbuffer;

					printf("Received GBS:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(gbs->tid), gbs->tid);
					printf("\tutc = %02u:%02u:%06.3f\n", gbs->utc.hour,
						gbs->utc.min, gbs->utc.sec);
					if (gbs->vfields & GBS_VALID_EXPERRLATLON)
						printf("\tExpected error in latitude: %f\n", gbs->experrlat);
					if (gbs->vfields & GBS_VALID_EXPERRLATLON)
						printf("\tExpected error in longitude: %f\n", gbs->experrlon);
					if (gbs->vfields & GBS_VALID_EXPERRALT)
						printf("\tExpected error in altitude: %f\n", gbs->experralt);
					if (gbs->vfields & GBS_VALID_ID)
						printf("\tFault station ID: %d\n", gbs->id);
					if (gbs->vfields & GBS_VALID_PROBABILITY)
						printf("\tProbability: %f\n", gbs->probability);
					if (gbs->vfields & GBS_VALID_ESTIMATE)
						printf("\tEstimated: %f\n", gbs->estimate);
					if (gbs->vfields & GBS_VALID_DEVIATION)
						printf("\tDeviation: %f\n", gbs->deviation);
				}
				break;
			case navi_GGA:
				{
					struct gga_t *gga = (struct gga_t *)parsedbuffer;

					printf("Received GGA:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(gga->tid), gga->tid);
					if (gga->vfields & GGA_VALID_UTC)
						printf("\tutc = %02u:%02u:%06.3f\n", gga->utc.hour,
							gga->utc.min, gga->utc.sec);
					if (gga->vfields & GGA_VALID_FIX)
						printf("\tlatitude = %f %s (%d)\n", gga->fix.latitude.offset,
							navi_fixsign_str(gga->fix.latitude.sign), gga->fix.latitude.sign);
					if (gga->vfields & GGA_VALID_FIX)
						printf("\tlongitude = %f %s (%d)\n", gga->fix.longitude.offset,
							navi_fixsign_str(gga->fix.longitude.sign), gga->fix.longitude.sign);
					printf("\tGPS quality indicator: %i\n", gga->gpsindicator);
					if (gga->vfields & GGA_VALID_NMSATELLITES)
						printf("\tNm of satellites in use: %i\n", gga->nmsatellites);
					if (gga->vfields & GGA_VALID_HDOP)
						printf("\tHDOP: %f\n", gga->hdop);
					if (gga->vfields & GGA_VALID_ANTALTITUDE)
						printf("\tAntenna altitude: %f\n", gga->antaltitude);
					if (gga->vfields & GGA_VALID_GEOIDALSEP)
						printf("\tGeoidal separation: %f\n", gga->geoidalsep);
					if (gga->vfields & GGA_VALID_DIFFAGE)
						printf("\tAge of differential GPS data: %i\n", gga->diffage);
					if (gga->vfields & GGA_VALID_ID)
						printf("\tRef. station ID: %i\n", gga->id);
				}
				break;
			case navi_GRS:
				{
					int i;
					struct grs_t *grs = (struct grs_t *)parsedbuffer;

					printf("Received GRS:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(grs->tid), grs->tid);
					printf("\tutc = %02u:%02u:%06.3f\n", grs->utc.hour,
							grs->utc.min, grs->utc.sec);
					printf("\tmode = %i\n", grs->mode);
					for (i = 0; i < 12; i++)
					{
						if (grs->residuals[i].notnull)
						{
							printf("\tResidual %i = %f\n", i, grs->residuals[i].residual);
						}
					}
				}
				break;
			case navi_GSA:
				{
					int i;
					struct gsa_t *gsa = (struct gsa_t *)parsedbuffer;

					printf("Received GSA:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(gsa->tid), gsa->tid);
					if (gsa->vfields & GSA_VALID_SWITCHMODE)
						printf("\tswitchmode = %i\n", gsa->swmode);
					if (gsa->vfields & GSA_VALID_FIXMODE)
						printf("\tfixmode = %i\n", gsa->fixmode);
					for (i = 0; i < 12; i++)
					{
						if (gsa->satellites[i].notnull)
						{
							printf("\tSatellite %i = %i\n", i, gsa->satellites[i].id);
						}
					}
					if (gsa->vfields & GSA_VALID_PDOP)
						printf("\tPDOP = %f\n", gsa->pdop);
					if (gsa->vfields & GSA_VALID_HDOP)
						printf("\tHDOP = %f\n", gsa->hdop);
					if (gsa->vfields & GSA_VALID_VDOP)
						printf("\tVDOP = %f\n", gsa->vdop);
				}
				break;
			case navi_GST:
				{
					struct gst_t *gst = (struct gst_t *)parsedbuffer;

					printf("Received GST:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(gst->tid), gst->tid);
					printf("\tutc = %02u:%02u:%06.3f\n", gst->utc.hour,
						gst->utc.min, gst->utc.sec);

					if (gst->vfields & GST_VALID_RMS)
					{
						printf("\tRMS = %f\n", gst->rms);
					}
					if (gst->vfields & GST_VALID_STDDEVELLIPSE)
					{
						printf("\tstd dev of semi-major = %f\n", gst->devmajor);
						printf("\tstd dev of semi-minor = %f\n", gst->devminor);
						printf("\torientation of semi-major = %f\n", gst->orientmajor);
					}
					if (gst->vfields & GST_VALID_DEVLATLONERR)
					{
						printf("\tstd dev of latitude err = %f\n", gst->devlaterr);
						printf("\tstd dev of longitude err = %f\n", gst->devlonerr);
					}
					if (gst->vfields & GST_VALID_DEVALTERR)
					{
						printf("\tstd dev of altitude err = %f\n", gst->devalterr);
					}
				}
				break;
			case navi_GSV:
				{
					int i;
					struct gsv_t *gsv = (struct gsv_t *)parsedbuffer;

					printf("Received GSV:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(gsv->tid), gsv->tid);
					printf("\tTotal nm of messages: %i\n", gsv->totalnm);
					printf("\tMessage number: %i\n", gsv->msgnm);
					if (gsv->nmsatellites != -1)
						printf("\tTotal satellites in view: %i\n", gsv->nmsatellites);

					for (i = 0; i < GSV_MAX_SATELLITES_PER_MESSAGE && gsv->info[i].id != 0; i++)
					{
						printf("\tSatellite id: %i\n", gsv->info[i].id);
						if (gsv->info[i].vfields & SATINFO_VALID_ORIENTATION)
							printf("\t\tElevation: %i\n", gsv->info[i].elevation);
						if (gsv->info[i].vfields & SATINFO_VALID_ORIENTATION)
							printf("\t\tAzimuth: %i\n", gsv->info[i].azimuth);
						if (gsv->info[i].vfields & SATINFO_VALID_SNR)
							printf("\t\tSNR: %i\n", gsv->info[i].snr);
					}
				}
				break;
			case navi_AAM:
				{
					struct aam_t *aam = (struct aam_t *)parsedbuffer;

					printf("Received AAM:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(aam->tid), aam->tid);
					printf("\tStatus of circle: %s\n", aam->circle == navi_status_A ? "entered" : "not entered");
					printf("\tStatus of perpendicular: %s\n", aam->perp == navi_status_A ? "passed" : "not passed");
					printf("\tArrival circle radius: %f nautical miles\n", aam->radius);
					printf("\tWaypoint ID: %s\n", aam->wpid);
				}
				break;
			case navi_ACK:
				{
					struct ack_t *ack = (struct ack_t *)parsedbuffer;

					printf("Received ACK:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(ack->tid), ack->tid);
					printf("\tLocal alarm identifier: %i\n", ack->alarmid);
				}
				break;
			case navi_ALR:
				{
					struct alr_t *alr = (struct alr_t *)parsedbuffer;

					printf("Received ALR:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(alr->tid), alr->tid);
					printf("\tutc = %02u:%02u:%06.3f\n", alr->utc.hour,
						alr->utc.min, alr->utc.sec);
					printf("\tLocal alarm identifier: %i\n", alr->alarmid);
					printf("\tCondition of alarm: %s\n", alr->condition == navi_status_A ?
						"threshold exceeded" : "not exceeded");
					printf("\tAcknowledge state: %s\n", alr->ackstate == navi_status_A ?
						"acknowledged" : "unacknowledged");
					if (strlen(alr->description) > 0)
					{
						printf("\tAlarm's description: %s\n", alr->description);
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

	msglength = 0;
	remain = sizeof(buffer);

	// TXT
	navi_init_txt(&txt, navi_GP);
	txt.textid = 25;
	strcpy(txt.textmsg, "DR MODE - ANTENNA FAULT!");

	result = navi_create_msg(navi_TXT, &txt, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of TXT failed (%d)\n", result);
	}

	// Long TXT, splitted into several messages
	result = navi_create_txt_sequence(navi_GL, 25, longtxtmessage, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of TXT failed (%d)\n", navierr_get_last()->errclass);
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
			case navi_TXT:
				{
					struct txt_t *txt = (struct txt_t *)parsedbuffer;

					printf("Received TXT:\n\ttalker id = %s (%d)\n",
						navi_talkerid_str(txt->tid), txt->tid);
					printf("\tTotal nm of messages: %i\n", txt->totalnm);
					printf("\tMessage number: %i\n", txt->msgnm);
					printf("\tText identifier: %i\n", txt->textid);
					if (strlen(txt->textmsg) > 0)
					{
						printf("\tText message: %s\n", txt->textmsg);
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
	printf("sizeof struct aam_t = %Iu\n", sizeof(struct aam_t));
	printf("sizeof struct ack_t = %Iu\n", sizeof(struct ack_t));
	printf("sizeof struct alr_t = %Iu\n", sizeof(struct alr_t));
	printf("sizeof struct dtm_t = %Iu\n", sizeof(struct dtm_t));
	printf("sizeof struct gbs_t = %Iu\n", sizeof(struct gbs_t));
	printf("sizeof struct gga_t = %Iu\n", sizeof(struct gga_t));
	printf("sizeof struct gll_t = %Iu\n", sizeof(struct gll_t));
	printf("sizeof struct gns_t = %Iu\n", sizeof(struct gns_t));
	printf("sizeof struct grs_t = %Iu\n", sizeof(struct grs_t));
	printf("sizeof struct gsa_t = %Iu\n", sizeof(struct gsa_t));
	printf("sizeof struct gst_t = %Iu\n", sizeof(struct gst_t));
	printf("sizeof struct gsv_t = %Iu\n", sizeof(struct gsv_t));
	printf("sizeof struct rmc_t = %Iu\n", sizeof(struct rmc_t));
	printf("sizeof struct txt_t = %Iu\n", sizeof(struct txt_t));
	printf("sizeof struct vtg_t = %Iu\n", sizeof(struct vtg_t));
	printf("sizeof struct zda_t = %Iu\n", sizeof(struct zda_t));
#else
	printf("sizeof struct aam_t = %zu\n", sizeof(struct aam_t));
	printf("sizeof struct ack_t = %zu\n", sizeof(struct ack_t));
	printf("sizeof struct alr_t = %zu\n", sizeof(struct alr_t));
	printf("sizeof struct dtm_t = %zu\n", sizeof(struct dtm_t));
	printf("sizeof struct gbs_t = %zu\n", sizeof(struct gbs_t));
	printf("sizeof struct gga_t = %zu\n", sizeof(struct gga_t));
	printf("sizeof struct gll_t = %zu\n", sizeof(struct gll_t));
	printf("sizeof struct gns_t = %zu\n", sizeof(struct gns_t));
	printf("sizeof struct grs_t = %zu\n", sizeof(struct grs_t));
	printf("sizeof struct gsa_t = %zu\n", sizeof(struct gsa_t));
	printf("sizeof struct gst_t = %zu\n", sizeof(struct gst_t));
	printf("sizeof struct gsv_t = %zu\n", sizeof(struct gsv_t));
	printf("sizeof struct rmc_t = %zu\n", sizeof(struct rmc_t));
	printf("sizeof struct txt_t = %zu\n", sizeof(struct txt_t));
	printf("sizeof struct vtg_t = %zu\n", sizeof(struct vtg_t));
	printf("sizeof struct zda_t = %zu\n", sizeof(struct zda_t));
#endif // MSVC_VER

	return 0;
}

