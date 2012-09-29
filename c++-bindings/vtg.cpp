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

#include <libnavigate/c++/vtg.hpp>

namespace libnavigate
{

Vtg_t::Vtg_t(const TalkerId_t &tid) : Message_t(MessageType_t::VTG)
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.vfields = 0;
}

Vtg_t::~Vtg_t() { }

TalkerId_t Vtg_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

void Vtg_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Vtg_t::clearMessage()
	{ m_value.vfields = 0; }

Vtg_t::operator const void *() const
	{ return (const void *)&m_value; }

Vtg_t::operator void *()
	{ return &m_value; }

double Vtg_t::courseTrue() const
	{ return m_value.courseTrue; }

double Vtg_t::courseMagnetic() const
	{ return m_value.courseMagn; }

double Vtg_t::speed() const
	{ return m_value.speed; }

ModeIndicator_t Vtg_t::modeIndicator() const
	{ return ModeIndicator_t::fromModeIndCode(m_value.mi); }

void Vtg_t::setCourseTrue(double value)
{
	m_value.courseTrue = value;
	m_value.vfields |= VTG_VALID_COURSETRUE;
}

void Vtg_t::setCourseMagnetic(double value)
{
	m_value.courseMagn = value;
	m_value.vfields |= VTG_VALID_COURSEMAGN;
}

void Vtg_t::setSpeed(double value)
{
	m_value.speed = value;
	m_value.vfields |= VTG_VALID_SPEED;
}

void Vtg_t::setModeIndicator(const ModeIndicator_t &mi)
{
	m_value.mi = mi.toModeIndCode();
}

}
