#include <libnavigate/config.h>
#include <libnavigate/errors.h>

#include "version.h"

struct navi_config_t
{
	unsigned int caps;		// capabilities of the library
	const char *version;	// version of the library
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
	LIBNAVIGATE_VERSION
};

unsigned int naviconf_get_caps(void)
{
	return g_navi_config_t.caps;
}
