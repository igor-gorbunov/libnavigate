#ifndef INCLUDE_navi_navigateplusplus
#define INCLUDE_navi_navigateplusplus

namespace libnavigate
{

#include <navigate.h>

	class NAVI_EXTERN(MessageType_t)
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

	private:
		enum msgtype_t m_value;
	};

	class NAVI_EXTERN(TalkerId_t)
	{
	};

	class NAVI_EXTERN(NaviError_t)
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

	class NAVI_EXTERN(Navigate_t)
	{
	public:
		// returns the number of characters written
		// in case of error throws an exception
		int CreateMessage(const MessageType_t &type, void *msg, char *buffer, int maxsize);

		// returns the number of characters read
		// in case of error throws an exception
		int ParseMessage(char *buffer, int maxsize, int msgsize, MessageType_t &type, void *msg);
	};

}

#endif // INCLUDE_navi_navigateplusplus
