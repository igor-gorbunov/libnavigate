#include "dtm.h"
#include "common.h"

#include <navigate.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

#ifndef NO_GENERATOR

int navi_create_dtm(const struct dtm_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	const char *talkerid, *localdatum, *refdatum, *latsign, *lonsign;
	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], locdatumsub[2], latofs[32],
		lonofs[32], altofs[32], cs[3];

	msglength = strlen(talkerid = navi_talkerid_str(msg->tid));
	msglength += strlen(localdatum = navi_datum_str(msg->ld,
		msg->vfields & DTM_VALID_LOCALDATUM));

	msglength += IecPrint_DatumSubdivision(msg->lds, locdatumsub,
		sizeof(locdatumsub), msg->vfields & DTM_VALID_LOCALDATUMSUB);

	msglength += navi_msg_create_double(msg->latofs.offset, latofs, sizeof(latofs),
		msg->vfields & DTM_VALID_LATOFFSET);

	msglength += strlen(latsign = navi_fixsign_str(msg->latofs.sign,
		msg->vfields & DTM_VALID_LATOFFSET));

	msglength += navi_msg_create_double(msg->lonofs.offset, lonofs, sizeof(lonofs),
		msg->vfields & DTM_VALID_LONOFFSET);

	msglength += strlen(lonsign = navi_fixsign_str(msg->lonofs.sign,
		msg->vfields & DTM_VALID_LONOFFSET));

	msglength += navi_msg_create_double(msg->altoffset, altofs, sizeof(altofs),
		msg->vfields & DTM_VALID_ALTITUDEOFFSET);

	msglength += strlen(refdatum = navi_datum_str(msg->rd,
		msg->vfields & DTM_VALID_REFERENCEDATUM));

	msglength += 17;
	if (msglength > NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return -1;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg),
		"$%sDTM,%s,%s,%s,%s,%s,%s,%s,%s*%s\r\n", talkerid, localdatum, locdatumsub,
		latofs, latsign, lonofs, lonsign, altofs, refdatum, "%s");
	IecPrint_Checksum(iecmsg, msglength, cs);

	*nmwritten = snprintf(buffer, maxsize, iecmsg, cs);
	return 0;
}

#endif // NO_GENERATOR

#ifndef NO_PARSER

int navi_msg_parse_dtm(struct dtm_t *msg, char *buffer)
{
	int result;
	int index = 1, nmread;

	msg->vfields = 0;

	if (IecParse_Datum(buffer + index, &msg->ld, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_LOCALDATUM;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}
	index += 1;

	if (IecParse_DatumSub(buffer + index, &msg->lds, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_LOCALDATUMSUB;
	}

	index += nmread;

	if (buffer[index] != ',')
	{
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}
	index += 1;

	if (navi_parse_offset(buffer + index, &msg->latofs, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_LATOFFSET;
	}
	index += nmread;

	if (navi_parse_offset(buffer + index, &msg->lonofs, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_LONOFFSET;
	}
	index += nmread;

	if (navi_parse_number(buffer + index, &msg->altoffset, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_ALTITUDEOFFSET;
	}
	index += nmread;

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
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}

	return 0;
}

#endif // NO_PARSER
