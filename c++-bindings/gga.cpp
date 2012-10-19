/*
 * gga.cpp - implementation of Gga_t class
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

#include "include/libnavigate/c++/gga.hpp"

namespace libnavigate
{

Gga_t::Gga_t(const TalkerId_t &tid) : Message_t(MessageType_t::GGA)
	{ navi_init_gga((struct gga_t *)(*this), tid.toTalkerIdCode()); }

Gga_t::Gga_t(const Message_t &msg) : Message_t(msg) { }

Gga_t::~Gga_t() { }

TalkerId_t Gga_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct gga_t *)(*this))->tid); }

Utc_t Gga_t::utc() const
	{ return Utc_t::fromUtcStruct(((const struct gga_t *)(*this))->utc); }

PositionFix_t Gga_t::positionFix() const
	{ return PositionFix_t::fromPosition(&((const struct gga_t *)(*this))->fix); }

GpsQualityIndicator_t Gga_t::qualityIndicator() const
	{ return GpsQualityIndicator_t::fromQualityCode(((const struct gga_t *)(*this))->gpsindicator); }

int Gga_t::nmOfSatellites() const
	{ return ((const struct gga_t *)(*this))->nmsatellites; }

double Gga_t::hdop() const
	{ return ((const struct gga_t *)(*this))->hdop; }

double Gga_t::antennaAltitude() const
	{ return ((const struct gga_t *)(*this))->antaltitude; }

double Gga_t::geoidalSeparation() const
	{ return ((const struct gga_t *)(*this))->geoidalsep; }

int Gga_t::ageOfDiffData() const
	{ return ((const struct gga_t *)(*this))->diffage; }

int Gga_t::diffReferenceStationId() const
	{ return ((const struct gga_t *)(*this))->id; }

void Gga_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct gga_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Gga_t::setUtc(const Utc_t &utc)
	{ ((struct gga_t *)(*this))->utc = utc.toUtcStruct(); }

void Gga_t::setPositionFix(const PositionFix_t &fix)
	{ ((struct gga_t *)(*this))->fix = fix.toPosition(); }

void Gga_t::setQualityIndicator(const GpsQualityIndicator_t &qi)
	{ ((struct gga_t *)(*this))->gpsindicator = qi.toQualityCode(); }

void Gga_t::setNmOfSatellites(int value)
{
	((struct gga_t *)(*this))->nmsatellites = value;
	((struct gga_t *)(*this))->vfields |= GGA_VALID_NMSATELLITES;
}

void Gga_t::setHdop(double value)
{
	((struct gga_t *)(*this))->hdop = value;
	((struct gga_t *)(*this))->vfields |= GGA_VALID_HDOP;
}

void Gga_t::setAntennaAltitude(double value)
{
	((struct gga_t *)(*this))->antaltitude = value;
	((struct gga_t *)(*this))->vfields |= GGA_VALID_ANTALTITUDE;
}

void Gga_t::setGeoidalSeparation(double value)
{
	((struct gga_t *)(*this))->geoidalsep = value;
	((struct gga_t *)(*this))->vfields |= GGA_VALID_GEOIDALSEP;
}

void Gga_t::setAgeOfDiffData(int value)
{
	((struct gga_t *)(*this))->diffage = value;
	((struct gga_t *)(*this))->vfields |= GGA_VALID_DIFFAGE;
}

void Gga_t::setDiffReferenceStationId(int value)
{
	((struct gga_t *)(*this))->id = value;
	((struct gga_t *)(*this))->vfields |= GGA_VALID_ID;
}

bool Gga_t::isUtcValid() const
	{ return navi_check_validity_utc(&((const struct gga_t *)(*this))->utc) == navi_Ok; }

bool Gga_t::isPositionValid() const
	{ return ((const struct gga_t *)(*this))->fix.latitude.sign != navi_offset_NULL; }

bool Gga_t::isNmSatellitesValid() const
{
	return (((const struct gga_t *)(*this))->vfields & GGA_VALID_NMSATELLITES) != 0 ? true : false;
}

bool Gga_t::isHdopValid() const
{
	return (((const struct gga_t *)(*this))->vfields & GGA_VALID_HDOP) != 0 ? true : false;
}

bool Gga_t::isAntennaAltitudeValid() const
{
	return (((const struct gga_t *)(*this))->vfields & GGA_VALID_ANTALTITUDE) != 0 ? true : false;
}

bool Gga_t::isGeoidalSeparationValid() const
{
	return (((const struct gga_t *)(*this))->vfields & GGA_VALID_GEOIDALSEP) != 0 ? true : false;
}

bool Gga_t::isDifferentialAgeValid() const
{
	return (((const struct gga_t *)(*this))->vfields & GGA_VALID_DIFFAGE) != 0 ? true : false;
}

bool Gga_t::isStationIdValid() const
{
	return (((const struct gga_t *)(*this))->vfields & GGA_VALID_ID) != 0 ? true : false;
}

void Gga_t::clearMessage()
	{ navi_init_gga((struct gga_t *)(*this), navi_talkerid_Unknown); }

Gga_t::operator const struct gga_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct gga_t *)p;
}

Gga_t::operator struct gga_t *()
{
	void *p = (void *)(*this);
	return (struct gga_t *)p;
}

}
