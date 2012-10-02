#include <libnavigate/c++/errors.hpp>
#include <libnavigate/c++/navigate.hpp>

namespace libnavigate
{

Message_t Navigate_t::ParseMessage(char *buffer, size_t maxsize, size_t *nmread)
{
	char parsed[2 * 1024];
	navierr_status_t result;
	navi_approved_fmt_t msgtype;

	if ((result = navi_parse_msg(buffer, maxsize, sizeof(parsed), parsed, &msgtype, nmread)) != navi_Ok)
		throw NaviError_t::fromErrorCode(navierr_get_last()->errclass);

	return Message_t(MessageType_t::fromSentenceFormatter(msgtype), parsed);
}

}
