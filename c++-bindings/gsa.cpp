#include <libnavigate/c++/gsa.hpp>

namespace libnavigate
{

Gsa_t::Gsa_t(const TalkerId_t &tid) : Message_t(MessageType_t::GSA)
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.vfields = 0;

	for (int i = 0; i < MaxSatellites; i++)
	{
		m_value.satellites[i].notnull = 0;
	}
}

Gsa_t::~Gsa_t() { }

TalkerId_t Gsa_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

GsaSwitchMode_t Gsa_t::switchMode() const
	{ return GsaSwitchMode_t::fromSwitchModeCode(m_value.switchmode); }

int Gsa_t::fixMode() const
	{ return m_value.fixmode; }

int Gsa_t::satelliteId(int satIdx) const
	{ return m_value.satellites[satIdx].id; }

double Gsa_t::pdop() const
	{ return m_value.pdop; }

double Gsa_t::hdop() const
	{ return m_value.hdop; }

double Gsa_t::vdop() const
	{ return m_value.vdop; }

void Gsa_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Gsa_t::setSwitchMode(const GsaSwitchMode_t &mode)
{
	m_value.switchmode = mode.toSwitchModeCode();
	m_value.vfields |= GSA_VALID_SWITCHMODE;
}

void Gsa_t::setFixMode(int value)
{
	m_value.fixmode = value;
	m_value.vfields |= GSA_VALID_FIXMODE;
}

void Gsa_t::setSatelliteId(int satIdx, int value)
{
	m_value.satellites[satIdx].notnull = 1;
	m_value.satellites[satIdx].id = value;
}

void Gsa_t::setPdop(double value)
{
	m_value.pdop = value;
	m_value.vfields |= GSA_VALID_PDOP;
}

void Gsa_t::setHdop(double value)
{
	m_value.hdop = value;
	m_value.vfields |= GSA_VALID_HDOP;
}

void Gsa_t::setVdop(double value)
{
	m_value.vdop = value;
	m_value.vfields |= GSA_VALID_VDOP;
}

void Gsa_t::clearMessage()
{
	m_value.vfields = 0;

	for (int i = 0; i < MaxSatellites; i++)
	{
		m_value.satellites[i].notnull = 0;
	}
}

Gsa_t::operator const void *() const
	{ return (const void *)&m_value; }

Gsa_t::operator void *()
	{ return &m_value; }

}
