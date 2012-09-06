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
		navierr_set_last(navi_MsgExceedsMaxSize);
		return -1;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg),
		"$%sDTM,%s,%s,%s,%s,%s,%s,%s,%s*%s\r\n", talkerid, locdatum, locdatumsub,
		latofs, latsign, lonofs, lonsign, altofs, refdatum, "%s");
	IecPrint_Checksum(iecmsg, msglength, cs);

	*nmwritten = snprintf(buffer, maxsize, iecmsg, cs);
	return 0;
}

int navi_msg_parse_dtm(struct dtm_t *msg, char *buffer, int maxsize)
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

	if (navi_msg_parse_offset(buffer + index, &msg->latofs, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_LATOFFSET;
	}
	index += nmread;

	if (navi_msg_parse_offset(buffer + index, &msg->lonofs, &nmread) != 0)
	{
		if (navierr_get_last()->errclass != navi_NullField)
			return -1;
	}
	else
	{
		msg->vfields |= DTM_VALID_LONOFFSET;
	}
	index += nmread;

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
		navierr_set_last(navi_InvalidMessage);
		return -1;
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
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}

	return 0;
}

