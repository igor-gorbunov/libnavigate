/*
 * check_query.c - query messages generating/parsing tests and usage examples.
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
	navierr_status_t result;
	size_t msglength, nmwritten, nmread, parsed;
	int finished;

	char inbuffer[1024], outbuffer[256];

	navi_approved_fmt_t data = navi_GLL;

	navi_addrfield_t msgtype;
	const navi_error_t *lasterr;

	struct query_field_t s;

	msglength = 0;

	s.from = navi_GL;
	s.to = navi_VW;

	result = navi_create_msg(navi_af_Query, &s, &data,
		inbuffer, sizeof(inbuffer), &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
	}
	else
	{
		printf("Composition of query message failed (%d)\n", navierr_get_last()->errclass);
	}

	printf("msglength = %d\n", msglength);
	printf("message = '%s'\n", inbuffer);

	finished = 0;
	parsed = 0;
	nmread = 0;

	memset(&s, 0, sizeof(s));
	data = navi_approvedfmt_Unknown;

	do
	{
		while ((result = navi_parse_msg(inbuffer + parsed, sizeof(inbuffer) - parsed,
			sizeof(outbuffer), &msgtype, outbuffer, &nmread)) == navi_Ok)
		{
			parsed += nmread;

			switch (msgtype)
			{
			case navi_af_Query:
				memmove(&s, outbuffer, sizeof(s));
				memmove(&data, outbuffer + sizeof(s), sizeof(data));
				printf("Received query sentence: from '%s (%d)' to '%s (%d)' requests '%s (%d)'\n",
					navi_talkerid_str(s.from), s.from, navi_talkerid_str(s.to), s.to,
					navi_sentencefmt_str(data), data);
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
			case navi_MLA:
				printf("Could not parse MLA\n");
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

	return 0;
}
