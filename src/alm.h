#ifndef INCLUDE_navi_alm_h
#define INCLUDE_navi_alm_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// ALM - GPS almanac data
// Contains GPS week number, satellite health and the complete almanac data
// for one satellite. Multiple messages may be transmitted, one for each
// satellite in the GPS constellation, up to a maximum of 32 messages.
// $--ALM,x.x,x.x,xx,x.x,hh,hhhh,hh,hhhh,hhhh,hhhhhh,hhhhhh,hhhhhh,hhhhhh,hhh,hhh*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_alm(const struct alm_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_alm(struct alm_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_alm_h

