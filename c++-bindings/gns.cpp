#include <libnavigate/c++/gns.hpp>

namespace libnavigate
{

Gns_t::Gns_t(const TalkerId_t &tid) : Message_t(MessageType_t::GNS)
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.vfields = 0;
}

Gns_t::~Gns_t() { }

TalkerId_t Gns_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

Utc_t Gns_t::utc() const
	{ return Utc_t(m_value.utc.hour, m_value.utc.min, m_value.utc.sec); }

PositionFix_t Gns_t::positionFix() const
	{ return PositionFix_t::fromPosition(&m_value.fix); }

ModeIndicatorArray_t Gns_t::modeIndicatorArray() const
	{ return ModeIndicatorArray_t::fromModeIndicators(m_value.mi); }

int Gns_t::nmOfSatellites() const
	{ return m_value.totalsats; }

double Gns_t::hdop() const
	{ return m_value.hdop; }

double Gns_t::antennaAltitude() const
	{ return m_value.antaltitude; }

double Gns_t::geoidalSeparation() const
	{ return m_value.geoidalsep; }

int Gns_t::ageOfDiffData() const
	{ return m_value.diffage; }

int Gns_t::diffReferenceStationId() const
	{ return m_value.id; }

void Gns_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Gns_t::setUtc(const Utc_t &utc)
{
	m_value.utc.hour = utc.hours();
	m_value.utc.min = utc.minutes();
	m_value.utc.sec = utc.seconds();
	m_value.vfields |= GNS_VALID_UTC;
}

void Gns_t::setPositionFix(const PositionFix_t &fix)
{
	m_value.fix = fix.toPosition();
	m_value.vfields |= GNS_VALID_POSITION_FIX;
}

void Gns_t::setModeIndicatorArray(const ModeIndicatorArray_t &modeArray)
	{ modeArray.toModeIndicators(m_value.mi); }

void Gns_t::setNmOfSatellites(int value)
{
	m_value.totalsats = value;
	m_value.vfields |= GNS_VALID_TOTALNMOFSATELLITES;
}

void Gns_t::setHdop(double value)
{
	m_value.hdop = value;
	m_value.vfields |= GNS_VALID_HDOP;
}

void Gns_t::setAntennaAltitude(double value)
{
	m_value.antaltitude = value;
	m_value.vfields |= GNS_VALID_ANTENNAALTITUDE;
}

void Gns_t::setGeoidalSeparation(double value)
{
	m_value.geoidalsep = value;
	m_value.vfields |= GNS_VALID_GEOIDALSEP;
}

void Gns_t::setAgeOfDiffData(int value)
{
	m_value.diffage = value;
	m_value.vfields |= GNS_VALID_AGEOFDIFFDATA;
}

void Gns_t::setDiffReferenceStationId(int value)
{
	m_value.id = value;
	m_value.vfields |= GNS_VALID_DIFFREFSTATIONID;
}

void Gns_t::clearMessage()
	{ m_value.vfields = 0; }

Gns_t::operator const void *() const
	{ return (const void *)&m_value; }

Gns_t::operator void *()
	{ return &m_value; }

}
