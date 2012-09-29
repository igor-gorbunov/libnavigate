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
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.vfields = 0;
}

Gst_t::~Gst_t() { }

TalkerId_t Gst_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

Utc_t Gst_t::utc() const
	{ return Utc_t(m_value.utc.hour, m_value.utc.min, m_value.utc.sec); }

double Gst_t::rmsOfStandardDeviation() const
	{ return m_value.rms; }

double Gst_t::deviationOfSemiMajorAxis() const
	{ return m_value.devmajor; }

double Gst_t::deviationOfSemiMinorAxis() const
	{ return m_value.devminor; }

double Gst_t::orientationOfSemiMajorAxis() const
	{ return m_value.orientmajor; }

double Gst_t::deviationOfLatitudeError() const
	{ return m_value.devlaterr; }

double Gst_t::deviationOfLongitudeError() const
	{ return m_value.devlonerr; }

double Gst_t::deviationOfAltitudeError() const
	{ return m_value.devalterr; }

void Gst_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Gst_t::setUtc(const Utc_t &utc)
{
	m_value.utc.hour = utc.hours();
	m_value.utc.min = utc.minutes();
	m_value.utc.sec = utc.seconds();
}

void Gst_t::setRmsOfStandardDeviation(double value)
{
	m_value.rms = value;
	m_value.vfields |= GST_VALID_RMS;
}

void Gst_t::setDeviationOfSemiMajorAxis(double value)
{
	m_value.devmajor = value;
	m_value.vfields |= GST_VALID_STDDEVELLIPSE;
}

void Gst_t::setDeviationOfSemiMinorAxis(double value)
{
	m_value.devminor = value;
	m_value.vfields |= GST_VALID_STDDEVELLIPSE;
}

void Gst_t::setOrientationOfSemiMajorAxis(double value)
{
	m_value.orientmajor = value;
	m_value.vfields |= GST_VALID_STDDEVELLIPSE;
}

void Gst_t::setDeviationOfLatitudeError(double value)
{
	m_value.devlaterr = value;
	m_value.vfields |= GST_VALID_DEVLATLONERR;
}

void Gst_t::setDeviationOfLongitudeError(double value)
{
	m_value.devlonerr = value;
	m_value.vfields |= GST_VALID_DEVLATLONERR;
}

void Gst_t::setDeviationOfAltitudeError(double value)
{
	m_value.devalterr = value;
	m_value.vfields |= GST_VALID_DEVALTERR;
}

void Gst_t::clearMessage()
	{ m_value.vfields = 0; }

Gst_t::operator const void *() const
	{ return (const void *)&m_value; }

Gst_t::operator void *()
	{ return &m_value; }

}
