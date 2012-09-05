#include "vtg.h"
#include "common.h"

#include <libnavigate/errors.h>
#include <stdio.h>

#ifdef _MSC_VER
#define snprintf	_snprintf
#endif // MSVC_VER

int IecCompose_VTG(const struct vtg_t *msg, char *buffer,
	int maxsize, int *nmwritten)
{
	int msglength;

	char iecmsg[NAVI_SENTENCE_MAXSIZE + 1], talkerid[3], ctrue[32], courseT[2],
		cmagn[32], courseM[2], snots[32], speedN[4], skmph[32], speedK[2],
		mi[2], cs[3];

	msglength = IecPrint_TalkerId(msg->tid, talkerid, sizeof(talkerid));
	msglength += IecPrint_Double(msg->courseTrue, ctrue, sizeof(ctrue),
		msg->vfields & VTG_VALID_COURSETRUE);
	msglength += snprintf(courseT, sizeof(courseT),
		(msg->vfields & VTG_VALID_COURSETRUE) ? "T" : "");
	msglength += IecPrint_Double(msg->courseMagn, cmagn, sizeof(cmagn),
		msg->vfields & VTG_VALID_COURSEMAGN);
	msglength += snprintf(courseM, sizeof(courseM),
		(msg->vfields & VTG_VALID_COURSEMAGN) ? "M" : "");
	msglength += IecPrint_Double(msg->speed * MPS_TO_KNOTS, snots, sizeof(snots),
		msg->vfields & VTG_VALID_SPEED);
	msglength += snprintf(speedN, sizeof(speedN),
		(msg->vfields & VTG_VALID_SPEED) ? "N" : "");
	msglength += IecPrint_Double(msg->speed * MPS_TO_KMH, skmph, sizeof(skmph),
		msg->vfields & VTG_VALID_SPEED);
	msglength += snprintf(speedK, sizeof(speedK),
		(msg->vfields & VTG_VALID_SPEED) ? "K" : "");
	msglength += IecPrint_ModeIndicator(msg->mi, mi, sizeof(mi));

	msglength += 18;
	if (msglength > NAVI_SENTENCE_MAXSIZE)
	{
		return navi_MsgExceedsMaxSize;
	}

	msglength = snprintf(iecmsg, sizeof(iecmsg),
		"$%sVTG,%s,%s,%s,%s,%s,%s,%s,%s,%s*%s\r\n", talkerid, ctrue, courseT,
		cmagn, courseM, snots, speedN, skmph, speedK, mi, "%s");
	IecPrint_Checksum(iecmsg, msglength, cs);

	*nmwritten = snprintf(buffer, maxsize, iecmsg, cs);
	return navi_Ok;
}

int IecParse_VTG(struct vtg_t *msg, char *buffer, int maxsize)
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

	result = IecParse_ModeIndicator(buffer + index, &msg->mi, &nmread);
	if (result != navi_Ok)
	{
		return navi_InvalidMessage;
	}

	index += nmread;

	if (buffer[index] != '*')
	{
		return navi_InvalidMessage;
	}

	return navi_Ok;
}

