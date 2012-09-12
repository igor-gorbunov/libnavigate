#ifndef INCLUDE_navi_gns_h
#define INCLUDE_navi_gns_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// GNS - GNSS fix data
// Fix data for single or combined sattelite navigation systems (GNSS).
// $--GNS,hhmmss.ss,llll.ll,a,yyyyy.yy,a,c--c,xx,x.x,x.x,x.x,x.x,x.x*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_gns(const struct gns_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_gns(struct gns_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gns_h
