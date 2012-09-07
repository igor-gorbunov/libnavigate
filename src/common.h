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
// Prints datum
int IecPrint_Datum(int datum, char *buffer, int maxsize, int notnull);

//
// Prints local datum subdivision
int IecPrint_DatumSubdivision(int lds, char *buffer, int maxsize, int notnull);

//
// Prints checksum of the generated message
int IecPrint_Checksum(char *msg, int maxsize, char *cs);

//
// Prints offset or position fix sign
// Returns the number of printed characters
int navi_msg_create_sign(int sign, char *buffer, int maxsize, int notnull);

//
// Prints a floating point value
// Returns the number of printed characters
int navi_msg_create_double(double value, char *buffer, int maxsize, int notnull);

//
// Prints position fix 'llll.ll,a,yyyyy.yy,a', or null fields
// Returns the number of printed characters
int navi_msg_create_position_fix(const struct navi_position_t *fix,
		char *buffer, int maxsize, int notnull);

//
// Prints UTC
int IecPrint_Utc(const struct navi_utc_t *utc, char *buffer,
	int maxsize, int notnull);

//
// Prints message status
int IecPrint_Status(int status, char *buffer, int maxsize);

//
// Prints mode indicator
int IecPrint_ModeIndicator(int mi, char *buffer, int maxsize);

//
// Prints array of mode indicators
int IecPrint_ModeIndicatorArray(const int mi[], char *buffer,
	int maxsize, int notnull);

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
// Parses datum field
int IecParse_Datum(char *buffer, int *datum, int *nmread);

//
// Parses datum subdivision code field
int IecParse_DatumSub(char *buffer, int *datumsub, int *nmread);

//
// Parses floating point value
int IecParse_Double(char *buffer, double *value, int *nmread);

//
// Parses mode indicator array
int IecParse_ModeIndicatorArray(char *buffer, int mi[], int *nmread);

//
// Parses integer value
int IecParse_Integer(char *buffer, int *value, int *nmread);

//
// Parses date (ddmmyy or ddmmyyyy)
int IecParse_Date(char *buffer, struct naviDate_t *date, int *nmread);

//
// Parses local zone (sxx,xx)
int IecParse_LocalZone(char *buffer, int *offset, int *nmread);

NAVI_END_DECL

#endif // INCLUDE_navi_common_h
