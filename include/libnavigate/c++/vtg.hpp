#ifndef INCLUDE_navi_vtgplusplus
#define INCLUDE_navi_vtgplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Vtg_t) : public Message_t
{
public:
	Vtg_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Vtg_t();

public:
	virtual TalkerId_t talkerId() const;

	virtual double courseTrue() const;
	virtual double courseMagnetic() const;
	virtual double speed() const;
	virtual ModeIndicator_t modeIndicator() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setCourseTrue(double value);
	virtual void setCourseMagnetic(double value);
	virtual void setSpeed(double value);
	virtual void setModeIndicator(const ModeIndicator_t &mi);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct vtg_t m_value;
};

}

#endif // INCLUDE_navi_vtgplusplus

