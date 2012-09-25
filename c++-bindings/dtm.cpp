#include <libnavigate/c++/dtm.hpp>

namespace libnavigate
{

Dtm_t::Dtm_t(const TalkerId_t &tid) : Message_t(MessageType_t::DTM)
{
	m_value.tid = tid.toTalkerIdCode();
	m_value.vfields = 0;
}

Dtm_t::~Dtm_t() { }

TalkerId_t Dtm_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

Datum_t Dtm_t::localDatum() const
	{ return Datum_t::fromDatumCode(m_value.locdatum); }

DatumSubdivision_t Dtm_t::datumSubdivision() const
	{ return DatumSubdivision_t::fromDatumSubcode(m_value.locdatumsub); }

Offset_t Dtm_t::latitudeOffset() const
	{ return Offset_t::fromOffset(&m_value.latofs); }

Offset_t Dtm_t::longitudeOffset() const
	{ return Offset_t::fromOffset(&m_value.lonofs); }

double Dtm_t::altitudeOffset() const
	{ return m_value.altoffset; }

Datum_t Dtm_t::referenceDatum() const
	{ return Datum_t::fromDatumCode(m_value.refdatum); }

void Dtm_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Dtm_t::setLocalDatum(const Datum_t &datum)
{
	m_value.locdatum = datum.toDatumCode();
	m_value.vfields |= DTM_VALID_LOCALDATUM;
}

void Dtm_t::setDatumSubdivision(const DatumSubdivision_t &datumSubdivision)
{
	m_value.locdatumsub = datumSubdivision.toDatumSubcode();
	m_value.vfields |= DTM_VALID_LOCALDATUMSUB;
}

void Dtm_t::setLatitudeOffset(const Offset_t &offset)
{
	m_value.latofs = offset.toOffset();
	m_value.vfields |= DTM_VALID_OFFSET;
}

void Dtm_t::setLongitudeOffset(const Offset_t &offset)
{
	m_value.lonofs = offset.toOffset();
	m_value.vfields |= DTM_VALID_OFFSET;
}

void Dtm_t::setAltitudeOffset(double offset)
{
	m_value.altoffset = offset;
	m_value.vfields |= DTM_VALID_ALTOFFSET;
}

void Dtm_t::setReferenceDatum(const Datum_t &datum)
{
	m_value.refdatum = datum.toDatumCode();
	m_value.vfields |= DTM_VALID_REFDATUM;
}

void Dtm_t::clearMessage()
	{ m_value.vfields = 0; }

Dtm_t::operator const void *() const
	{ return (const void *)&m_value; }

Dtm_t::operator void *()
	{ return &m_value; }

}
