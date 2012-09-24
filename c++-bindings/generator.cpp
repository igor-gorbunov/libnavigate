#include <navigate++>

namespace libnavigate
{

int Navigate_t::CreateMessage(const Message_t &msg, char *buffer, int maxsize)
{
	int nmwritten;

	if (navi_create_msg(msg.type().toSentenceFormatter(), msg, buffer,
			maxsize, &nmwritten) != navi_Ok)
		throw NaviError_t::fromErrorCode(navierr_get_last()->errclass);

	return nmwritten;
}

}

