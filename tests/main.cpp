#include <navigate++.hpp>
#include <iostream>

using namespace libnavigate;

int main(void)
{
	Navigate_t navi;
	int nmwritten = 0;

	char buffer[1024];
	struct alm_t alm;

	try
	{
		nmwritten = navi.CreateMessage(MessageType_t::ALM, &alm, buffer, sizeof(buffer));
	}
	catch (NaviError_t e)
	{
		switch (e)
		{
		case NaviError_t::NotImplemented:
			std::cout << "Method not implemented\n";
			break;
		}
	}

	int nmread = 0;
	MessageType_t mtype;

	try
	{
		nmread = navi.ParseMessage(0, 0, 0, mtype, 0);
	}
	catch (NaviError_t e)
	{
		switch (e)
		{
		case NaviError_t::NotImplemented:
			std::cout << "Method not implemented\n";
			break;
		}
	}

	return 0;
}
