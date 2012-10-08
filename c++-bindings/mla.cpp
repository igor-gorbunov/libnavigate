/*
 * mla.cpp - implementation of Mla_t class
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

#include "include/libnavigate/c++/mla.hpp"

namespace libnavigate
{

Mla_t::Mla_t(const TalkerId_t &tid) : Message_t(MessageType_t::MLA)
	{ navi_init_mla((struct mla_t *)(*this), tid.toTalkerIdCode()); }

Mla_t::Mla_t(const Message_t &msg) : Message_t(msg) { }

Mla_t::~Mla_t() { }

TalkerId_t Mla_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct mla_t *)(*this))->tid); }

int Mla_t::totalNmOfMessages() const
	{ return ((const struct mla_t *)(*this))->totalnm; }

int Mla_t::messageNumber() const
	{ return ((const struct mla_t *)(*this))->msgnm; }

unsigned int Mla_t::satelliteSlot() const
	{ return ((const struct mla_t *)(*this))->alm.satslot; }

unsigned int Mla_t::dayCount() const
	{ return ((const struct mla_t *)(*this))->alm.daycount; }

unsigned int Mla_t::svHealth() const
	{ return ((const struct mla_t *)(*this))->alm.svhealth; }

unsigned int Mla_t::eccentricity() const
	{ return ((const struct mla_t *)(*this))->alm.e; }

unsigned int Mla_t::rateOfChangeOfDraconicTime() const
	{ return ((const struct mla_t *)(*this))->alm.dot; }

unsigned int Mla_t::argumentOfPerigee() const
	{ return ((const struct mla_t *)(*this))->alm.omega; }

unsigned int Mla_t::systemTimescaleCorrection_High() const
	{ return ((const struct mla_t *)(*this))->alm.tauc_high; }

unsigned int Mla_t::correctionToDraconicTime() const
	{ return ((const struct mla_t *)(*this))->alm.deltat; }

unsigned int Mla_t::timeOfAscensionNode() const
	{ return ((const struct mla_t *)(*this))->alm.t; }

unsigned int Mla_t::longitudeOfAscensionNode() const
	{ return ((const struct mla_t *)(*this))->alm.lambda; }

unsigned int Mla_t::correctionToInclinationAngle() const
	{ return ((const struct mla_t *)(*this))->alm.deltai; }

unsigned int Mla_t::systemTimescaleCorrection_Low() const
	{ return ((const struct mla_t *)(*this))->alm.tauc_low; }

unsigned int Mla_t::courseValueOfTimescaleShift() const
	{ return ((const struct mla_t *)(*this))->alm.taun; }

void Mla_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct mla_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Mla_t::setTotalNmOfMessages(int value)
	{ ((struct mla_t *)(*this))->totalnm = value; }

void Mla_t::setMessageNumber(int value)
	{ ((struct mla_t *)(*this))->msgnm = value; }

void Mla_t::setSatelliteSlot(unsigned int value)
	{ ((struct mla_t *)(*this))->alm.satslot = value; }

void Mla_t::setDayCount(unsigned int value)
{
	((struct mla_t *)(*this))->alm.daycount = value;
	((struct mla_t *)(*this))->alm.vfields |= GLOALM_VALID_DAYCOUNT;
}

void Mla_t::setSvHealth(unsigned int value)
{
	((struct mla_t *)(*this))->alm.svhealth = value;
	((struct mla_t *)(*this))->alm.vfields |= GLOALM_VALID_SVHEALTH;
}

void Mla_t::setEccentricity(unsigned int value)
{
	((struct mla_t *)(*this))->alm.e = value;
	((struct mla_t *)(*this))->alm.vfields |= GLOALM_VALID_E;
}

void Mla_t::setRateOfChangeOfDraconicTime(unsigned int value)
{
	((struct mla_t *)(*this))->alm.dot = value;
	((struct mla_t *)(*this))->alm.vfields |= GLOALM_VALID_DOT;
}

void Mla_t::setArgumentOfPerigee(unsigned int value)
{
	((struct mla_t *)(*this))->alm.omega = value;
	((struct mla_t *)(*this))->alm.vfields |= GLOALM_VALID_OMEGA;
}

void Mla_t::setSystemTimescaleCorrection_High(unsigned int value)
{
	((struct mla_t *)(*this))->alm.tauc_high = value;
	((struct mla_t *)(*this))->alm.vfields |= GLOALM_VALID_TAUC;
}

void Mla_t::setCorrectionToDraconicTime(unsigned int value)
{
	((struct mla_t *)(*this))->alm.deltat = value;
	((struct mla_t *)(*this))->alm.vfields |= GLOALM_VALID_DELTAT;
}

void Mla_t::setTimeOfAscensionNode(unsigned int value)
{
	((struct mla_t *)(*this))->alm.t = value;
	((struct mla_t *)(*this))->alm.vfields |= GLOALM_VALID_T;
}

void Mla_t::setLongitudeOfAscensionNode(unsigned int value)
{
	((struct mla_t *)(*this))->alm.lambda = value;
	((struct mla_t *)(*this))->alm.vfields |= GLOALM_VALID_LAMBDA;
}

void Mla_t::setCorrectionToInclinationAngle(unsigned int value)
{
	((struct mla_t *)(*this))->alm.deltai = value;
	((struct mla_t *)(*this))->alm.vfields |= GLOALM_VALID_DELTAI;
}

void Mla_t::setSystemTimescaleCorrection_Low(unsigned int value)
{
	((struct mla_t *)(*this))->alm.tauc_low = value;
	((struct mla_t *)(*this))->alm.vfields |= GLOALM_VALID_TAUC;
}

void Mla_t::setCourseValueOfTimescaleShift(unsigned int value)
{
	((struct mla_t *)(*this))->alm.taun = value;
	((struct mla_t *)(*this))->alm.vfields |= GLOALM_VALID_TAUN;
}

bool Mla_t::isDayCountValid() const
{
	return (((const struct mla_t *)(*this))->alm.vfields & GLOALM_VALID_DAYCOUNT) != 0 ? true : false;
}

bool Mla_t::isSvHealthValid() const
{
	return (((const struct mla_t *)(*this))->alm.vfields & GLOALM_VALID_SVHEALTH) != 0 ? true : false;
}

bool Mla_t::isEccentricityValid() const
{
	return (((const struct mla_t *)(*this))->alm.vfields & GLOALM_VALID_E) != 0 ? true : false;
}

bool Mla_t::isRateOfChangeOfDraconicTimeValid() const
{
	return (((const struct mla_t *)(*this))->alm.vfields & GLOALM_VALID_DOT) != 0 ? true : false;
}

bool Mla_t::isArgumentOfPerigeeValid() const
{
	return (((const struct mla_t *)(*this))->alm.vfields & GLOALM_VALID_OMEGA) != 0 ? true : false;
}

bool Mla_t::isSystemTimescaleCorrectionValid() const
{
	return (((const struct mla_t *)(*this))->alm.vfields & GLOALM_VALID_TAUC) != 0 ? true : false;
}

bool Mla_t::isCorrectionToDraconicTimeValid() const
{
	return (((const struct mla_t *)(*this))->alm.vfields & GLOALM_VALID_DELTAT) != 0 ? true : false;
}

bool Mla_t::isTimeOfAscensionNodeValid() const
{
	return (((const struct mla_t *)(*this))->alm.vfields & GLOALM_VALID_T) != 0 ? true : false;
}

bool Mla_t::isLongitudeOfAscensionNodeValid() const
{
	return (((const struct mla_t *)(*this))->alm.vfields & GLOALM_VALID_LAMBDA) != 0 ? true : false;
}

bool Mla_t::isCorrectionToInclinationAngleValid() const
{
	return (((const struct mla_t *)(*this))->alm.vfields & GLOALM_VALID_DELTAI) != 0 ? true : false;
}

bool Mla_t::isCourseValueOfTimescaleShiftValid() const
{
	return (((const struct mla_t *)(*this))->alm.vfields & GLOALM_VALID_TAUN) != 0 ? true : false;
}

void Mla_t::clearMessage()
	{ navi_init_mla((struct mla_t *)(*this), navi_talkerid_Unknown); }

Mla_t::operator const struct mla_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct mla_t *)p;
}

Mla_t::operator struct mla_t *()
{
	void *p = (void *)(*this);
	return (struct mla_t *)p;
}

}
