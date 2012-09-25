#ifndef INCLUDE_navi_ggaplusplus
#define INCLUDE_navi_ggaplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Gga_t) : public Message_t
{
public:
	Gga_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Gga_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual Utc_t utc() const;
	virtual PositionFix_t positionFix() const;
	virtual GpsQualityIndicator_t qualityIndicator() const;
	virtual int nmOfSatellites() const;
	virtual double hdop() const;
	virtual double antennaAltitude() const;
	virtual double geoidalSeparation() const;
	virtual int ageOfDiffData() const;
	virtual int diffReferenceStationId() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setUtc(const Utc_t &utc);
	virtual void setPositionFix(const PositionFix_t &fix);
	virtual void setQualityIndicator(const GpsQualityIndicator_t &qi);
	virtual void setNmOfSatellites(int value);
	virtual void setHdop(double value);
	virtual void setAntennaAltitude(double value);
	virtual void setGeoidalSeparation(double value);
	virtual void setAgeOfDiffData(int value);
	virtual void setDiffReferenceStationId(int value);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct gga_t m_value;
};

}

#endif // INCLUDE_navi_ggaplusplus

