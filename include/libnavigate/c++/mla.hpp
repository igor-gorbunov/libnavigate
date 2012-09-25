#ifndef INCLUDE_navi_mlaplusplus
#define INCLUDE_navi_mlaplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Mla_t) : public Message_t
{
public:
	static const int MaxSatellites = 32;

public:
	Mla_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Mla_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual int nmOfSatellites() const;
	virtual int totalNmOfMessages() const;
	virtual int messageNumber() const;

	virtual unsigned int satelliteSlot(int satIdx) const;
	virtual unsigned int dayCount(int satIdx) const;
	virtual unsigned int svHealth(int satIdx) const;
	virtual unsigned int eccentricity(int satIdx) const;
	virtual unsigned int rateOfChangeOfDraconicTime(int satIdx) const;
	virtual unsigned int argumentOfPerigee(int satIdx) const;
	virtual unsigned int systemTimescaleCorrection_High(int satIdx) const;
	virtual unsigned int correctionToDraconicTime(int satIdx) const;
	virtual unsigned int timeOfAscensionNode(int satIdx) const;
	virtual unsigned int longitudeOfAscensionNode(int satIdx) const;
	virtual unsigned int correctionToInclinationAngle(int satIdx) const;
	virtual unsigned int systemTimescaleCorrection_Low(int satIdx) const;
	virtual unsigned int courseValueOfTimescaleShift(int satIdx) const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setNmOfSatellites(int value);
	virtual void setTotalNmOfMessages(int value);
	virtual void setMessageNumber(int value);

	virtual void setSatelliteSlot(int satIdx, unsigned int value);
	virtual void setDayCount(int satIdx, unsigned int value);
	virtual void setSvHealth(int satIdx, unsigned int value);
	virtual void setEccentricity(int satIdx, unsigned int value);
	virtual void setRateOfChangeOfDraconicTime(int satIdx, unsigned int value);
	virtual void setArgumentOfPerigee(int satIdx, unsigned int value);
	virtual void setSystemTimescaleCorrection_High(int satIdx, unsigned int value);
	virtual void setCorrectionToDraconicTime(int satIdx, unsigned int value);
	virtual void setTimeOfAscensionNode(int satIdx, unsigned int value);
	virtual void setLongitudeOfAscensionNode(int satIdx, unsigned int value);
	virtual void setCorrectionToInclinationAngle(int satIdx, unsigned int value);
	virtual void setSystemTimescaleCorrection_Low(int satIdx, unsigned int value);
	virtual void setCourseValueOfTimescaleShift(int satIdx, unsigned int value);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct mla_t m_value;
};

}

#endif // INCLUDE_navi_mlaplusplus

