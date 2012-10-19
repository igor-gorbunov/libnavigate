/*
 * gll.cpp - implementation of Gll_t class
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

#include "include/libnavigate/c++/gll.hpp"

namespace libnavigate
{

Gll_t::Gll_t(const TalkerId_t &tid) : Message_t(MessageType_t::GLL)
	{ navi_init_gll((struct gll_t *)(*this), tid.toTalkerIdCode()); }

Gll_t::Gll_t(const Message_t &msg) : Message_t(msg) { }

Gll_t::~Gll_t() { }

TalkerId_t Gll_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct gll_t *)(*this))->tid); }

PositionFix_t Gll_t::positionFix() const
	{ return PositionFix_t::fromPosition(&((const struct gll_t *)(*this))->fix); }

Utc_t Gll_t::utc() const
	{ return Utc_t::fromUtcStruct(((const struct gll_t *)(*this))->utc); }

Status_t Gll_t::status() const
	{ return Status_t::fromStatusCode(((const struct gll_t *)(*this))->status); }

ModeIndicator_t Gll_t::modeIndicator() const
	{ return ModeIndicator_t::fromModeIndCode(((const struct gll_t *)(*this))->mi); }

void Gll_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct gll_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Gll_t::setPositionFix(const PositionFix_t &fix)
	{ ((struct gll_t *)(*this))->fix = fix.toPosition(); }

void Gll_t::setUtc(const Utc_t &utc)
{
	((struct gll_t *)(*this))->utc = utc.toUtcStruct();
	((struct gll_t *)(*this))->vfields |= GLL_VALID_UTC;
}

void Gll_t::setStatus(const Status_t &status)
	{ ((struct gll_t *)(*this))->status = status.toStatusCode(); }

void Gll_t::setModeIndicator(const ModeIndicator_t &mi)
	{ ((struct gll_t *)(*this))->mi = mi.toModeIndCode(); }

bool Gll_t::isPositionValid() const
	{ return ((const struct gll_t *)(*this))->fix.latitude.sign != navi_offset_NULL; }

bool Gll_t::isUtcValid() const
{
	return (((const struct gll_t *)(*this))->vfields & GLL_VALID_UTC) != 0 ? true : false;
}

void Gll_t::clearMessage()
	{ navi_init_gll((struct gll_t *)(*this), navi_talkerid_Unknown); }

Gll_t::operator const struct gll_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct gll_t *)p;
}

Gll_t::operator struct gll_t *()
{
	void *p = (void *)(*this);
	return (struct gll_t *)p;
}

}
