#ifndef INCLUDE_navi_rmcplusplus
#define INCLUDE_navi_rmcplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Rmc_t) : public Message_t
{
public:
	Rmc_t(const TalkerId_t &tid = TalkerId_t::Unknown) :
		Message_t(MessageType_t::RMC)
	{
		m_value.tid = tid.toTalkerIdCode();
	}

	virtual ~Rmc_t() { }

public:
	virtual TalkerId_t talkerId() const
		{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

	virtual Utc_t utc() const
		{ return Utc_t(m_value.utc.hour, m_value.utc.min, m_value.utc.sec); }

	virtual Status_t status() const
		{ return Status_t::fromStatusCode(m_value.status); }

	virtual PositionFix_t positionFix() const
		{ return PositionFix_t::fromPosition(&m_value.fix); }

	virtual double speed() const
		{ return m_value.speed; }

	virtual double course() const
		{ return m_value.courseTrue; }

	virtual Date_t date() const
		{ return Date_t(m_value.date.year, m_value.date.month, m_value.date.day); }

	virtual Offset_t magneticVariation() const
		{ return Offset_t::fromOffset(&m_value.magnetic); }

	virtual ModeIndicator_t modeIndicator() const
		{ return ModeIndicator_t::fromModeIndCode(m_value.mi); }

public:
	virtual void setTalkerId(const TalkerId_t &tid)
		{ m_value.tid = tid.toTalkerIdCode(); }

	virtual void setUtc(const Utc_t &utc);

	virtual void setStatus(const Status_t &status)
		{ m_value.status = status.toStatusCode(); }

	virtual void setPositionFix(const PositionFix_t &fix);

	virtual void setSpeed(double value)
		{
			m_value.speed = value;
			m_value.vfields |= RMC_VALID_SPEED;
		}

	virtual void setCourse(double value)
		{
			m_value.courseTrue = value;
			m_value.vfields |= RMC_VALID_COURSETRUE;
		}

	virtual void setDate(const Date_t &date)
		{
			m_value.date = date.toDate();
			m_value.vfields |= RMC_VALID_DATE;
		}

	virtual void setMagneticVariation(const Offset_t &offset)
		{
			m_value.magnetic = offset.toOffset();
			m_value.vfields |= RMC_VALID_MAGNVARIATION;
		}

	virtual void setModeIndicator(const ModeIndicator_t &mi)
		{ m_value.mi = mi.toModeIndCode(); }

public:
	virtual void clearMessage()
		{ m_value.vfields = 0; }

public:
	virtual operator const void *() const
		{ return (const void *)&m_value; }

	virtual operator void *()
		{ return &m_value; }

private:
	struct rmc_t m_value;
};

}

#endif // INCLUDE_navi_rmcplusplus

