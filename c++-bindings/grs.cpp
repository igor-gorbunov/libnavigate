/*
 * grs.cpp - implementation of Grs_t class
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

#include <libnavigate/c++/grs.hpp>

namespace libnavigate
{

Grs_t::Grs_t(const TalkerId_t &tid) : Message_t(MessageType_t::GRS)
{
	m_value.tid = tid.toTalkerIdCode();

	for (int i = 0; i < MaxSatellites; i++)
	{
		m_value.residuals[i].notnull = 0;
	}
}

Grs_t::~Grs_t() { }

TalkerId_t Grs_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

Utc_t Grs_t::utc() const
	{ return Utc_t(m_value.utc.hour, m_value.utc.min, m_value.utc.sec); }

int Grs_t::mode() const
	{ return m_value.mode; }

double Grs_t::residual(int satIdx) const
	{ return m_value.residuals[satIdx].residual; }

void Grs_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Grs_t::setUtc(const Utc_t &utc)
{
	m_value.utc.hour = utc.hours();
	m_value.utc.min = utc.minutes();
	m_value.utc.sec = utc.seconds();
}

void Grs_t::setMode(int mode)
	{ m_value.mode = mode; }

void Grs_t::setResidual(int satIdx, double value)
{
	m_value.residuals[satIdx].notnull = 1;
	m_value.residuals[satIdx].residual = value;
}

void Grs_t::clearMessage()
{
	for (int i = 0; i < MaxSatellites; i++)
	{
		m_value.residuals[i].notnull = 0;
	}
}

Grs_t::operator const void *() const
	{ return (const void *)&m_value; }

Grs_t::operator void *()
	{ return &m_value; }

}
