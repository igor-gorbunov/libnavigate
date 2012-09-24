#ifndef INCLUDE_navi_almplusplus
#define INCLUDE_navi_almplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Alm_t) : public Message_t
{
public:
	static const int MaxSatellites = 32;

public:
	Alm_t(const TalkerId_t &tid = TalkerId_t::Unknown) :
		Message_t(MessageType_t::ALM)
	{
		m_value.tid = tid.toTalkerIdCode();
		m_value.nmsatellites = 0;
		for (int i = 0; i < MaxSatellites; i++)
		{
			m_value.almlist[i].vfields = 0;
		}
		m_value.totalnm = m_value.msgnm = 0;
	}

	virtual ~Alm_t() { }

public:
	virtual TalkerId_t talkerId() const
		{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

	virtual int nmOfSatellites() const
		{ return m_value.nmsatellites; }

	virtual int totalNmOfMessages() const
		{ return m_value.totalnm; }

	virtual int messageNumber() const
		{ return m_value.msgnm; }

	virtual unsigned int satellitePrn(int satIdx) const
		{ return m_value.almlist[satIdx].satelliteprn; }

	virtual unsigned int gpsWeek(int satIdx) const
		{ return m_value.almlist[satIdx].gpsweek; }

	virtual unsigned int svHealth(int satIdx) const
		{ return m_value.almlist[satIdx].svhealth; }

	virtual unsigned int eccentricity(int satIdx) const
		{ return m_value.almlist[satIdx].e; }

	virtual unsigned int almanacReferenceTime(int satIdx) const
		{ return m_value.almlist[satIdx].toa; }

	virtual unsigned int inclinationAngle(int satIdx) const
		{ return m_value.almlist[satIdx].sigmai; }

	virtual unsigned int rateOfRightAscension(int satIdx) const
		{ return m_value.almlist[satIdx].omegadot; }

	virtual unsigned int sqrtOfSemiMajorAxis(int satIdx) const
		{ return m_value.almlist[satIdx].sqrtsemiaxis; }

	virtual unsigned int argumentOfPerigee(int satIdx) const
		{ return m_value.almlist[satIdx].omega; }

	virtual unsigned int longitudeOfAscensionNode(int satIdx) const
		{ return m_value.almlist[satIdx].omega0; }

	virtual unsigned int meanAnomaly(int satIdx) const
		{ return m_value.almlist[satIdx].m0; }

	virtual unsigned int clockParameter0(int satIdx) const
		{ return m_value.almlist[satIdx].af0; }

	virtual unsigned int clockParameter1(int satIdx) const
		{ return m_value.almlist[satIdx].af1; }

public:
	virtual void setTalkerId(const TalkerId_t &tid)
		{ m_value.tid = tid.toTalkerIdCode(); }

	virtual void setNmOfSatellites(int value)
		{ m_value.nmsatellites = value; }

	virtual void totalNmOfMessages(int value)
		{ m_value.totalnm = value; }

	virtual void messageNumber(int value)
		{ m_value.msgnm = value; }

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
	virtual operator const void *() const
		{ return (const void *)&m_value; }

	virtual operator void *()
		{ return &m_value; }

private:
	struct alm_t m_value;
};

}

#endif // INCLUDE_navi_almplusplus

