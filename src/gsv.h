#ifndef INCLUDE_navi_gsv_h
#define INCLUDE_navi_gsv_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// GSV - GNSS satellites in view
// Number of satellites in view, satellite ID numbers, elevation, azimuth and
// SNR value. Four satellites maximum per transmission. Null fields are not
// required for unused sets when less than four sets are transmitted.
// $--GSV,x,x,xx,xx,xx,xxx,xx......,xx,xx,xxx,xx*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_gsv(const struct gsv_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_gsv(struct gsv_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gsv_h

