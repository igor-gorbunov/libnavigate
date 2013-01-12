/*
* grs.cpp - implementation of Grs_t class
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

#include "include/libnavigate/c++/grs.hpp"

namespace libnavigate
{

Grs_t::Grs_t(const TalkerId_t &tid) : Message_t(MessageType_t::GRS)
{ navi_init_grs((struct grs_t *)(*this), tid.toTalkerIdCode()); }

Grs_t::Grs_t(const Message_t &msg) : Message_t(msg) { }

Grs_t::~Grs_t() { }

TalkerId_t Grs_t::talkerId() const
{ return TalkerId_t::fromTalkerIdCode(((const struct grs_t *)(*this))->tid); }

Utc_t Grs_t::utc() const
{ return Utc_t::fromUtcStruct(((const struct grs_t *)(*this))->utc); }

int Grs_t::mode() const
{ return ((const struct grs_t *)(*this))->mode; }

double Grs_t::residual(int satIdx) const
{ return ((const struct grs_t *)(*this))->residuals[satIdx]; }

void Grs_t::setTalkerId(const TalkerId_t &tid)
{ ((struct grs_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Grs_t::setUtc(const Utc_t &utc)
{ ((struct grs_t *)(*this))->utc = utc.toUtcStruct(); }

void Grs_t::setMode(int mode)
{ ((struct grs_t *)(*this))->mode = mode; }

void Grs_t::setResidual(int satIdx, double value)
{ ((struct grs_t *)(*this))->residuals[satIdx] = value; }

bool Grs_t::isResidualValid(int satIdx) const
{ return navi_check_validity_number(((const struct grs_t *)(*this))->residuals[satIdx]) == navi_Ok; }

void Grs_t::clearMessage()
{ navi_init_grs((struct grs_t *)(*this), navi_talkerid_Unknown); }

Grs_t::operator const struct grs_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct grs_t *)p;
}

Grs_t::operator struct grs_t *()
{
	void *p = (void *)(*this);
	return (struct grs_t *)p;
}

}
