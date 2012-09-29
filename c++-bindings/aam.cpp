/*
 * aam.cpp - implementation of Aam_t class
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

#include <libnavigate/c++/aam.hpp>

namespace libnavigate
{

Aam_t::Aam_t(const TalkerId_t &tid) : Message_t(MessageType_t::AAM)
{
	navi_init_aam(&m_value, tid.toTalkerIdCode());
}

Aam_t::~Aam_t() { }

TalkerId_t Aam_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

void Aam_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Aam_t::clearMessage()
{
	navi_init_aam(&m_value, TalkerId_t::Unknown);
}

Aam_t::operator const void *() const
	{ return (const void *)&m_value; }

Aam_t::operator void *()
	{ return &m_value; }

Status_t Aam_t::circleStatus() const
	{ return Status_t::fromStatusCode(m_value.circle); }

Status_t Aam_t::perpendicularStatus() const
	{ return Status_t::fromStatusCode(m_value.perp); }

double Aam_t::waypointRadius() const
	{ return m_value.radius; }

std::string Aam_t::waypointId() const
	{ return std::string(m_value.wpid); }

void Aam_t::setCircleStatus(const Status_t &value)
	{ m_value.circle = value.toStatusCode(); }

void Aam_t::setPerpendicularStatus(const Status_t &value)
	{ m_value.perp = value.toStatusCode(); }

void Aam_t::setWaypointRadius(double value)
	{ m_value.radius = value; }

void Aam_t::setWaypointId(const std::string &value)
	{ strncpy(m_value.wpid, value.c_str(), sizeof(m_value.wpid)); }

}
