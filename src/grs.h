#ifndef INCLUDE_navi_grs_h
#define INCLUDE_navi_grs_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// GRS - GNSS range residuals
// This message is used to support receiver autonomous integrity monitoring (RAIM).
// $--GRS,hhmmss.ss,x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_grs(const struct grs_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_grs(struct grs_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_grs_h

