#include <libnavigate/c++/zda.hpp>

namespace libnavigate
{

Zda_t::Zda_t(const TalkerId_t &tid) : Message_t(MessageType_t::ZDA)
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.vfields = 0;
}

Zda_t::~Zda_t() { }

TalkerId_t Zda_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

Utc_t Zda_t::utc() const
	{ return Utc_t(m_value.utc.hour, m_value.utc.min, m_value.utc.sec); }

Date_t Zda_t::date() const
	{ return Date_t(m_value.date.year, m_value.date.month, m_value.date.day); }

int Zda_t::localZoneOffset() const
	{ return m_value.lzoffset; }

void Zda_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Zda_t::setUtc(const Utc_t &utc)
{
	m_value.utc.hour = utc.hours();
	m_value.utc.min = utc.minutes();
	m_value.utc.sec = utc.seconds();
	m_value.vfields |= ZDA_VALID_UTC;
}

void Zda_t::setDate(const Date_t &date)
{
	m_value.date = date.toDate();
	m_value.vfields |= ZDA_VALID_DAY | ZDA_VALID_MONTH | ZDA_VALID_YEAR;
}

void Zda_t::setLocalZoneOffset(int value)
{
	m_value.lzoffset = value;
	m_value.vfields |= ZDA_VALID_LOCALZONE;
}

void Zda_t::clearMessage()
	{ m_value.vfields = 0; }

Zda_t::operator const void *() const
	{ return (const void *)&m_value; }

Zda_t::operator void *()
	{ return &m_value; }

}
