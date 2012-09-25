#ifndef INCLUDE_navi_gsaplusplus
#define INCLUDE_navi_gsaplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Gsa_t) : public Message_t
{
public:
	static const int MaxSatellites = 12;

public:
	Gsa_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Gsa_t();

public:
	virtual TalkerId_t talkerId() const;

	virtual GsaSwitchMode_t switchMode() const;
	virtual int fixMode() const;
	virtual int satelliteId(int satIdx) const;
	virtual double pdop() const;
	virtual double hdop() const;
	virtual double vdop() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setSwitchMode(const GsaSwitchMode_t &mode);
	virtual void setFixMode(int value);
	virtual void setSatelliteId(int satIdx, int value);
	virtual void setPdop(double value);
	virtual void setHdop(double value);
	virtual void setVdop(double value);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct gsa_t m_value;
};

}

#endif // INCLUDE_navi_gsaplusplus

