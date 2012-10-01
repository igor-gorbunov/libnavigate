/*
 * gbs.cpp - implementation of Gbs_t class
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

#include <libnavigate/c++/gbs.hpp>

namespace libnavigate
{

Gbs_t::Gbs_t(const TalkerId_t &tid) : Message_t(MessageType_t::GBS)
	{ navi_init_gbs((struct gbs_t *)(*this), tid.toTalkerIdCode()); }

Gbs_t::Gbs_t(const Message_t &msg) : Message_t(msg) { }

Gbs_t::~Gbs_t() { }

TalkerId_t Gbs_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct gbs_t *)(*this))->tid); }

Utc_t Gbs_t::utc() const
{
	return Utc_t(((const struct gbs_t *)(*this))->utc.hour,
		((const struct gbs_t *)(*this))->utc.min,
		((const struct gbs_t *)(*this))->utc.sec);
}

double Gbs_t::expErrInLatitude() const
	{ return ((const struct gbs_t *)(*this))->experrlat; }

double Gbs_t::expErrInLongitude() const
	{ return ((const struct gbs_t *)(*this))->experrlon; }

double Gbs_t::expErrInAltitude() const
	{ return ((const struct gbs_t *)(*this))->experralt; }

int Gbs_t::failedSatelliteId() const
	{ return ((const struct gbs_t *)(*this))->id; }

double Gbs_t::probabilityOfMissedDetection() const
	{ return ((const struct gbs_t *)(*this))->probability; }

double Gbs_t::estimateOfBias() const
	{ return ((const struct gbs_t *)(*this))->estimate; }

double Gbs_t::deviationOfBias() const
	{ return ((const struct gbs_t *)(*this))->deviation; }

void Gbs_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct gbs_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Gbs_t::setUtc(const Utc_t &utc)
	{ ((struct gbs_t *)(*this))->utc = utc.toUtcStruct(); }

void Gbs_t::setExpErrInLatitude(double value)
{
	((struct gbs_t *)(*this))->experrlat = value;
	((struct gbs_t *)(*this))->vfields |= GBS_VALID_EXPERRLATLON;
}

void Gbs_t::setExpErrInLongitude(double value)
{
	((struct gbs_t *)(*this))->experrlon = value;
	((struct gbs_t *)(*this))->vfields |= GBS_VALID_EXPERRLATLON;
}

void Gbs_t::setExpErrInAltitude(double value)
{
	((struct gbs_t *)(*this))->experralt = value;
	((struct gbs_t *)(*this))->vfields |= GBS_VALID_EXPERRALT;
}

void Gbs_t::setFailedSatelliteId(int value)
{
	((struct gbs_t *)(*this))->id = value;
	((struct gbs_t *)(*this))->vfields |= GBS_VALID_ID;
}

void Gbs_t::setProbabilityOfMissedDetection(double value)
{
	((struct gbs_t *)(*this))->probability = value;
	((struct gbs_t *)(*this))->vfields |= GBS_VALID_PROBABILITY;
}

void Gbs_t::setEstimateOfBias(double value)
{
	((struct gbs_t *)(*this))->estimate = value;
	((struct gbs_t *)(*this))->vfields |= GBS_VALID_ESTIMATE;
}

void Gbs_t::setDeviationOfBias(double value)
{
	((struct gbs_t *)(*this))->deviation = value;
	((struct gbs_t *)(*this))->vfields |= GBS_VALID_DEVIATION;
}

bool Gbs_t::isExpectedErrorValid() const
{
	return (((const struct gbs_t *)(*this))->vfields & GBS_VALID_EXPERRLATLON) != 0 ? true : false;
}

bool Gbs_t::isExpectedAltitudeErrorValid() const
{
	return (((const struct gbs_t *)(*this))->vfields & GBS_VALID_EXPERRALT) != 0 ? true : false;
}

bool Gbs_t::isFailedIdValid() const
{
	return (((const struct gbs_t *)(*this))->vfields & GBS_VALID_ID) != 0 ? true : false;
}

bool Gbs_t::isProbabilityValid() const
{
	return (((const struct gbs_t *)(*this))->vfields & GBS_VALID_PROBABILITY) != 0 ? true : false;
}

bool Gbs_t::isEstimateValid() const
{
	return (((const struct gbs_t *)(*this))->vfields & GBS_VALID_ESTIMATE) != 0 ? true : false;
}

bool Gbs_t::isStandardDeviationValid() const
{
	return (((const struct gbs_t *)(*this))->vfields & GBS_VALID_DEVIATION) != 0 ? true : false;
}

void Gbs_t::clearMessage()
	{ navi_init_gbs((struct gbs_t *)(*this), navi_talkerid_Unknown); }

Gbs_t::operator const struct gbs_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct gbs_t *)p;
}

Gbs_t::operator struct gbs_t *()
{
	void *p = (void *)(*this);
	return (struct gbs_t *)p;
}

}
