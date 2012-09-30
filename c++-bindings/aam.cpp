/*
 * aam.cpp - implementation of Aam_t class
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

#include <libnavigate/c++/aam.hpp>
#include <string.h>

namespace libnavigate
{

Aam_t::Aam_t(const TalkerId_t &tid) : Message_t(MessageType_t::AAM)
	{ navi_init_aam((struct aam_t *)(*this), tid.toTalkerIdCode()); }

Aam_t::Aam_t(const Message_t &msg) : Message_t(msg) { }

Aam_t::~Aam_t() { }

TalkerId_t Aam_t::talkerId() const
{
	return TalkerId_t::fromTalkerIdCode(((const struct aam_t *)(*this))->tid);
}

void Aam_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct aam_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Aam_t::clearMessage()
{
	navi_init_aam((struct aam_t *)(*this), TalkerId_t::Unknown);
}

Aam_t::operator const struct aam_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct aam_t *)p;
}

Aam_t::operator struct aam_t *()
{
	void *p = (void *)(*this);
	return (struct aam_t *)p;
}

Status_t Aam_t::circleStatus() const
{
	return Status_t::fromStatusCode(((const struct aam_t *)(*this))->circle);
}

Status_t Aam_t::perpendicularStatus() const
{
	return Status_t::fromStatusCode(((const struct aam_t *)(*this))->perp);
}

double Aam_t::waypointRadius() const
	{ return ((const struct aam_t *)(*this))->radius; }

std::string Aam_t::waypointId() const
	{ return std::string(((const struct aam_t *)(*this))->wpid); }

void Aam_t::setCircleStatus(const Status_t &value)
	{ ((struct aam_t *)(*this))->circle = value.toStatusCode(); }

void Aam_t::setPerpendicularStatus(const Status_t &value)
	{ ((struct aam_t *)(*this))->perp = value.toStatusCode(); }

void Aam_t::setWaypointRadius(double value)
	{ ((struct aam_t *)(*this))->radius = value; }

void Aam_t::setWaypointId(const std::string &value)
	{ strncpy(((struct aam_t *)(*this))->wpid, value.c_str(), sizeof(((struct aam_t *)(*this))->wpid)); }

}
