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

#include "include/libnavigate/c++/alr.hpp"
#include <string.h>

namespace libnavigate
{

Alr_t::Alr_t(const TalkerId_t &tid) : Message_t(MessageType_t::ALR)
{
	navi_init_alr((struct alr_t *)(*this), tid.toTalkerIdCode());
}

Alr_t::Alr_t(const Message_t &msg) : Message_t(msg) { }

Alr_t::~Alr_t() { }

TalkerId_t Alr_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct alr_t *)(*this))->tid); }

void Alr_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct alr_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Alr_t::clearMessage()
{
	navi_init_alr((struct alr_t *)(*this), TalkerId_t::Unknown);
}

Alr_t::operator const struct alr_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct alr_t *)p;
}

Alr_t::operator struct alr_t *()
{
	void *p = (void *)(*this);
	return (struct alr_t *)p;
}

Utc_t Alr_t::utc() const
	{ return Utc_t::fromUtcStruct(((const struct alr_t *)(*this))->utc); }

int Alr_t::alarmId() const
	{ return ((const struct alr_t *)(*this))->alarmid; }

Status_t Alr_t::condition() const
	{ return Status_t::fromStatusCode(((const struct alr_t *)(*this))->condition); }

Status_t Alr_t::acknowledgeState() const
	{ return Status_t::fromStatusCode(((const struct alr_t *)(*this))->ackstate); }

std::string Alr_t::description() const
	{ return std::string(((const struct alr_t *)(*this))->description); }

void Alr_t::setUtc(const Utc_t &value)
{
	((struct alr_t *)(*this))->utc = value.toUtcStruct();
}

void Alr_t::setAlarmId(int value)
	{ ((struct alr_t *)(*this))->alarmid = value; }

void Alr_t::setCondition(const Status_t &value)
	{ ((struct alr_t *)(*this))->condition = value.toStatusCode(); }

void Alr_t::setAcknowledgeState(const Status_t &value)
	{ ((struct alr_t *)(*this))->ackstate = value.toStatusCode(); }

void Alr_t::setDescription(const std::string &value)
{
	strncpy(((struct alr_t *)(*this))->description, value.c_str(),
		sizeof(((const struct alr_t *)(*this))->description));
}

}
