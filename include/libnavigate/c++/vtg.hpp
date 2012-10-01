/*
 * vtg.hpp - C++ bindings for VTG message
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

#ifndef INCLUDE_navi_vtgplusplus
#define INCLUDE_navi_vtgplusplus

#include <libnavigate/c++/sentence.hpp>

namespace libnavigate
{

#include <libnavigate/vtg.h>

NAVI_EXTERN_CLASS(Vtg_t) : public Message_t
{
public:
	Vtg_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Vtg_t(const Message_t &msg);
	virtual ~Vtg_t();

public:
	virtual TalkerId_t talkerId() const;

public:
	virtual bool isCourseTrueValid() const;
	virtual bool isCourseMagneticValid() const;
	virtual bool isSpeedValid() const;

public:
	virtual double courseTrue() const;
	virtual double courseMagnetic() const;
	virtual double speed() const;
	virtual ModeIndicator_t modeIndicator() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setCourseTrue(double value);
	virtual void setCourseMagnetic(double value);
	virtual void setSpeed(double value);
	virtual void setModeIndicator(const ModeIndicator_t &mi);

public:
	virtual void clearMessage();

public:
	virtual operator const struct vtg_t *() const;
	virtual operator struct vtg_t *();
};

}

#endif // INCLUDE_navi_vtgplusplus

