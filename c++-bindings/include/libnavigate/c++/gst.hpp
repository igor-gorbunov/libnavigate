/*
 * gst.hpp - C++ bindings for GST message
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

#ifndef INCLUDE_navi_gstplusplus
#define INCLUDE_navi_gstplusplus

#include "sentence.hpp"
#include <libnavigate/gst.h>

namespace libnavigate
{

NAVI_EXTERN_CLASS(Gst_t) : public Message_t
{
public:
	Gst_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Gst_t(const Message_t &msg);
	virtual ~Gst_t();

public:
	virtual TalkerId_t talkerId() const;

public:
	virtual bool isRmsValid() const;
	virtual bool isStdDeviationOfEllipseValid() const;
	virtual bool isStdDeviationOfPositionValid() const;
	virtual bool isStdDevofAltitudeValid() const;

public:
	virtual Utc_t utc() const;
	virtual double rmsOfStandardDeviation() const;
	virtual double deviationOfSemiMajorAxis() const;
	virtual double deviationOfSemiMinorAxis() const;
	virtual double orientationOfSemiMajorAxis() const;
	virtual double deviationOfLatitudeError() const;
	virtual double deviationOfLongitudeError() const;
	virtual double deviationOfAltitudeError() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setUtc(const Utc_t &utc);
	virtual void setRmsOfStandardDeviation(double value);
	virtual void setDeviationOfSemiMajorAxis(double value);
	virtual void setDeviationOfSemiMinorAxis(double value);
	virtual void setOrientationOfSemiMajorAxis(double value);
	virtual void setDeviationOfLatitudeError(double value);
	virtual void setDeviationOfLongitudeError(double value);
	virtual void setDeviationOfAltitudeError(double value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct gst_t *() const;
	virtual operator struct gst_t *();
};

}

#endif // INCLUDE_navi_gstplusplus
