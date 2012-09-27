#include <libnavigate/c++/gsv.hpp>

namespace libnavigate
{

Gsv_t::Gsv_t(const TalkerId_t &tid) : Message_t(MessageType_t::GSV)
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.nmsatellites = 0;
	for (int i = 0; i < MaxSatellites; i++)
	{
		m_value.info[i].vfields = 0;
	}
	m_value.totalnm = m_value.msgnm = 0;
}

Gsv_t::~Gsv_t() { }

TalkerId_t Gsv_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

void Gsv_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Gsv_t::clearMessage()
{
	m_value.nmsatellites = 0;
	for (int i = 0; i < MaxSatellites; i++)
	{
		m_value.info[i].vfields = 0;
	}
}

Gsv_t::operator const void *() const
	{ return (const void *)&m_value; }

Gsv_t::operator void *()
	{ return &m_value; }

int Gsv_t::nmOfSatellites() const
	{ return m_value.nmsatellites; }

int Gsv_t::totalNmOfMessages() const
	{ return m_value.totalnm; }

int Gsv_t::messageNumber() const
	{ return m_value.msgnm; }

void Gsv_t::setNmOfSatellites(int value)
	{ m_value.nmsatellites = value; }

void Gsv_t::setTotalNmOfMessages(int value)
	{ m_value.totalnm = value; }

void Gsv_t::setMessageNumber(int value)
	{ m_value.msgnm = value; }

unsigned int Gsv_t::satelliteId(int satIdx) const
	{ return m_value.info[satIdx].id; }

unsigned int Gsv_t::elevation(int satIdx) const
	{ return m_value.info[satIdx].elevation; }

unsigned int Gsv_t::azimuth(int satIdx) const
	{ return m_value.info[satIdx].azimuth; }

unsigned int Gsv_t::snratio(int satIdx) const
	{ return m_value.info[satIdx].snr; }

void Gsv_t::setSatelliteId(int satIdx, unsigned int value)
{
	m_value.info[satIdx].id = value;
}

void Gsv_t::setOrientation(int satIdx, unsigned int elevation,
	unsigned int azimuth)
{
	m_value.info[satIdx].elevation = elevation;
	m_value.info[satIdx].azimuth = azimuth;
	m_value.info[satIdx].vfields |= SATINFO_VALID_ORIENTATION;
}

void Gsv_t::setSnratio(int satIdx, unsigned int value)
{
	m_value.info[satIdx].snr = value;
	m_value.info[satIdx].vfields |= SATINFO_VALID_SNR;
}

}
