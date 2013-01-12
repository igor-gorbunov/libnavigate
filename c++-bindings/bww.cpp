/*
* bww.cpp - implementation of Bww_t class
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

#include "include/libnavigate/c++/bww.hpp"
#include <string.h>

namespace libnavigate
{

	Bww_t::Bww_t(const TalkerId_t &tid) : Message_t(MessageType_t::BWW)
	{
		navi_init_bww((struct bww_t *)(*this), tid.toTalkerIdCode());
	}

	Bww_t::Bww_t(const Message_t &msg) : Message_t(msg) { }

	Bww_t::~Bww_t() { }

	TalkerId_t Bww_t::talkerId() const
	{
		return TalkerId_t::fromTalkerIdCode(((const struct bww_t *)(*this))->tid);
	}

	void Bww_t::setTalkerId(const TalkerId_t &tid)
	{
		((struct bww_t *)(*this))->tid = tid.toTalkerIdCode();
	}

	void Bww_t::clearMessage()
	{
		navi_init_bww((struct bww_t *)(*this), TalkerId_t::Unknown);
	}

	Bww_t::operator const struct bww_t *() const
	{
		const void *p = (const void *)(*this);
		return (const struct bww_t *)p;
	}

	Bww_t::operator struct bww_t *()
	{
		void *p = (void *)(*this);
		return (struct bww_t *)p;
	}

	Offset_t Bww_t::bearingTrue() const
	{
		return Offset_t::fromOffset(&((const struct bww_t *)(*this))->bearingT);
	}

	Offset_t Bww_t::bearingMagnetic() const
	{
		return Offset_t::fromOffset(&((const struct bww_t *)(*this))->bearingM);
	}

	std::string Bww_t::toWaypointId() const
	{
		return std::string(((const struct bww_t *)(*this))->to_waypoint);
	}

	std::string Bww_t::fromWaypointId() const
	{
		return std::string(((const struct bww_t *)(*this))->from_waypoint);
	}

	void Bww_t::setBearingTrue(const Offset_t &value)
	{
		((struct bww_t *)(*this))->bearingT = value.toOffset();
	}

	void Bww_t::setBearingMagnetic(const Offset_t &value)
	{
		((struct bww_t *)(*this))->bearingM = value.toOffset();
	}

	void Bww_t::setToWaypointId(const std::string &value)
	{
		(void)strncpy(((struct bww_t *)(*this))->to_waypoint, value.c_str(),
			sizeof(((struct bww_t *)(*this))->to_waypoint));
	}

	void Bww_t::setFromWaypointId(const std::string &value)
	{
		(void)strncpy(((struct bww_t *)(*this))->from_waypoint, value.c_str(),
			sizeof(((struct bww_t *)(*this))->from_waypoint));
	}

}
