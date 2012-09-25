#ifndef INCLUDE_navi_gllplusplus
#define INCLUDE_navi_gllplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Gll_t) : public Message_t
{
public:
	Gll_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Gll_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual PositionFix_t positionFix() const;
	virtual Utc_t utc() const;
	virtual Status_t status() const;
	virtual ModeIndicator_t modeIndicator() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setPositionFix(const PositionFix_t &fix);
	virtual void setUtc(const Utc_t &utc);
	virtual void setStatus(const Status_t &status);
	virtual void setModeIndicator(const ModeIndicator_t &mi);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct gll_t m_value;
};

}

#endif // INCLUDE_navi_gllplusplus

