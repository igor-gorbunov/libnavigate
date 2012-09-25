#include <libnavigate/c++/vtg.hpp>

namespace libnavigate
{

Vtg_t::Vtg_t(const TalkerId_t &tid) : Message_t(MessageType_t::VTG)
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.vfields = 0;
}

Vtg_t::~Vtg_t() { }

TalkerId_t Vtg_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

void Vtg_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Vtg_t::clearMessage()
	{ m_value.vfields = 0; }

Vtg_t::operator const void *() const
	{ return (const void *)&m_value; }

Vtg_t::operator void *()
	{ return &m_value; }

double Vtg_t::courseTrue() const
	{ return m_value.courseTrue; }

double Vtg_t::courseMagnetic() const
	{ return m_value.courseMagn; }

double Vtg_t::speed() const
	{ return m_value.speed; }

ModeIndicator_t Vtg_t::modeIndicator() const
	{ return ModeIndicator_t::fromModeIndCode(m_value.mi); }

void Vtg_t::setCourseTrue(double value)
{
	m_value.courseTrue = value;
	m_value.vfields |= VTG_VALID_COURSETRUE;
}

void Vtg_t::setCourseMagnetic(double value)
{
	m_value.courseMagn = value;
	m_value.vfields |= VTG_VALID_COURSEMAGN;
}

void Vtg_t::setSpeed(double value)
{
	m_value.speed = value;
	m_value.vfields |= VTG_VALID_SPEED;
}

void Vtg_t::setModeIndicator(const ModeIndicator_t &mi)
{
	m_value.mi = mi.toModeIndCode();
}

}
