#include <iecgenerator.h>
#include <stdio.h>

int main()
{
	char buffer[1024];
	struct zda_t zda;
	int result;

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
	printf("result = %d\n", result);
	printf("message = %s\n", buffer);
}

