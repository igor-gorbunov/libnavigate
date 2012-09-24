#include <libnavigate/c++/errors.hpp>

namespace libnavigate
{

NaviError_t NaviError_t::fromErrorCode(int errcode)
{
	switch (errcode)
	{
	case navi_MsgExceedsMaxSize: return MsgExceedsMaxSize;
	case navi_CrcEror: return CrcEror;
	case navi_NotEnoughBuffer: return NotEnoughBuffer;
	case navi_MsgNotSupported: return MsgNotSupported;
	case navi_NoValidMessage: return NoValidMessage;
	case navi_NullField: return NullField;
	case navi_InvalidMessage: return InvalidMessage;
	case navi_NotImplemented: return NotImplemented;
	case navi_InvalidParameter: return InvalidParameter;
	default:
		return Unknown;
	}
}

}

