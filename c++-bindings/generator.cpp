#include <navigate++.hpp>

namespace libnavigate
{

	int Navigate_t::CreateMessage(const Message_t &msg, char *buffer, int maxsize)
	{
		int nmwritten;

		if (navi_create_msg(MsgCodeFromMessageType(msg.type()), msg, buffer, maxsize, &nmwritten) != navi_Ok)
			throw NaviErrorFromErrorCode(navierr_get_last()->errclass);

		return nmwritten;
	}
}
