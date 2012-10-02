#ifndef INCLUDE_navi_errorsplusplus
#define INCLUDE_navi_errorsplusplus

#include <libnavigate/c++/generic.hpp>
#include <libnavigate/errors.h>

namespace libnavigate
{

NAVI_EXTERN_CLASS(NaviError_t)
{
public:
	enum errtype_t
	{
		Unknown,			// unknown or not defined
		MsgExceedsMaxSize,	// message too long
		CrcEror,			// crc error
		NotEnoughBuffer,	// not enough space in output buffer
		MsgNotSupported,	// message type not supported
		NoValidMessage,		// no valid message in buffer
		NullField,			// null field in a message
		InvalidMessage,		// message does not conform to protocol
		NotImplemented,		// method not implemented
		InvalidParameter	// invalid parameter to method
	};

public:
	static NaviError_t fromErrorCode(int errcode);

public:
	NaviError_t();
	NaviError_t(enum NaviError_t::errtype_t initial);
	NaviError_t(const NaviError_t &right);
	virtual ~NaviError_t();

public:
	inline operator int() const
		{ return int(m_value); }

private:
	enum errtype_t m_value;
};

}

#endif // INCLUDE_navi_errorsplusplus
