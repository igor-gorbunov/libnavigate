#ifndef INCLUDE_navi_grsplusplus
#define INCLUDE_navi_grsplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Grs_t) : public Message_t
{
public:
	static const int MaxSatellites = 12;

public:
	Grs_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Grs_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual Utc_t utc() const;
	virtual int mode() const;
	virtual double residual(int satIdx) const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setUtc(const Utc_t &utc);
	virtual void setMode(int mode);
	virtual void setResidual(int satIdx, double value);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct grs_t m_value;
};

}

#endif // INCLUDE_navi_grsplusplus

