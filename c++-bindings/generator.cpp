#include "include/libnavigate/c++/errors.hpp"
#include "include/libnavigate/c++/navigate.hpp"

namespace libnavigate
{

size_t Navigate_t::CreateMessage(const Message_t &msg, char *buffer, size_t maxsize)
{
	size_t nmwritten;

	if (navi_create_msg(msg.type().toSentenceFormatter(), msg, buffer,
			maxsize, &nmwritten) != navi_Ok)
		throw NaviError_t::fromErrorCode(navierr_get_last()->errclass);

	return nmwritten;
}

}
