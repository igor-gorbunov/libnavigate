#include "common.h"
#include <libnavigate/generator.h>
#include <libnavigate/errors.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#define EPROTO 134
#endif // MSVC_VER

//
// navi_parse_status
//
int navi_parse_status(char *buffer, int *status, int *nmread)
{

#ifndef NO_PARSER

	int i = 0, c, error = 0;

	assert(buffer != NULL);
	assert(status != NULL);
	assert(nmread != NULL);

	c = buffer[i++];
	if ((c == 'A') || (c == 'V'))
	{
		*status = (c == 'A') ? navi_DataValid : navi_DataInvalid;
		c = buffer[i++];
		if ((c != ',') && (c != '*'))
		{
			error = navi_InvalidMessage;
		}
	}
	else if ((c == ',') || (c == '*'))
	{
		error = navi_NullField;
	}
	else
	{
		error = navi_InvalidMessage;
	}

	*nmread = i;

	if (error)
	{
		navierr_set_last(error);
		return navi_Error;
	}

	return navi_Ok;

#else

	navierr_set_last(navi_NotImplemented);
	return -1;

#endif // NO_PARSER

}

//
// navi_parse_modeindicator
//
int navi_parse_modeindicator(char *buffer, int *mi, int *nmread)
{

#ifndef NO_PARSER

	int i = 0, c, error = 0;

	assert(buffer != NULL);
	assert(mi != NULL);
	assert(nmread != NULL);

	c = buffer[i++];

	if ((c == 'A') || (c == 'D') || (c == 'E') ||
		(c == 'M') || (c == 'S') || (c == 'N'))
	{
		switch (c)
		{
		case 'A':
			*mi = navi_Autonomous;
			break;
		case 'D':
			*mi = navi_Differential;
			break;
		case 'E':
			*mi = navi_Estimated;
			break;
		case 'M':
			*mi = navi_ManualInput;
			break;
		case 'S':
			*mi = navi_Simulator;
			break;
		case 'N':
			*mi = navi_DataNotValid;
			break;
		}

		c = buffer[i++];
		if ((c != ',') && (c != '*'))
		{
			error = navi_InvalidMessage;
		}
	}
	else if ((c == ',') || (c == '*'))
	{
		error = navi_NullField;
	}
	else
	{
		error = navi_InvalidMessage;
	}

	*nmread = i;

	if (error)
	{
		navierr_set_last(error);
		return navi_Error;
	}

	return navi_Ok;

#else

	navierr_set_last(navi_NotImplemented);
	return -1;

#endif // NO_PARSER

}

//
// remove_trailing_zeroes
//
int remove_trailing_zeroes(char *buffer, int length)
{
	int i;

	for (i = length - 1; ; i--)
	{
		if (buffer[i] == '0')
		{
			buffer[i] = '\0';
			length--;
		}
		else if (buffer[i] == '.')
		{
			buffer[i] = '\0';
			length--;
			break;
		}
		else
		{
			break;
		}
	}

	return length;
}
