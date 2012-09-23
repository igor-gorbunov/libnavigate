#include <navigate++.hpp>

namespace libnavigate
{

	MessageType_t::MessageType_t() { m_value = Unknown; }

	MessageType_t::MessageType_t(enum MessageType_t::msgtype_t initial) { m_value = initial; }

	MessageType_t::MessageType_t(const MessageType_t &right) { m_value = right.m_value; }

	MessageType_t::~MessageType_t() { }

	MessageType_t::operator int() const
	{
		return int(m_value);
	}

	NaviError_t::NaviError_t() { m_value = Unknown; }

	NaviError_t::NaviError_t(enum NaviError_t::errtype_t initial) { m_value = initial; }

	NaviError_t::NaviError_t(const NaviError_t &right) { m_value = right.m_value; }

	NaviError_t::~NaviError_t() { }

	NaviError_t::operator int() const
	{
		return int(m_value);
	}

	NaviError_t Navigate_t::NaviErrorFromErrorCode(int errcode)
	{
		switch (errcode)
		{
		case navi_MsgExceedsMaxSize:
			return NaviError_t(NaviError_t::MsgExceedsMaxSize);
		case navi_CrcEror:
			return NaviError_t(NaviError_t::CrcEror);
		case navi_NotEnoughBuffer:
			return NaviError_t(NaviError_t::NotEnoughBuffer);
		case navi_MsgNotSupported:
			return NaviError_t(NaviError_t::MsgNotSupported);
		case navi_NoValidMessage:
			return NaviError_t(NaviError_t::NoValidMessage);
		case navi_NullField:
			return NaviError_t(NaviError_t::NullField);
		case navi_InvalidMessage:
			return NaviError_t(NaviError_t::InvalidMessage);
		case navi_NotImplemented:
			return NaviError_t(NaviError_t::NotImplemented);
		case navi_InvalidParameter:
			return NaviError_t(NaviError_t::InvalidParameter);
		case navi_Undefined:
		default:
			return NaviError_t(NaviError_t::Unknown);
		}
	}

	int Navigate_t::MsgCodeFromMessageType(const MessageType_t &type)
	{
		switch (type)
		{
		case MessageType_t::AAM:
			return navi_AAM;
		case MessageType_t::ACK:
			return navi_ACK;
		case MessageType_t::ALM:
			return navi_ALM;
		case MessageType_t::ALR:
			return navi_ALR;
		case MessageType_t::APB:
			return navi_APB;
		case MessageType_t::BEC:
			return navi_BEC;
		case MessageType_t::BOD:
			return navi_BOD;
		case MessageType_t::BWC:
			return navi_BWC;
		case MessageType_t::BWR:
			return navi_BWR;
		case MessageType_t::BWW:
			return navi_BWW;
		case MessageType_t::DBT:
			return navi_DBT;
		case MessageType_t::DCN:
			return navi_DCN;
		case MessageType_t::DPT:
			return navi_DPT;
		case MessageType_t::DSC:
			return navi_DSC;
		case MessageType_t::DSE:
			return navi_DSE;
		case MessageType_t::DSI:
			return navi_DSI;
		case MessageType_t::DSR:
			return navi_DSR;
		case MessageType_t::DTM:
			return navi_DTM;
		case MessageType_t::FSI:
			return navi_FSI;
		case MessageType_t::GBS:
			return navi_GBS;
		case MessageType_t::GGA:
			return navi_GGA;
		case MessageType_t::GLC:
			return navi_GLC;
		case MessageType_t::GLL:
			return navi_GLL;
		case MessageType_t::GNS:
			return navi_GNS;
		case MessageType_t::GRS:
			return navi_GRS;
		case MessageType_t::GSA:
			return navi_GSA;
		case MessageType_t::GST:
			return navi_GST;
		case MessageType_t::GSV:
			return navi_GSV;
		case MessageType_t::HDG:
			return navi_HDG;
		case MessageType_t::HDT:
			return navi_HDT;
		case MessageType_t::HMR:
			return navi_HMR;
		case MessageType_t::HMS:
			return navi_HMS;
		case MessageType_t::HSC:
			return navi_HSC;
		case MessageType_t::HTC:
			return navi_HTC;
		case MessageType_t::HTD:
			return navi_HTD;
		case MessageType_t::LCD:
			return navi_LCD;
		case MessageType_t::MLA:
			return navi_MLA;
		case MessageType_t::MSK:
			return navi_MSK;
		case MessageType_t::MSS:
			return navi_MSS;
		case MessageType_t::MTW:
			return navi_MTW;
		case MessageType_t::MWD:
			return navi_MWD;
		case MessageType_t::MWV:
			return navi_MWV;
		case MessageType_t::OSD:
			return navi_OSD;
		case MessageType_t::RMA:
			return navi_RMA;
		case MessageType_t::RMB:
			return navi_RMB;
		case MessageType_t::RMC:
			return navi_RMC;
		case MessageType_t::ROT:
			return navi_ROT;
		case MessageType_t::RPM:
			return navi_RPM;
		case MessageType_t::RSA:
			return navi_RSA;
		case MessageType_t::RSD:
			return navi_RSD;
		case MessageType_t::RTE:
			return navi_RTE;
		case MessageType_t::SFI:
			return navi_SFI;
		case MessageType_t::STN:
			return navi_STN;
		case MessageType_t::TLB:
			return navi_TLB;
		case MessageType_t::TLL:
			return navi_TLL;
		case MessageType_t::TTM:
			return navi_TTM;
		case MessageType_t::TXT:
			return navi_TXT;
		case MessageType_t::VBW:
			return navi_VBW;
		case MessageType_t::VDR:
			return navi_VDR;
		case MessageType_t::VHW:
			return navi_VHW;
		case MessageType_t::VLW:
			return navi_VLW;
		case MessageType_t::VPW:
			return navi_VPW;
		case MessageType_t::VTG:
			return navi_VTG;
		case MessageType_t::WCV:
			return navi_WCV;
		case MessageType_t::WNC:
			return navi_WNC;
		case MessageType_t::WPL:
			return navi_WPL;
		case MessageType_t::XDR:
			return navi_XDR;
		case MessageType_t::XTE:
			return navi_XTE;
		case MessageType_t::XTR:
			return navi_XTR;
		case MessageType_t::ZDA:
			return navi_ZDA;
		case MessageType_t::ZDL:
			return navi_ZDL;
		case MessageType_t::ZFO:
			return navi_ZFO;
		case MessageType_t::ZTG:
			return navi_ZTG;
		default:
			throw NaviError_t(NaviError_t::InvalidParameter);
		}
	}
}
