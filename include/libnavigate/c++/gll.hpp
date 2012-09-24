#ifndef INCLUDE_navi_gllplusplus
#define INCLUDE_navi_gllplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Gll_t) : public Message_t
{
public:
	Gll_t(const TalkerId_t &tid = TalkerId_t::Unknown) :
		Message_t(MessageType_t::GLL)
	{
		m_value.tid = tid.toTalkerIdCode();
		m_value.vfields = 0;
	}

	virtual ~Gll_t() { }

public:
	virtual TalkerId_t talkerId() const
		{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

	virtual PositionFix_t positionFix() const
		{ return PositionFix_t::fromPosition(&m_value.fix); }

	virtual Utc_t utc() const
		{ return Utc_t(m_value.utc.hour, m_value.utc.min, m_value.utc.sec); }

	virtual Status_t status() const
		{ return Status_t::fromStatusCode(m_value.status); }

	virtual ModeIndicator_t modeIndicator() const
		{ return ModeIndicator_t::fromModeIndCode(m_value.mi); }

public:
	virtual void setTalkerId(const TalkerId_t &tid)
		{ m_value.tid = tid.toTalkerIdCode(); }

	virtual void setPositionFix(const PositionFix_t &fix);
	virtual void setUtc(const Utc_t &utc);

	virtual void setStatus(const Status_t &status)
		{ m_value.status = status.toStatusCode(); }

	virtual void setModeIndicator(const ModeIndicator_t &mi)
		{ m_value.mi = mi.toModeIndCode(); }

public:
	virtual operator const void *() const
		{ return (const void *)&m_value; }

	virtual operator void *()
		{ return &m_value; }

private:
	struct gll_t m_value;
};

}

#endif // INCLUDE_navi_gllplusplus

