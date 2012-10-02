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
	size_t msglength = 0, nmwritten = 0;

	char buffer[1024];

	size_t remain = sizeof(buffer);

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
	rmc.setTalkerId(TalkerId_t::GN);
	rmc.setStatus(Status_t::DataInvalid);
	rmc.setModeIndicator(ModeIndicator_t::Estimated);

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

	// TXT
	Txt_t txt(TalkerId_t::GP);
	txt.setTextId(25);
	txt.setTextMessage("DR MODE - ANTENNA FAULT!");

	try
	{
		nmwritten = navi.CreateMessage(txt, buffer + msglength, remain);
		msglength += nmwritten;
		remain -= nmwritten;
	}
	catch (NaviError_t e)
	{
	}

	// ZDA
	Zda_t zda(TalkerId_t::GP);
	zda.setUtc(Utc_t(8, 12, 38.56));
	zda.setDate(Date_t(1982, 5, 25));
	zda.setLocalZoneOffset(-240);

	try
	{
		nmwritten = navi.CreateMessage(zda, buffer + msglength, remain);
		msglength += nmwritten;
		remain -= nmwritten;
	}
	catch (NaviError_t)
	{
		std::cout << "Could not generate ZDA sentence.\n";
	}

	std::cout << "msglength = " << msglength << "\n";
	std::cout << "message = '" << buffer << "'\n";

	size_t i = 0, nmread = 0;
	remain = sizeof(buffer);

	while (remain > 0)
	{
		try
		{
			Message_t msg = navi.ParseMessage(buffer + i, remain, &nmread);
			i += nmread;
			remain -= nmread;

			switch (msg.type())
			{
			case MessageType_t::ACK:
				{
					Ack_t ack(msg);
					std::cout << "ACK message\n";
					std::cout << "\tLocal alarm number: " << ack.alarmId() << "\n";
				}
				break;
			case MessageType_t::AAM:
				{
					Aam_t aam(msg);
					std::cout << "AAM message\n";
					std::cout << "\tDescription: " << aam.waypointId().c_str() << "\n";
				}
				break;
			case MessageType_t::ALM:
				{
					Alm_t alm(msg);
					std::cout << "ALM message\n";
				}
				break;
			case MessageType_t::ALR:
				{
					Alr_t alr(msg);
					std::cout << "ALR message\n";
					std::cout << "\tDescription: " << alr.description().c_str() << "\n";
				}
				break;
			case MessageType_t::DTM:
				{
					Dtm_t dtm(msg);
					std::cout << "DTM message\n";
				}
				break;
			case MessageType_t::GBS:
				{
					Gbs_t gbs(msg);
					std::cout << "GBS message\n";
				}
				break;
			case MessageType_t::GGA:
				{
					Gga_t gga(msg);
					std::cout << "GGA message\n";
				}
				break;
			case MessageType_t::GLL:
				{
					Gll_t gll(msg);
					std::cout << "GLL message\n";
				}
				break;
			case MessageType_t::GNS:
				{
					Gns_t gns(msg);
					std::cout << "GNS message\n";
				}
				break;
			case MessageType_t::GRS:
				{
					Grs_t grs(msg);
					std::cout << "GRS message\n";
				}
				break;
			case MessageType_t::GSA:
				{
					Gsa_t gsa(msg);
					std::cout << "GSA message\n";
				}
				break;
			case MessageType_t::GST:
				{
					Gst_t gst(msg);
					std::cout << "GST message\n";
				}
				break;
			case MessageType_t::GSV:
				{
					Gsv_t gsv(msg);
					std::cout << "GSV message\n";
				}
				break;
			case MessageType_t::MLA:
				{
					Mla_t mla(msg);
					std::cout << "MLA message\n";
				}
				break;
			case MessageType_t::RMC:
				{
					Rmc_t rmc(msg);
					std::cout << "RMC message: Talker Id = " << rmc.talkerId().toTalkerIdCode() << "\n";
					if (rmc.isUtcValid())
						std::cout << "\tUTC: " << rmc.utc().hours() << ":" << rmc.utc().minutes() << ":" << rmc.utc().seconds() << "\n";
					std::cout << "\tStatus: " << rmc.status().toStatusCode() << "\n";
					if (rmc.isPositionValid())
						std::cout << "\tPosition: " << rmc.positionFix().latitude() << ", " << rmc.positionFix().longitude() << "\n";
					if (rmc.isSpeedValid())
						std::cout << "\tSpeed: " << rmc.speed() << "\n";
					if (rmc.isCourseValid())
						std::cout << "\tCourse: " << rmc.course() << "\n";
					if (rmc.isDateValid())
						std::cout << "\tDate: " << rmc.date().year() << "-" << rmc.date().month() << "-" << rmc.date().day() << "\n";
					if (rmc.isMagneticVariationValid())
						std::cout << "\tMagnetic variation: " << rmc.magneticVariation().offset() << " " << rmc.magneticVariation().quarter() << "\n";
					std::cout << "\tMode indicator: " << rmc.modeIndicator().toModeIndCode() << "\n";
				}
				break;
			case MessageType_t::TXT:
				{
					Txt_t txt(msg);
					std::cout << "TXT message: Talker Id = " << txt.talkerId().toTalkerIdCode() << "\n";
					std::cout << "Message text: " << txt.textMessage() << "\n";
				}
				break;
			case MessageType_t::ZDA:
				{
					Zda_t zda(msg);
					std::cout << "ZDA message: Talker Id = " << zda.talkerId().toTalkerIdCode() << "\n";
					if (zda.isUtcValid())
						std::cout << "\tUTC: " << zda.utc().hours() << ":" << zda.utc().minutes() << ":" << zda.utc().seconds() << "\n";
					if (zda.isDateValid())
						std::cout << "\tDate: " << zda.date().year() << "-" << zda.date().month() << "-" << zda.date().day() << "\n";
					if (zda.isLocalZoneOffsetValid())
						std::cout << "\tLocal zone offset: " << zda.localZoneOffset() << "\n";
				}
				break;
			default:
				break;
			}
		}
		catch (NaviError_t e)
		{
			switch (e)
			{
			case NaviError_t::NotImplemented:
				std::cout << "Method not implemented\n";
				break;
			case NaviError_t::NoValidMessage:
				std::cout << "Buffer empty\n";
				remain = 0;
				break;
			default:
				std::cout << "Exception\n";
				break;
			}
		}
	}

	msglength = 0, nmwritten = 0;
	remain = sizeof(buffer);

	// VTG
	Vtg_t vtg(TalkerId_t::VW);
	vtg.setCourseTrue(1.2);
	vtg.setCourseMagnetic(1.68);
	vtg.setSpeed(2.40);
	vtg.setModeIndicator(ModeIndicator_t::Autonomous);

	try
	{
		nmwritten = navi.CreateMessage(vtg, buffer + msglength, remain);
		msglength += nmwritten;
		remain -= nmwritten;
	}
	catch (NaviError_t)
	{
		std::cout << "Could not generate VTG sentence.\n";
	}

	std::cout << "msglength = " << msglength << "\n";
	std::cout << "message = '" << buffer << "'\n";

	i = 0, nmread = 0;
	remain = sizeof(buffer);

	while (remain > 0)
	{
		try
		{
			Message_t msg = navi.ParseMessage(buffer + i, remain, &nmread);
			i += nmread;
			remain -= nmread;

			switch (msg.type())
			{
			case MessageType_t::VTG:
				{
					Vtg_t vtg(msg);
					std::cout << "VTG message: Talker Id = " << vtg.talkerId().toTalkerIdCode() << "\n";
					if (vtg.isCourseTrueValid())
						std::cout << "\tCourse, true: " << vtg.courseTrue() << "\n";
					if (vtg.isCourseMagneticValid())
						std::cout << "\tCourse, magnetic: " << vtg.courseMagnetic() << "\n";
					if (vtg.isSpeedValid())
						std::cout << "\tSpeed, m/s: " << vtg.speed() << "\n";
					std::cout << "\tMode indicator: " << vtg.modeIndicator().toModeIndCode() << "\n";
				}
				break;
			default:
				break;
			}
		}
		catch (NaviError_t e)
		{
			switch (e)
			{
			case NaviError_t::NotImplemented:
				std::cout << "Method not implemented\n";
				break;
			case NaviError_t::NoValidMessage:
				std::cout << "Buffer empty\n";
				remain = 0;
				break;
			default:
				std::cout << "Exception\n";
				break;
			}
		}
	}

	return 0;
}
