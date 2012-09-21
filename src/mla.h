#ifndef INCLUDE_navi_mla_h
#define INCLUDE_navi_mla_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// MLA - GLONASS almanac data
// Contains complete almanac data for one GLONASS satellite.
// $--MLA,x.x,x.x,xx,x.x,hh,hhhh,hh,hhhh,hhhh,hhhhhh,hhhhhh,hhhhhh,hhhhhh,hhh,hhh*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_mla(const struct mla_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_mla(struct mla_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_mla_h

