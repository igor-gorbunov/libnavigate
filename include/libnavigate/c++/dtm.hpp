/*
 * dtm.hpp - C++ bindings for DTM message
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

#ifndef INCLUDE_navi_dtmplusplus
#define INCLUDE_navi_dtmplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

#include <libnavigate/dtm.h>

	NAVI_EXTERN_CLASS(Dtm_t) : public Message_t
{
public:
	Dtm_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Dtm_t(const Message_t &msg);
	virtual ~Dtm_t();

public:
	virtual TalkerId_t talkerId() const;

	virtual Datum_t localDatum() const;
	virtual DatumSubdivision_t datumSubdivision() const;
	virtual Offset_t latitudeOffset() const;
	virtual Offset_t longitudeOffset() const;
	virtual double altitudeOffset() const;
	virtual Datum_t referenceDatum() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setLocalDatum(const Datum_t &datum);
	virtual void setDatumSubdivision(const DatumSubdivision_t
		&datumSubdivision);
	virtual void setLatitudeOffset(const Offset_t &offset);
	virtual void setLongitudeOffset(const Offset_t &offset);
	virtual void setAltitudeOffset(double offset);
	virtual void setReferenceDatum(const Datum_t &datum);

public:
	virtual void clearMessage();

public:
	virtual operator const struct dtm_t *() const;
	virtual operator struct dtm_t *();
};

}

#endif // INCLUDE_navi_dtmplusplus

