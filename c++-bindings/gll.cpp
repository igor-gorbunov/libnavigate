#include <libnavigate/c++/gll.hpp>

namespace libnavigate
{

void Gll_t::setPositionFix(const PositionFix_t &fix)
{
	navi_set_position(fix.latitude(), fix.longitude(), &m_value.fix);
	m_value.vfields |= GLL_VALID_POSITION_FIX;
}

void Gll_t::setUtc(const Utc_t &utc)
{
	m_value.utc.hour = utc.hours();
	m_value.utc.min = utc.minutes();
	m_value.utc.sec = utc.seconds();
	m_value.vfields |= GLL_VALID_UTC;
}

}

