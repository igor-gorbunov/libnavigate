#include <libnavigate/c++/gll.hpp>

namespace libnavigate
{

Gll_t::Gll_t(const TalkerId_t &tid) : Message_t(MessageType_t::GLL)
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.vfields = 0;
}

Gll_t::~Gll_t() { }

TalkerId_t Gll_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

PositionFix_t Gll_t::positionFix() const
	{ return PositionFix_t::fromPosition(&m_value.fix); }

Utc_t Gll_t::utc() const
	{ return Utc_t(m_value.utc.hour, m_value.utc.min, m_value.utc.sec); }

Status_t Gll_t::status() const
	{ return Status_t::fromStatusCode(m_value.status); }

ModeIndicator_t Gll_t::modeIndicator() const
	{ return ModeIndicator_t::fromModeIndCode(m_value.mi); }

void Gll_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Gll_t::setPositionFix(const PositionFix_t &fix)
{
	m_value.fix = fix.toPosition();
	m_value.vfields |= GLL_VALID_POSITION_FIX;
}

void Gll_t::setUtc(const Utc_t &utc)
{
	m_value.utc.hour = utc.hours();
	m_value.utc.min = utc.minutes();
	m_value.utc.sec = utc.seconds();
	m_value.vfields |= GLL_VALID_UTC;
}

void Gll_t::setStatus(const Status_t &status)
	{ m_value.status = status.toStatusCode(); }

void Gll_t::setModeIndicator(const ModeIndicator_t &mi)
	{ m_value.mi = mi.toModeIndCode(); }

void Gll_t::clearMessage()
	{ m_value.vfields = 0; }

Gll_t::operator const void *() const
	{ return (const void *)&m_value; }

Gll_t::operator void *()
	{ return &m_value; }

}

