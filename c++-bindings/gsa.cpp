/*
 * gsa.cpp - implementation of Gsa_t class
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

#include "include/libnavigate/c++/gsa.hpp"

namespace libnavigate
{

Gsa_t::Gsa_t(const TalkerId_t &tid) : Message_t(MessageType_t::GSA)
	{ navi_init_gsa((struct gsa_t *)(*this), tid.toTalkerIdCode()); }

Gsa_t::Gsa_t(const Message_t &msg) : Message_t(msg) { }

Gsa_t::~Gsa_t() { }

TalkerId_t Gsa_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct gsa_t *)(*this))->tid); }

GsaSwitchMode_t Gsa_t::switchMode() const
	{ return GsaSwitchMode_t::fromSwitchModeCode(((const struct gsa_t *)(*this))->swmode); }

int Gsa_t::fixMode() const
	{ return ((const struct gsa_t *)(*this))->fixmode; }

int Gsa_t::satelliteId(int satIdx) const
	{ return ((const struct gsa_t *)(*this))->satellites[satIdx].id; }

double Gsa_t::pdop() const
	{ return ((const struct gsa_t *)(*this))->pdop; }

double Gsa_t::hdop() const
	{ return ((const struct gsa_t *)(*this))->hdop; }

double Gsa_t::vdop() const
	{ return ((const struct gsa_t *)(*this))->vdop; }

void Gsa_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct gsa_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Gsa_t::setSwitchMode(const GsaSwitchMode_t &mode)
{
	((struct gsa_t *)(*this))->swmode = mode.toSwitchModeCode();
	((struct gsa_t *)(*this))->vfields |= GSA_VALID_SWITCHMODE;
}

void Gsa_t::setFixMode(int value)
{
	((struct gsa_t *)(*this))->fixmode = value;
	((struct gsa_t *)(*this))->vfields |= GSA_VALID_FIXMODE;
}

void Gsa_t::setSatelliteId(int satIdx, int value)
{
	((struct gsa_t *)(*this))->satellites[satIdx].notnull = 1;
	((struct gsa_t *)(*this))->satellites[satIdx].id = value;
}

void Gsa_t::setPdop(double value)
{
	((struct gsa_t *)(*this))->pdop = value;
	((struct gsa_t *)(*this))->vfields |= GSA_VALID_PDOP;
}

void Gsa_t::setHdop(double value)
{
	((struct gsa_t *)(*this))->hdop = value;
	((struct gsa_t *)(*this))->vfields |= GSA_VALID_HDOP;
}

void Gsa_t::setVdop(double value)
{
	((struct gsa_t *)(*this))->vdop = value;
	((struct gsa_t *)(*this))->vfields |= GSA_VALID_VDOP;
}

bool Gsa_t::isSwitchModeValid() const
{
	return (((const struct gsa_t *)(*this))->vfields & GSA_VALID_SWITCHMODE) != 0 ? true : false;
}

bool Gsa_t::isFixModeValid() const
{
	return (((const struct gsa_t *)(*this))->vfields & GSA_VALID_FIXMODE) != 0 ? true : false;
}

bool Gsa_t::isSatelliteIdValid(int satIdx) const
{
	return ((const struct gsa_t *)(*this))->satellites[satIdx].notnull != 0 ? true : false;
}

bool Gsa_t::isPdopValid() const
{
	return (((const struct gsa_t *)(*this))->vfields & GSA_VALID_PDOP) != 0 ? true : false;
}

bool Gsa_t::isHdopValid() const
{
	return (((const struct gsa_t *)(*this))->vfields & GSA_VALID_HDOP) != 0 ? true : false;
}

bool Gsa_t::isVdopValid() const
{
	return (((const struct gsa_t *)(*this))->vfields & GSA_VALID_VDOP) != 0 ? true : false;
}

void Gsa_t::clearMessage()
	{ navi_init_gsa((struct gsa_t *)(*this), navi_talkerid_Unknown); }

Gsa_t::operator const struct gsa_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct gsa_t *)p;
}

Gsa_t::operator struct gsa_t *()
{
	void *p = (void *)(*this);
	return (struct gsa_t *)p;
}

}
