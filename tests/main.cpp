/*
 * main.cpp - IEC messages generating/parsing tests and usage examples
 * for C++ bindings.
 *
 * Copyright (C) 2012 I. S. Gorbunov <igor.genius at gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <navigate++>
#include <iostream>

using namespace libnavigate;

int main(void)
{
	Navigate_t navi;
	int msglength = 0, nmwritten = 0;

	char buffer[1024];

	int remain = sizeof(buffer);

	// GLL
	Gll_t gll;
	gll.setTalkerId(TalkerId_t::GN);
	gll.setPositionFix(PositionFix_t(0.02, 0.00000000999));
	gll.setUtc(Utc_t(4, 34, 18.4));
	gll.setStatus(Status_t::DataValid);
	gll.setModeIndicator(ModeIndicator_t::Autonomous);

	try
	{
		nmwritten = navi.CreateMessage(gll, buffer + msglength, remain);
		msglength += nmwritten;
		remain -= nmwritten;
	}
	catch (NaviError_t e)
	{
	}

	// ALM
	Alm_t alm;
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
		nmwritten = navi.CreateMessage(alm, buffer + msglength, remain);
		msglength += nmwritten;
		remain -= nmwritten;
	}
	catch (NaviError_t e)
	{
	}

	// RMC
	Rmc_t rmc;
	rmc.setTalkerId(TalkerId_t::GN);
	rmc.setStatus(Status_t::DataInvalid);
	rmc.setModeIndicator(ModeIndicator_t::Estimated);

	rmc.setUtc(Utc_t(9, 19, 39.98));
	rmc.setPositionFix(PositionFix_t(-1.2323440, 1.834949));
	rmc.setDate(Date_t(2012, 3, 18));

	// Part 1
	try
	{
		nmwritten = navi.CreateMessage(rmc, buffer + msglength, remain);
		msglength += nmwritten;
		remain -= nmwritten;
	}
	catch (NaviError_t e)
	{
	}

	rmc.clearMessage();
	rmc.setUtc(Utc_t(9, 19, 39.98));
	rmc.setDate(Date_t(2012, 3, 18));
	rmc.setSpeed(1.03553);
	rmc.setCourse(180.2112);
	rmc.setMagneticVariation(Offset_t(23.011, Offset_t::East));

	// Part 2
	try
	{
		nmwritten = navi.CreateMessage(rmc, buffer + msglength, remain);
		msglength += nmwritten;
		remain -= nmwritten;
	}
	catch (NaviError_t e)
	{
	}

	// AAM
	Aam_t aam(TalkerId_t::GP);
	aam.setCircleStatus(Status_t::DataValid);
	aam.setPerpendicularStatus(Status_t::DataInvalid);
	aam.setWaypointRadius(10.1);
	aam.setWaypointId("St. Petersburg, Russia");

	try
	{
		nmwritten = navi.CreateMessage(aam, buffer + msglength, remain);
		msglength += nmwritten;
		remain -= nmwritten;
	}
	catch (NaviError_t e)
	{
	}

	// ACK
	Ack_t ack(TalkerId_t::GP);
	ack.setAlarmId(7);

	try
	{
		nmwritten = navi.CreateMessage(ack, buffer + msglength, remain);
		msglength += nmwritten;
		remain -= nmwritten;
	}
	catch (NaviError_t e)
	{
	}

	// ALR
	Alr_t alr(TalkerId_t::GL);
	alr.setUtc(Utc_t(12, 8, 13));
	alr.setAlarmId(846);
	alr.setCondition(Status_t::DataValid);
	alr.setAcknowledgeState(Status_t::DataInvalid);

	try
	{
		nmwritten = navi.CreateMessage(alr, buffer + msglength, remain);
		msglength += nmwritten;
		remain -= nmwritten;
	}
	catch (NaviError_t e)
	{
	}

	// ALR
	alr.clearMessage();
	alr.setTalkerId(TalkerId_t::GL);
	alr.setUtc(Utc_t(16, 12, 0));
	alr.setAlarmId(7);
	alr.setCondition(Status_t::DataInvalid);
	alr.setAcknowledgeState(Status_t::DataInvalid);
	alr.setDescription(std::string("Captain, take your pills."));

	try
	{
		nmwritten = navi.CreateMessage(alr, buffer + msglength, remain);
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
