#include "dtm.h"
#include "common.h"

#include <libnavigate/errors.h>
#include <stdio.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

int navi_msg_create_dtm(const struct dtm_t *msg, char *buffer,
		int maxsize, int *nmwritten)
{
	int msglength;

	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], talkerid[3], locdatum[4],
		locdatumsub[2], latofs[32], latsign[2], lonofs[32], lonsign[2],
		altofs[32], refdatum[4], cs[3];

	msglength = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	msglength += IecPrint_Datum(msg->ld, locdatum, sizeof(locdatum),
		msg->vfields & DTM_VALID_LOCALDATUM);
	msglength += IecPrint_DatumSubdivision(msg->lds, locdatumsub,
		sizeof(locdatumsub), msg->vfields & DTM_VALID_LOCALDATUMSUB);
	msglength += IecPrint_Double(msg->latofs.offset, latofs, sizeof(latofs),
		msg->vfields & DTM_VALID_LATOFFSET);
	msglength += IecPrint_OffsetSign(msg->latofs.sign, latsign, sizeof(latsign),
		msg->vfields & DTM_VALID_LATOFFSET);
	msglength += IecPrint_Double(msg->lonofs.offset, lonofs, sizeof(lonofs),
		msg->vfields & DTM_VALID_LONOFFSET);
	msglength += IecPrint_OffsetSign(msg->lonofs.sign, lonsign, sizeof(lonsign),
		msg->vfields & DTM_VALID_LONOFFSET);
	msglength += IecPrint_Double(msg->altoffset, altofs, sizeof(altofs),
		msg->vfields & DTM_VALID_ALTITUDEOFFSET);
	msglength += IecPrint_Datum(msg->rd, refdatum, sizeof(refdatum),
		msg->vfields & DTM_VALID_REFERENCEDATUM);

	msglength += 17;
	if (msglength > NAVI_SENTENCE_MAXSIZE)
	{
		//result = naviError_MsgExceedsMaxSize;
		return navi_Error;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg),
		"$%sDTM,%s,%s,%s,%s,%s,%s,%s,%s*%s\r\n", talkerid, locdatum, locdatumsub,
		latofs, latsign, lonofs, lonsign, altofs, refdatum, "%s");
	IecPrint_Checksum(iecmsg, msglength, cs);

	*nmwritten = snprintf(buffer, maxsize, iecmsg, cs);
	return navi_Ok;
}

int navi_msg_parse_dtm(struct dtm_t *msg, char *buffer, int maxsize)
{
	int result;
	size_t index = 1, nmread;

	msg->vfields = 0;

	result = IecParse_Datum(buffer + index, &msg->ld, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= DTM_VALID_LOCALDATUM;
		break;
	case navi_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;

	result = IecParse_DatumSub(buffer + index, &msg->lds, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= DTM_VALID_LOCALDATUMSUB;
		break;
	case navi_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->latofs.offset, &nmread);
	index += nmread;
	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;
	switch (result)
	{
	case navi_Ok:
		// next field must not be null too
		result = IecParse_OffsetSign(buffer + index, &msg->latofs.sign, &nmread);
		if (result == navi_Ok)
		{
			msg->vfields |= DTM_VALID_LATOFFSET;
		}
		else
		{
			return navi_InvalidMessage;
		}
		break;
	case navi_NullField:
		// next field must be null too
		result = IecParse_OffsetSign(buffer + index, &msg->latofs.sign, &nmread);
		if (result != navi_NullField)
		{
			return navi_InvalidMessage;
		}
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->lonofs.offset, &nmread);
	index += nmread;
	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;
	switch (result)
	{
	case navi_Ok:
		// next field must not be null too
		result = IecParse_OffsetSign(buffer + index, &msg->lonofs.sign, &nmread);
		if (result == navi_Ok)
		{
			msg->vfields |= DTM_VALID_LONOFFSET;
		}
		else
		{
			return navi_InvalidMessage;
		}
		break;
	case navi_NullField:
		// next field must be null too
		result = IecParse_OffsetSign(buffer + index, &msg->latofs.sign, &nmread);
		if (result != navi_NullField)
		{
			return navi_InvalidMessage;
		}
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->altoffset, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= DTM_VALID_ALTITUDEOFFSET;
		break;
	case navi_NullField:
		break;
	default:
		return result;
	}

	index += nmread;
	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;

	result = IecParse_Datum(buffer + index, &msg->rd, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= DTM_VALID_REFERENCEDATUM;
		break;
	case navi_NullField:
		break;
	default:
		return result;
	}

	index += nmread;

	if (buffer[index] != '*')
	{
		return navi_InvalidMessage;
	}

	return navi_Ok;
}

