#include <libnavigate/c++/alm.hpp>

namespace libnavigate
{

void Alm_t::setSatellitePrn(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].satelliteprn = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_SATELLITEPRN;
}

void Alm_t::setGpsWeek(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].gpsweek = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_GPSWEEK;
}

void Alm_t::setSvHealth(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].svhealth = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_SVHEALTH;
}

void Alm_t::setEccentricity(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].e = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_E;
}

void Alm_t::setAlmanacReferenceTime(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].toa = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_TOA;
}

void Alm_t::setInclinationAngle(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].sigmai = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_SIGMAI;
}

void Alm_t::setRateOfRightAscension(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].omegadot = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_OMEGADOT;
}

void Alm_t::setSqrtOfSemiMajorAxis(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].sqrtsemiaxis = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_SQRTSEMIAXIS;
}

void Alm_t::setArgumentOfPerigee(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].omega = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_OMEGA;
}

void Alm_t::setLongitudeOfAscensionNode(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].omega0 = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_OMEGA0;
}

void Alm_t::setMeanAnomaly(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].m0 = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_M0;
}

void Alm_t::setClockParameter0(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].af0;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_AF0;
}

void Alm_t::setClockParameter1(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].af1;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_AF1;
}

}

