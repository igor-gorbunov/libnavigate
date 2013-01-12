/*
* apb.cpp - implementation of Apb_t class
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

#include "include/libnavigate/c++/apb.hpp"
#include <string.h>

namespace libnavigate
{

	Apb_t::Apb_t(const TalkerId_t &tid) : Message_t(MessageType_t::APB)
	{
		navi_init_apb((struct apb_t *)(*this), tid.toTalkerIdCode());
	}

	Apb_t::Apb_t(const Message_t &msg) : Message_t(msg) { }

	Apb_t::~Apb_t() { }

	TalkerId_t Apb_t::talkerId() const
	{
		return TalkerId_t::fromTalkerIdCode(((const struct apb_t *)(*this))->tid);
	}

	void Apb_t::setTalkerId(const TalkerId_t &tid)
	{
		((struct apb_t *)(*this))->tid = tid.toTalkerIdCode();
	}

	void Apb_t::clearMessage()
	{
		navi_init_apb((struct apb_t *)(*this), TalkerId_t::Unknown);
	}

	Apb_t::operator const struct apb_t *() const
	{
		const void *p = (const void *)(*this);
		return (const struct apb_t *)p;
	}

	Apb_t::operator struct apb_t *()
	{
		void *p = (void *)(*this);
		return (struct apb_t *)p;
	}

	Status_t Apb_t::status0() const
	{
		return Status_t::fromStatusCode(((const struct apb_t *)(*this))->status_0);
	}

	Status_t Apb_t::status1() const
	{
		return Status_t::fromStatusCode(((const struct apb_t *)(*this))->status_1);
	}

	Offset_t Apb_t::xteMagnitude() const
	{
		return Offset_t::fromOffset(&((const struct apb_t *)(*this))->xte_magnitude);
	}

	Status_t Apb_t::arrivalCircle() const
	{
		return Status_t::fromStatusCode(((const struct apb_t *)(*this))->arrival_circle);
	}

	Status_t Apb_t::perpendicular() const
	{
		return Status_t::fromStatusCode(((const struct apb_t *)(*this))->perpendicular);
	}

	Offset_t Apb_t::bearingOrigin() const
	{
		return Offset_t::fromOffset(&((const struct apb_t *)(*this))->bearing_origin);
	}

	std::string Apb_t::waypointId() const
	{
		return std::string(((const struct apb_t *)(*this))->waypoint_id);
	}

	Offset_t Apb_t::bearingPresent() const
	{
		return Offset_t::fromOffset(&((const struct apb_t *)(*this))->bearing_present);
	}

	Offset_t Apb_t::heading() const
	{
		return Offset_t::fromOffset(&((const struct apb_t *)(*this))->heading);
	}

	ModeIndicator_t Apb_t::modeIndicator() const
	{
		return ModeIndicator_t::fromModeIndCode(((const struct apb_t *)(*this))->mode_indicator);
	}

	void Apb_t::setStatus0(const Status_t &value)
	{
		((struct apb_t *)(*this))->status_0 = value.toStatusCode();
	}

	void Apb_t::setStatus1(const Status_t &value)
	{
		((struct apb_t *)(*this))->status_1 = value.toStatusCode();
	}

	void Apb_t::setXteMagnitude(const Offset_t &value)
	{
		((struct apb_t *)(*this))->xte_magnitude = value.toOffset();
	}

	void Apb_t::setArrivalCircle(const Status_t &value)
	{
		((struct apb_t *)(*this))->arrival_circle = value.toStatusCode();
	}

	void Apb_t::setPerpendicular(const Status_t &value)
	{
		((struct apb_t *)(*this))->perpendicular = value.toStatusCode();
	}

	void Apb_t::setBearingOrigin(const Offset_t &value)
	{
		((struct apb_t *)(*this))->bearing_origin = value.toOffset();
	}

	void Apb_t::setWaypointId(const std::string &value)
	{
		(void)strncpy(((struct apb_t *)(*this))->waypoint_id, value.c_str(),
			sizeof(((struct apb_t *)(*this))->waypoint_id));
	}

	void Apb_t::setBearingPresent(const Offset_t &value)
	{
		((struct apb_t *)(*this))->bearing_present = value.toOffset();
	}

	void Apb_t::setHeading(const Offset_t &value)
	{
		((struct apb_t *)(*this))->heading = value.toOffset();
	}

	void Apb_t::setModeIndicator(const ModeIndicator_t &value)
	{
		((struct apb_t *)(*this))->mode_indicator = value.toModeIndCode();
	}

}
