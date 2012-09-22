#include <navigate++.hpp>

namespace libnavigate
{

	int Navigate_t::CreateMessage(const MessageType_t &type, void *msg, char *buffer, int maxsize)
	{
		throw NaviError_t(NaviError_t::NotImplemented);
	}

}
