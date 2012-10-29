/*
 * bod.hpp - C++ bindings for BOD message
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

#ifndef INCLUDE_navi_bodplusplus
#define INCLUDE_navi_bodplusplus

#include "sentence.hpp"
#include <libnavigate/bod.h>
#include <string>

namespace libnavigate
{

NAVI_EXTERN_CLASS(Bod_t) : public Message_t
{
public:
	Bod_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Bod_t(const Message_t &msg);
	virtual ~Bod_t();

public:
	virtual TalkerId_t talkerId() const;

	virtual Offset_t bearingTrue() const;
	virtual Offset_t bearingMagnetic() const;
	virtual std::string destWaypointId() const;
	virtual std::string origWaypointId() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setBearingTrue(const Offset_t &value);
	virtual void setBearingMagnetic(const Offset_t &value);
	virtual void setDestWaypointId(const std::string &value);
	virtual void setOrigWaypointId(const std::string &value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct bod_t *() const;
	virtual operator struct bod_t *();
};

}

#endif // INCLUDE_navi_bodplusplus
