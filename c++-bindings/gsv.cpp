/*
 * gsv.cpp - implementation of Gsv_t class
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

#include <libnavigate/c++/gsv.hpp>

namespace libnavigate
{

Gsv_t::Gsv_t(const TalkerId_t &tid) : Message_t(MessageType_t::GSV)
{
	((struct gsv_t *)(*this))->tid = tid.toTalkerIdCode();
	((struct gsv_t *)(*this))->nmsatellites = 0;
	for (int i = 0; i < MaxSatellites; i++)
	{
		((struct gsv_t *)(*this))->info[i].vfields = 0;
	}
	((struct gsv_t *)(*this))->totalnm = ((struct gsv_t *)(*this))->msgnm = 0;
}

Gsv_t::Gsv_t(const Message_t &msg) : Message_t(msg) { }

Gsv_t::~Gsv_t() { }

TalkerId_t Gsv_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct gsv_t *)(*this))->tid); }

void Gsv_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct gsv_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Gsv_t::clearMessage()
{
	((struct gsv_t *)(*this))->nmsatellites = 0;
	for (int i = 0; i < MaxSatellites; i++)
	{
		((struct gsv_t *)(*this))->info[i].vfields = 0;
	}
}

int Gsv_t::nmOfSatellites() const
	{ return ((const struct gsv_t *)(*this))->nmsatellites; }

int Gsv_t::totalNmOfMessages() const
	{ return ((const struct gsv_t *)(*this))->totalnm; }

int Gsv_t::messageNumber() const
	{ return ((const struct gsv_t *)(*this))->msgnm; }

void Gsv_t::setNmOfSatellites(int value)
	{ ((struct gsv_t *)(*this))->nmsatellites = value; }

void Gsv_t::setTotalNmOfMessages(int value)
	{ ((struct gsv_t *)(*this))->totalnm = value; }

void Gsv_t::setMessageNumber(int value)
	{ ((struct gsv_t *)(*this))->msgnm = value; }

unsigned int Gsv_t::satelliteId(int satIdx) const
	{ return ((const struct gsv_t *)(*this))->info[satIdx].id; }

unsigned int Gsv_t::elevation(int satIdx) const
	{ return ((const struct gsv_t *)(*this))->info[satIdx].elevation; }

unsigned int Gsv_t::azimuth(int satIdx) const
	{ return ((const struct gsv_t *)(*this))->info[satIdx].azimuth; }

unsigned int Gsv_t::snratio(int satIdx) const
	{ return ((const struct gsv_t *)(*this))->info[satIdx].snr; }

void Gsv_t::setSatelliteId(int satIdx, unsigned int value)
{
	((struct gsv_t *)(*this))->info[satIdx].id = value;
}

void Gsv_t::setOrientation(int satIdx, unsigned int elevation,
	unsigned int azimuth)
{
	((struct gsv_t *)(*this))->info[satIdx].elevation = elevation;
	((struct gsv_t *)(*this))->info[satIdx].azimuth = azimuth;
	((struct gsv_t *)(*this))->info[satIdx].vfields |= SATINFO_VALID_ORIENTATION;
}

void Gsv_t::setSnratio(int satIdx, unsigned int value)
{
	((struct gsv_t *)(*this))->info[satIdx].snr = value;
	((struct gsv_t *)(*this))->info[satIdx].vfields |= SATINFO_VALID_SNR;
}

Gsv_t::operator const struct gsv_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct gsv_t *)p;
}

Gsv_t::operator struct gsv_t *()
{
	void *p = (void *)(*this);
	return (struct gsv_t *)p;
}

}
