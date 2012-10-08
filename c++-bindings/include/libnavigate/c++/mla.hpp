/*
 * mla.hpp - C++ bindings for MLA message
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

#ifndef INCLUDE_navi_mlaplusplus
#define INCLUDE_navi_mlaplusplus

#include "sentence.hpp"
#include <libnavigate/mla.h>

namespace libnavigate
{

NAVI_EXTERN_CLASS(Mla_t) : public Message_t
{
public:
	static const int MaxSatellites = MLA_MAX_SATELLITES;

public:
	Mla_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Mla_t(const Message_t &msg);
	virtual ~Mla_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual int totalNmOfMessages() const;
	virtual int messageNumber() const;

public:
	virtual unsigned int satelliteSlot() const;
	virtual unsigned int dayCount() const;
	virtual unsigned int svHealth() const;
	virtual unsigned int eccentricity() const;
	virtual unsigned int rateOfChangeOfDraconicTime() const;
	virtual unsigned int argumentOfPerigee() const;
	virtual unsigned int systemTimescaleCorrection_High() const;
	virtual unsigned int correctionToDraconicTime() const;
	virtual unsigned int timeOfAscensionNode() const;
	virtual unsigned int longitudeOfAscensionNode() const;
	virtual unsigned int correctionToInclinationAngle() const;
	virtual unsigned int systemTimescaleCorrection_Low() const;
	virtual unsigned int courseValueOfTimescaleShift() const;

public:
	virtual bool isDayCountValid() const;
	virtual bool isSvHealthValid() const;
	virtual bool isEccentricityValid() const;
	virtual bool isRateOfChangeOfDraconicTimeValid() const;
	virtual bool isArgumentOfPerigeeValid() const;
	virtual bool isSystemTimescaleCorrectionValid() const;
	virtual bool isCorrectionToDraconicTimeValid() const;
	virtual bool isTimeOfAscensionNodeValid() const;
	virtual bool isLongitudeOfAscensionNodeValid() const;
	virtual bool isCorrectionToInclinationAngleValid() const;
	virtual bool isCourseValueOfTimescaleShiftValid() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setTotalNmOfMessages(int value);
	virtual void setMessageNumber(int value);

	virtual void setSatelliteSlot(unsigned int value);
	virtual void setDayCount(unsigned int value);
	virtual void setSvHealth(unsigned int value);
	virtual void setEccentricity(unsigned int value);
	virtual void setRateOfChangeOfDraconicTime(unsigned int value);
	virtual void setArgumentOfPerigee(unsigned int value);
	virtual void setSystemTimescaleCorrection_High(unsigned int value);
	virtual void setCorrectionToDraconicTime(unsigned int value);
	virtual void setTimeOfAscensionNode(unsigned int value);
	virtual void setLongitudeOfAscensionNode(unsigned int value);
	virtual void setCorrectionToInclinationAngle(unsigned int value);
	virtual void setSystemTimescaleCorrection_Low(unsigned int value);
	virtual void setCourseValueOfTimescaleShift(unsigned int value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct mla_t *() const;
	virtual operator struct mla_t *();
};

}

#endif // INCLUDE_navi_mlaplusplus
