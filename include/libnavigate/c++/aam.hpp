/*
 * aam.hpp - C++ bindings for AAM message
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

#ifndef INCLUDE_navi_aamplusplus
#define INCLUDE_navi_aamplusplus

#include <libnavigate/c++/sentence.hpp>
#include <string>

namespace libnavigate
{

#include <libnavigate/aam.h>

NAVI_EXTERN_CLASS(class, Aam_t) : public Message_t
{
public:
	static const int MaxWaypointIdSize = 60;

public:
	Aam_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Aam_t();

public:
	virtual TalkerId_t talkerId() const;

	virtual Status_t circleStatus() const;
	virtual Status_t perpendicularStatus() const;
	virtual double waypointRadius() const;
	virtual std::string waypointId() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setCircleStatus(const Status_t &value);
	virtual void setPerpendicularStatus(const Status_t &value);
	virtual void setWaypointRadius(double value);
	virtual void setWaypointId(const std::string &value);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct aam_t m_value;
};

}

#endif // INCLUDE_navi_aamplusplus
