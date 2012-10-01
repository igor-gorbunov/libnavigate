/*
 * txt.cpp - implementation of Txt_t class
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

#include <libnavigate/c++/txt.hpp>
#include <string.h>

namespace libnavigate
{

Txt_t::Txt_t(const TalkerId_t &tid) : Message_t(MessageType_t::TXT)
	{ navi_init_txt((struct txt_t *)(*this), tid.toTalkerIdCode()); }

Txt_t::Txt_t(const Message_t &msg) : Message_t(msg) { }

Txt_t::~Txt_t() { }

TalkerId_t Txt_t::talkerId() const
{
	return TalkerId_t::fromTalkerIdCode(((const struct txt_t *)(*this))->tid);
}

void Txt_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct txt_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Txt_t::clearMessage()
{
	navi_init_txt((struct txt_t *)(*this), TalkerId_t::Unknown);
}

Txt_t::operator const struct txt_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct txt_t *)p;
}

Txt_t::operator struct txt_t *()
{
	void *p = (void *)(*this);
	return (struct txt_t *)p;
}

std::string Txt_t::textMessage() const
	{ return std::string(((const struct txt_t *)(*this))->textmsg); }

void Txt_t::setTextMessage(const std::string &value)
{
	strncpy(((struct txt_t *)(*this))->textmsg, value.c_str(),
		sizeof(((struct txt_t *)(*this))->textmsg));
}

int Txt_t::textId() const
{
	return ((const struct txt_t *)(*this))->textid;
}

void Txt_t::setTextId(int value)
{
	((struct txt_t *)(*this))->textid = value;
}

}
