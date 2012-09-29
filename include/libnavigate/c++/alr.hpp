/*
 * alr.hpp - C++ bindings for ALR message
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

#ifndef INCLUDE_navi_alrplusplus
#define INCLUDE_navi_alrplusplus

#include <libnavigate/c++/sentence.hpp>
#include <string>

namespace libnavigate
{

#include <libnavigate/alr.h>

NAVI_EXTERN_CLASS(class, Alr_t) : public Message_t
{
public:
	Alr_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Alr_t();

public:
	virtual TalkerId_t talkerId() const;

	virtual Utc_t utc() const;
	virtual int alarmId() const;
	virtual Status_t condition() const;
	virtual Status_t acknowledgeState() const;
	virtual std::string description() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setUtc(const Utc_t &value);
	virtual void setAlarmId(int value);
	virtual void setCondition(const Status_t &value);
	virtual void setAcknowledgeState(const Status_t &value);
	virtual void setDescription(const std::string &value);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct alr_t m_value;
};

}

#endif // INCLUDE_navi_alrplusplus
