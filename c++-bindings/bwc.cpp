/*
* bwc.cpp - implementation of Bwc_t class
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

#include "include/libnavigate/c++/bwc.hpp"
#include <string.h>

namespace libnavigate
{

	Bwc_t::Bwc_t(const TalkerId_t &tid) : Message_t(MessageType_t::BWC)
	{
		navi_init_bwc((struct bwc_t *)(*this), tid.toTalkerIdCode());
	}

	Bwc_t::Bwc_t(const Message_t &msg) : Message_t(msg) { }

	Bwc_t::~Bwc_t() { }

	TalkerId_t Bwc_t::talkerId() const
	{
		return TalkerId_t::fromTalkerIdCode(((const struct bwc_t *)(*this))->tid);
	}

	void Bwc_t::setTalkerId(const TalkerId_t &tid)
	{
		((struct bwc_t *)(*this))->tid = tid.toTalkerIdCode();
	}

	void Bwc_t::clearMessage()
	{
		navi_init_bwc((struct bwc_t *)(*this), TalkerId_t::Unknown);
	}

	Bwc_t::operator const struct bwc_t *() const
	{
		const void *p = (const void *)(*this);
		return (const struct bwc_t *)p;
	}

	Bwc_t::operator struct bwc_t *()
	{
		void *p = (void *)(*this);
		return (struct bwc_t *)p;
	}

	Utc_t Bwc_t::utc() const
	{
		return Utc_t::fromUtcStruct(((const struct bwc_t *)(*this))->utc);
	}

	PositionFix_t Bwc_t::waypointFix() const
	{
		return PositionFix_t::fromPosition(&((const struct bwc_t *)(*this))->waypointfix);
	}

	Offset_t Bwc_t::bearingTrue() const
	{
		return Offset_t::fromOffset(&((const struct bwc_t *)(*this))->bearingT);
	}

	Offset_t Bwc_t::bearingMagnetic() const
	{
		return Offset_t::fromOffset(&((const struct bwc_t *)(*this))->bearingM);
	}

	double Bwc_t::distance() const
	{
		return ((const struct bwc_t *)(*this))->distance;
	}

	std::string Bwc_t::waypointId() const
	{
		return std::string(((const struct bwc_t *)(*this))->waypoint_id);
	}

	ModeIndicator_t Bwc_t::modeIndicator() const
	{
		return ModeIndicator_t::fromModeIndCode(((const struct bwc_t *)(*this))->mi);
	}

	void Bwc_t::setUtc(const Utc_t &value)
	{
		((struct bwc_t *)(*this))->utc = value.toUtcStruct();
	}

	void Bwc_t::setWaypointFix(const PositionFix_t &value)
	{
		((struct bwc_t *)(*this))->waypointfix = value.toPosition();
	}

	void Bwc_t::setBearingTrue(const Offset_t &value)
	{
		((struct bwc_t *)(*this))->bearingT = value.toOffset();
	}

	void Bwc_t::setBearingMagnetic(const Offset_t &value)
	{
		((struct bwc_t *)(*this))->bearingM = value.toOffset();
	}

	void Bwc_t::setDistance(double value)
	{
		((struct bwc_t *)(*this))->distance = value;
	}

	void Bwc_t::setWaypointId(const std::string &value)
	{
		(void)strncpy(((struct bwc_t *)(*this))->waypoint_id, value.c_str(),
			sizeof(((struct bwc_t *)(*this))->waypoint_id));
	}

	void Bwc_t::setModeIndicator(const ModeIndicator_t &value)
	{
		((struct bwc_t *)(*this))->mi = value.toModeIndCode();
	}

}
