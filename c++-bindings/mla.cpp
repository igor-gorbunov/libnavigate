#include <libnavigate/c++/mla.hpp>

namespace libnavigate
{

Mla_t::Mla_t(const TalkerId_t &tid) : Message_t(MessageType_t::MLA)
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.nmsatellites = 0;
	for (int i = 0; i < MaxSatellites; i++)
	{
		m_value.almlist[i].vfields = 0;
	}
	m_value.totalnm = m_value.msgnm = 0;
}

Mla_t::~Mla_t() { }

TalkerId_t Mla_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

int Mla_t::nmOfSatellites() const
	{ return m_value.nmsatellites; }

int Mla_t::totalNmOfMessages() const
	{ return m_value.totalnm; }

int Mla_t::messageNumber() const
	{ return m_value.msgnm; }

unsigned int Mla_t::satelliteSlot(int satIdx) const
	{ return m_value.almlist[satIdx].satslot; }

unsigned int Mla_t::dayCount(int satIdx) const
	{ return m_value.almlist[satIdx].daycount; }

unsigned int Mla_t::svHealth(int satIdx) const
	{ return m_value.almlist[satIdx].svhealth; }

unsigned int Mla_t::eccentricity(int satIdx) const
	{ return m_value.almlist[satIdx].e; }

unsigned int Mla_t::rateOfChangeOfDraconicTime(int satIdx) const
	{ return m_value.almlist[satIdx].dot; }

unsigned int Mla_t::argumentOfPerigee(int satIdx) const
	{ return m_value.almlist[satIdx].omega; }

unsigned int Mla_t::systemTimescaleCorrection_High(int satIdx) const
	{ return m_value.almlist[satIdx].tauc_high; }

unsigned int Mla_t::correctionToDraconicTime(int satIdx) const
	{ return m_value.almlist[satIdx].deltat; }

unsigned int Mla_t::timeOfAscensionNode(int satIdx) const
	{ return m_value.almlist[satIdx].t; }

unsigned int Mla_t::longitudeOfAscensionNode(int satIdx) const
	{ return m_value.almlist[satIdx].lambda; }

unsigned int Mla_t::correctionToInclinationAngle(int satIdx) const
	{ return m_value.almlist[satIdx].deltai; }

unsigned int Mla_t::systemTimescaleCorrection_Low(int satIdx) const
	{ return m_value.almlist[satIdx].tauc_low; }

unsigned int Mla_t::courseValueOfTimescaleShift(int satIdx) const
	{ return m_value.almlist[satIdx].taun; }

void Mla_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Mla_t::setNmOfSatellites(int value)
	{ m_value.nmsatellites = value; }

void Mla_t::setTotalNmOfMessages(int value)
	{ m_value.totalnm = value; }

void Mla_t::setMessageNumber(int value)
	{ m_value.msgnm = value; }

void Mla_t::setSatelliteSlot(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].satslot = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_SATSLOT;
}

void Mla_t::setDayCount(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].daycount = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_DAYCOUNT;
}

void Mla_t::setSvHealth(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].svhealth = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_SVHEALTH;
}

void Mla_t::setEccentricity(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].e = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_E;
}

void Mla_t::setRateOfChangeOfDraconicTime(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].dot = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_DOT;
}

void Mla_t::setArgumentOfPerigee(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].omega = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_OMEGA;
}

void Mla_t::setSystemTimescaleCorrection_High(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].tauc_high = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_TAUC;
}

void Mla_t::setCorrectionToDraconicTime(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].deltat = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_DELTAT;
}

void Mla_t::setTimeOfAscensionNode(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].t = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_T;
}

void Mla_t::setLongitudeOfAscensionNode(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].lambda = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_LAMBDA;
}

void Mla_t::setCorrectionToInclinationAngle(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].deltai = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_DELTAI;
}

void Mla_t::setSystemTimescaleCorrection_Low(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].tauc_low = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_TAUC;
}

void Mla_t::setCourseValueOfTimescaleShift(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].taun = value;
	m_value.almlist[satIdx].vfields |= GLOALM_VALID_TAUN;
}

void Mla_t::clearMessage()
{
	m_value.nmsatellites = 0;
	for (int i = 0; i < MaxSatellites; i++)
	{
		m_value.almlist[i].vfields = 0;
	}
}

Mla_t::operator const void *() const
	{ return (const void *)&m_value; }

Mla_t::operator void *()
	{ return &m_value; }

}

