#ifndef INCLUDE_navi_gsvplusplus
#define INCLUDE_navi_gsvplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Gsv_t) : public Message_t
{
public:
	static const int MaxSatellites = 36;

public:
	Gsv_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Gsv_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual int nmOfSatellites() const;
	virtual int totalNmOfMessages() const;
	virtual int messageNumber() const;

	virtual unsigned int satelliteId(int satIdx) const;
	virtual unsigned int elevation(int satIdx) const;
	virtual unsigned int azimuth(int satIdx) const;
	virtual unsigned int snratio(int satIdx) const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setNmOfSatellites(int value);
	virtual void setTotalNmOfMessages(int value);
	virtual void setMessageNumber(int value);

	virtual void setSatelliteId(int satIdx, unsigned int value);
	virtual void setElevation(int satIdx, unsigned int value);
	virtual void setAzimuth(int satIdx, unsigned int value);
	virtual void setSnratio(int satIdx, unsigned int value);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct gsv_t m_value;
};

}

#endif // INCLUDE_navi_gsvplusplus

