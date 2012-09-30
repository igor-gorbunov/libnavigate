/*
 * zda.cpp - implementation of Zda_t class
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

#include <libnavigate/c++/zda.hpp>

namespace libnavigate
{

Zda_t::Zda_t(const TalkerId_t &tid) : Message_t(MessageType_t::ZDA)
{
	((struct zda_t *)(*this))->tid = tid.toTalkerIdCode();
	((struct zda_t *)(*this))->vfields = 0;
}

Zda_t::Zda_t(const Message_t &msg) : Message_t(msg) { }

Zda_t::~Zda_t() { }

TalkerId_t Zda_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct zda_t *)(*this))->tid); }

Utc_t Zda_t::utc() const
{
	return Utc_t(((const struct zda_t *)(*this))->utc.hour,
		((const struct zda_t *)(*this))->utc.min,
		((const struct zda_t *)(*this))->utc.sec);
}

Date_t Zda_t::date() const
{
	return Date_t(((const struct zda_t *)(*this))->date.year,
		((const struct zda_t *)(*this))->date.month,
		((const struct zda_t *)(*this))->date.day);
}

int Zda_t::localZoneOffset() const
	{ return ((const struct zda_t *)(*this))->lzoffset; }

void Zda_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct zda_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Zda_t::setUtc(const Utc_t &utc)
{
	((struct zda_t *)(*this))->utc.hour = utc.hours();
	((struct zda_t *)(*this))->utc.min = utc.minutes();
	((struct zda_t *)(*this))->utc.sec = utc.seconds();
	((struct zda_t *)(*this))->vfields |= ZDA_VALID_UTC;
}

void Zda_t::setDate(const Date_t &date)
{
	((struct zda_t *)(*this))->date = date.toDate();
	((struct zda_t *)(*this))->vfields |= ZDA_VALID_DAY | ZDA_VALID_MONTH | ZDA_VALID_YEAR;
}

void Zda_t::setLocalZoneOffset(int value)
{
	((struct zda_t *)(*this))->lzoffset = value;
	((struct zda_t *)(*this))->vfields |= ZDA_VALID_LOCALZONE;
}

void Zda_t::clearMessage()
	{ ((struct zda_t *)(*this))->vfields = 0; }

Zda_t::operator const struct zda_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct zda_t *)p;
}

Zda_t::operator struct zda_t *()
{
	void *p = (void *)(*this);
	return (struct zda_t *)p;
}

}
