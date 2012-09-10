#ifndef INCLUDE_navi_errors_h
#define INCLUDE_navi_errors_h

#include "generic.h"

NAVI_BEGIN_DECL

//
// Return statuses while generation/parsing
//
enum
{
	navi_Error = -1,		// error
	navi_Ok = 0				// no error
};

//
// Error classes
//
enum
{
	navi_Undefined = 0,			// undefined or no error
	navi_MsgExceedsMaxSize = 1,	// message too long
	navi_CrcEror = 2,			// crc error
	navi_NotEnoughBuffer = 3,	// not enough space in output buffer
	navi_MsgNotSupported = 4,	// message type not supported
	navi_NoValidMessage = 5,	// no valid message in buffer
	navi_NullField = 6,			// null field in a message
	navi_InvalidMessage = 7,	// message does not conform to protocol
	navi_NotImplemented = 8,	// method not implemented
	navi_InvalidParameter = 9	// invalid parameter to method
};

typedef struct _navi_error_t
{
	int errclass;
} navi_error_t;

/**
 * Return the pointer to 'navi_error_t' object that holds the last library error
 * that occurred for this thread.
 */
NAVI_EXTERN(const navi_error_t *) navierr_get_last(void);

NAVI_EXTERN(void) navierr_set_last(int errclass);

NAVI_END_DECL

#endif // INCLUDE_navi_errors_h
