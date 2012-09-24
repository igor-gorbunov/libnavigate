#ifndef INCLUDE_navi_navigateplusplus
#define INCLUDE_navi_navigateplusplus

namespace libnavigate
{

#include <navigate.h>

#if defined(__GNUC__) && __GNUC__ >= 4
#define NAVI_EXTERN_CLASS(type, name)	type __attribute__((visibility("default"))) name
#elif defined(_MSC_VER)
#define NAVI_EXTERN_CLASS(type, name)	type __declspec(dllexport) name
#else
#define NAVI_EXTERN_CLASS(type, name)	extern type name
#endif // __GNUC__, _MSC_VER or other compiler

	NAVI_EXTERN_CLASS(class, MessageType_t)
	{
	public:
		enum msgtype_t
		{
			Unknown,	// not defined
			AAM,	// waypoint arrival alarm
			ACK,	// acknowledgement alarm
			ALM,	// GPS almanac data
			ALR,	// set alarm state
			APB,	// heading/track controller (Autopilot) sentence B
			BEC,	// bearing and distance to waypoint, dead reckoning
			BOD,	// bearing, origin to destination
			BWC,	// bearing and distance to waypoint
			BWR,	// bearing and distance to waypoint, rhumb line
			BWW,	// bearing, waypoint to waypoint
			DBT,	// depth below transducer
			DCN,	// DECCA position
			DPT,	// depth
			DSC,	// digital selective calling information
			DSE,	// expanded digital selective calling
			DSI,	// DSC transponder initialize
			DSR,	// DSC transponder response
			DTM,	// datum reference
			FSI,	// frequency set information
			GBS,	// GNSS satellite fault detection
			GGA,	// global positioning system fix data
			GLC,	// geographic position, LORAN-C
			GLL,	// geographic position, latitude/longitude
			GNS,	// GNSS fix data
			GRS,	// GNSS range residuals
			GSA,	// GNSS DOP and active satellites
			GST,	// GNSS pseudorange error statistics
			GSV,	// GNSS satellites in view
			HDG,	// heading, deviation and variation
			HDT,	// heading, true
			HMR,	// heading monitor - receive
			HMS,	// heading monitor - set
			HSC,	// heading steering command
			HTC,	// heading/track control command
			HTD,	// heading/track control data
			LCD,	// LORAN-C signal data
			MLA,	// Glonass almanac data
			MSK,	// MSK receiver interface
			MSS,	// MSK receiver signal status
			MTW,	// water temperature
			MWD,	// wind direction and speed
			MWV,	// wind speed and angle
			OSD,	// own ship data
			RMA,	// recommended minimum specific LORAN-C data
			RMB,	// recommended minimum navigation information
			RMC,	// recommended minimum specific GNSS data
			ROT,	// rate of turn
			RPM,	// revolutions
			RSA,	// rudder sensor angle
			RSD,	// radar system data
			RTE,	// routes
			SFI,	// scanning frequency information
			STN,	// multiple data ID
			TLB,	// target label
			TLL,	// target latitude and longitude
			TTM,	// tracked target message
			TXT,	// text transmission
			VBW,	// dual ground/water speed
			VDR,	// set and drift
			VHW,	// water speed and heading
			VLW,	// distance travelled through the water
			VPW,	// speed, measured parallel to wind
			VTG,	// course over ground and ground speed
			WCV,	// waypoint closure velocity
			WNC,	// distance, waypoint to waypoint
			WPL,	// waypoint location
			XDR,	// transducer measurements
			XTE,	// cross-track error, measured
			XTR,	// cross-track error, dead reckoning
			ZDA,	// time and date
			ZDL,	// time and distance to variable point
			ZFO,	// UTC and time from origin waypoint
			ZTG		// UTC and time to destination waypoint
		};

	public:
		MessageType_t();
		MessageType_t(enum MessageType_t::msgtype_t initial);
		MessageType_t(const MessageType_t &right);

		virtual ~MessageType_t();

	public:
		operator int() const;

	private:
		enum msgtype_t m_value;
	};

	NAVI_EXTERN_CLASS(class, TalkerId_t)
	{
	public:
		enum talkerid_t
		{
			Unknown,	// not defined
			// Heading/track controller (autopilot)
			AG,	// general
			AP,	// magnetic
			// Automatic identification system
			AI,
			// Communications:
			CD,	// digital selective calling (DSC)
			CR,	// data receiver
			CS,	// satellite
			CT,	// radio-telephone (MF/HF)
			CV,	// radio-telephone (VHF)
			CX,	// scanning receiver
			// DECCA navigator
			DE,
			// Direction finder
			DF,
			// Electronic chart systems (ECS)
			EC,
			// Electronic chart display and information system (ECDIS)
			EI,
			// Emergency position indicating radio beacon (EPIRB)
			EP,
			// Engine room monitoring systems
			ER,
			// Galileo receiver
			GA,
			// Global positioning system (GPS)
			GP,
			// GLONASS receiver
			GL,
			// Global navigation satellite system (GNSS)
			GN,
			// SBAS receiver
			GW,
			// Heading sensors:
			HC,	// compass, magnetic
			HE,	// gyro, north seeking
			HN,	// gyro, non-north seeking
			// Integrated instrumentation
			II,
			// Integrated navigation
			IN,
			// LORAN: LORAN-C
			LC,
			// Radar and/or radar plotting
			RA,
			// Sounder, depth
			SD,
			// Electronic positioning system, other/general
			SN,
			// Sounder, scanning
			SS,
			// Turn rate indicator
			TI,
			// Velocity sensors:
			VD,	// Doppler, other/general
			VM,	// speed log, water, magnetic
			VW,	// speed log, water, mechanical
			// Voyage data recorder
			VR,
			// Transducer
			YX,
			// Timekeepers, time/date
			ZA,	// atomic clock
			ZC,	// chronometer
			ZQ,	// quartz
			ZV,	// radio update
			// Weather instruments
			WI,
			// Proprietary code
			P
		};

	public:
		TalkerId_t();
		TalkerId_t(enum TalkerId_t::talkerid_t initial);
		TalkerId_t(const TalkerId_t &right);

		virtual ~TalkerId_t();

	public:
		operator int() const;

	private:
		enum talkerid_t m_value;
	};

	NAVI_EXTERN_CLASS(class, NaviError_t)
	{
	public:
		enum errtype_t
		{
			Unknown,			// not defined
			MsgExceedsMaxSize,	// message too long
			CrcEror,			// crc error
			NotEnoughBuffer,	// not enough space in output buffer
			MsgNotSupported,	// message type not supported
			NoValidMessage,		// no valid message in buffer
			NullField,			// null field in a message
			InvalidMessage,		// message does not conform to protocol
			NotImplemented,		// method not implemented
			InvalidParameter	// invalid parameter to method
		};

	public:
		NaviError_t();
		NaviError_t(enum NaviError_t::errtype_t initial);
		NaviError_t(const NaviError_t &right);

		virtual ~NaviError_t();

	public:
		operator int() const;

	private:
		enum errtype_t m_value;
	};

	NAVI_EXTERN_CLASS(class, PositionFix_t)
	{
	public:
		PositionFix_t(double latitude, double longitude)
			{ m_latitude = latitude; m_longitude = longitude; }

	public:
		virtual double latitude() const;
		virtual double longitude() const;

	private:
		double m_latitude;
		double m_longitude;
	};

	NAVI_EXTERN_CLASS(class, Utc_t)
	{
	public:
		Utc_t(int hh, int mm, double ss)
			{ m_hours = hh; m_minutes = mm; m_seconds = ss; }

	public:
		virtual int hours() const
			{ return m_hours; }

		virtual int minutes() const
			{ return m_minutes; }

		virtual double seconds() const
			{ return m_seconds; }

	private:
		int m_hours;
		int m_minutes;
		double m_seconds;
	};

	NAVI_EXTERN_CLASS(class, Status_t)
	{
	public:
		enum status_t
		{
			Unknown,
			DataValid,
			DataInvalid
		};

	public:
		Status_t(enum Status_t::status_t status = Unknown)
			{ m_status = status; }

	public:
		operator int() const
			{ return int(m_status); }

	private:
		enum status_t m_status;
	};

	NAVI_EXTERN_CLASS(class, ModeIndicator_t)
	{
	public:
		enum modeind_t
		{
			Unknown,

			// Satellite system used in non-differential
			// mode in position fix (A)
			Autonomous,

			// Satellite sysytem used in differential
			// mode in position fix (D)
			Differential,

			// Estimated (dead reckoning) mode (E)
			Estimated,

			// Manual input mode (M)
			ManualInput,

			// Simulator mode (S)
			Simulator,

			// No fix. Satellite system not used in
			// position fix, or fix not valid (N)
			DataNotValid,

			//
			// Additions to GNS message

			// Satellite system used in precision mode (P)
			Precise,

			// Satellite system used in Real Time
			// Kinematic mode with fixed integers (R)
			RTKinematic,

			// Satellite system used in Real Time
			// Kinematic mode with floating integers (F)
			FloatRTK
		};

	public:
		ModeIndicator_t(enum ModeIndicator_t::modeind_t mi = Unknown)
			{ m_modeind = mi; }

	public:
		operator int() const
			{ return int(m_modeind); }

	private:
		enum modeind_t m_modeind;
	};

	NAVI_EXTERN_CLASS(class, Message_t)
	{
	public:
		Message_t(const MessageType_t &type)
			{ m_type = type; }

		virtual ~Message_t();

	public:
		virtual const MessageType_t &type() const;

	public:
		virtual operator const void *() const;
		virtual operator void *();

	private:
		MessageType_t m_type;
	};

	NAVI_EXTERN_CLASS(class, Gll_t) : public Message_t
	{
	public:
		Gll_t(const TalkerId_t &tid = TalkerId_t::Unknown);

		virtual ~Gll_t() { }

	public:
		virtual TalkerId_t talkerId() const;
		virtual PositionFix_t positionFix() const;
		virtual Utc_t utc() const;
		virtual Status_t status() const;
		virtual ModeIndicator_t modeIndicator() const;

	public:
		virtual void setTalkerId(const TalkerId_t &tid);
		virtual void setPositionFix(const PositionFix_t &fix);
		virtual void setUtc(const Utc_t &utc);
		virtual void setStatus(const Status_t &status);
		virtual void setModeIndicator(const ModeIndicator_t &mi);

	public:
		virtual operator const void *() const;
		virtual operator void *();

	private:
		struct gll_t m_value;
	};

	NAVI_EXTERN_CLASS(class, Navigate_t)
	{
	public:
		// returns the number of characters written
		// in case of error throws an exception
		int CreateMessage(const Message_t &msg, char *buffer, int maxsize);

		// returns the number of characters read
		// in case of error throws an exception
		Message_t ParseMessage(char *buffer, int maxsize, int *nmread);
	};

	NaviError_t NaviErrorFromErrorCode(int errcode);
	TalkerId_t TalkerIdFromCode(int tid);
	PositionFix_t PositionFixFromPosition(const struct navi_position_t *position);
	Status_t StatusFromCode(int status);
	ModeIndicator_t ModeIndicatorFromCode(int mi);

	int MsgCodeFromMessageType(const MessageType_t &type);
	int TalkerIdCodeFromTalkerId(const TalkerId_t &tid);
	int StatusCodeFromStatus(const Status_t &status);
	int ModeIndicatorCodeFromModeIndicator(const ModeIndicator_t &mi);
}

#endif // INCLUDE_navi_navigateplusplus
