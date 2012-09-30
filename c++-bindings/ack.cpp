/*
 * ack.cpp - implementation of Ack_t class
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

#include <libnavigate/c++/ack.hpp>

namespace libnavigate
{

Ack_t::Ack_t(const TalkerId_t &tid) : Message_t(MessageType_t::ACK)
{
	navi_init_ack((struct ack_t *)(*this), tid.toTalkerIdCode());
}

Ack_t::Ack_t(const Message_t &msg) : Message_t(msg) { }

Ack_t::~Ack_t() { }

TalkerId_t Ack_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct ack_t *)(*this))->tid); }

void Ack_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct ack_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Ack_t::clearMessage()
{
	navi_init_ack((struct ack_t *)(*this), TalkerId_t::Unknown);
}

Ack_t::operator const struct ack_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct ack_t *)p;
}

Ack_t::operator struct ack_t *()
{
	void *p = (void *)(*this);
	return (struct ack_t *)p;
}

int Ack_t::alarmId() const
{
	return ((const struct ack_t *)(*this))->alarmid;
}

void Ack_t::setAlarmId(int value)
{
	((struct ack_t *)(*this))->alarmid = value;
}

}
