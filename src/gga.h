#ifndef INCLUDE_navi_gga_h
#define INCLUDE_navi_gga_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// GGA - Global positioning system (GPS) fix data
// Time, position and fix-related data for a GPS receiver.
// $--GGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_gga(const struct gga_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_gga(struct gga_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gga_h

