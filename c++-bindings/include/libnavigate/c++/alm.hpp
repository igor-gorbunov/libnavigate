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
	virtual int totalNmOfMessages() const;
	virtual int messageNumber() const;

	virtual unsigned int satellitePrn() const;
	virtual unsigned int gpsWeek() const;
	virtual unsigned int svHealth() const;
	virtual unsigned int eccentricity() const;
	virtual unsigned int almanacReferenceTime() const;
	virtual unsigned int inclinationAngle() const;
	virtual unsigned int rateOfRightAscension() const;
	virtual unsigned int sqrtOfSemiMajorAxis() const;
	virtual unsigned int argumentOfPerigee() const;
	virtual unsigned int longitudeOfAscensionNode() const;
	virtual unsigned int meanAnomaly() const;
	virtual unsigned int clockParameter0() const;
	virtual unsigned int clockParameter1() const;

public:
	virtual bool isGpsWeekValid() const;
	virtual bool isSvHealthValid() const;
	virtual bool isEccentricityValid() const;
	virtual bool isAlmanacReferenceTimeValid() const;
	virtual bool isInclinationAngleValid() const;
	virtual bool isRateOfRightAscensionValid() const;
	virtual bool isSqrtOfSemiMajorAxisValid() const;
	virtual bool isArgumentOfPerigeeValid() const;
	virtual bool isLongitudeOfAscensionNodeValid() const;
	virtual bool isMeanAnomalyValid() const;
	virtual bool isClockParameter0Valid() const;
	virtual bool isClockParameter1Valid() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setTotalNmOfMessages(int value);
	virtual void setMessageNumber(int value);

	virtual void setSatellitePrn(unsigned int value);
	virtual void setGpsWeek(unsigned int value);
	virtual void setSvHealth(unsigned int value);
	virtual void setEccentricity(unsigned int value);
	virtual void setAlmanacReferenceTime(unsigned int value);
	virtual void setInclinationAngle(unsigned int value);
	virtual void setRateOfRightAscension(unsigned int value);
	virtual void setSqrtOfSemiMajorAxis(unsigned int value);
	virtual void setArgumentOfPerigee(unsigned int value);
	virtual void setLongitudeOfAscensionNode(unsigned int value);
	virtual void setMeanAnomaly(unsigned int value);
	virtual void setClockParameter0(unsigned int value);
	virtual void setClockParameter1(unsigned int value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct alm_t *() const;
	virtual operator struct alm_t *();
};

}

#endif // INCLUDE_navi_almplusplus
