/*
* bec.cpp - implementation of Bec_t class
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

#include "include/libnavigate/c++/bec.hpp"
#include <string.h>

namespace libnavigate
{

	Bec_t::Bec_t(const TalkerId_t &tid) : Message_t(MessageType_t::BEC)
	{
		navi_init_bec((struct bec_t *)(*this), tid.toTalkerIdCode());
	}

	Bec_t::Bec_t(const Message_t &msg) : Message_t(msg) { }

	Bec_t::~Bec_t() { }

	TalkerId_t Bec_t::talkerId() const
	{
		return TalkerId_t::fromTalkerIdCode(((const struct bec_t *)(*this))->tid);
	}

	void Bec_t::setTalkerId(const TalkerId_t &tid)
	{
		((struct bec_t *)(*this))->tid = tid.toTalkerIdCode();
	}

	void Bec_t::clearMessage()
	{
		navi_init_bec((struct bec_t *)(*this), TalkerId_t::Unknown);
	}

	Bec_t::operator const struct bec_t *() const
	{
		const void *p = (const void *)(*this);
		return (const struct bec_t *)p;
	}

	Bec_t::operator struct bec_t *()
	{
		void *p = (void *)(*this);
		return (struct bec_t *)p;
	}

	Utc_t Bec_t::utc() const
	{
		return Utc_t::fromUtcStruct(((const struct bec_t *)(*this))->utc);
	}

	PositionFix_t Bec_t::waypointFix() const
	{
		return PositionFix_t::fromPosition(&((const struct bec_t *)(*this))->waypointfix);
	}

	Offset_t Bec_t::bearingTrue() const
	{
		return Offset_t::fromOffset(&((const struct bec_t *)(*this))->bearingT);
	}

	Offset_t Bec_t::bearingMagnetic() const
	{
		return Offset_t::fromOffset(&((const struct bec_t *)(*this))->bearingM);
	}

	double Bec_t::distance() const
	{
		return ((const struct bec_t *)(*this))->distance;
	}

	std::string Bec_t::waypointId() const
	{
		return std::string(((const struct bec_t *)(*this))->waypoint_id);
	}

	void Bec_t::setUtc(const Utc_t &value)
	{
		((struct bec_t *)(*this))->utc = value.toUtcStruct();
	}

	void Bec_t::setWaypointFix(const PositionFix_t &value)
	{
		((struct bec_t *)(*this))->waypointfix = value.toPosition();
	}

	void Bec_t::setBearingTrue(const Offset_t &value)
	{
		((struct bec_t *)(*this))->bearingT = value.toOffset();
	}

	void Bec_t::setBearingMagnetic(const Offset_t &value)
	{
		((struct bec_t *)(*this))->bearingM = value.toOffset();
	}

	void Bec_t::setDistance(double value)
	{
		((struct bec_t *)(*this))->distance = value;
	}

	void Bec_t::setWaypointId(const std::string &value)
	{
		(void)strncpy(((struct bec_t *)(*this))->waypoint_id, value.c_str(),
			sizeof(((struct bec_t *)(*this))->waypoint_id));
	}

}
