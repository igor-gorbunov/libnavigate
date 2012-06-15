#include <iecgenerator.h>
#include <stdio.h>

int main()
{
	char buffer[1024];
	struct zda_t zda;
	struct dtm_t dtm;
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

	result = IecComposeMessage(_DTM, &dtm, buffer + result,
		sizeof(buffer) - result);
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
}

