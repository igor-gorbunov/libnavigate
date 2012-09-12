#ifndef INCLUDE_navi_config_h
#define INCLUDE_navi_config_h

#include "generic.h"

NAVI_BEGIN_DECL

#define LIBNAVIGATE_CAPS_GENERATOR		0x00000001
#define LIBNAVIGATE_CAPS_PARSER			0x00000002

NAVI_EXTERN(unsigned int) naviconf_get_caps(void);

NAVI_END_DECL

#endif // INCLUDE_navi_config_h
