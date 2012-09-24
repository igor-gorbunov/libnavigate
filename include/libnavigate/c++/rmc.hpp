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

public:
	virtual void setTalkerId(const TalkerId_t &tid)
		{ m_value.tid = tid.toTalkerIdCode(); }

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

