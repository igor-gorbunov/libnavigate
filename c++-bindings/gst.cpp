/*
 * gst.cpp - implementation of Gst_t class
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

#include <libnavigate/c++/gst.hpp>

namespace libnavigate
{

Gst_t::Gst_t(const TalkerId_t &tid) : Message_t(MessageType_t::GST)
	{ navi_init_gst((struct gst_t *)(*this), tid.toTalkerIdCode()); }

Gst_t::Gst_t(const Message_t &msg) : Message_t(msg) { }

Gst_t::~Gst_t() { }

TalkerId_t Gst_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(((const struct gst_t *)(*this))->tid); }

Utc_t Gst_t::utc() const
	{ return Utc_t::fromUtcStruct(((const struct gst_t *)(*this))->utc); }

double Gst_t::rmsOfStandardDeviation() const
	{ return ((const struct gst_t *)(*this))->rms; }

double Gst_t::deviationOfSemiMajorAxis() const
	{ return ((const struct gst_t *)(*this))->devmajor; }

double Gst_t::deviationOfSemiMinorAxis() const
	{ return ((const struct gst_t *)(*this))->devminor; }

double Gst_t::orientationOfSemiMajorAxis() const
	{ return ((const struct gst_t *)(*this))->orientmajor; }

double Gst_t::deviationOfLatitudeError() const
	{ return ((const struct gst_t *)(*this))->devlaterr; }

double Gst_t::deviationOfLongitudeError() const
	{ return ((const struct gst_t *)(*this))->devlonerr; }

double Gst_t::deviationOfAltitudeError() const
	{ return ((const struct gst_t *)(*this))->devalterr; }

void Gst_t::setTalkerId(const TalkerId_t &tid)
	{ ((struct gst_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Gst_t::setUtc(const Utc_t &utc)
	{ ((struct gst_t *)(*this))->utc = utc.toUtcStruct(); }

void Gst_t::setRmsOfStandardDeviation(double value)
{
	((struct gst_t *)(*this))->rms = value;
	((struct gst_t *)(*this))->vfields |= GST_VALID_RMS;
}

void Gst_t::setDeviationOfSemiMajorAxis(double value)
{
	((struct gst_t *)(*this))->devmajor = value;
	((struct gst_t *)(*this))->vfields |= GST_VALID_STDDEVELLIPSE;
}

void Gst_t::setDeviationOfSemiMinorAxis(double value)
{
	((struct gst_t *)(*this))->devminor = value;
	((struct gst_t *)(*this))->vfields |= GST_VALID_STDDEVELLIPSE;
}

void Gst_t::setOrientationOfSemiMajorAxis(double value)
{
	((struct gst_t *)(*this))->orientmajor = value;
	((struct gst_t *)(*this))->vfields |= GST_VALID_STDDEVELLIPSE;
}

void Gst_t::setDeviationOfLatitudeError(double value)
{
	((struct gst_t *)(*this))->devlaterr = value;
	((struct gst_t *)(*this))->vfields |= GST_VALID_DEVLATLONERR;
}

void Gst_t::setDeviationOfLongitudeError(double value)
{
	((struct gst_t *)(*this))->devlonerr = value;
	((struct gst_t *)(*this))->vfields |= GST_VALID_DEVLATLONERR;
}

void Gst_t::setDeviationOfAltitudeError(double value)
{
	((struct gst_t *)(*this))->devalterr = value;
	((struct gst_t *)(*this))->vfields |= GST_VALID_DEVALTERR;
}

bool Gst_t::isRmsValid() const
{
	return (((const struct gst_t *)(*this))->vfields & GST_VALID_RMS) != 0 ? true : false;
}

bool Gst_t::isStdDeviationOfEllipseValid() const
{
	return (((const struct gst_t *)(*this))->vfields & GST_VALID_STDDEVELLIPSE) != 0 ? true : false;
}

bool Gst_t::isStdDeviationOfPositionValid() const
{
	return (((const struct gst_t *)(*this))->vfields & GST_VALID_DEVLATLONERR) != 0 ? true : false;
}

bool Gst_t::isStdDevofAltitudeValid() const
{
	return (((const struct gst_t *)(*this))->vfields & GST_VALID_DEVALTERR) != 0 ? true : false;
}

void Gst_t::clearMessage()
	{ navi_init_gst((struct gst_t *)(*this), navi_talkerid_Unknown); }

Gst_t::operator const struct gst_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct gst_t *)p;
}

Gst_t::operator struct gst_t *()
{
	void *p = (void *)(*this);
	return (struct gst_t *)p;
}

}
