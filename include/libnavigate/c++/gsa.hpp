/*
 * gsa.hpp - C++ bindings for GSA message
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

#ifndef INCLUDE_navi_gsaplusplus
#define INCLUDE_navi_gsaplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(Gsa_t) : public Message_t
{
public:
	static const int MaxSatellites = 12;

public:
	Gsa_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Gsa_t(const Message_t &msg);
	virtual ~Gsa_t();

public:
	virtual TalkerId_t talkerId() const;

	virtual GsaSwitchMode_t switchMode() const;
	virtual int fixMode() const;
	virtual int satelliteId(int satIdx) const;
	virtual double pdop() const;
	virtual double hdop() const;
	virtual double vdop() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setSwitchMode(const GsaSwitchMode_t &mode);
	virtual void setFixMode(int value);
	virtual void setSatelliteId(int satIdx, int value);
	virtual void setPdop(double value);
	virtual void setHdop(double value);
	virtual void setVdop(double value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct gsa_t *() const;
	virtual operator struct gsa_t *();
};

}

#endif // INCLUDE_navi_gsaplusplus

