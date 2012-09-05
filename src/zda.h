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

int IecCompose_ZDA(const struct zda_t *msg, char *buffer,
	int maxsize, int *nmwritten);

int IecParse_ZDA(struct zda_t *msg, char *buffer, int maxsize);

NAVI_END_DECL

#endif // INCLUDE_navi_zda_h

