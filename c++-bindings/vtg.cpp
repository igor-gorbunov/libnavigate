/*
* vtg.cpp - implementation of Vtg_t class
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

#include "include/libnavigate/c++/vtg.hpp"

namespace libnavigate
{

Vtg_t::Vtg_t(const TalkerId_t &tid) : Message_t(MessageType_t::VTG)
{ navi_init_vtg((struct vtg_t *)(*this), tid.toTalkerIdCode()); }

Vtg_t::Vtg_t(const Message_t &msg) : Message_t(msg) { }

Vtg_t::~Vtg_t() { }

TalkerId_t Vtg_t::talkerId() const
{ return TalkerId_t::fromTalkerIdCode(((const struct vtg_t *)(*this))->tid); }

void Vtg_t::setTalkerId(const TalkerId_t &tid)
{ ((struct vtg_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Vtg_t::clearMessage()
{ navi_init_vtg((struct vtg_t *)(*this), navi_talkerid_Unknown); }

double Vtg_t::courseTrue() const
{ return ((const struct vtg_t *)(*this))->courseT; }

double Vtg_t::courseMagnetic() const
{ return ((const struct vtg_t *)(*this))->courseM; }

double Vtg_t::speedKnots() const
{ return ((const struct vtg_t *)(*this))->speedN; }

double Vtg_t::speedKmph() const
{ return ((const struct vtg_t *)(*this))->speedK; }

ModeIndicator_t Vtg_t::modeIndicator() const
{ return ModeIndicator_t::fromModeIndCode(((const struct vtg_t *)(*this))->mi); }

void Vtg_t::setCourseTrue(double value)
{ ((struct vtg_t *)(*this))->courseT = value; }

void Vtg_t::setCourseMagnetic(double value)
{ ((struct vtg_t *)(*this))->courseM = value; }

void Vtg_t::setSpeedKnots(double value)
{ ((struct vtg_t *)(*this))->speedN = value; }

void Vtg_t::setSpeedKmph(double value)
{ ((struct vtg_t *)(*this))->speedK = value; }

void Vtg_t::setModeIndicator(const ModeIndicator_t &mi)
{ ((struct vtg_t *)(*this))->mi = mi.toModeIndCode(); }

bool Vtg_t::isCourseTrueValid() const
{ return navi_check_validity_number(((const struct vtg_t *)(*this))->courseT) == navi_Ok; }

bool Vtg_t::isCourseMagneticValid() const
{ return navi_check_validity_number(((const struct vtg_t *)(*this))->courseM) == navi_Ok; }

bool Vtg_t::isSpeedKnotsValid() const
{ return navi_check_validity_number(((const struct vtg_t *)(*this))->speedN) == navi_Ok; }

bool Vtg_t::isSpeedKmphValid() const
{ return navi_check_validity_number(((const struct vtg_t *)(*this))->speedK) == navi_Ok; }

Vtg_t::operator const struct vtg_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct vtg_t *)p;
}

Vtg_t::operator struct vtg_t *()
{
	void *p = (void *)(*this);
	return (struct vtg_t *)p;
}

}
