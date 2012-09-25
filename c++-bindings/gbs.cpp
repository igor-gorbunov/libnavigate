#include <libnavigate/c++/gbs.hpp>

namespace libnavigate
{

Gbs_t::Gbs_t(const TalkerId_t &tid) : Message_t(MessageType_t::GBS)
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.vfields = 0;
}

Gbs_t::~Gbs_t() { }

TalkerId_t Gbs_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

Utc_t Gbs_t::utc() const
	{ return Utc_t(m_value.utc.hour, m_value.utc.min, m_value.utc.sec); }

double Gbs_t::expErrInLatitude() const
	{ return m_value.experrlat; }

double Gbs_t::expErrInLongitude() const
	{ return m_value.experrlon; }

double Gbs_t::expErrInAltitude() const
	{ return m_value.experralt; }

int Gbs_t::failedSatelliteId() const
	{ return m_value.id; }

double Gbs_t::probabilityOfMissedDetection() const
	{ return m_value.probability; }

double Gbs_t::estimateOfBias() const
	{ return m_value.estimate; }

double Gbs_t::deviationOfBias() const
	{ return m_value.deviation; }

void Gbs_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Gbs_t::setUtc(const Utc_t &utc)
{
	m_value.utc.hour = utc.hours();
	m_value.utc.min = utc.minutes();
	m_value.utc.sec = utc.seconds();
}

void Gbs_t::setExpErrInLatitude(double value)
{
	m_value.experrlat = value;
	m_value.vfields |= GBS_VALID_EXPERRLATLON;
}

void Gbs_t::setExpErrInLongitude(double value)
{
	m_value.experrlon = value;
	m_value.vfields |= GBS_VALID_EXPERRLATLON;
}

void Gbs_t::setExpErrInAltitude(double value)
{
	m_value.experralt = value;
	m_value.vfields |= GBS_VALID_EXPERRALT;
}

void Gbs_t::setFailedSatelliteId(int value)
{
	m_value.id = value;
	m_value.vfields |= GBS_VALID_ID;
}

void Gbs_t::setProbabilityOfMissedDetection(double value)
{
	m_value.probability = value;
	m_value.vfields |= GBS_VALID_PROBABILITY;
}

void Gbs_t::setEstimateOfBias(double value)
{
	m_value.estimate = value;
	m_value.vfields |= GBS_VALID_ESTIMATE;
}

void Gbs_t::setDeviationOfBias(double value)
{
	m_value.deviation = value;
	m_value.vfields |= GBS_VALID_DEVIATION;
}

void Gbs_t::clearMessage()
	{ m_value.vfields = 0; }

Gbs_t::operator const void *() const
	{ return (const void *)&m_value; }

Gbs_t::operator void *()
	{ return &m_value; }

}
