/*
 * gll.hpp - C++ bindings for GLL message
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

#ifndef INCLUDE_navi_gllplusplus
#define INCLUDE_navi_gllplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(Gll_t) : public Message_t
{
public:
	Gll_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Gll_t(const Message_t &msg);
	virtual ~Gll_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual PositionFix_t positionFix() const;
	virtual Utc_t utc() const;
	virtual Status_t status() const;
	virtual ModeIndicator_t modeIndicator() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setPositionFix(const PositionFix_t &fix);
	virtual void setUtc(const Utc_t &utc);
	virtual void setStatus(const Status_t &status);
	virtual void setModeIndicator(const ModeIndicator_t &mi);

public:
	virtual void clearMessage();

public:
	virtual operator const struct gll_t *() const;
	virtual operator struct gll_t *();
};

}

#endif // INCLUDE_navi_gllplusplus

