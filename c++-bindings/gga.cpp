#include <libnavigate/c++/gga.hpp>

namespace libnavigate
{

Gga_t::Gga_t(const TalkerId_t &tid) : Message_t(MessageType_t::GGA)
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.vfields = 0;
}

Gga_t::~Gga_t() { }

TalkerId_t Gga_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

Utc_t Gga_t::utc() const
	{ return Utc_t(m_value.utc.hour, m_value.utc.min, m_value.utc.sec); }

PositionFix_t Gga_t::positionFix() const
	{ return PositionFix_t::fromPosition(&m_value.fix); }

GpsQualityIndicator_t Gga_t::qualityIndicator() const
	{ return GpsQualityIndicator_t::fromQualityCode(m_value.gpsindicator); }

int Gga_t::nmOfSatellites() const
	{ return m_value.nmsatellites; }

double Gga_t::hdop() const
	{ return m_value.hdop; }

double Gga_t::antennaAltitude() const
	{ return m_value.antaltitude; }

double Gga_t::geoidalSeparation() const
	{ return m_value.geoidalsep; }

int Gga_t::ageOfDiffData() const
	{ return m_value.diffage; }

int Gga_t::diffReferenceStationId() const
	{ return m_value.id; }

void Gga_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Gga_t::setUtc(const Utc_t &utc)
{
	m_value.utc.hour = utc.hours();
	m_value.utc.min = utc.minutes();
	m_value.utc.sec = utc.seconds();
	m_value.vfields |= GGA_VALID_UTC;
}

void Gga_t::setPositionFix(const PositionFix_t &fix)
{
	m_value.fix = fix.toPosition();
	m_value.vfields |= GGA_VALID_FIX;
}

void Gga_t::setQualityIndicator(const GpsQualityIndicator_t &qi)
	{ m_value.gpsindicator = qi.toQualityCode(); }

void Gga_t::setNmOfSatellites(int value)
{
	m_value.nmsatellites = value;
	m_value.vfields |= GGA_VALID_NMSATELLITES;
}

void Gga_t::setHdop(double value)
{
	m_value.hdop = value;
	m_value.vfields |= GGA_VALID_HDOP;
}

void Gga_t::setAntennaAltitude(double value)
{
	m_value.antaltitude = value;
	m_value.vfields |= GGA_VALID_ANTALTITUDE;
}

void Gga_t::setGeoidalSeparation(double value)
{
	m_value.geoidalsep = value;
	m_value.vfields |= GGA_VALID_GEOIDALSEP;
}

void Gga_t::setAgeOfDiffData(int value)
{
	m_value.diffage = value;
	m_value.vfields |= GGA_VALID_DIFFAGE;
}

void Gga_t::setDiffReferenceStationId(int value)
{
	m_value.id = value;
	m_value.vfields |= GGA_VALID_ID;
}

void Gga_t::clearMessage()
	{ m_value.vfields = 0; }

Gga_t::operator const void *() const
	{ return (const void *)&m_value; }

Gga_t::operator void *()
	{ return &m_value; }

}
