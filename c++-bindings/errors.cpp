#include "include/libnavigate/c++/errors.hpp"

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

NaviError_t::NaviError_t()
	{ m_value = Unknown; }

NaviError_t::NaviError_t(enum NaviError_t::errtype_t initial)
	{ m_value = initial; }

NaviError_t::NaviError_t(const NaviError_t &right)
	{ m_value = right.m_value; }

NaviError_t::~NaviError_t() { }

}
