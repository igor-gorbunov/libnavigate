#ifndef INCLUDE_navi_gsa_h
#define INCLUDE_navi_gsa_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// GSA - GNSS DOP and active satellites
// GNSS receiver operating mode, satellites used in the navigation solution
// reported by the GGA or GNS sentences, and DOP values.
// $--GSA,a,x,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,x.x,x.x,x.x*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_gsa(const struct gsa_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_gsa(struct gsa_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gsa_h

