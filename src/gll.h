#ifndef INCLUDE_navi_gll_h
#define INCLUDE_navi_gll_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// GLL - Geographic position - latitude/longitude
// Latitude and longitude of vessel position, time of position fix and status.
// $--GLL,llll.ll,a,yyyyy.yy,a,hhmmss.ss,A,a*hh<cr><lf>
//

NAVI_BEGIN_DECL

int IecCompose_GLL(const struct gll_t *msg, char *buffer,
	int maxsize, int *nmwritten);

int IecParse_GLL(struct gll_t *msg, char *buffer, int maxsize);

NAVI_END_DECL

#endif // INCLUDE_navi_gll_h

