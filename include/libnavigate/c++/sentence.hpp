#ifndef INCLUDE_navi_sentenceplusplus
#define INCLUDE_navi_sentenceplusplus

#include <libnavigate/sentence.h>
#include <libnavigate/generator.h>
#include <libnavigate/parser.h>

#include <libnavigate/c++/generic.hpp>

namespace libnavigate
{

NAVI_EXTERN_CLASS(MessageType_t)
{
public:
	enum msgtype_t
	{
		Unknown,	// unknown or not defined
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
	static MessageType_t fromSentenceFormatter(navi_approved_fmt_t type);

public:
	MessageType_t();
	MessageType_t(enum MessageType_t::msgtype_t initial);
	MessageType_t(const MessageType_t &right);

	virtual ~MessageType_t();

public:
	inline operator int() const
		{ return int(m_value); }

public:
	virtual navi_approved_fmt_t toSentenceFormatter() const;

private:
	enum msgtype_t m_value;
};

NAVI_EXTERN_CLASS(TalkerId_t)
{
public:
	enum talkerid_t
	{
		Unknown,	// unknown or not defined
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
	static TalkerId_t fromTalkerIdCode(navi_talkerid_t tid);

public:
	TalkerId_t();
	TalkerId_t(enum TalkerId_t::talkerid_t initial);
	TalkerId_t(const TalkerId_t &right);

	virtual ~TalkerId_t();

public:
	inline operator int() const
		{ return int(m_value); }

public:
	virtual navi_talkerid_t toTalkerIdCode() const;

private:
	enum talkerid_t m_value;
};

NAVI_EXTERN_CLASS(Datum_t)
{
public:
	static Datum_t fromDatumCode(int code);

public:
	enum datums_t
		{ Unknown, WGS84, WGS72, SGS85, PE90, UserDefined };

public:
	Datum_t(enum datums_t datum = Unknown);
	virtual ~Datum_t();

public:
	virtual enum datums_t datum() const;

public:
	virtual void setDatum(enum datums_t datum);

public:
	inline operator int() const
		{ return int(m_value); }

public:
	virtual int toDatumCode() const;

private:
	enum datums_t m_value;
};

NAVI_EXTERN_CLASS(DatumSubdivision_t)
{
public:
	static DatumSubdivision_t fromDatumSubcode(int subcode);

public:
	enum datumsubcodes_t
		{ Unknown };

public:
	DatumSubdivision_t(enum datumsubcodes_t datumsubcode = Unknown);
	virtual ~DatumSubdivision_t();

public:
	virtual enum datumsubcodes_t datumSubcode() const;

public:
	virtual void setDatum(enum datumsubcodes_t datumSubcode);

public:
	inline operator int() const
		{ return int(m_value); }

public:
	virtual int toDatumSubcode() const;

private:
	enum datumsubcodes_t m_value;
};

NAVI_EXTERN_CLASS(PositionFix_t)
{
public:
	static PositionFix_t fromPosition(const struct navi_position_t *position);

public:
	PositionFix_t(double latitude, double longitude);
	virtual ~PositionFix_t();

public:
	virtual double latitude() const;
	virtual double longitude() const;

public:
	virtual struct navi_position_t toPosition() const;

private:
	double m_latitude;
	double m_longitude;
};

NAVI_EXTERN_CLASS(Utc_t)
{
public:
	static Utc_t fromUtcStruct(const struct navi_utc_t &utc);

public:
	Utc_t(int hh, int mm, double ss);
	virtual ~Utc_t();

public:
	virtual int hours() const;
	virtual int minutes() const;
	virtual double seconds() const;

public:
	struct navi_utc_t toUtcStruct() const;

private:
	int m_hours;
	int m_minutes;
	double m_seconds;
};

NAVI_EXTERN_CLASS(Date_t)
{
public:
	static Date_t fromDateStruct(const struct navi_date_t &date);

public:
	Date_t(int yy, int mm, int dd);
	virtual ~Date_t();

public:
	virtual int year() const;
	virtual int month() const;
	virtual int day() const;

public:
	virtual struct navi_date_t toDateStruct() const;

private:
	int m_year;
	int m_month;
	int m_day;
};

NAVI_EXTERN_CLASS(Offset_t)
{
public:
	enum quarters_t
	{
		Unknown, North, South, East, West
	};

public:
	static Offset_t fromOffset(const struct navi_offset_t *offset);

	static enum quarters_t quarterFromCode(int quarter);
	static int quarterToCode(enum quarters_t quarter);

public:
	Offset_t(double offset, enum quarters_t quarter);
	virtual ~Offset_t();

public:
	virtual double offset() const;
	virtual enum quarters_t quarter() const;

public:
	virtual void setOffset(double offset);
	virtual void setQuarter(enum quarters_t quarter);

public:
	virtual struct navi_offset_t toOffset() const;

private:
	double m_offset;
	enum quarters_t m_quarter;
};

NAVI_EXTERN_CLASS(Status_t)
{
public:
	static Status_t fromStatusCode(int status);

public:
	enum status_t
	{
		Unknown,		// unknown or not defined
		DataValid,		// A = data valid
		DataInvalid		// V = data invalid
	};

public:
	Status_t(enum status_t status = Unknown);
	virtual ~Status_t();

public:
	inline operator int() const
		{ return int(m_value); }

public:
	virtual int toStatusCode() const;

private:
	enum status_t m_value;
};

NAVI_EXTERN_CLASS(ModeIndicator_t)
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
	static ModeIndicator_t fromModeIndCode(int mi);

public:
	ModeIndicator_t(enum modeind_t mi = Unknown);
	virtual ~ModeIndicator_t();

public:
	inline operator int() const
		{ return int(m_value); }

public:
	virtual int toModeIndCode() const;

private:
	enum modeind_t m_value;
};

NAVI_EXTERN_CLASS(GsaSwitchMode_t)
{
public:
	static GsaSwitchMode_t fromSwitchModeCode(int code);

public:
	enum switchmodes_t
		{ Unknown, Manual, Automatic };

public:
	GsaSwitchMode_t(enum switchmodes_t mode = Unknown);
	virtual ~GsaSwitchMode_t();

public:
	inline operator int() const
		{ return int(m_value); }

public:
	virtual int toSwitchModeCode() const;

private:
	enum switchmodes_t m_value;
};

NAVI_EXTERN_CLASS(GpsQualityIndicator_t)
{
public:
	static GpsQualityIndicator_t fromQualityCode(int code);

public:
	enum qualityIndicators_t
	{
		Unknown,
		GpsInvalid,
		GpsSpsMode,
		GpsDifferential,
		GpsPpsMode,
		GpsFixedRtk,
		GpsFloatRtk,
		GpsEstimated,
		GpsManual,
		GpsSimulator
	};

public:
	GpsQualityIndicator_t(enum qualityIndicators_t mode = Unknown);
	virtual ~GpsQualityIndicator_t();

public:
	inline operator int() const
		{ return int(m_value); }

public:
	virtual int toQualityCode() const;

private:
	enum qualityIndicators_t m_value;
};

NAVI_EXTERN_CLASS(ModeIndicatorArray_t)
{
public:
	static const int MaxIndicators = 2;

public:
	static ModeIndicatorArray_t fromModeIndicators(const int modeArray[]);

public:
	ModeIndicatorArray_t();
	virtual ~ModeIndicatorArray_t();

public:
	virtual void toModeIndicators(int modeArray[]) const;

private:
	ModeIndicator_t m_array[MaxIndicators];
};

NAVI_EXTERN_CLASS(Message_t)
{
public:
	Message_t(const MessageType_t &type);
	Message_t(const MessageType_t &type, const void *data);
	Message_t(const Message_t &right);
	virtual ~Message_t();

public:
	virtual const MessageType_t &type() const;

public:
	virtual void clearMessage();

public:
	virtual operator const void *() const
		{ return (const void *)m_data; }

	virtual operator void *()
		{ return m_data; }

private:
	void setType(const MessageType_t &type);

private:
	MessageType_t m_type;
	int m_size;
	void *m_data;
};

}

#endif // INCLUDE_navi_sentenceplusplus
