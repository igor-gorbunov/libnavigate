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
		case MessageType_t::ACK:
		case MessageType_t::ALM:
		case MessageType_t::ALR:
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
		case MessageType_t::DTM:
		case MessageType_t::FSI:
		case MessageType_t::GBS:
		case MessageType_t::GGA:
		case MessageType_t::GLC:
		case MessageType_t::GLL:
		case MessageType_t::GNS:
		case MessageType_t::GRS:
		case MessageType_t::GSA:
		case MessageType_t::GST:
		case MessageType_t::GSV:
		case MessageType_t::HDG:
		case MessageType_t::HDT:
		case MessageType_t::HMR:
		case MessageType_t::HMS:
		case MessageType_t::HSC:
		case MessageType_t::HTC:
		case MessageType_t::HTD:
		case MessageType_t::LCD:
		case MessageType_t::MLA:
		case MessageType_t::MSK:
		case MessageType_t::MSS:
		case MessageType_t::MTW:
		case MessageType_t::MWD:
		case MessageType_t::MWV:
		case MessageType_t::OSD:
		case MessageType_t::RMA:
		case MessageType_t::RMB:
		case MessageType_t::RMC:
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
		case MessageType_t::TXT:
		case MessageType_t::VBW:
		case MessageType_t::VDR:
		case MessageType_t::VHW:
		case MessageType_t::VLW:
		case MessageType_t::VPW:
		case MessageType_t::VTG:
		case MessageType_t::WCV:
		case MessageType_t::WNC:
		case MessageType_t::WPL:
		case MessageType_t::XDR:
		case MessageType_t::XTE:
		case MessageType_t::XTR:
		case MessageType_t::ZDA:
		case MessageType_t::ZDL:
		case MessageType_t::ZFO:
		case MessageType_t::ZTG:
		default:
			throw NaviError_t(NaviError_t::InvalidParameter);
		}
	}
}
