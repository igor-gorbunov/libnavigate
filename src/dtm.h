#ifndef INCLUDE_navi_dtm_h
#define INCLUDE_navi_dtm_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// DTM - Datum reference
// Local geodetic datum and datum offsets from a reference datum. This sentence
// is used to define the datum to which a position location, and geographic
// locations in subsequent sentences, are referenced. Lattitude, longitude and
// altitude offsets from the reference datum, and the selection of the reference
// datum, are also provided.
// $--DTM,ccc,a,x.x,a,x.x,a,x.x,ccc*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_dtm(const struct dtm_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_msg_parse_dtm(struct dtm_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_dtm_h
