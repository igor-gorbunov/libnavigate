#include <navigate++>
#include <iostream>

using namespace libnavigate;

int main(void)
{
	Navigate_t navi;
	int msglength = 0, nmwritten = 0;

	char buffer[1024];
	Alm_t alm;
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
	}

	// ALM
	alm.setTalkerId(TalkerId_t::GP);
	alm.setNmOfSatellites(3);

	alm.setSatellitePrn(0, 4);
	alm.setGpsWeek(0, 3400);
	alm.setSvHealth(0, 0x44);
	alm.setEccentricity(0, 0x0011);
	alm.setAlmanacReferenceTime(0, 0x09);
	alm.setInclinationAngle(0, 0x8a14);
	alm.setRateOfRightAscension(0, 0x7f01);
	alm.setSqrtOfSemiMajorAxis(0, 0x780012);
	alm.setArgumentOfPerigee(0, 0x00dd01);
	alm.setLongitudeOfAscensionNode(0, 0x000000);
	alm.setMeanAnomaly(0, 0x920f15);
	alm.setClockParameter0(0, 0x115);
	alm.setClockParameter1(0, 0x023);

	alm.setSatellitePrn(1, 14);
	alm.setGpsWeek(1, 3400);
	alm.setSvHealth(1, 0xaf);
	alm.setEccentricity(1, 0x0011);
	alm.setAlmanacReferenceTime(1, 0x00);
	alm.setInclinationAngle(1, 0x8114);
	alm.setRateOfRightAscension(1, 0x7701);
	alm.setSqrtOfSemiMajorAxis(1, 0x000012);
	alm.setArgumentOfPerigee(1, 0x002201);
	alm.setLongitudeOfAscensionNode(1, 0x000000);
	alm.setMeanAnomaly(1, 0x920115);

	alm.setSatellitePrn(2, 32);
	alm.setGpsWeek(1, 3400);
	alm.setSvHealth(1, 0x00);

	try
	{
		nmwritten = navi.CreateMessage(alm, buffer, sizeof(buffer));
		msglength += nmwritten;
		remain -= nmwritten;
	}
	catch (NaviError_t e)
	{
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
