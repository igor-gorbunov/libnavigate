#ifndef INCLUDE_navi_gbsplusplus
#define INCLUDE_navi_gbsplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Gbs_t) : public Message_t
{
public:
	Gbs_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Gbs_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual Utc_t utc() const;
	virtual double expErrInLatitude() const;
	virtual double expErrInLongitude() const;
	virtual double expErrInAltitude() const;
	virtual int failedSatelliteId() const;
	virtual double probabilityOfMissedDetection() const;
	virtual double estimateOfBias() const;
	virtual double deviationOfBias() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setUtc(const Utc_t &utc);
	virtual void setExpErrInLatitude(double value);
	virtual void setExpErrInLongitude(double value);
	virtual void setExpErrInAltitude(double value);
	virtual void setFailedSatelliteId(int value);
	virtual void setProbabilityOfMissedDetection(double value);
	virtual void setEstimateOfBias(double value);
	virtual void setDeviationOfBias(double value);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct gbs_t m_value;
};

}

#endif // INCLUDE_navi_gbsplusplus

