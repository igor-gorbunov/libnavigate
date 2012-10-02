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

#include <libnavigate/c++/sentence.hpp>
#include <libnavigate/mla.h>

namespace libnavigate
{

NAVI_EXTERN_CLASS(Mla_t) : public Message_t
{
public:
	static const int MaxSatellites = 32;

public:
	Mla_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Mla_t(const Message_t &msg);
	virtual ~Mla_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual int nmOfSatellites() const;
	virtual int totalNmOfMessages() const;
	virtual int messageNumber() const;

public:
	virtual bool isSatelliteSlotValid(int satIdx) const;
	virtual bool isDayCountValid(int satIdx) const;
	virtual bool isSvHealthValid(int satIdx) const;
	virtual bool isEccentricityValid(int satIdx) const;
	virtual bool isRateOfChangeOfDraconicTimeValid(int satIdx) const;
	virtual bool isArgumentOfPerigeeValid(int satIdx) const;
	virtual bool isSystemTimescaleCorrectionValid(int satIdx) const;
	virtual bool isCorrectionToDraconicTimeValid(int satIdx) const;
	virtual bool isTimeOfAscensionNodeValid(int satIdx) const;
	virtual bool isLongitudeOfAscensionNodeValid(int satIdx) const;
	virtual bool isCorrectionToInclinationAngleValid(int satIdx) const;
	virtual bool isCourseValueOfTimescaleShiftValid(int satIdx) const;

public:

	virtual unsigned int satelliteSlot(int satIdx) const;
	virtual unsigned int dayCount(int satIdx) const;
	virtual unsigned int svHealth(int satIdx) const;
	virtual unsigned int eccentricity(int satIdx) const;
	virtual unsigned int rateOfChangeOfDraconicTime(int satIdx) const;
	virtual unsigned int argumentOfPerigee(int satIdx) const;
	virtual unsigned int systemTimescaleCorrection_High(int satIdx) const;
	virtual unsigned int correctionToDraconicTime(int satIdx) const;
	virtual unsigned int timeOfAscensionNode(int satIdx) const;
	virtual unsigned int longitudeOfAscensionNode(int satIdx) const;
	virtual unsigned int correctionToInclinationAngle(int satIdx) const;
	virtual unsigned int systemTimescaleCorrection_Low(int satIdx) const;
	virtual unsigned int courseValueOfTimescaleShift(int satIdx) const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setNmOfSatellites(int value);
	virtual void setTotalNmOfMessages(int value);
	virtual void setMessageNumber(int value);

	virtual void setSatelliteSlot(int satIdx, unsigned int value);
	virtual void setDayCount(int satIdx, unsigned int value);
	virtual void setSvHealth(int satIdx, unsigned int value);
	virtual void setEccentricity(int satIdx, unsigned int value);
	virtual void setRateOfChangeOfDraconicTime(int satIdx, unsigned int value);
	virtual void setArgumentOfPerigee(int satIdx, unsigned int value);
	virtual void setSystemTimescaleCorrection_High(int satIdx, unsigned int value);
	virtual void setCorrectionToDraconicTime(int satIdx, unsigned int value);
	virtual void setTimeOfAscensionNode(int satIdx, unsigned int value);
	virtual void setLongitudeOfAscensionNode(int satIdx, unsigned int value);
	virtual void setCorrectionToInclinationAngle(int satIdx, unsigned int value);
	virtual void setSystemTimescaleCorrection_Low(int satIdx, unsigned int value);
	virtual void setCourseValueOfTimescaleShift(int satIdx, unsigned int value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct mla_t *() const;
	virtual operator struct mla_t *();
};

}

#endif // INCLUDE_navi_mlaplusplus

