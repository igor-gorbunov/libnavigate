#ifndef INCLUDE_navi_zdaplusplus
#define INCLUDE_navi_zdaplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Zda_t) : public Message_t
{
public:
	Zda_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Zda_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual Utc_t utc() const;
	virtual Date_t date() const;
	virtual int localZoneOffset() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setUtc(const Utc_t &utc);
	virtual void setDate(const Date_t &date);
	virtual void setLocalZoneOffset(int value);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct zda_t m_value;
};

}

#endif // INCLUDE_navi_zdaplusplus

