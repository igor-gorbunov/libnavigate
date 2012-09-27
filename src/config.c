/*
 * config.c - libnavigate configuration methods
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

#include <libnavigate/config.h>
#include <libnavigate/errors.h>

#include "version.h"

struct navi_config_t
{
	unsigned int caps;		// capabilities of the library
	const char *version;	// version of the library
	int presicion;			// precision of generated variable numbers
};

static struct navi_config_t g_navi_config_t =
{

#ifndef NO_GENERATOR
	LIBNAVIGATE_CAPS_GENERATOR |
#endif //  NO_GENERATOR

#ifndef NO_PARSER
	LIBNAVIGATE_CAPS_PARSER |
#endif //  NO_PARSER

	0,
	LIBNAVIGATE_VERSION_STRING,
	5
};

unsigned int naviconf_get_caps(void)
{
	return g_navi_config_t.caps;
}

int naviconf_get_presicion(void)
{
	return g_navi_config_t.presicion;
}

int naviconf_set_presicion(int precision)
{
	if ((precision < 0) || (precision > 15))
	{
		navierr_set_last(navi_InvalidParameter);
		return navi_Error;
	}

	g_navi_config_t.presicion = precision;
	return navi_Ok;
}

