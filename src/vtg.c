#include "vtg.h"
#include "common.h"

#include <navigate.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

int navi_create_vtg(const struct vtg_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	const char *talkerid, *mi;
	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], ctrue[32], courseT[2], cmagn[32],
		courseM[2], snots[32], speedN[4], skmph[32], speedK[2], cs[3];

	msglength = strlen(talkerid = navi_talkerid_str(msg->tid));

	msglength += navi_msg_create_double(msg->courseTrue, ctrue, sizeof(ctrue),
		msg->vfields & VTG_VALID_COURSETRUE);
	msglength += snprintf(courseT, sizeof(courseT),
		(msg->vfields & VTG_VALID_COURSETRUE) ? "T" : "");
	msglength += navi_msg_create_double(msg->courseMagn, cmagn, sizeof(cmagn),
		msg->vfields & VTG_VALID_COURSEMAGN);
	msglength += snprintf(courseM, sizeof(courseM),
		(msg->vfields & VTG_VALID_COURSEMAGN) ? "M" : "");
	msglength += navi_msg_create_double(msg->speed * MPS_TO_KNOTS, snots, sizeof(snots),
		msg->vfields & VTG_VALID_SPEED);
	msglength += snprintf(speedN, sizeof(speedN),
		(msg->vfields & VTG_VALID_SPEED) ? "N" : "");
	msglength += navi_msg_create_double(msg->speed * MPS_TO_KMH, skmph, sizeof(skmph),
		msg->vfields & VTG_VALID_SPEED);
	msglength += snprintf(speedK, sizeof(speedK),
		(msg->vfields & VTG_VALID_SPEED) ? "K" : "");

	msglength += strlen(mi = navi_modeindicator_str(msg->mi));

	msglength += 18;
	if (msglength > NAVI_SENTENCE_MAXSIZE)
	{
		navierr_set_last(navi_MsgExceedsMaxSize);
		return navi_Error;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg),
		"$%sVTG,%s,%s,%s,%s,%s,%s,%s,%s,%s*%s\r\n", talkerid, ctrue, courseT,
		cmagn, courseM, snots, speedN, skmph, speedK, mi, "%s");
	IecPrint_Checksum(iecmsg, msglength, cs);

	*nmwritten = snprintf(buffer, maxsize, iecmsg, cs);
	return navi_Ok;
}

int IecParse_VTG(struct vtg_t *msg, char *buffer)
{
	int result;
	int index = 1, nmread;
	double speedknots, speedkmph;

	msg->vfields = 0;

	result = IecParse_Double(buffer + index, &msg->courseTrue, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= VTG_VALID_COURSETRUE;
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
	if (buffer[index] == 'T')
	{
		index += 1;
	}
	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &msg->courseMagn, &nmread);
	switch (result)
	{
	case navi_Ok:
		msg->vfields |= VTG_VALID_COURSEMAGN;
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
	if (buffer[index] == 'M')
	{
		index += 1;
	}
	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &speedknots, &nmread);
	switch (result)
	{
	case navi_Ok:
		break;
	case navi_NullField:
		speedknots = -1.0;
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
	if (buffer[index] == 'N')
	{
		index += 1;
	}
	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;

	result = IecParse_Double(buffer + index, &speedkmph, &nmread);
	switch (result)
	{
	case navi_Ok:
		break;
	case navi_NullField:
		speedkmph = -1.0;
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
	if (buffer[index] == 'K')
	{
		index += 1;
	}
	if (buffer[index] != ',')
	{
		return navi_InvalidMessage;
	}
	index += 1;

	if (speedkmph > -1.0)
	{
		msg->speed = speedkmph * KMH_TO_MPS;
		msg->vfields |= VTG_VALID_SPEED;
	}
	else if (speedknots > -1.0)
	{
		msg->speed = speedknots * KNOTS_TO_MPS;
		msg->vfields |= VTG_VALID_SPEED;
	}

	if (navi_parse_modeindicator(buffer + index, &msg->mi, &nmread) != 0)
	{	// cannot be null field
		navierr_set_last(navi_InvalidMessage);
		return -1;
	}

	return navi_Ok;
}
