#ifndef INCLUDE_navi_gstplusplus
#define INCLUDE_navi_gstplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Gst_t) : public Message_t
{
public:
	Gst_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Gst_t();

public:
	virtual TalkerId_t talkerId() const;
	virtual Utc_t utc() const;

	virtual double rmsOfStandardDeviation() const;
	virtual double deviationOfSemiMajorAxis() const;
	virtual double deviationOfSemiMinorAxis() const;
	virtual double orientationOfSemiMajorAxis() const;
	virtual double deviationOfLatitudeError() const;
	virtual double deviationOfLongitudeError() const;
	virtual double deviationOfAltitudeError() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);
	virtual void setUtc(const Utc_t &utc);

	virtual void setRmsOfStandardDeviation(double value);
	virtual void setDeviationOfSemiMajorAxis(double value);
	virtual void setDeviationOfSemiMinorAxis(double value);
	virtual void setOrientationOfSemiMajorAxis(double value);
	virtual void setDeviationOfLatitudeError(double value);
	virtual void setDeviationOfLongitudeError(double value);
	virtual void setDeviationOfAltitudeError(double value);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct gst_t m_value;
};

}

#endif // INCLUDE_navi_gstplusplus

