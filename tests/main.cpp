#include <navigate++.hpp>
#include <iostream>

using namespace libnavigate;

int main(void)
{
	Navigate_t navi;
	int msglength = 0, nmwritten = 0;

	char buffer[1024];
	Gll_t gll;

	int remain = sizeof(buffer);

	// GLL
	gll.setTalkerId(TalkerId_t::GN);
	gll.setPositionFix(PositionFix_t(0.02, 0.00000000999));
	gll.setUtc(Utc_t(4, 34, 18.4));
	gll.setStatus(Status_t::DataValid);
	gll.setModeIndicator(ModeIndicator_t::Autonomous);

	try
	{
		nmwritten = navi.CreateMessage(gll, buffer, sizeof(buffer));
		msglength += nmwritten;
		remain -= nmwritten;
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

	std::cout << "msglength = " << msglength << "\n";
	std::cout << "message = '" << buffer << "'\n";

	//int nmread = 0;
	//Message_t 

	//try
	//{
	//	nmread = navi.ParseMessage(0, 0, 0, mtype, 0);
	//}
	//catch (NaviError_t e)
	//{
	//	switch (e)
	//	{
	//	case NaviError_t::NotImplemented:
	//		std::cout << "Method not implemented\n";
	//		break;
	//	}
	//}

	return 0;
}
