#include <iecgenerator.h>
#include <stdio.h>

int main()
{
	char buffer[1024];
	struct zda_t zda;
	struct dtm_t dtm;
	struct gll_t gll;
	struct gns_t gns;
	struct rmc_t rmc;
	int result, msglength;

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

	msglength = 0;
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

	printf("msglength = %d\n", msglength);
	printf("message = %s\n", buffer);

	return 0;
}

