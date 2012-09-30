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

#include <libnavigate/c++/mla.hpp>

namespace libnavigate
{

Mla_t::Mla_t(const TalkerId_t &tid) : Message_t(MessageType_t::MLA)
{
	((struct mla_t *)(*this))->tid = tid.toTalkerIdCode();
	((struct mla_t *)(*this))->nmsatellites = 0;
	for (int i = 0; i < MaxSatellites; i++)
	{
		((struct mla_t *)(*this))->almlist[i].vfields = 0;
	}
	((struct mla_t *)(*this))->totalnm = ((struct mla_t *)(*this))->msgnm = 0;
}

Mla_t::Mla_t(const Message_t &msg) : Message_t(msg) { }

Mla_t::~Mla_t() { }

TalkerId_t Mla_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct mla_t *)(*this))->tid); }

int Mla_t::nmOfSatellites() const
	{ return ((const struct mla_t *)(*this))->nmsatellites; }

int Mla_t::totalNmOfMessages() const
	{ return ((const struct mla_t *)(*this))->totalnm; }

int Mla_t::messageNumber() const
	{ return ((const struct mla_t *)(*this))->msgnm; }

unsigned int Mla_t::satelliteSlot(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].satslot; }

unsigned int Mla_t::dayCount(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].daycount; }

unsigned int Mla_t::svHealth(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].svhealth; }

unsigned int Mla_t::eccentricity(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].e; }

unsigned int Mla_t::rateOfChangeOfDraconicTime(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].dot; }

unsigned int Mla_t::argumentOfPerigee(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].omega; }

unsigned int Mla_t::systemTimescaleCorrection_High(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].tauc_high; }

unsigned int Mla_t::correctionToDraconicTime(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].deltat; }

unsigned int Mla_t::timeOfAscensionNode(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].t; }

unsigned int Mla_t::longitudeOfAscensionNode(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].lambda; }

unsigned int Mla_t::correctionToInclinationAngle(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].deltai; }

unsigned int Mla_t::systemTimescaleCorrection_Low(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].tauc_low; }

unsigned int Mla_t::courseValueOfTimescaleShift(int satIdx) const
	{ return ((const struct mla_t *)(*this))->almlist[satIdx].taun; }

void Mla_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct mla_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Mla_t::setNmOfSatellites(int value)
	{ ((struct mla_t *)(*this))->nmsatellites = value; }

void Mla_t::setTotalNmOfMessages(int value)
	{ ((struct mla_t *)(*this))->totalnm = value; }

void Mla_t::setMessageNumber(int value)
	{ ((struct mla_t *)(*this))->msgnm = value; }

void Mla_t::setSatelliteSlot(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].satslot = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_SATSLOT;
}

void Mla_t::setDayCount(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].daycount = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_DAYCOUNT;
}

void Mla_t::setSvHealth(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].svhealth = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_SVHEALTH;
}

void Mla_t::setEccentricity(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].e = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_E;
}

void Mla_t::setRateOfChangeOfDraconicTime(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].dot = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_DOT;
}

void Mla_t::setArgumentOfPerigee(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].omega = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_OMEGA;
}

void Mla_t::setSystemTimescaleCorrection_High(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].tauc_high = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_TAUC;
}

void Mla_t::setCorrectionToDraconicTime(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].deltat = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_DELTAT;
}

void Mla_t::setTimeOfAscensionNode(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].t = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_T;
}

void Mla_t::setLongitudeOfAscensionNode(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].lambda = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_LAMBDA;
}

void Mla_t::setCorrectionToInclinationAngle(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].deltai = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_DELTAI;
}

void Mla_t::setSystemTimescaleCorrection_Low(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].tauc_low = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_TAUC;
}

void Mla_t::setCourseValueOfTimescaleShift(int satIdx, unsigned int value)
{
	((struct mla_t *)(*this))->almlist[satIdx].taun = value;
	((struct mla_t *)(*this))->almlist[satIdx].vfields |= GLOALM_VALID_TAUN;
}

void Mla_t::clearMessage()
{
	((struct mla_t *)(*this))->nmsatellites = 0;
	for (int i = 0; i < MaxSatellites; i++)
	{
		((struct mla_t *)(*this))->almlist[i].vfields = 0;
	}
}

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
