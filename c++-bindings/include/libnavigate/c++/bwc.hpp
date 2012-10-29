/*
 * bwc.hpp - C++ bindings for BWC message
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

#ifndef INCLUDE_navi_bwcplusplus
#define INCLUDE_navi_bwcplusplus

#include "sentence.hpp"
#include <libnavigate/bwc.h>
#include <string>

namespace libnavigate
{

NAVI_EXTERN_CLASS(Bwc_t) : public Message_t
{
public:
	Bwc_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Bwc_t(const Message_t &msg);
	virtual ~Bwc_t();

public:
	virtual TalkerId_t talkerId() const;

	virtual Utc_t utc() const;
	virtual PositionFix_t waypointFix() const;
	virtual Offset_t bearingTrue() const;
	virtual Offset_t bearingMagnetic() const;
	virtual double distance() const;
	virtual std::string waypointId() const;
	virtual ModeIndicator_t modeIndicator() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setUtc(const Utc_t &value);
	virtual void setWaypointFix(const PositionFix_t &value);
	virtual void setBearingTrue(const Offset_t &value);
	virtual void setBearingMagnetic(const Offset_t &value);
	virtual void setDistance(double value);
	virtual void setWaypointId(const std::string &value);
	virtual void setModeIndicator(const ModeIndicator_t &value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct bwc_t *() const;
	virtual operator struct bwc_t *();
};

}

#endif // INCLUDE_navi_bwcplusplus
