/*
 * txt.hpp - C++ bindings for AAM message
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

#ifndef INCLUDE_navi_txtplusplus
#define INCLUDE_navi_txtplusplus

#include "sentence.hpp"
#include <libnavigate/txt.h>
#include <string>

namespace libnavigate
{

NAVI_EXTERN_CLASS(Txt_t) : public Message_t
{
public:
	static const int MaxTextMessageSize = 62;

public:
	Txt_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Txt_t(const Message_t &msg);
	virtual ~Txt_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual int textId() const;
	virtual std::string textMessage() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setTextId(int value);
	virtual void setTextMessage(const std::string &value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct txt_t *() const;
	virtual operator struct txt_t *();
};

}

#endif // INCLUDE_navi_txtplusplus
