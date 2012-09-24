#ifndef INCLUDE_navi_gsvplusplus
#define INCLUDE_navi_gsvplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Gsv_t) : public Message_t
{
public:
	Gsv_t(const TalkerId_t &tid = TalkerId_t::Unknown) :
		Message_t(MessageType_t::GSV)
	{
		m_value.tid = tid.toTalkerIdCode();
	}

	virtual ~Gsv_t() { }

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
	struct gsv_t m_value;
};

}

#endif // INCLUDE_navi_gsvplusplus

