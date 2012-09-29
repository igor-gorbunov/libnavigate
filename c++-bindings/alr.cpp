/*
 * alr.cpp - implementation of Alr_t class
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

#include <libnavigate/c++/alr.hpp>

namespace libnavigate
{

Alr_t::Alr_t(const TalkerId_t &tid) : Message_t(MessageType_t::ALR)
{
	navi_init_alr(&m_value, tid.toTalkerIdCode());
}

Alr_t::~Alr_t() { }

TalkerId_t Alr_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

void Alr_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Alr_t::clearMessage()
{
	navi_init_alr(&m_value, TalkerId_t::Unknown);
}

Alr_t::operator const void *() const
	{ return (const void *)&m_value; }

Alr_t::operator void *()
	{ return &m_value; }

Utc_t Alr_t::utc() const
	{ return Utc_t::fromUtcStruct(m_value.utc); }

int Alr_t::alarmId() const
	{ return m_value.alarmid; }

Status_t Alr_t::condition() const
	{ return Status_t::fromStatusCode(m_value.condition); }

Status_t Alr_t::acknowledgeState() const
	{ return Status_t::fromStatusCode(m_value.ackstate); }

std::string Alr_t::description() const
	{ return std::string(m_value.description); }

void Alr_t::setUtc(const Utc_t &value)
{
	m_value.utc = value.toUtcStruct();
}

void Alr_t::setAlarmId(int value)
	{ m_value.alarmid = value; }

void Alr_t::setCondition(const Status_t &value)
	{ m_value.condition = value.toStatusCode(); }

void Alr_t::setAcknowledgeState(const Status_t &value)
	{ m_value.ackstate = value.toStatusCode(); }

void Alr_t::setDescription(const std::string &value)
	{ strncpy(m_value.description, value.c_str(), sizeof(m_value.description)); }

}
