/*
 * grs.hpp - C++ bindings for GRS message
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

#ifndef INCLUDE_navi_grsplusplus
#define INCLUDE_navi_grsplusplus

#include <libnavigate/c++/sentence.hpp>
#include <libnavigate/grs.h>

namespace libnavigate
{

NAVI_EXTERN_CLASS(Grs_t) : public Message_t
{
public:
	static const int MaxSatellites = GRS_MAX_SATELLITES;

public:
	Grs_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	Grs_t(const Message_t &msg);
	virtual ~Grs_t();

public:
	virtual TalkerId_t talkerId() const;

public:
	virtual bool isResidualValid(int satIdx) const;

public:
	virtual Utc_t utc() const;
	virtual int mode() const;
	virtual double residual(int satIdx) const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setUtc(const Utc_t &utc);
	virtual void setMode(int mode);
	virtual void setResidual(int satIdx, double value);

public:
	virtual void clearMessage();

public:
	virtual operator const struct grs_t *() const;
	virtual operator struct grs_t *();
};

}

#endif // INCLUDE_navi_grsplusplus
