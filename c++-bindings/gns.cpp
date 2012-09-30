/*
 * gns.cpp - implementation of Gns_t class
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

#include <libnavigate/c++/gns.hpp>

namespace libnavigate
{

Gns_t::Gns_t(const TalkerId_t &tid) : Message_t(MessageType_t::GNS)
{
	((struct gns_t *)(*this))->tid = tid.toTalkerIdCode();
	((struct gns_t *)(*this))->vfields = 0;
}

Gns_t::Gns_t(const Message_t &msg) : Message_t(msg) { }

Gns_t::~Gns_t() { }

TalkerId_t Gns_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct gns_t *)(*this))->tid); }

Utc_t Gns_t::utc() const
	{ return Utc_t(((const struct gns_t *)(*this))->utc.hour, ((const struct gns_t *)(*this))->utc.min, ((const struct gns_t *)(*this))->utc.sec); }

PositionFix_t Gns_t::positionFix() const
	{ return PositionFix_t::fromPosition(&((const struct gns_t *)(*this))->fix); }

ModeIndicatorArray_t Gns_t::modeIndicatorArray() const
	{ return ModeIndicatorArray_t::fromModeIndicators(((const struct gns_t *)(*this))->mi); }

int Gns_t::nmOfSatellites() const
	{ return ((const struct gns_t *)(*this))->totalsats; }

double Gns_t::hdop() const
	{ return ((const struct gns_t *)(*this))->hdop; }

double Gns_t::antennaAltitude() const
	{ return ((const struct gns_t *)(*this))->antaltitude; }

double Gns_t::geoidalSeparation() const
	{ return ((const struct gns_t *)(*this))->geoidalsep; }

int Gns_t::ageOfDiffData() const
	{ return ((const struct gns_t *)(*this))->diffage; }

int Gns_t::diffReferenceStationId() const
	{ return ((const struct gns_t *)(*this))->id; }

void Gns_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct gns_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Gns_t::setUtc(const Utc_t &utc)
{
	((struct gns_t *)(*this))->utc.hour = utc.hours();
	((struct gns_t *)(*this))->utc.min = utc.minutes();
	((struct gns_t *)(*this))->utc.sec = utc.seconds();
	((struct gns_t *)(*this))->vfields |= GNS_VALID_UTC;
}

void Gns_t::setPositionFix(const PositionFix_t &fix)
{
	((struct gns_t *)(*this))->fix = fix.toPosition();
	((struct gns_t *)(*this))->vfields |= GNS_VALID_POSITION_FIX;
}

void Gns_t::setModeIndicatorArray(const ModeIndicatorArray_t &modeArray)
	{ modeArray.toModeIndicators(((struct gns_t *)(*this))->mi); }

void Gns_t::setNmOfSatellites(int value)
{
	((struct gns_t *)(*this))->totalsats = value;
	((struct gns_t *)(*this))->vfields |= GNS_VALID_TOTALNMOFSATELLITES;
}

void Gns_t::setHdop(double value)
{
	((struct gns_t *)(*this))->hdop = value;
	((struct gns_t *)(*this))->vfields |= GNS_VALID_HDOP;
}

void Gns_t::setAntennaAltitude(double value)
{
	((struct gns_t *)(*this))->antaltitude = value;
	((struct gns_t *)(*this))->vfields |= GNS_VALID_ANTENNAALTITUDE;
}

void Gns_t::setGeoidalSeparation(double value)
{
	((struct gns_t *)(*this))->geoidalsep = value;
	((struct gns_t *)(*this))->vfields |= GNS_VALID_GEOIDALSEP;
}

void Gns_t::setAgeOfDiffData(int value)
{
	((struct gns_t *)(*this))->diffage = value;
	((struct gns_t *)(*this))->vfields |= GNS_VALID_AGEOFDIFFDATA;
}

void Gns_t::setDiffReferenceStationId(int value)
{
	((struct gns_t *)(*this))->id = value;
	((struct gns_t *)(*this))->vfields |= GNS_VALID_DIFFREFSTATIONID;
}

void Gns_t::clearMessage()
	{ ((struct gns_t *)(*this))->vfields = 0; }

Gns_t::operator const struct gns_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct gns_t *)p;
}

Gns_t::operator struct gns_t *()
{
	void *p = (void *)(*this);
	return (struct gns_t *)p;
}

}
