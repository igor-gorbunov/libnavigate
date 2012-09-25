#ifndef INCLUDE_navi_dtmplusplus
#define INCLUDE_navi_dtmplusplus

#include "libnavigate/c++/sentence.hpp"

namespace libnavigate
{

NAVI_EXTERN_CLASS(class, Dtm_t) : public Message_t
{
public:
	Dtm_t(const TalkerId_t &tid = TalkerId_t::Unknown);
	virtual ~Dtm_t();

public:
	virtual TalkerId_t talkerId() const;

	virtual Datum_t localDatum() const;
	virtual DatumSubdivision_t datumSubdivision() const;
	virtual Offset_t latitudeOffset() const;
	virtual Offset_t longitudeOffset() const;
	virtual double altitudeOffset() const;
	virtual Datum_t referenceDatum() const;

public:
	virtual void setTalkerId(const TalkerId_t &tid);

	virtual void setLocalDatum(const Datum_t &datum);
	virtual void setDatumSubdivision(const DatumSubdivision_t
		&datumSubdivision);
	virtual void setLatitudeOffset(const Offset_t &offset);
	virtual void setLongitudeOffset(const Offset_t &offset);
	virtual void setAltitudeOffset(double offset);
	virtual void setReferenceDatum(const Datum_t &datum);

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const;
	virtual operator void *();

private:
	struct dtm_t m_value;
};

}

#endif // INCLUDE_navi_dtmplusplus

