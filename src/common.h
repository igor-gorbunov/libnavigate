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

//
// Print fixed length field with given radix
extern int navi_print_fixedfield(const char bytes[], int fieldwidth, int radix,
	char *buffer, int maxsize);

//
// Splits an integer into array of digits. Radix may be 10 or 16.
// Most significant digit is put at bytes[0]
extern int navi_split_integer(unsigned int value, char bytes[], int width, int radix);

//
// Composes an integer from array of digits. Radix may be 10 or 16.
// Most significant digit is taken from bytes[0]
//
// Returns the combined value
extern unsigned int navi_compose_integer(char bytes[], int width, int radix);

//
// Talker IDs list
extern const char *navi_tidlist[];

//
// Approved sentence formatters list
extern const char *navi_fmtlist[];

NAVI_END_DECL

#endif // INCLUDE_navi_common_h
