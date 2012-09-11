#ifndef INCLUDE_navi_common_h
#define INCLUDE_navi_common_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

NAVI_BEGIN_DECL

//
// Meters per second to knots (nautical mile per hour)
#define MPS_TO_KNOTS(mps)		(mps * 1.94384449)

//
// Meters per second to km/h convertion coefficient
#define MPS_TO_KMPH(mps)		(mps * 3.600)

//
// Knots (nautical mile per hour) to meters per second
#define KNOTS_TO_MPS(knots)		(knots * 0.514444445)

//
// km/h to meters per second convertion coefficient
#define KMPH_TO_MPS(kmph)		(kmph * 0.277777777777777778)


//
// Removes trailing zeroes of a floating point zeroes
// Returns the remaining string length
int remove_trailing_zeroes(char *buffer, int length);

#ifdef WIN32
extern double round(double x);
#endif // WIN32

extern const char *navi_fmtlist[];

NAVI_END_DECL

#endif // INCLUDE_navi_common_h
