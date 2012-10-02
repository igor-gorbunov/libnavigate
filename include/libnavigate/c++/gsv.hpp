/*
 * gsv.hpp - C++ bindings for GSV message
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

#ifndef INCLUDE_navi_gsvplusplus
#define INCLUDE_navi_gsvplusplus

#include <libnavigate/c++/sentence.hpp>
#include <libnavigate/gsv.h>

namespace libnavigate
{

NAVI_EXTERN_CLASS(Gsv_t) : public Message_t
{
public:
	static const int MaxSatellites = GSV_MAX_SATELLITES;

public:
	Gsv_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Gsv_t(const Message_t &msg);
	virtual ~Gsv_t();

public:
	virtual TalkerId_t talkerId() const;

public:
	virtual bool isOrientationValid(int satIdx) const;
	virtual bool isSnrValid(int satIdx) const;

public:
	virtual int nmOfSatellites() const;
	virtual int totalNmOfMessages() const;
	virtual int messageNumber() const;

	virtual unsigned int satelliteId(int satIdx) const;
	virtual unsigned int elevation(int satIdx) const;
	virtual unsigned int azimuth(int satIdx) const;
	virtual unsigned int snratio(int satIdx) const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setNmOfSatellites(int value);
	virtual void setTotalNmOfMessages(int value);
	virtual void setMessageNumber(int value);

	virtual void setSatelliteId(int satIdx, unsigned int value);
	virtual void setOrientation(int satIdx, unsigned int elevation,
			unsigned int azimuth);
	virtual void setSnratio(int satIdx, unsigned int value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct gsv_t *() const;
	virtual operator struct gsv_t *();
};

}

#endif // INCLUDE_navi_gsvplusplus
