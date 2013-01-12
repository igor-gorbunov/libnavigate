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

#include "include/libnavigate/c++/gns.hpp"

namespace libnavigate
{

Gns_t::Gns_t(const TalkerId_t &tid) : Message_t(MessageType_t::GNS)
{ navi_init_gns((struct gns_t *)(*this), tid.toTalkerIdCode()); }

Gns_t::Gns_t(const Message_t &msg) : Message_t(msg) { }

Gns_t::~Gns_t() { }

TalkerId_t Gns_t::talkerId() const
{ return TalkerId_t::fromTalkerIdCode(((const struct gns_t *)(*this))->tid); }

Utc_t Gns_t::utc() const
{ return Utc_t::fromUtcStruct(((const struct gns_t *)(*this))->utc); }

PositionFix_t Gns_t::positionFix() const
{ return PositionFix_t::fromPosition(&((const struct gns_t *)(*this))->fix); }

ModeIndicatorArray_t Gns_t::modeIndicatorArray() const
{ return ModeIndicatorArray_t::fromModeIndicators(((const struct gns_t *)(*this))->mi); }

int Gns_t::nmOfSatellites() const
{ return ((const struct gns_t *)(*this))->nmsatellites; }

double Gns_t::hdop() const
{ return ((const struct gns_t *)(*this))->hdop; }

double Gns_t::antennaAltitude() const
{ return ((const struct gns_t *)(*this))->antaltitude; }

double Gns_t::geoidalSeparation() const
{ return ((const struct gns_t *)(*this))->geoidalsep; }

int Gns_t::ageOfDiffData() const
{ return ((const struct gns_t *)(*this))->diffdata_age; }

int Gns_t::diffReferenceStationId() const
{ return ((const struct gns_t *)(*this))->station_id; }

void Gns_t::setTalkerId(const TalkerId_t &tid)
{ ((struct gns_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Gns_t::setUtc(const Utc_t &utc)
{ ((struct gns_t *)(*this))->utc = utc.toUtcStruct(); }

void Gns_t::setPositionFix(const PositionFix_t &fix)
{ ((struct gns_t *)(*this))->fix = fix.toPosition(); }

void Gns_t::setModeIndicatorArray(const ModeIndicatorArray_t &modeArray)
{ modeArray.toModeIndicators(((struct gns_t *)(*this))->mi); }

void Gns_t::setNmOfSatellites(int value)
{ ((struct gns_t *)(*this))->nmsatellites = value; }

void Gns_t::setHdop(double value)
{ ((struct gns_t *)(*this))->hdop = value; }

void Gns_t::setAntennaAltitude(double value)
{ ((struct gns_t *)(*this))->antaltitude = value; }

void Gns_t::setGeoidalSeparation(double value)
{ ((struct gns_t *)(*this))->geoidalsep = value; }

void Gns_t::setAgeOfDiffData(int value)
{ ((struct gns_t *)(*this))->diffdata_age = value; }

void Gns_t::setDiffReferenceStationId(int value)
{ ((struct gns_t *)(*this))->station_id = value; }

bool Gns_t::isUtcValid() const
{ return navi_check_validity_utc(&((const struct gns_t *)(*this))->utc) == navi_Ok; }

bool Gns_t::isPositionValid() const
{ return ((const struct gns_t *)(*this))->fix.latitude.sign != navi_offset_NULL; }

bool Gns_t::isNmSatellitesValid() const
{ return ((const struct gns_t *)(*this))->nmsatellites != -1; }

bool Gns_t::isHdopValid() const
{ return navi_check_validity_number(((const struct gns_t *)(*this))->hdop) == navi_Ok; }

bool Gns_t::isAntennaAltitudeValid() const
{ return navi_check_validity_number(((const struct gns_t *)(*this))->antaltitude) == navi_Ok; }

bool Gns_t::isGeoidalSeparationValid() const
{ return navi_check_validity_number(((const struct gns_t *)(*this))->geoidalsep) == navi_Ok; }

bool Gns_t::isDifferentialAgeValid() const
{ return ((const struct gns_t *)(*this))->diffdata_age != -1; }

bool Gns_t::isStationIdValid() const
{ return ((const struct gns_t *)(*this))->station_id != -1; }

void Gns_t::clearMessage()
{ navi_init_gns((struct gns_t *)(*this), navi_talkerid_Unknown); }

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
