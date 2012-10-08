/*
 * alm.cpp - implementation of Alm_t class
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

#include "include/libnavigate/c++/alm.hpp"

namespace libnavigate
{

Alm_t::Alm_t(const TalkerId_t &tid) : Message_t(MessageType_t::ALM)
	{ navi_init_alm((struct alm_t *)(*this), tid.toTalkerIdCode()); }

Alm_t::Alm_t(const Message_t &msg) : Message_t(msg) { }

Alm_t::~Alm_t() { }

TalkerId_t Alm_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct alm_t *)(*this))->tid); }

int Alm_t::totalNmOfMessages() const
	{ return ((const struct alm_t *)(*this))->totalnm; }

int Alm_t::messageNumber() const
	{ return ((const struct alm_t *)(*this))->msgnm; }

unsigned int Alm_t::satellitePrn() const
	{ return ((const struct alm_t *)(*this))->alm.satelliteprn; }

unsigned int Alm_t::gpsWeek() const
	{ return ((const struct alm_t *)(*this))->alm.gpsweek; }

unsigned int Alm_t::svHealth() const
	{ return ((const struct alm_t *)(*this))->alm.svhealth; }

unsigned int Alm_t::eccentricity() const
	{ return ((const struct alm_t *)(*this))->alm.e; }

unsigned int Alm_t::almanacReferenceTime() const
	{ return ((const struct alm_t *)(*this))->alm.toa; }

unsigned int Alm_t::inclinationAngle() const
	{ return ((const struct alm_t *)(*this))->alm.sigmai; }

unsigned int Alm_t::rateOfRightAscension() const
	{ return ((const struct alm_t *)(*this))->alm.omegadot; }

unsigned int Alm_t::sqrtOfSemiMajorAxis() const
	{ return ((const struct alm_t *)(*this))->alm.sqrtsemiaxis; }

unsigned int Alm_t::argumentOfPerigee() const
	{ return ((const struct alm_t *)(*this))->alm.omega; }

unsigned int Alm_t::longitudeOfAscensionNode() const
	{ return ((const struct alm_t *)(*this))->alm.omega0; }

unsigned int Alm_t::meanAnomaly() const
	{ return ((const struct alm_t *)(*this))->alm.m0; }

unsigned int Alm_t::clockParameter0() const
	{ return ((const struct alm_t *)(*this))->alm.af0; }

unsigned int Alm_t::clockParameter1() const
	{ return ((const struct alm_t *)(*this))->alm.af1; }

void Alm_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct alm_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Alm_t::setTotalNmOfMessages(int value)
	{ ((struct alm_t *)(*this))->totalnm = value; }

void Alm_t::setMessageNumber(int value)
	{ ((struct alm_t *)(*this))->msgnm = value; }

void Alm_t::setSatellitePrn(unsigned int value)
	{ ((struct alm_t *)(*this))->alm.satelliteprn = value; }

void Alm_t::setGpsWeek(unsigned int value)
{
	((struct alm_t *)(*this))->alm.gpsweek = value;
	((struct alm_t *)(*this))->alm.vfields |= GPSALM_VALID_GPSWEEK;
}

void Alm_t::setSvHealth(unsigned int value)
{
	((struct alm_t *)(*this))->alm.svhealth = value;
	((struct alm_t *)(*this))->alm.vfields |= GPSALM_VALID_SVHEALTH;
}

void Alm_t::setEccentricity(unsigned int value)
{
	((struct alm_t *)(*this))->alm.e = value;
	((struct alm_t *)(*this))->alm.vfields |= GPSALM_VALID_E;
}

void Alm_t::setAlmanacReferenceTime(unsigned int value)
{
	((struct alm_t *)(*this))->alm.toa = value;
	((struct alm_t *)(*this))->alm.vfields |= GPSALM_VALID_TOA;
}

void Alm_t::setInclinationAngle(unsigned int value)
{
	((struct alm_t *)(*this))->alm.sigmai = value;
	((struct alm_t *)(*this))->alm.vfields |= GPSALM_VALID_SIGMAI;
}

void Alm_t::setRateOfRightAscension(unsigned int value)
{
	((struct alm_t *)(*this))->alm.omegadot = value;
	((struct alm_t *)(*this))->alm.vfields |= GPSALM_VALID_OMEGADOT;
}

void Alm_t::setSqrtOfSemiMajorAxis(unsigned int value)
{
	((struct alm_t *)(*this))->alm.sqrtsemiaxis = value;
	((struct alm_t *)(*this))->alm.vfields |= GPSALM_VALID_SQRTSEMIAXIS;
}

void Alm_t::setArgumentOfPerigee(unsigned int value)
{
	((struct alm_t *)(*this))->alm.omega = value;
	((struct alm_t *)(*this))->alm.vfields |= GPSALM_VALID_OMEGA;
}

void Alm_t::setLongitudeOfAscensionNode(unsigned int value)
{
	((struct alm_t *)(*this))->alm.omega0 = value;
	((struct alm_t *)(*this))->alm.vfields |= GPSALM_VALID_OMEGA0;
}

void Alm_t::setMeanAnomaly(unsigned int value)
{
	((struct alm_t *)(*this))->alm.m0 = value;
	((struct alm_t *)(*this))->alm.vfields |= GPSALM_VALID_M0;
}

void Alm_t::setClockParameter0(unsigned int value)
{
	((struct alm_t *)(*this))->alm.af0 = value;
	((struct alm_t *)(*this))->alm.vfields |= GPSALM_VALID_AF0;
}

void Alm_t::setClockParameter1(unsigned int value)
{
	((struct alm_t *)(*this))->alm.af1 = value;
	((struct alm_t *)(*this))->alm.vfields |= GPSALM_VALID_AF1;
}

bool Alm_t::isGpsWeekValid() const
{
	return (((const struct alm_t *)(*this))->alm.vfields & GPSALM_VALID_GPSWEEK) != 0 ? true : false;
}

bool Alm_t::isSvHealthValid() const
{
	return (((const struct alm_t *)(*this))->alm.vfields & GPSALM_VALID_SVHEALTH) != 0 ? true : false;
}

bool Alm_t::isEccentricityValid() const
{
	return (((const struct alm_t *)(*this))->alm.vfields & GPSALM_VALID_E) != 0 ? true : false;
}

bool Alm_t::isAlmanacReferenceTimeValid() const
{
	return (((const struct alm_t *)(*this))->alm.vfields & GPSALM_VALID_TOA) != 0 ? true : false;
}

bool Alm_t::isInclinationAngleValid() const
{
	return (((const struct alm_t *)(*this))->alm.vfields & GPSALM_VALID_SIGMAI) != 0 ? true : false;
}

bool Alm_t::isRateOfRightAscensionValid() const
{
	return (((const struct alm_t *)(*this))->alm.vfields & GPSALM_VALID_OMEGADOT) != 0 ? true : false;
}

bool Alm_t::isSqrtOfSemiMajorAxisValid() const
{
	return (((const struct alm_t *)(*this))->alm.vfields & GPSALM_VALID_SQRTSEMIAXIS) != 0 ? true : false;
}

bool Alm_t::isArgumentOfPerigeeValid() const
{
	return (((const struct alm_t *)(*this))->alm.vfields & GPSALM_VALID_OMEGA) != 0 ? true : false;
}

bool Alm_t::isLongitudeOfAscensionNodeValid() const
{
	return (((const struct alm_t *)(*this))->alm.vfields & GPSALM_VALID_OMEGA0) != 0 ? true : false;
}

bool Alm_t::isMeanAnomalyValid() const
{
	return (((const struct alm_t *)(*this))->alm.vfields & GPSALM_VALID_M0) != 0 ? true : false;
}

bool Alm_t::isClockParameter0Valid() const
{
	return (((const struct alm_t *)(*this))->alm.vfields & GPSALM_VALID_AF0) != 0 ? true : false;
}

bool Alm_t::isClockParameter1Valid() const
{
	return (((const struct alm_t *)(*this))->alm.vfields & GPSALM_VALID_AF1) != 0 ? true : false;
}

void Alm_t::clearMessage()
{
	navi_init_alm((struct alm_t *)(*this), TalkerId_t::Unknown);
}

Alm_t::operator const struct alm_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct alm_t *)p;
}

Alm_t::operator struct alm_t *()
{
	void *p = (void *)(*this);
	return (struct alm_t *)p;
}

}
