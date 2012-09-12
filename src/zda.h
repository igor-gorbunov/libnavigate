#ifndef INCLUDE_navi_zda_h
#define INCLUDE_navi_zda_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// ZDA - Time and date
// UTC, day, month, year and local time zone.
// $--ZDA,hhmmss.ss,xx,xx,xxxx,xx,xx*hh<cr><lf>
//

NAVI_BEGIN_DECL

//
// ZDA Message Generator
//
#ifndef NO_GENERATOR

int navi_create_zda(const struct zda_t *msg, char *buffer,
		int maxsize, int *nmwritten);

#endif // NO_GENERATOR

//
// ZDA Message Parser
//

#ifndef NO_PARSER

int navi_parse_zda(struct zda_t *msg, char *buffer);

#endif // NO_PARSER

NAVI_END_DECL

#endif // INCLUDE_navi_zda_h
