#ifndef INCLUDE_navi_gst_h
#define INCLUDE_navi_gst_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

//
// GST - GNSS pseudorange noise statistics
// This message is used to support RAIM.
// $--GST,hhmmss.ss,x.x,x.x,x.x,x.x,x.x,x.x,x.x*hh<cr><lf>
//

NAVI_BEGIN_DECL

int navi_create_gst(const struct gst_t *msg, char *buffer,
		int maxsize, int *nmwritten);

int navi_parse_gst(struct gst_t *msg, char *buffer);

NAVI_END_DECL

#endif // INCLUDE_navi_gst_h

