#include <navigate++.hpp>

namespace libnavigate
{

	int Navigate_t::ParseMessage(char *buffer, int maxsize, int msgsize, MessageType_t &type, void *msg)
	{
		throw NaviError_t(NaviError_t::NotImplemented);
	}

}
