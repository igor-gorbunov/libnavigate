/*
 * rmc.cpp - implementation of Rmc_t class
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

#include <libnavigate/c++/rmc.hpp>

namespace libnavigate
{

Rmc_t::Rmc_t(const TalkerId_t &tid) : Message_t(MessageType_t::RMC)
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.vfields = 0;
}

Rmc_t::~Rmc_t() { }

TalkerId_t Rmc_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

Utc_t Rmc_t::utc() const
	{ return Utc_t(m_value.utc.hour, m_value.utc.min, m_value.utc.sec); }

Status_t Rmc_t::status() const
	{ return Status_t::fromStatusCode(m_value.status); }

PositionFix_t Rmc_t::positionFix() const
	{ return PositionFix_t::fromPosition(&m_value.fix); }

double Rmc_t::speed() const
	{ return m_value.speed; }

double Rmc_t::course() const
	{ return m_value.courseTrue; }

Date_t Rmc_t::date() const
	{ return Date_t(m_value.date.year, m_value.date.month, m_value.date.day); }

Offset_t Rmc_t::magneticVariation() const
	{ return Offset_t::fromOffset(&m_value.magnetic); }

ModeIndicator_t Rmc_t::modeIndicator() const
	{ return ModeIndicator_t::fromModeIndCode(m_value.mi); }

void Rmc_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Rmc_t::setUtc(const Utc_t &utc)
{
	m_value.utc.hour = utc.hours();
	m_value.utc.min = utc.minutes();
	m_value.utc.sec = utc.seconds();
	m_value.vfields |= RMC_VALID_UTC;
}

void Rmc_t::setStatus(const Status_t &status)
	{ m_value.status = status.toStatusCode(); }

void Rmc_t::setPositionFix(const PositionFix_t &fix)
{
	m_value.fix = fix.toPosition();
	m_value.vfields |= RMC_VALID_POSITION_FIX;
}

void Rmc_t::setSpeed(double value)
{
	m_value.speed = value;
	m_value.vfields |= RMC_VALID_SPEED;
}

void Rmc_t::setCourse(double value)
{
	m_value.courseTrue = value;
	m_value.vfields |= RMC_VALID_COURSETRUE;
}

void Rmc_t::setDate(const Date_t &date)
{
	m_value.date = date.toDate();
	m_value.vfields |= RMC_VALID_DATE;
}

void Rmc_t::setMagneticVariation(const Offset_t &offset)
{
	m_value.magnetic = offset.toOffset();
	m_value.vfields |= RMC_VALID_MAGNVARIATION;
}

void Rmc_t::setModeIndicator(const ModeIndicator_t &mi)
	{ m_value.mi = mi.toModeIndCode(); }

void Rmc_t::clearMessage()
	{ m_value.vfields = 0; }

Rmc_t::operator const void *() const
	{ return (const void *)&m_value; }

Rmc_t::operator void *()
	{ return &m_value; }

}

