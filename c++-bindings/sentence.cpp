#include <libnavigate/c++/sentence.hpp>

namespace libnavigate
{

int MessageType_t::toSentenceFormatter() const
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
		return -1;
	}
}

MessageType_t MessageType_t::fromSentenceFormatter(int type)
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

TalkerId_t TalkerId_t::fromTalkerIdCode(int tid)
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

int TalkerId_t::toTalkerIdCode() const
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
		return -1;
	}
}

PositionFix_t PositionFix_t::fromPosition(const struct navi_position_t *position)
{
	double latitude, longitude;
	navi_get_position(position, &latitude, &longitude);
	return PositionFix_t(latitude, longitude);
}

Status_t Status_t::fromStatusCode(int status)
{
	switch (status)
	{
	case navi_DataValid: return DataValid;
	case navi_DataInvalid: return DataInvalid;
	default:
		return Unknown;
	}
}

int Status_t::toStatusCode() const
{
	switch (m_value)
	{
	case DataValid: return navi_DataValid;
	case DataInvalid: return navi_DataInvalid;
	default:
		return -1;
	}
}

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

}

