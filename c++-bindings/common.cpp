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

	NaviError_t NaviErrorFromErrorCode(int errcode)
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

	int MsgCodeFromMessageType(const MessageType_t &type)
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

	TalkerId_t::TalkerId_t(enum TalkerId_t::talkerid_t initial)
	{
		m_value = initial;
	}

	TalkerId_t::~TalkerId_t() { }

	Message_t::~Message_t() { }

	const MessageType_t &Message_t::type() const
	{
		return m_type;
	}

	Message_t::operator void *() { return 0; }

	Message_t::operator const void *() const { return 0; }

	Gll_t::operator const void *() const { return (const void *)&m_value; }

	Gll_t::operator void *() { return &m_value; }

	TalkerId_t Gll_t::talkerId() const
	{
		return TalkerIdFromCode(m_value.tid);
	}

	TalkerId_t TalkerIdFromCode(int tid)
	{
		switch (tid)
		{
		case navi_AG:
			return TalkerId_t::AG;
		case navi_AP:
			return TalkerId_t::AP;
		case navi_AI:
			return TalkerId_t::AI;
		case navi_CD:
			return TalkerId_t::CD;
		case navi_CR:
			return TalkerId_t::CR;
		case navi_CS:
			return TalkerId_t::CS;
		case navi_CT:
			return TalkerId_t::CT;
		case navi_CV:
			return TalkerId_t::CV;
		case navi_CX:
			return TalkerId_t::CX;
		case navi_DE:
			return TalkerId_t::DE;
		case navi_DF:
			return TalkerId_t::DF;
		case navi_EC:
			return TalkerId_t::EC;
		case navi_EI:
			return TalkerId_t::EI;
		case navi_EP:
			return TalkerId_t::EP;
		case navi_ER:
			return TalkerId_t::ER;
		case navi_GA:
			return TalkerId_t::GA;
		case navi_GP:
			return TalkerId_t::GP;
		case navi_GL:
			return TalkerId_t::GL;
		case navi_GN:
			return TalkerId_t::GN;
		case navi_GW:
			return TalkerId_t::GW;
		case navi_HC:
			return TalkerId_t::HC;
		case navi_HE:
			return TalkerId_t::HE;
		case navi_HN:
			return TalkerId_t::HN;
		case navi_II:
			return TalkerId_t::II;
		case navi_IN:
			return TalkerId_t::IN;
		case navi_LC:
			return TalkerId_t::LC;
		case navi_RA:
			return TalkerId_t::RA;
		case navi_SD:
			return TalkerId_t::SD;
		case navi_SN:
			return TalkerId_t::SN;
		case navi_SS:
			return TalkerId_t::SS;
		case navi_TI:
			return TalkerId_t::TI;
		case navi_VD:
			return TalkerId_t::VD;
		case navi_VM:
			return TalkerId_t::VM;
		case navi_VW:
			return TalkerId_t::VW;
		case navi_VR:
			return TalkerId_t::VR;
		case navi_YX:
			return TalkerId_t::YX;
		case navi_ZA:
			return TalkerId_t::ZA;
		case navi_ZC:
			return TalkerId_t::ZC;
		case navi_ZQ:
			return TalkerId_t::ZQ;
		case navi_ZV:
			return TalkerId_t::ZV;
		case navi_WI:
			return TalkerId_t::WI;
		case navi_P:
			return TalkerId_t::P;
		default:
			return TalkerId_t::Unknown;
		}
	}

	PositionFix_t PositionFixFromPosition(const struct navi_position_t *position)
	{
		double latitude, longitude;

		navi_get_position(position, &latitude, &longitude);

		return PositionFix_t(latitude, longitude);
	}

	PositionFix_t Gll_t::positionFix() const
	{
		return PositionFixFromPosition(&m_value.fix);
	}

	Utc_t Gll_t::utc() const
	{
		return Utc_t(m_value.utc.hour, m_value.utc.min, m_value.utc.sec);
	}

	Status_t Gll_t::status() const
	{
		return StatusFromCode(m_value.status);
	}

	ModeIndicator_t Gll_t::modeIndicator() const
	{
		return ModeIndicatorFromCode(m_value.mi);
	}

	Status_t StatusFromCode(int status)
	{
		switch (status)
		{
		case navi_DataValid:
			return Status_t::DataValid;
		case navi_DataInvalid:
			return Status_t::DataInvalid;
		default:
			return Status_t::Unknown;
		}
	}

	ModeIndicator_t ModeIndicatorFromCode(int mi)
	{
		switch (mi)
		{
		case navi_Autonomous:
			return ModeIndicator_t::Autonomous;
		case navi_Differential:
			return ModeIndicator_t::Differential;
		case navi_Estimated:
			return ModeIndicator_t::Estimated;
		case navi_ManualInput:
			return ModeIndicator_t::ManualInput;
		case navi_Simulator:
			return ModeIndicator_t::Simulator;
		case navi_DataNotValid:
			return ModeIndicator_t::DataNotValid;
		case navi_Precise:
			return ModeIndicator_t::Precise;
		case navi_RTKinematic:
			return ModeIndicator_t::RTKinematic;
		case navi_FloatRTK:
			return ModeIndicator_t::FloatRTK;
		default:
			return ModeIndicator_t::Unknown;
		}
	}

	Gll_t::Gll_t(const TalkerId_t &tid) : Message_t(MessageType_t::GLL)
	{
		m_value.tid = TalkerIdCodeFromTalkerId(tid);
		m_value.vfields = 0;
	}

	TalkerId_t::operator int() const
	{
		return int(m_value);
	}

	int TalkerIdCodeFromTalkerId(const TalkerId_t &tid)
	{
		switch (tid)
		{
		case TalkerId_t::AG:
			return navi_AG;
		case TalkerId_t::AP:
			return navi_AP;
		case TalkerId_t::AI:
			return navi_AI;
		case TalkerId_t::CD:
			return navi_CD;
		case TalkerId_t::CR:
			return navi_CR;
		case TalkerId_t::CS:
			return navi_CS;
		case TalkerId_t::CT:
			return navi_CT;
		case TalkerId_t::CV:
			return navi_CV;
		case TalkerId_t::CX:
			return navi_CX;
		case TalkerId_t::DE:
			return navi_DE;
		case TalkerId_t::DF:
			return navi_DF;
		case TalkerId_t::EC:
			return navi_EC;
		case TalkerId_t::EI:
			return navi_EI;
		case TalkerId_t::EP:
			return navi_EP;
		case TalkerId_t::ER:
			return navi_ER;
		case TalkerId_t::GA:
			return navi_GA;
		case TalkerId_t::GP:
			return navi_GP;
		case TalkerId_t::GL:
			return navi_GL;
		case TalkerId_t::GN:
			return navi_GN;
		case TalkerId_t::GW:
			return navi_GW;
		case TalkerId_t::HC:
			return navi_HC;
		case TalkerId_t::HE:
			return navi_HE;
		case TalkerId_t::HN:
			return navi_HN;
		case TalkerId_t::II:
			return navi_II;
		case TalkerId_t::IN:
			return navi_IN;
		case TalkerId_t::LC:
			return navi_LC;
		case TalkerId_t::RA:
			return navi_RA;
		case TalkerId_t::SD:
			return navi_SD;
		case TalkerId_t::SN:
			return navi_SN;
		case TalkerId_t::SS:
			return navi_SS;
		case TalkerId_t::TI:
			return navi_TI;
		case TalkerId_t::VD:
			return navi_VD;
		case TalkerId_t::VM:
			return navi_VM;
		case TalkerId_t::VW:
			return navi_VW;
		case TalkerId_t::VR:
			return navi_VR;
		case TalkerId_t::YX:
			return navi_YX;
		case TalkerId_t::ZA:
			return navi_ZA;
		case TalkerId_t::ZC:
			return navi_ZC;
		case TalkerId_t::ZQ:
			return navi_ZQ;
		case TalkerId_t::ZV:
			return navi_ZV;
		case TalkerId_t::WI:
			return navi_WI;
		case TalkerId_t::P:
			return navi_P;
		default:
			return -1;
		}
	}

	void Gll_t::setTalkerId(const TalkerId_t &tid)
	{
		m_value.tid = TalkerIdCodeFromTalkerId(tid);
	}

	void Gll_t::setPositionFix(const PositionFix_t &fix)
	{
		navi_set_position(fix.latitude(), fix.longitude(), &m_value.fix);
		m_value.vfields |= GLL_VALID_POSITION_FIX;
	}

	double PositionFix_t::latitude() const { return m_latitude; }

	double PositionFix_t::longitude() const  { return m_longitude; }

	void Gll_t::setUtc(const Utc_t &utc)
	{
		m_value.utc.hour = utc.hours();
		m_value.utc.min = utc.minutes();
		m_value.utc.sec = utc.seconds();
		m_value.vfields |= GLL_VALID_UTC;
	}

	void Gll_t::setStatus(const Status_t &status)
	{
		m_value.status = StatusCodeFromStatus(status);
	}

	void Gll_t::setModeIndicator(const ModeIndicator_t &mi)
	{
		m_value.mi = ModeIndicatorCodeFromModeIndicator(mi);
	}

	int StatusCodeFromStatus(const Status_t &status)
	{
		switch (status)
		{
		case Status_t::DataValid:
			return navi_DataValid;
		case Status_t::DataInvalid:
			return navi_DataInvalid;
		default:
			return -1;
		}
	}

	int ModeIndicatorCodeFromModeIndicator(const ModeIndicator_t &mi)
	{
		switch (mi)
		{
		case ModeIndicator_t::Autonomous:
			return navi_Autonomous;
		case ModeIndicator_t::Differential:
			return navi_Differential;
		case ModeIndicator_t::Estimated:
			return navi_Estimated;
		case ModeIndicator_t::ManualInput:
			return navi_ManualInput;
		case ModeIndicator_t::Simulator:
			return navi_Simulator;
		case ModeIndicator_t::DataNotValid:
			return navi_DataNotValid;
		case ModeIndicator_t::Precise:
			return navi_Precise;
		case ModeIndicator_t::RTKinematic:
			return navi_RTKinematic;
		case ModeIndicator_t::FloatRTK:
			return navi_FloatRTK;
		default:
			return -1;
		}
	}
}

