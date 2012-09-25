#ifndef INCLUDE_navi_rmcplusplus
#define INCLUDE_navi_rmcplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Rmc_t) : public Message_t
{
public:
	Rmc_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Rmc_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual Utc_t utc() const;
	virtual Status_t status() const;
	virtual PositionFix_t positionFix() const;
	virtual double speed() const;
	virtual double course() const;
	virtual Date_t date() const;
	virtual Offset_t magneticVariation() const;
	virtual ModeIndicator_t modeIndicator() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setUtc(const Utc_t &utc);
	virtual void setStatus(const Status_t &status);
	virtual void setPositionFix(const PositionFix_t &fix);
	virtual void setSpeed(double value);
	virtual void setCourse(double value);
	virtual void setDate(const Date_t &date);
	virtual void setMagneticVariation(const Offset_t &offset);
	virtual void setModeIndicator(const ModeIndicator_t &mi);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct rmc_t m_value;
};

}

#endif // INCLUDE_navi_rmcplusplus

