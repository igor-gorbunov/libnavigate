/*
 * bww.hpp - C++ bindings for BWW message
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

#ifndef INCLUDE_navi_bwwplusplus
#define INCLUDE_navi_bwwplusplus

#include "sentence.hpp"
#include <libnavigate/bww.h>
#include <string>

namespace libnavigate
{

NAVI_EXTERN_CLASS(Bww_t) : public Message_t
{
public:
	Bww_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Bww_t(const Message_t &msg);
	virtual ~Bww_t();

public:
	virtual TalkerId_t talkerId() const;

	virtual Offset_t bearingTrue() const;
	virtual Offset_t bearingMagnetic() const;
	virtual std::string toWaypointId() const;
	virtual std::string fromWaypointId() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setBearingTrue(const Offset_t &value);
	virtual void setBearingMagnetic(const Offset_t &value);
	virtual void setToWaypointId(const std::string &value);
	virtual void setFromWaypointId(const std::string &value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct bww_t *() const;
	virtual operator struct bww_t *();
};

}

#endif // INCLUDE_navi_bwwplusplus
