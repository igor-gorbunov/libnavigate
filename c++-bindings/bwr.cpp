/*
* bwr.cpp - implementation of Bwr_t class
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

#include "include/libnavigate/c++/bwr.hpp"
#include <string.h>

namespace libnavigate
{

	Bwr_t::Bwr_t(const TalkerId_t &tid) : Message_t(MessageType_t::BWR)
	{
		navi_init_bwr((struct bwr_t *)(*this), tid.toTalkerIdCode());
	}

	Bwr_t::Bwr_t(const Message_t &msg) : Message_t(msg) { }

	Bwr_t::~Bwr_t() { }

	TalkerId_t Bwr_t::talkerId() const
	{
		return TalkerId_t::fromTalkerIdCode(((const struct bwr_t *)(*this))->tid);
	}

	void Bwr_t::setTalkerId(const TalkerId_t &tid)
	{
		((struct bwr_t *)(*this))->tid = tid.toTalkerIdCode();
	}

	void Bwr_t::clearMessage()
	{
		navi_init_bwr((struct bwr_t *)(*this), TalkerId_t::Unknown);
	}

	Bwr_t::operator const struct bwr_t *() const
	{
		const void *p = (const void *)(*this);
		return (const struct bwr_t *)p;
	}

	Bwr_t::operator struct bwr_t *()
	{
		void *p = (void *)(*this);
		return (struct bwr_t *)p;
	}

	Utc_t Bwr_t::utc() const
	{
		return Utc_t::fromUtcStruct(((const struct bwr_t *)(*this))->utc);
	}

	PositionFix_t Bwr_t::waypointFix() const
	{
		return PositionFix_t::fromPosition(&((const struct bwr_t *)(*this))->waypointfix);
	}

	Offset_t Bwr_t::bearingTrue() const
	{
		return Offset_t::fromOffset(&((const struct bwr_t *)(*this))->bearingT);
	}

	Offset_t Bwr_t::bearingMagnetic() const
	{
		return Offset_t::fromOffset(&((const struct bwr_t *)(*this))->bearingM);
	}

	double Bwr_t::distance() const
	{
		return ((const struct bwr_t *)(*this))->distance;
	}

	std::string Bwr_t::waypointId() const
	{
		return std::string(((const struct bwr_t *)(*this))->waypoint_id);
	}

	ModeIndicator_t Bwr_t::modeIndicator() const
	{
		return ModeIndicator_t::fromModeIndCode(((const struct bwr_t *)(*this))->mi);
	}

	void Bwr_t::setUtc(const Utc_t &value)
	{
		((struct bwr_t *)(*this))->utc = value.toUtcStruct();
	}

	void Bwr_t::setWaypointFix(const PositionFix_t &value)
	{
		((struct bwr_t *)(*this))->waypointfix = value.toPosition();
	}

	void Bwr_t::setBearingTrue(const Offset_t &value)
	{
		((struct bwr_t *)(*this))->bearingT = value.toOffset();
	}

	void Bwr_t::setBearingMagnetic(const Offset_t &value)
	{
		((struct bwr_t *)(*this))->bearingM = value.toOffset();
	}

	void Bwr_t::setDistance(double value)
	{
		((struct bwr_t *)(*this))->distance = value;
	}

	void Bwr_t::setWaypointId(const std::string &value)
	{
		(void)strncpy(((struct bwr_t *)(*this))->waypoint_id, value.c_str(),
			sizeof(((struct bwr_t *)(*this))->waypoint_id));
	}

	void Bwr_t::setModeIndicator(const ModeIndicator_t &value)
	{
		((struct bwr_t *)(*this))->mi = value.toModeIndCode();
	}

}
