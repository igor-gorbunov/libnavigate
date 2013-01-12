/*
* dtm.cpp - implementation of Dtm_t class
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

#include "include/libnavigate/c++/dtm.hpp"

namespace libnavigate
{

Dtm_t::Dtm_t(const TalkerId_t &tid) : Message_t(MessageType_t::DTM)
{ navi_init_dtm((struct dtm_t *)(*this), tid.toTalkerIdCode()); }

Dtm_t::Dtm_t(const Message_t &msg) : Message_t(msg) { }

Dtm_t::~Dtm_t() { }

TalkerId_t Dtm_t::talkerId() const
{ return TalkerId_t::fromTalkerIdCode(((const struct dtm_t *)(*this))->tid); }

Datum_t Dtm_t::localDatum() const
{ return Datum_t::fromDatumCode(((const struct dtm_t *)(*this))->local_dtm); }

DatumSubdivision_t Dtm_t::datumSubdivision() const
{ return DatumSubdivision_t::fromDatumSubcode(((const struct dtm_t *)(*this))->local_dtmsd); }

Offset_t Dtm_t::latitudeOffset() const
{ return Offset_t::fromOffset(&((const struct dtm_t *)(*this))->lat_offset); }

Offset_t Dtm_t::longitudeOffset() const
{ return Offset_t::fromOffset(&((const struct dtm_t *)(*this))->long_offset); }

double Dtm_t::altitudeOffset() const
{ return ((const struct dtm_t *)(*this))->alt_offset; }

Datum_t Dtm_t::referenceDatum() const
{ return Datum_t::fromDatumCode(((const struct dtm_t *)(*this))->reference_dtm); }

void Dtm_t::setTalkerId(const TalkerId_t &tid)
{ ((struct dtm_t *)(*this))->tid = tid.toTalkerIdCode(); }

void Dtm_t::setLocalDatum(const Datum_t &datum)
{ ((struct dtm_t *)(*this))->local_dtm = datum.toDatumCode(); }

void Dtm_t::setDatumSubdivision(const DatumSubdivision_t &datumSubdivision)
{ ((struct dtm_t *)(*this))->local_dtmsd = datumSubdivision.toDatumSubcode(); }

void Dtm_t::setLatitudeOffset(const Offset_t &offset)
{ ((struct dtm_t *)(*this))->lat_offset = offset.toOffset(); }

void Dtm_t::setLongitudeOffset(const Offset_t &offset)
{ ((struct dtm_t *)(*this))->long_offset = offset.toOffset(); }

void Dtm_t::setAltitudeOffset(double offset)
{ ((struct dtm_t *)(*this))->alt_offset = offset; }

void Dtm_t::setReferenceDatum(const Datum_t &datum)
{ ((struct dtm_t *)(*this))->reference_dtm = datum.toDatumCode(); }

bool Dtm_t::isLocalDatumValid() const
{ return ((const struct dtm_t *)(*this))->local_dtm != navi_datum_NULL; }

bool Dtm_t::isLocalDatumSubdivisionValid() const
{ return ((const struct dtm_t *)(*this))->local_dtmsd != navi_datumsub_NULL; }

bool Dtm_t::isOffsetValid() const
{
	return (((const struct dtm_t *)(*this))->lat_offset.sign != navi_offset_NULL) &&
		(((const struct dtm_t *)(*this))->long_offset.sign != navi_offset_NULL);
}

bool Dtm_t::isAltitudeOffsetValid() const
{ return navi_check_validity_number(((const struct dtm_t *)(*this))->alt_offset) == navi_Ok; }

bool Dtm_t::isReferenceDatumValid() const
{ return ((const struct dtm_t *)(*this))->reference_dtm != navi_datum_NULL; }

void Dtm_t::clearMessage()
{ navi_init_dtm((struct dtm_t *)(*this), navi_talkerid_Unknown); }

Dtm_t::operator const struct dtm_t *() const
{
	const void *p = (const void *)(*this);
	return (const struct dtm_t *)p;
}

Dtm_t::operator struct dtm_t *()
{
	void *p = (void *)(*this);
	return (struct dtm_t *)p;
}

}
