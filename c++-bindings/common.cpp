#include <navigate++.hpp>

namespace libnavigate
{

	MessageType_t::MessageType_t() { m_value = Unknown; }

	MessageType_t::MessageType_t(enum MessageType_t::msgtype_t initial) { m_value = initial; }

	MessageType_t::MessageType_t(const MessageType_t &right) { m_value = right.m_value; }

	MessageType_t::~MessageType_t() { }

	NaviError_t::NaviError_t() { m_value = Unknown; }

	NaviError_t::NaviError_t(enum NaviError_t::errtype_t initial) { m_value = initial; }

	NaviError_t::NaviError_t(const NaviError_t &right) { m_value = right.m_value; }

	NaviError_t::~NaviError_t() { }

	NaviError_t::operator int() const
	{
		return int(m_value);
	}
}
