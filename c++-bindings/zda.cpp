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

#include "include/libnavigate/c++/zda.hpp"
#include <libnavigate/common.h>

namespace libnavigate
{

Zda_t::Zda_t(const TalkerId_t &tid) : Message_t(MessageType_t::ZDA)
	{ navi_init_zda((struct zda_t *)(*this), tid.toTalkerIdCode()); }

Zda_t::Zda_t(const Message_t &msg) : Message_t(msg) { }

Zda_t::~Zda_t() { }

TalkerId_t Zda_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct zda_t *)(*this))->tid); }

Utc_t Zda_t::utc() const
	{ return Utc_t::fromUtcStruct(((const struct zda_t *)(*this))->utc); }

Date_t Zda_t::date() const
	{ return Date_t::fromDateStruct(((const struct zda_t *)(*this))->date); }

int Zda_t::localZoneOffset() const
	{ return ((const struct zda_t *)(*this))->lzoffset; }

void Zda_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct zda_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Zda_t::setUtc(const Utc_t &utc)
{
	((struct zda_t *)(*this))->utc = utc.toUtcStruct();
	((struct zda_t *)(*this))->vfields |= ZDA_VALID_UTC;
}

void Zda_t::setDate(const Date_t &date)
{
	((struct zda_t *)(*this))->date = date.toDateStruct();
	((struct zda_t *)(*this))->vfields |= ZDA_VALID_DATE;
}

void Zda_t::setLocalZoneOffset(int value)
{
	((struct zda_t *)(*this))->lzoffset = value;
	((struct zda_t *)(*this))->vfields |= ZDA_VALID_LOCALZONE;
}

bool Zda_t::isUtcValid() const
{
	return (((const struct zda_t *)(*this))->vfields & ZDA_VALID_UTC) != 0 ? true : false;
}

bool Zda_t::isDateValid() const
{
	return (((const struct zda_t *)(*this))->vfields & ZDA_VALID_DATE) != 0 ? true : false;
}

bool Zda_t::isLocalZoneOffsetValid() const
{
	return (((const struct zda_t *)(*this))->vfields & ZDA_VALID_LOCALZONE) != 0 ? true : false;
}

void Zda_t::clearMessage()
	{ navi_init_zda((struct zda_t *)(*this), navi_talkerid_Unknown); }

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
