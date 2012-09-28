#ifndef INCLUDE_navi_almplusplus
#define INCLUDE_navi_almplusplus

#include <libnavigate/c++/sentence.hpp>

namespace libnavigate
{

#include <libnavigate/alm.h>

NAVI_EXTERN_CLASS(class, Alm_t) : public Message_t
{
public:
	static const int MaxSatellites = 32;

public:
	Alm_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Alm_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual int nmOfSatellites() const;
	virtual int totalNmOfMessages() const;
	virtual int messageNumber() const;

	virtual unsigned int satellitePrn(int satIdx) const;
	virtual unsigned int gpsWeek(int satIdx) const;
	virtual unsigned int svHealth(int satIdx) const;
	virtual unsigned int eccentricity(int satIdx) const;
	virtual unsigned int almanacReferenceTime(int satIdx) const;
	virtual unsigned int inclinationAngle(int satIdx) const;
	virtual unsigned int rateOfRightAscension(int satIdx) const;
	virtual unsigned int sqrtOfSemiMajorAxis(int satIdx) const;
	virtual unsigned int argumentOfPerigee(int satIdx) const;
	virtual unsigned int longitudeOfAscensionNode(int satIdx) const;
	virtual unsigned int meanAnomaly(int satIdx) const;
	virtual unsigned int clockParameter0(int satIdx) const;
	virtual unsigned int clockParameter1(int satIdx) const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setNmOfSatellites(int value);
	virtual void setTotalNmOfMessages(int value);
	virtual void setMessageNumber(int value);

	virtual void setSatellitePrn(int satIdx, unsigned int value);
	virtual void setGpsWeek(int satIdx, unsigned int value);
	virtual void setSvHealth(int satIdx, unsigned int value);
	virtual void setEccentricity(int satIdx, unsigned int value);
	virtual void setAlmanacReferenceTime(int satIdx, unsigned int value);
	virtual void setInclinationAngle(int satIdx, unsigned int value);
	virtual void setRateOfRightAscension(int satIdx, unsigned int value);
	virtual void setSqrtOfSemiMajorAxis(int satIdx, unsigned int value);
	virtual void setArgumentOfPerigee(int satIdx, unsigned int value);
	virtual void setLongitudeOfAscensionNode(int satIdx, unsigned int value);
	virtual void setMeanAnomaly(int satIdx, unsigned int value);
	virtual void setClockParameter0(int satIdx, unsigned int value);
	virtual void setClockParameter1(int satIdx, unsigned int value);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct alm_t m_value;
};

}

#endif // INCLUDE_navi_almplusplus

