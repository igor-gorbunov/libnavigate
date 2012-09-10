#ifndef INCLUDE_navi_common_h
#define INCLUDE_navi_common_h

#include <libnavigate/generic.h>
#include <libnavigate/sentence.h>

NAVI_BEGIN_DECL

//
// Meters per second to knots (nautical mile per hour)
#define MPS_TO_KNOTS		1.94384449

//
// Meters per second to km/h convertion coefficient
#define MPS_TO_KMH			3.600

//
// Knots (nautical mile per hour) to meters per second
#define KNOTS_TO_MPS		0.514444445

//
// km/h to meters per second convertion coefficient
#define KMH_TO_MPS			0.277777777777777778


//
// Removes trailing zeroes of a floating point zeroes
// Returns the remaining string length
int remove_trailing_zeroes(char *buffer, int length);

//
// Prints checksum of the generated message
int IecPrint_Checksum(char *msg, int maxsize, char *cs);

//
// Determines the talker id and sentence formatter
int IecScan_AdressField(char *buffer, int maxsize, int *tid, int *msgtype);

//
// Checks that the message is not broken
// Returns 0, if the checksum is correct, -EPROTO otherwise
int IecScan_CheckSum(char *buffer, int maxsize);

//
// Looks up Talker ID
int IecLookupTalkerId(char *buffer, int *nmread);

//
// Looks up sentence formatter
int IecLookupSentenceFormatter(char *buffer, int *nmread);

//
// Parses local zone (sxx,xx)
int IecParse_LocalZone(char *buffer, int *offset, int *nmread);

#ifdef WIN32
extern double round(double x);
#endif // WIN32

NAVI_END_DECL

#endif // INCLUDE_navi_common_h
