#ifndef INCLUDE_navi_rmc_h
#define INCLUDE_navi_rmc_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// RMC - Recommended minimum specific GNSS data
// Time, date, position, course and speed data provided by a GNSS navigation
// receiver. This sentence is transmitted at intervals not exceeding 2 s and is
// always accompanied by RMB when a destination waypoint is active. RMC and RMB
// are the recommended minimum data to be provided by a GNSS receiver. All data
// fields must be provided, null fields used only when data is temporarily
// unavailable.
// $--RMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxxxx,x.x,a,a*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_msg_create_rmc(const struct rmc_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int IecParse_RMC(struct rmc_t *msg, char *buffer, int maxsize);

NAVI_END_DECL

#endif // INCLUDE_navi_rmc_h

