/*
 * gga.hpp - C++ bindings for GGA message
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

#ifndef INCLUDE_navi_ggaplusplus
#define INCLUDE_navi_ggaplusplus

#include <libnavigate/c++/sentence.hpp>

namespace libnavigate
{

#include <libnavigate/gga.h>

NAVI_EXTERN_CLASS(Gga_t) : public Message_t
{
public:
	Gga_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Gga_t(const Message_t &msg);
	virtual ~Gga_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual Utc_t utc() const;
	virtual PositionFix_t positionFix() const;
	virtual GpsQualityIndicator_t qualityIndicator() const;
	virtual int nmOfSatellites() const;
	virtual double hdop() const;
	virtual double antennaAltitude() const;
	virtual double geoidalSeparation() const;
	virtual int ageOfDiffData() const;
	virtual int diffReferenceStationId() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setUtc(const Utc_t &utc);
	virtual void setPositionFix(const PositionFix_t &fix);
	virtual void setQualityIndicator(const GpsQualityIndicator_t &qi);
	virtual void setNmOfSatellites(int value);
	virtual void setHdop(double value);
	virtual void setAntennaAltitude(double value);
	virtual void setGeoidalSeparation(double value);
	virtual void setAgeOfDiffData(int value);
	virtual void setDiffReferenceStationId(int value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct gga_t *() const;
	virtual operator struct gga_t *();
};

}

#endif // INCLUDE_navi_ggaplusplus

