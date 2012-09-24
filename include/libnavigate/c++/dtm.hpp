#ifndef INCLUDE_navi_dtmplusplus
#define INCLUDE_navi_dtmplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Dtm_t) : public Message_t
{
public:
	Dtm_t(const TalkerId_t &tid = TalkerId_t::Unknown) :
		Message_t(MessageType_t::DTM)
	{
		m_value.tid = tid.toTalkerIdCode();
	}

	virtual ~Dtm_t() { }

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
	struct dtm_t m_value;
};

}

#endif // INCLUDE_navi_dtmplusplus

