#include <libnavigate/c++/grs.hpp>

namespace libnavigate
{

Grs_t::Grs_t(const TalkerId_t &tid) : Message_t(MessageType_t::GRS)
{
	m_value.tid = tid.toTalkerIdCode();

	for (int i = 0; i < MaxSatellites; i++)
	{
		m_value.residuals[i].notnull = 0;
	}
}

Grs_t::~Grs_t() { }

TalkerId_t Grs_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

Utc_t Grs_t::utc() const
	{ return Utc_t(m_value.utc.hour, m_value.utc.min, m_value.utc.sec); }

int Grs_t::mode() const
	{ return m_value.mode; }

double Grs_t::residual(int satIdx) const
	{ return m_value.residuals[satIdx].residual; }

void Grs_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Grs_t::setUtc(const Utc_t &utc)
{
	m_value.utc.hour = utc.hours();
	m_value.utc.min = utc.minutes();
	m_value.utc.sec = utc.seconds();
}

void Grs_t::setMode(int mode)
	{ m_value.mode = mode; }

void Grs_t::setResidual(int satIdx, double value)
{
	m_value.residuals[satIdx].notnull = 1;
	m_value.residuals[satIdx].residual = value;
}

void Grs_t::clearMessage()
{
	for (int i = 0; i < MaxSatellites; i++)
	{
		m_value.residuals[i].notnull = 0;
	}
}

Grs_t::operator const void *() const
	{ return (const void *)&m_value; }

Grs_t::operator void *()
	{ return &m_value; }

}
