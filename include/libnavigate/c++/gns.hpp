#ifndef INCLUDE_navi_gnsplusplus
#define INCLUDE_navi_gnsplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Gns_t) : public Message_t
{
public:
	Gns_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Gns_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual Utc_t utc() const;
	virtual PositionFix_t positionFix() const;
	virtual ModeIndicatorArray_t modeIndicatorArray() const;
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
	virtual void setModeIndicatorArray(const ModeIndicatorArray_t &modeArray);
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
	struct gns_t m_value;
};

}

#endif // INCLUDE_navi_gnsplusplus

