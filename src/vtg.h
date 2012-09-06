#ifndef INCLUDE_navi_vtg_h
#define INCLUDE_navi_vtg_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// VTG - Course over ground and ground speed
// The actual course and speed relative to the ground.
// $--VTG,x.x,T,x.x,M,x.x,N,x.x,K,a*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_vtg(const struct vtg_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int IecParse_VTG(struct vtg_t *msg, char *buffer, int maxsize);

NAVI_END_DECL

#endif // INCLUDE_navi_vtg_h

