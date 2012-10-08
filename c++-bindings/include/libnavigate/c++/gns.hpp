/*
 * gns.hpp - C++ bindings for GNS message
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

#ifndef INCLUDE_navi_gnsplusplus
#define INCLUDE_navi_gnsplusplus

#include "sentence.hpp"
#include <libnavigate/gns.h>

namespace libnavigate
{

NAVI_EXTERN_CLASS(Gns_t) : public Message_t
{
public:
	Gns_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Gns_t(const Message_t &msg);
	virtual ~Gns_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual void setTalkerId(const TalkerId_t &tid);

public:
	virtual bool isUtcValid() const;
	virtual bool isPositionValid() const;
	virtual bool isNmSatellitesValid() const;
	virtual bool isHdopValid() const;
	virtual bool isAntennaAltitudeValid() const;
	virtual bool isGeoidalSeparationValid() const;
	virtual bool isDifferentialAgeValid() const;
	virtual bool isStationIdValid() const;

public:
	virtual Utc_t utc() const;
	virtual PositionFix_t positionFix() const;
	virtual ModeIndicatorArray_t modeIndicatorArray() const;
	virtual int nmOfSatellites() const;
	virtual double hdop() const;
	virtual double antennaAltitude() const;
	virtual double geoidalSeparation() const;
	virtual int ageOfDiffData() const;
	virtual int diffReferenceStationId() const;

public:
	virtual void setUtc(const Utc_t &utc);
	virtual void setPositionFix(const PositionFix_t &fix);
	virtual void setModeIndicatorArray(const ModeIndicatorArray_t &modeArray);
	virtual void setNmOfSatellites(int value);
	virtual void setHdop(double value);
	virtual void setAntennaAltitude(double value);
	virtual void setGeoidalSeparation(double value);
	virtual void setAgeOfDiffData(int value);
	virtual void setDiffReferenceStationId(int value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct gns_t *() const;
	virtual operator struct gns_t *();
};

}

#endif // INCLUDE_navi_gnsplusplus

