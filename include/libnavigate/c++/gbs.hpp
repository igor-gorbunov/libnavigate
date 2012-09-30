/*
 * gbs.hpp - C++ bindings for GBS message
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

#ifndef INCLUDE_navi_gbsplusplus
#define INCLUDE_navi_gbsplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(Gbs_t) : public Message_t
{
public:
	Gbs_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Gbs_t(const Message_t &msg);
	virtual ~Gbs_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual Utc_t utc() const;
	virtual double expErrInLatitude() const;
	virtual double expErrInLongitude() const;
	virtual double expErrInAltitude() const;
	virtual int failedSatelliteId() const;
	virtual double probabilityOfMissedDetection() const;
	virtual double estimateOfBias() const;
	virtual double deviationOfBias() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setUtc(const Utc_t &utc);
	virtual void setExpErrInLatitude(double value);
	virtual void setExpErrInLongitude(double value);
	virtual void setExpErrInAltitude(double value);
	virtual void setFailedSatelliteId(int value);
	virtual void setProbabilityOfMissedDetection(double value);
	virtual void setEstimateOfBias(double value);
	virtual void setDeviationOfBias(double value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct gbs_t *() const;
	virtual operator struct gbs_t *();
};

}

#endif // INCLUDE_navi_gbsplusplus

