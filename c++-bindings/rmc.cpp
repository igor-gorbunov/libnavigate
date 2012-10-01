/*
 * rmc.cpp - implementation of Rmc_t class
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

#include <libnavigate/c++/rmc.hpp>

namespace libnavigate
{

Rmc_t::Rmc_t(const TalkerId_t &tid) : Message_t(MessageType_t::RMC)
{
	((struct rmc_t *)(*this))->tid = tid.toTalkerIdCode();
	((struct rmc_t *)(*this))->vfields = 0;
}

Rmc_t::Rmc_t(const Message_t &msg) : Message_t(msg) { }

Rmc_t::~Rmc_t() { }

TalkerId_t Rmc_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct rmc_t *)(*this))->tid); }

Utc_t Rmc_t::utc() const
{
	return Utc_t(((const struct rmc_t *)(*this))->utc.hour,
		((const struct rmc_t *)(*this))->utc.min,
		((const struct rmc_t *)(*this))->utc.sec);
}

Status_t Rmc_t::status() const
	{ return Status_t::fromStatusCode(((const struct rmc_t *)(*this))->status); }

PositionFix_t Rmc_t::positionFix() const
	{ return PositionFix_t::fromPosition(&((const struct rmc_t *)(*this))->fix); }

double Rmc_t::speed() const
	{ return ((const struct rmc_t *)(*this))->speed; }

double Rmc_t::course() const
	{ return ((const struct rmc_t *)(*this))->courseTrue; }

Date_t Rmc_t::date() const
{
	return Date_t(((const struct rmc_t *)(*this))->date.year,
		((const struct rmc_t *)(*this))->date.month,
		((const struct rmc_t *)(*this))->date.day);
}

Offset_t Rmc_t::magneticVariation() const
	{ return Offset_t::fromOffset(&((const struct rmc_t *)(*this))->magnetic); }

ModeIndicator_t Rmc_t::modeIndicator() const
	{ return ModeIndicator_t::fromModeIndCode(((const struct rmc_t *)(*this))->mi); }

void Rmc_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct rmc_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Rmc_t::setUtc(const Utc_t &utc)
{
	((struct rmc_t *)(*this))->utc.hour = utc.hours();
	((struct rmc_t *)(*this))->utc.min = utc.minutes();
	((struct rmc_t *)(*this))->utc.sec = utc.seconds();
	((struct rmc_t *)(*this))->vfields |= RMC_VALID_UTC;
}

void Rmc_t::setStatus(const Status_t &status)
	{ ((struct rmc_t *)(*this))->status = status.toStatusCode(); }

void Rmc_t::setPositionFix(const PositionFix_t &fix)
{
	((struct rmc_t *)(*this))->fix = fix.toPosition();
	((struct rmc_t *)(*this))->vfields |= RMC_VALID_POSITION_FIX;
}

void Rmc_t::setSpeed(double value)
{
	((struct rmc_t *)(*this))->speed = value;
	((struct rmc_t *)(*this))->vfields |= RMC_VALID_SPEED;
}

void Rmc_t::setCourse(double value)
{
	((struct rmc_t *)(*this))->courseTrue = value;
	((struct rmc_t *)(*this))->vfields |= RMC_VALID_COURSETRUE;
}

void Rmc_t::setDate(const Date_t &date)
{
	((struct rmc_t *)(*this))->date = date.toDateStruct();
	((struct rmc_t *)(*this))->vfields |= RMC_VALID_DATE;
}

void Rmc_t::setMagneticVariation(const Offset_t &offset)
{
	((struct rmc_t *)(*this))->magnetic = offset.toOffset();
	((struct rmc_t *)(*this))->vfields |= RMC_VALID_MAGNVARIATION;
}

void Rmc_t::setModeIndicator(const ModeIndicator_t &mi)
	{ ((struct rmc_t *)(*this))->mi = mi.toModeIndCode(); }

void Rmc_t::clearMessage()
	{ ((struct rmc_t *)(*this))->vfields = 0; }

Rmc_t::operator const struct rmc_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct rmc_t *)p;
}

Rmc_t::operator struct rmc_t *()
{
	void *p = (void *)(*this);
	return (struct rmc_t *)p;
}

}
