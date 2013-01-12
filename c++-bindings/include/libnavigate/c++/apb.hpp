/*
 * apb.hpp - C++ bindings for APB message
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

#ifndef INCLUDE_navi_apbplusplus
#define INCLUDE_navi_apbplusplus

#include "sentence.hpp"
#include <libnavigate/apb.h>
#include <string>

namespace libnavigate
{

NAVI_EXTERN_CLASS(Apb_t) : public Message_t
{
public:
	Apb_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Apb_t(const Message_t &msg);
	virtual ~Apb_t();

public:
	virtual TalkerId_t talkerId() const;

	virtual Status_t status0() const;
	virtual Status_t status1() const;
	virtual Offset_t xteMagnitude() const;
	virtual Status_t arrivalCircle() const;
	virtual Status_t perpendicular() const;
	virtual Offset_t bearingOrigin() const;
	virtual std::string waypointId() const;
	virtual Offset_t bearingPresent() const;
	virtual Offset_t heading() const;
	virtual ModeIndicator_t modeIndicator() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setStatus0(const Status_t &value);
	virtual void setStatus1(const Status_t &value);
	virtual void setXteMagnitude(const Offset_t &value);
	virtual void setArrivalCircle(const Status_t &value);
	virtual void setPerpendicular(const Status_t &value);
	virtual void setBearingOrigin(const Offset_t &value);
	virtual void setWaypointId(const std::string &value);
	virtual void setBearingPresent(const Offset_t &value);
	virtual void setHeading(const Offset_t &value);
	virtual void setModeIndicator(const ModeIndicator_t &value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct apb_t *() const;
	virtual operator struct apb_t *();
};

}

#endif // INCLUDE_navi_apbplusplus
