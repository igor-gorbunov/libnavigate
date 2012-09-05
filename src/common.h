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
// Prints talker identifier
int IecPrint_TalkerId(int tid, char *buffer, int maxsize);

//
// Prints datum
int IecPrint_Datum(int datum, char *buffer, int maxsize, int notnull);

//
// Prints local datum subdivision
int IecPrint_DatumSubdivision(int lds, char *buffer, int maxsize, int notnull);

//
// Prints a floating point value
int IecPrint_Double(double value, char *buffer, int maxsize, int notnull);

//
// Prints offset sign
int IecPrint_OffsetSign(int sign, char *buffer, int maxsize, int notnull);

//
// Prints checksum of the generated message
int IecPrint_Checksum(char *msg, int maxsize, char *cs);

//
// Prints latitude (llll.ll)
int IecPrint_Latitude(double value, char *buffer, int maxsize, int notnull);

//
// Prints longitude (yyyyy.yy)
int IecPrint_Longitude(double value, char *buffer, int maxsize, int notnull);

//
// Prints UTC
int IecPrint_Utc(const struct naviUtc_t *utc, char *buffer,
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
// Removes trailing zeroes of a floating point zeroes
int RemoveTrailingZeroes(char *buffer, int maxsize);

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
// Parses latitude/longitude/offset sign
int IecParse_OffsetSign(char *buffer, int *sign, int *nmread);

//
// Parses latitude
int IecParse_Latitude(char *buffer, struct navi_offset_t *latitude,
	int *nmread);

//
// Parses longitude sign
int IecParse_Longitude(char *buffer, struct navi_offset_t *longitude,
	int *nmread);

//
// Parses time
int IecParse_Time(char *buffer, struct naviUtc_t *utc, int *nmread);

//
// Parses status
int IecParse_Status(char *buffer, int *status, int *nmread);

//
// Parses mode indicator
int IecParse_ModeIndicator(char *buffer, int *mi, int *nmread);

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

/**
 * Parses offset field in the form of x.x,a. The field must end with ',' or '*'
 *
 * @param pointer to the first byte of field
 * @param out pointer to structure where the result is stored
 * @param pointer to variable where the number of read bytes is stored
 * @return 0 on success, or navi_Error if it's null or an error occured. Call
 * navierr_get_last() to check the error
 */
int navi_msg_parse_offset(char *buffer, struct navi_offset_t *offset,
		int *nmread);

NAVI_END_DECL

#endif // INCLUDE_navi_common_h

