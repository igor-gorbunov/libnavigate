/*
 * alm.hpp - C++ bindings for ALM message
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

#ifndef INCLUDE_navi_almplusplus
#define INCLUDE_navi_almplusplus

#include "sentence.hpp"
#include <libnavigate/alm.h>

namespace libnavigate
{

NAVI_EXTERN_CLASS(Alm_t) : public Message_t
{
public:
	static const int MaxSatellites = ALM_MAX_SATELLITES;

public:
	Alm_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Alm_t(const Message_t &msg);
	virtual ~Alm_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual int nmOfSatellites() const;
	virtual int totalNmOfMessages() const;
	virtual int messageNumber() const;

	virtual unsigned int satellitePrn(int satIdx) const;
	virtual unsigned int gpsWeek(int satIdx) const;
	virtual unsigned int svHealth(int satIdx) const;
	virtual unsigned int eccentricity(int satIdx) const;
	virtual unsigned int almanacReferenceTime(int satIdx) const;
	virtual unsigned int inclinationAngle(int satIdx) const;
	virtual unsigned int rateOfRightAscension(int satIdx) const;
	virtual unsigned int sqrtOfSemiMajorAxis(int satIdx) const;
	virtual unsigned int argumentOfPerigee(int satIdx) const;
	virtual unsigned int longitudeOfAscensionNode(int satIdx) const;
	virtual unsigned int meanAnomaly(int satIdx) const;
	virtual unsigned int clockParameter0(int satIdx) const;
	virtual unsigned int clockParameter1(int satIdx) const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setNmOfSatellites(int value);
	virtual void setTotalNmOfMessages(int value);
	virtual void setMessageNumber(int value);

	virtual void setSatellitePrn(int satIdx, unsigned int value);
	virtual void setGpsWeek(int satIdx, unsigned int value);
	virtual void setSvHealth(int satIdx, unsigned int value);
	virtual void setEccentricity(int satIdx, unsigned int value);
	virtual void setAlmanacReferenceTime(int satIdx, unsigned int value);
	virtual void setInclinationAngle(int satIdx, unsigned int value);
	virtual void setRateOfRightAscension(int satIdx, unsigned int value);
	virtual void setSqrtOfSemiMajorAxis(int satIdx, unsigned int value);
	virtual void setArgumentOfPerigee(int satIdx, unsigned int value);
	virtual void setLongitudeOfAscensionNode(int satIdx, unsigned int value);
	virtual void setMeanAnomaly(int satIdx, unsigned int value);
	virtual void setClockParameter0(int satIdx, unsigned int value);
	virtual void setClockParameter1(int satIdx, unsigned int value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct alm_t *() const;
	virtual operator struct alm_t *();
};

}

#endif // INCLUDE_navi_almplusplus

