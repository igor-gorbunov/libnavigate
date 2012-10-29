/*
* bod.cpp - implementation of Bod_t class
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

#include "include/libnavigate/c++/bod.hpp"
#include <string.h>

namespace libnavigate
{

	Bod_t::Bod_t(const TalkerId_t &tid) : Message_t(MessageType_t::APB)
	{
		navi_init_bod((struct bod_t *)(*this), tid.toTalkerIdCode());
	}

	Bod_t::Bod_t(const Message_t &msg) : Message_t(msg) { }

	Bod_t::~Bod_t() { }

	TalkerId_t Bod_t::talkerId() const
	{
		return TalkerId_t::fromTalkerIdCode(((const struct bod_t *)(*this))->tid);
	}

	void Bod_t::setTalkerId(const TalkerId_t &tid)
	{
		((struct bod_t *)(*this))->tid = tid.toTalkerIdCode();
	}

	void Bod_t::clearMessage()
	{
		navi_init_bod((struct bod_t *)(*this), TalkerId_t::Unknown);
	}

	Bod_t::operator const struct bod_t *() const
	{
		const void *p = (const void *)(*this);
		return (const struct bod_t *)p;
	}

	Bod_t::operator struct bod_t *()
	{
		void *p = (void *)(*this);
		return (struct bod_t *)p;
	}

	Offset_t Bod_t::bearingTrue() const
	{
		return Offset_t::fromOffset(&((const struct bod_t *)(*this))->bearingT);
	}

	Offset_t Bod_t::bearingMagnetic() const
	{
		return Offset_t::fromOffset(&((const struct bod_t *)(*this))->bearingM);
	}

	std::string Bod_t::destWaypointId() const
	{
		return std::string(((const struct bod_t *)(*this))->dest_waypoint);
	}

	std::string Bod_t::origWaypointId() const
	{
		return std::string(((const struct bod_t *)(*this))->orig_waypoint);
	}

	void Bod_t::setBearingTrue(const Offset_t &value)
	{
		((struct bod_t *)(*this))->bearingT = value.toOffset();
	}

	void Bod_t::setBearingMagnetic(const Offset_t &value)
	{
		((struct bod_t *)(*this))->bearingM = value.toOffset();
	}

	void Bod_t::setDestWaypointId(const std::string &value)
	{
		(void)strncpy(((struct bod_t *)(*this))->dest_waypoint, value.c_str(),
			sizeof(((struct bod_t *)(*this))->dest_waypoint));
	}

	void Bod_t::setOrigWaypointId(const std::string &value)
	{
		(void)strncpy(((struct bod_t *)(*this))->orig_waypoint, value.c_str(),
			sizeof(((struct bod_t *)(*this))->orig_waypoint));
	}

}
