#include <libnavigate/c++/rmc.hpp>

namespace libnavigate
{

void Rmc_t::setPositionFix(const PositionFix_t &fix)
{
	m_value.fix = fix.toPosition();
	m_value.vfields |= RMC_VALID_POSITION_FIX;
}

void Rmc_t::setUtc(const Utc_t &utc)
{
	m_value.utc.hour = utc.hours();
	m_value.utc.min = utc.minutes();
	m_value.utc.sec = utc.seconds();
	m_value.vfields |= RMC_VALID_UTC;
}

}

