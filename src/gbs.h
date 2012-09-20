#ifndef INCLUDE_navi_gbs_h
#define INCLUDE_navi_gbs_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// GBS - GNSS satellite fault detection
// This message shall be used for reporting RAIM information.
// $--GBS,hhmmss.ss,x.x,x.x,x.x,xx,x.x,x.x,x.x*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_gbs(const struct gbs_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_gbs(struct gbs_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gbs_h

