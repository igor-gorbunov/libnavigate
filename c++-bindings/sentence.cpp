#include "include/libnavigate/c++/errors.hpp"
#include "include/libnavigate/c++/sentence.hpp"
#include <string.h>
#include <stdlib.h>

#include <libnavigate/aam.h>
#include <libnavigate/ack.h>
#include <libnavigate/alm.h>
#include <libnavigate/alr.h>
#include <libnavigate/dtm.h>
#include <libnavigate/gbs.h>
#include <libnavigate/gga.h>
#include <libnavigate/gll.h>
#include <libnavigate/gns.h>
#include <libnavigate/grs.h>
#include <libnavigate/gsa.h>
#include <libnavigate/gst.h>
#include <libnavigate/gsv.h>
#include <libnavigate/mla.h>
#include <libnavigate/rmc.h>
#include <libnavigate/txt.h>
#include <libnavigate/vtg.h>
#include <libnavigate/zda.h>

#include <libnavigate/common.h>

namespace libnavigate
{

navi_approved_fmt_t MessageType_t::toSentenceFormatter() const
{
	switch (m_value)
	{
	case AAM: return navi_AAM;
	case ACK: return navi_ACK;
	case ALM: return navi_ALM;
	case ALR: return navi_ALR;
	case APB: return navi_APB;
	case BEC: return navi_BEC;
	case BOD: return navi_BOD;
	case BWC: return navi_BWC;
	case BWR: return navi_BWR;
	case BWW: return navi_BWW;
	case DBT: return navi_DBT;
	case DCN: return navi_DCN;
	case DPT: return navi_DPT;
	case DSC: return navi_DSC;
	case DSE: return navi_DSE;
	case DSI: return navi_DSI;
	case DSR: return navi_DSR;
	case DTM: return navi_DTM;
	case FSI: return navi_FSI;
	case GBS: return navi_GBS;
	case GGA: return navi_GGA;
	case GLC: return navi_GLC;
	case GLL: return navi_GLL;
	case GNS: return navi_GNS;
	case GRS: return navi_GRS;
	case GSA: return navi_GSA;
	case GST: return navi_GST;
	case GSV: return navi_GSV;
	case HDG: return navi_HDG;
	case HDT: return navi_HDT;
	case HMR: return navi_HMR;
	case HMS: return navi_HMS;
	case HSC: return navi_HSC;
	case HTC: return navi_HTC;
	case HTD: return navi_HTD;
	case LCD: return navi_LCD;
	case MLA: return navi_MLA;
	case MSK: return navi_MSK;
	case MSS: return navi_MSS;
	case MTW: return navi_MTW;
	case MWD: return navi_MWD;
	case MWV: return navi_MWV;
	case OSD: return navi_OSD;
	case RMA: return navi_RMA;
	case RMB: return navi_RMB;
	case RMC: return navi_RMC;
	case ROT: return navi_ROT;
	case RPM: return navi_RPM;
	case RSA: return navi_RSA;
	case RSD: return navi_RSD;
	case RTE: return navi_RTE;
	case SFI: return navi_SFI;
	case STN: return navi_STN;
	case TLB: return navi_TLB;
	case TLL: return navi_TLL;
	case TTM: return navi_TTM;
	case TXT: return navi_TXT;
	case VBW: return navi_VBW;
	case VDR: return navi_VDR;
	case VHW: return navi_VHW;
	case VLW: return navi_VLW;
	case VPW: return navi_VPW;
	case VTG: return navi_VTG;
	case WCV: return navi_WCV;
	case WNC: return navi_WNC;
	case WPL: return navi_WPL;
	case XDR: return navi_XDR;
	case XTE: return navi_XTE;
	case XTR: return navi_XTR;
	case ZDA: return navi_ZDA;
	case ZDL: return navi_ZDL;
	case ZFO: return navi_ZFO;
	case ZTG: return navi_ZTG;
	default:
		return navi_approvedfmt_Unknown;
	}
}

MessageType_t MessageType_t::fromSentenceFormatter(navi_approved_fmt_t type)
{
	switch (type)
	{
	case navi_AAM: return AAM;
	case navi_ACK: return ACK;
	case navi_ALM: return ALM;
	case navi_ALR: return ALR;
	case navi_APB: return APB;
	case navi_BEC: return BEC;
	case navi_BOD: return BOD;
	case navi_BWC: return BWC;
	case navi_BWR: return BWR;
	case navi_BWW: return BWW;
	case navi_DBT: return DBT;
	case navi_DCN: return DCN;
	case navi_DPT: return DPT;
	case navi_DSC: return DSC;
	case navi_DSE: return DSE;
	case navi_DSI: return DSI;
	case navi_DSR: return DSR;
	case navi_DTM: return DTM;
	case navi_FSI: return FSI;
	case navi_GBS: return GBS;
	case navi_GGA: return GGA;
	case navi_GLC: return GLC;
	case navi_GLL: return GLL;
	case navi_GNS: return GNS;
	case navi_GRS: return GRS;
	case navi_GSA: return GSA;
	case navi_GST: return GST;
	case navi_GSV: return GSV;
	case navi_HDG: return HDG;
	case navi_HDT: return HDT;
	case navi_HMR: return HMR;
	case navi_HMS: return HMS;
	case navi_HSC: return HSC;
	case navi_HTC: return HTC;
	case navi_HTD: return HTD;
	case navi_LCD: return LCD;
	case navi_MLA: return MLA;
	case navi_MSK: return MSK;
	case navi_MSS: return MSS;
	case navi_MTW: return MTW;
	case navi_MWD: return MWD;
	case navi_MWV: return MWV;
	case navi_OSD: return OSD;
	case navi_RMA: return RMA;
	case navi_RMB: return RMB;
	case navi_RMC: return RMC;
	case navi_ROT: return ROT;
	case navi_RPM: return RPM;
	case navi_RSA: return RSA;
	case navi_RSD: return RSD;
	case navi_RTE: return RTE;
	case navi_SFI: return SFI;
	case navi_STN: return STN;
	case navi_TLB: return TLB;
	case navi_TLL: return TLL;
	case navi_TTM: return TTM;
	case navi_TXT: return TXT;
	case navi_VBW: return VBW;
	case navi_VDR: return VDR;
	case navi_VHW: return VHW;
	case navi_VLW: return VLW;
	case navi_VPW: return VPW;
	case navi_VTG: return VTG;
	case navi_WCV: return WCV;
	case navi_WNC: return WNC;
	case navi_WPL: return WPL;
	case navi_XDR: return XDR;
	case navi_XTE: return XTE;
	case navi_XTR: return XTR;
	case navi_ZDA: return ZDA;
	case navi_ZDL: return ZDL;
	case navi_ZFO: return ZFO;
	case navi_ZTG: return ZTG;
	default:
		return Unknown;
	}
}

MessageType_t::MessageType_t()
	{ m_value = Unknown; }

MessageType_t::MessageType_t(enum MessageType_t::msgtype_t initial)
	{ m_value = initial; }

MessageType_t::MessageType_t(const MessageType_t &right)
	{ m_value = right.m_value; }

MessageType_t::~MessageType_t() { }

TalkerId_t TalkerId_t::fromTalkerIdCode(navi_talkerid_t tid)
{
	switch (tid)
	{
	case navi_AG: return AG;
	case navi_AP: return AP;
	case navi_AI: return AI;
	case navi_CD: return CD;
	case navi_CR: return CR;
	case navi_CS: return CS;
	case navi_CT: return CT;
	case navi_CV: return CV;
	case navi_CX: return CX;
	case navi_DE: return DE;
	case navi_DF: return DF;
	case navi_EC: return EC;
	case navi_EI: return EI;
	case navi_EP: return EP;
	case navi_ER: return ER;
	case navi_GA: return GA;
	case navi_GP: return GP;
	case navi_GL: return GL;
	case navi_GN: return GN;
	case navi_GW: return GW;
	case navi_HC: return HC;
	case navi_HE: return HE;
	case navi_HN: return HN;
	case navi_II: return II;
	case navi_IN: return IN;
	case navi_LC: return LC;
	case navi_RA: return RA;
	case navi_SD: return SD;
	case navi_SN: return SN;
	case navi_SS: return SS;
	case navi_TI: return TI;
	case navi_VD: return VD;
	case navi_VM: return VM;
	case navi_VW: return VW;
	case navi_VR: return VR;
	case navi_YX: return YX;
	case navi_ZA: return ZA;
	case navi_ZC: return ZC;
	case navi_ZQ: return ZQ;
	case navi_ZV: return ZV;
	case navi_WI: return WI;
	case navi_P: return P;
	default:
		return Unknown;
	}
}

navi_talkerid_t TalkerId_t::toTalkerIdCode() const
{
	switch (m_value)
	{
	case AG: return navi_AG;
	case AP: return navi_AP;
	case AI: return navi_AI;
	case CD: return navi_CD;
	case CR: return navi_CR;
	case CS: return navi_CS;
	case CT: return navi_CT;
	case CV: return navi_CV;
	case CX: return navi_CX;
	case DE: return navi_DE;
	case DF: return navi_DF;
	case EC: return navi_EC;
	case EI: return navi_EI;
	case EP: return navi_EP;
	case ER: return navi_ER;
	case GA: return navi_GA;
	case GP: return navi_GP;
	case GL: return navi_GL;
	case GN: return navi_GN;
	case GW: return navi_GW;
	case HC: return navi_HC;
	case HE: return navi_HE;
	case HN: return navi_HN;
	case II: return navi_II;
	case IN: return navi_IN;
	case LC: return navi_LC;
	case RA: return navi_RA;
	case SD: return navi_SD;
	case SN: return navi_SN;
	case SS: return navi_SS;
	case TI: return navi_TI;
	case VD: return navi_VD;
	case VM: return navi_VM;
	case VW: return navi_VW;
	case VR: return navi_VR;
	case YX: return navi_YX;
	case ZA: return navi_ZA;
	case ZC: return navi_ZC;
	case ZQ: return navi_ZQ;
	case ZV: return navi_ZV;
	case WI: return navi_WI;
	case P: return navi_P;
	default:
		return navi_talkerid_Unknown;
	}
}

TalkerId_t::TalkerId_t()
	{ m_value = Unknown; }

TalkerId_t::TalkerId_t(enum TalkerId_t::talkerid_t initial)
	{ m_value = initial; }

TalkerId_t::TalkerId_t(const TalkerId_t &right)
	{ m_value = right.m_value; }

TalkerId_t::~TalkerId_t() { }

PositionFix_t PositionFix_t::fromPosition(const struct navi_position_t *position)
{
	double latitude, longitude;
	navi_get_position(position, &latitude, &longitude);
	return PositionFix_t(latitude, longitude);
}

PositionFix_t::PositionFix_t(double latitude, double longitude)
	{ m_latitude = latitude; m_longitude = longitude; }

PositionFix_t::~PositionFix_t() { }

double PositionFix_t::latitude() const
	{ return m_latitude; }

double PositionFix_t::longitude() const
	{ return m_longitude; }

struct navi_position_t PositionFix_t::toPosition() const
{
	struct navi_position_t result;
	navi_init_position_from_degrees(latitude(), longitude(), &result);
	return result;
}

Status_t Status_t::fromStatusCode(int status)
{
	switch (status)
	{
	case navi_status_A: return DataValid;
	case navi_status_V: return DataInvalid;
	default:
		return Unknown;
	}
}

int Status_t::toStatusCode() const
{
	switch (m_value)
	{
	case DataValid: return navi_status_A;
	case DataInvalid: return navi_status_V;
	default:
		return -1;
	}
}

Status_t::Status_t(enum Status_t::status_t status)
	{ m_value = status; }

Status_t::~Status_t() { }

ModeIndicator_t ModeIndicator_t::fromModeIndCode(int mi)
{
	switch (mi)
	{
	case navi_Autonomous: return Autonomous;
	case navi_Differential: return Differential;
	case navi_Estimated: return Estimated;
	case navi_ManualInput: return ManualInput;
	case navi_Simulator: return Simulator;
	case navi_DataNotValid: return DataNotValid;
	case navi_Precise: return Precise;
	case navi_RTKinematic: return RTKinematic;
	case navi_FloatRTK: return FloatRTK;
	default:
		return Unknown;
	}
}

int ModeIndicator_t::toModeIndCode() const
{
	switch (m_value)
	{
	case Autonomous: return navi_Autonomous;
	case Differential: return navi_Differential;
	case Estimated: return navi_Estimated;
	case ManualInput: return navi_ManualInput;
	case Simulator: return navi_Simulator;
	case DataNotValid: return navi_DataNotValid;
	case Precise: return navi_Precise;
	case RTKinematic: return navi_RTKinematic;
	case FloatRTK: return navi_FloatRTK;
	default:
		return -1;
	}
}

ModeIndicator_t::ModeIndicator_t(enum ModeIndicator_t::modeind_t mi)
	{ m_value = mi; }

ModeIndicator_t::~ModeIndicator_t() { }

Utc_t::Utc_t(int hh, int mm, double ss)
	{ m_hours = hh; m_minutes = mm; m_seconds = ss; }

Utc_t::~Utc_t() { }

int Utc_t::hours() const
	{ return m_hours; }

int Utc_t::minutes() const
	{ return m_minutes; }

double Utc_t::seconds() const
	{ return m_seconds; }

Utc_t Utc_t::fromUtcStruct(const struct navi_utc_t &utc)
	{ return Utc_t(utc.hour, utc.min, utc.sec); }

struct navi_utc_t Utc_t::toUtcStruct() const
{
	struct navi_utc_t s;
	navi_init_utc(hours(), minutes(), seconds(), &s);
	return s;
}

Date_t::Date_t(int yy, int mm, int dd)
	{ m_year = yy; m_month = mm; m_day = dd; }

Date_t::~Date_t() { }

int Date_t::year() const
	{ return m_year; }

int Date_t::month() const
	{ return m_month; }

int Date_t::day() const
	{ return m_day; }

Date_t Date_t::fromDateStruct(const struct navi_date_t &date)
	{ return Date_t(date.year, date.month, date.day); }

struct navi_date_t Date_t::toDateStruct() const
{
	struct navi_date_t s;
	navi_init_date(year(), month(), day(), &s);
	return s;
}

Offset_t Offset_t::fromOffset(const struct navi_offset_t *offset)
	{ return Offset_t(offset->offset, quarterFromCode(offset->sign)); }

Offset_t::Offset_t(double offset, enum quarters_t quarter)
{
	m_offset = offset;
	m_quarter = quarter;
}

Offset_t::~Offset_t() { }

double Offset_t::offset() const
	{ return m_offset; }

enum Offset_t::quarters_t Offset_t::quarter() const
	{ return m_quarter; }

void Offset_t::setOffset(double offset)
	{ m_offset = offset; }

void Offset_t::setQuarter(enum Offset_t::quarters_t quarter)
	{ m_quarter = quarter; }

enum Offset_t::quarters_t Offset_t::quarterFromCode(int quarter)
{
	switch (quarter)
	{
	case navi_North: return North;
	case navi_South: return South;
	case navi_East: return East;
	case navi_West: return West;
	default:
		return Unknown;
	}
}

int Offset_t::quarterToCode(enum quarters_t quarter)
{
	switch (quarter)
	{
	case North: return navi_North;
	case South: return navi_South;
	case East: return navi_East;
	case West: return navi_West;
	default:
		return -1;
	}
}

struct navi_offset_t Offset_t::toOffset() const
{
	struct navi_offset_t result;

	result.offset = m_offset;
	result.sign = quarterToCode(m_quarter);

	return result;
}

Message_t::Message_t(const MessageType_t &type)
{
	m_type = MessageType_t::Unknown;
	m_data = 0;
	m_size = 0;

	setType(type);
}

Message_t::Message_t(const MessageType_t &type, const void *data)
{
	m_type = MessageType_t::Unknown;
	m_data = 0;
	m_size = 0;

	setType(type);
	memcpy(m_data, data, m_size);
}

Message_t::Message_t(const Message_t &right)
{
	m_type = MessageType_t::Unknown;
	m_data = 0;
	m_size = 0;

	setType(right.type());
	memcpy(m_data, right, m_size);
}

Message_t::~Message_t()
{
	clearMessage();
}

const MessageType_t & Message_t::type() const
	{ return m_type; }

void Message_t::setType(const MessageType_t &type)
{
	clearMessage();

	m_type = type;

	switch (m_type)
	{
	case MessageType_t::AAM:
		m_size = sizeof(struct aam_t);
		break;
	case MessageType_t::ACK:
		m_size = sizeof(struct ack_t);
		break;
	case MessageType_t::ALM:
		m_size = sizeof(struct alm_t);
		break;
	case MessageType_t::ALR:
		m_size = sizeof(struct alr_t);
		break;
	case MessageType_t::APB:
	case MessageType_t::BEC:
	case MessageType_t::BOD:
	case MessageType_t::BWC:
	case MessageType_t::BWR:
	case MessageType_t::BWW:
	case MessageType_t::DBT:
	case MessageType_t::DCN:
	case MessageType_t::DPT:
	case MessageType_t::DSC:
	case MessageType_t::DSE:
	case MessageType_t::DSI:
	case MessageType_t::DSR:
		throw NaviError_t::NotImplemented;
	case MessageType_t::DTM:
		m_size = sizeof(struct dtm_t);
		break;
	case MessageType_t::FSI:
		throw NaviError_t::NotImplemented;
	case MessageType_t::GBS:
		m_size = sizeof(struct gbs_t);
		break;
	case MessageType_t::GGA:
		m_size = sizeof(struct gga_t);
		break;
	case MessageType_t::GLC:
		throw NaviError_t::NotImplemented;
	case MessageType_t::GLL:
		m_size = sizeof(struct gll_t);
		break;
	case MessageType_t::GNS:
		m_size = sizeof(struct gns_t);
		break;
	case MessageType_t::GRS:
		m_size = sizeof(struct grs_t);
		break;
	case MessageType_t::GSA:
		m_size = sizeof(struct gsa_t);
		break;
	case MessageType_t::GST:
		m_size = sizeof(struct gst_t);
		break;
	case MessageType_t::GSV:
		m_size = sizeof(struct gsv_t);
		break;
	case MessageType_t::HDG:
	case MessageType_t::HDT:
	case MessageType_t::HMR:
	case MessageType_t::HMS:
	case MessageType_t::HSC:
	case MessageType_t::HTC:
	case MessageType_t::HTD:
	case MessageType_t::LCD:
		throw NaviError_t::NotImplemented;
	case MessageType_t::MLA:
		m_size = sizeof(struct mla_t);
		break;
	case MessageType_t::MSK:
	case MessageType_t::MSS:
	case MessageType_t::MTW:
	case MessageType_t::MWD:
	case MessageType_t::MWV:
	case MessageType_t::OSD:
	case MessageType_t::RMA:
	case MessageType_t::RMB:
		throw NaviError_t::NotImplemented;
	case MessageType_t::RMC:
		m_size = sizeof(struct rmc_t);
		break;
	case MessageType_t::ROT:
	case MessageType_t::RPM:
	case MessageType_t::RSA:
	case MessageType_t::RSD:
	case MessageType_t::RTE:
	case MessageType_t::SFI:
	case MessageType_t::STN:
	case MessageType_t::TLB:
	case MessageType_t::TLL:
	case MessageType_t::TTM:
		throw NaviError_t::NotImplemented;
	case MessageType_t::TXT:
		m_size = sizeof(struct txt_t);
		break;
	case MessageType_t::VBW:
	case MessageType_t::VDR:
	case MessageType_t::VHW:
	case MessageType_t::VLW:
	case MessageType_t::VPW:
		throw NaviError_t::NotImplemented;
	case MessageType_t::VTG:
		m_size = sizeof(struct vtg_t);
		break;
	case MessageType_t::WCV:
	case MessageType_t::WNC:
	case MessageType_t::WPL:
	case MessageType_t::XDR:
	case MessageType_t::XTE:
	case MessageType_t::XTR:
		throw NaviError_t::NotImplemented;
	case MessageType_t::ZDA:
		m_size = sizeof(struct zda_t);
		break;
	case MessageType_t::ZDL:
	case MessageType_t::ZFO:
	case MessageType_t::ZTG:
		throw NaviError_t::NotImplemented;
	default:
		m_data = 0;
		m_size = 0;
		break;
	}

	if (m_size > 0)
		m_data = ::malloc(m_size);
}

void Message_t::clearMessage()
{
	if (m_data)
		::free(m_data);

	m_data = 0;
	m_size = 0;
	m_type = MessageType_t::Unknown;
}

Message_t & Message_t::operator=(const Message_t &right)
{
	if (this != &right)
	{
		setType(right.type());
		memcpy(m_data, right, m_size);
	}

	return *this;
}

Datum_t Datum_t::fromDatumCode(int code)
{
	switch (code)
	{
	case navi_WGS84: return WGS84;
	case navi_WGS72: return WGS72;
	case navi_SGS85: return SGS85;
	case navi_PE90: return PE90;
	case navi_UserDefined: return UserDefined;
	default:
		return Unknown;
	}
}

Datum_t::Datum_t(enum Datum_t::datums_t datum)
	{ m_value = datum; }

Datum_t::~Datum_t() { }

enum Datum_t::datums_t Datum_t::datum() const
	{ return m_value; }

void Datum_t::setDatum(enum Datum_t::datums_t datum)
	{ m_value = datum; }

int Datum_t::toDatumCode() const
{
	switch (m_value)
	{
	case WGS84: return navi_WGS84;
	case WGS72: return navi_WGS72;
	case SGS85: return navi_SGS85;
	case PE90: return navi_PE90;
	case UserDefined: return navi_UserDefined;
	default:
		return -1;
	}
}

DatumSubdivision_t DatumSubdivision_t::fromDatumSubcode(int subcode)
{
	switch (subcode)
	{
	case navi_datumsub_NULL:
	default:
		return Unknown;
	}
}

DatumSubdivision_t::DatumSubdivision_t(enum datumsubcodes_t datumsubcode)
	{ m_value = datumsubcode; }

DatumSubdivision_t::~DatumSubdivision_t() { }

enum DatumSubdivision_t::datumsubcodes_t DatumSubdivision_t::datumSubcode() const
	{ return m_value; }

void DatumSubdivision_t::setDatum(enum DatumSubdivision_t::datumsubcodes_t datumSubcode)
	{ m_value = datumSubcode; }

int DatumSubdivision_t::toDatumSubcode() const
{
	switch (m_value)
	{
	case Unknown:
	default:
		return navi_datumsub_NULL;
	}
}

GsaSwitchMode_t GsaSwitchMode_t::fromSwitchModeCode(int code)
{
	switch (code)
	{
	case navi_gsa_Manual: return Manual;
	case navi_gsa_Automatic: return Automatic;
	default:
		return Unknown;
	}
}

GsaSwitchMode_t::GsaSwitchMode_t(enum GsaSwitchMode_t::switchmodes_t mode)
	{ m_value = mode; }

GsaSwitchMode_t::~GsaSwitchMode_t() { }

int GsaSwitchMode_t::toSwitchModeCode() const
{
	switch (m_value)
	{
	case Manual: return navi_gsa_Manual;
	case Automatic: return navi_gsa_Automatic;
	default:
		return -1;
	}
}

GpsQualityIndicator_t GpsQualityIndicator_t::fromQualityCode(int code)
{
	switch (code)
	{
	case navi_gps_Invalid: return GpsInvalid;
	case navi_gps_SpsMode: return GpsSpsMode;
	case navi_gps_Differential: return GpsDifferential;
	case navi_gps_PpsMode: return GpsPpsMode;
	case navi_gps_FixedRtk: return GpsFixedRtk;
	case navi_gps_FloatRtk: return GpsFloatRtk;
	case navi_gps_Estimated: return GpsEstimated;
	case navi_gps_Manual: return GpsManual;
	case navi_gps_Simulator: return GpsSimulator;
	default:
		return Unknown;
	}
}

GpsQualityIndicator_t::GpsQualityIndicator_t(enum qualityIndicators_t mode)
	{ m_value = mode; }

GpsQualityIndicator_t::~GpsQualityIndicator_t() { }

int GpsQualityIndicator_t::toQualityCode() const
{
	switch (m_value)
	{
	case GpsInvalid: return navi_gps_Invalid;
	case GpsSpsMode: return navi_gps_SpsMode;
	case GpsDifferential: return navi_gps_Differential;
	case GpsPpsMode: return navi_gps_PpsMode;
	case GpsFixedRtk: return navi_gps_FixedRtk;
	case GpsFloatRtk: return navi_gps_FloatRtk;
	case GpsEstimated: return navi_gps_Estimated;
	case GpsManual: return navi_gps_Manual;
	case GpsSimulator: return navi_gps_Simulator;
	default:
		return -1;
	}
}

ModeIndicatorArray_t ModeIndicatorArray_t::fromModeIndicators(const int modeArray[])
{
	ModeIndicatorArray_t result;

	for (int i = 0; i < MaxIndicators; i++)
	{
		result.m_array[i] = ModeIndicator_t::fromModeIndCode(modeArray[i]);
	}

	return result;
}

ModeIndicatorArray_t::ModeIndicatorArray_t() { }

ModeIndicatorArray_t::~ModeIndicatorArray_t() { }

void ModeIndicatorArray_t::toModeIndicators(int modeArray[]) const
{
	for (int i = 0; i < MaxIndicators; i++)
	{
		modeArray[i] = m_array[i].toModeIndCode();
	}
}

}

