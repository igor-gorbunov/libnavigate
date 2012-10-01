/*
 * sentence.h - supported IEC message definitions
 *
 * Copyright (C) 2012 I. S. Gorbunov <igor.genius at gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INCLUDE_navi_sentence_h
#define INCLUDE_navi_sentence_h

#include <libnavigate/generic.h>

NAVI_BEGIN_DECL

//
// Supported IEC 61162-1 (2000-07) messages
//

// The maximum number of characters in a sentence shall be 82,
// consisting of a maximum of 79 characters between the starting
// delimeter '$' and the terminating delimeter <cr><lf>.
#define NAVI_SENTENCE_MAXSIZE		82

//
// Approved sentence formatters
//
enum _navi_approved_fmt_t
{
	// Unknown or undefined sentence formatter
	navi_approvedfmt_Unknown = -1,

	navi_AAM = 0,	// waypoint arrival alarm
	navi_ACK,	// acknowledgement alarm
	navi_ALM,	// GPS almanac data
	navi_ALR,	// set alarm state
	navi_APB,	// heading/track controller (Autopilot) sentence B
	navi_BEC,	// bearing and distance to waypoint, dead reckoning
	navi_BOD,	// bearing, origin to destination
	navi_BWC,	// bearing and distance to waypoint
	navi_BWR,	// bearing and distance to waypoint, rhumb line
	navi_BWW,	// bearing, waypoint to waypoint
	navi_DBT,	// depth below transducer
	navi_DCN,	// DECCA position
	navi_DPT,	// depth
	navi_DSC,	// digital selective calling information
	navi_DSE,	// expanded digital selective calling
	navi_DSI,	// DSC transponder initialize
	navi_DSR,	// DSC transponder response
	navi_DTM,	// datum reference
	navi_FSI,	// frequency set information
	navi_GBS,	// GNSS satellite fault detection
	navi_GGA,	// global positioning system fix data
	navi_GLC,	// geographic position, LORAN-C
	navi_GLL,	// geographic position, latitude/longitude
	navi_GNS,	// GNSS fix data
	navi_GRS,	// GNSS range residuals
	navi_GSA,	// GNSS DOP and active satellites
	navi_GST,	// GNSS pseudorange error statistics
	navi_GSV,	// GNSS satellites in view
	navi_HDG,	// heading, deviation and variation
	navi_HDT,	// heading, true
	navi_HMR,	// heading monitor - receive
	navi_HMS,	// heading monitor - set
	navi_HSC,	// heading steering command
	navi_HTC,	// heading/track control command
	navi_HTD,	// heading/track control data
	navi_LCD,	// LORAN-C signal data
	navi_MLA,	// Glonass almanac data
	navi_MSK,	// MSK receiver interface
	navi_MSS,	// MSK receiver signal status
	navi_MTW,	// water temperature
	navi_MWD,	// wind direction and speed
	navi_MWV,	// wind speed and angle
	navi_OSD,	// own ship data
	navi_RMA,	// recommended minimum specific LORAN-C data
	navi_RMB,	// recommended minimum navigation information
	navi_RMC,	// recommended minimum specific GNSS data
	navi_ROT,	// rate of turn
	navi_RPM,	// revolutions
	navi_RSA,	// rudder sensor angle
	navi_RSD,	// radar system data
	navi_RTE,	// routes
	navi_SFI,	// scanning frequency information
	navi_STN,	// multiple data ID
	navi_TLB,	// target label
	navi_TLL,	// target latitude and longitude
	navi_TTM,	// tracked target message
	navi_TXT,	// text transmission
	navi_VBW,	// dual ground/water speed
	navi_VDR,	// set and drift
	navi_VHW,	// water speed and heading
	navi_VLW,	// distance travelled through the water
	navi_VPW,	// speed, measured parallel to wind
	navi_VTG,	// course over ground and ground speed
	navi_WCV,	// waypoint closure velocity
	navi_WNC,	// distance, waypoint to waypoint
	navi_WPL,	// waypoint location
	navi_XDR,	// transducer measurements
	navi_XTE,	// cross-track error, measured
	navi_XTR,	// cross-track error, dead reckoning
	navi_ZDA,	// time and date
	navi_ZDL,	// time and distance to variable point
	navi_ZFO,	// UTC and time from origin waypoint
	navi_ZTG	// UTC and time to destination waypoint
};

typedef int navi_approved_fmt_t;

//
// Talker Identifier Mnemonics
//
enum _navi_talkerid_t
{
	// Unknown or undefined talker id
	navi_talkerid_Unknown = -1,

	// Heading/track controller (autopilot)
	navi_AG = 0,	// general
	navi_AP,		// magnetic
	// Automatic identification system
	navi_AI,
	// Communications:
	navi_CD,	// digital selective calling (DSC)
	navi_CR,	// data receiver
	navi_CS,	// satellite
	navi_CT,	// radio-telephone (MF/HF)
	navi_CV,	// radio-telephone (VHF)
	navi_CX,	// scanning receiver
	// DECCA navigator
	navi_DE,
	// Direction finder
	navi_DF,
	// Electronic chart systems (ECS)
	navi_EC,
	// Electronic chart display and information system (ECDIS)
	navi_EI,
	// Emergency position indicating radio beacon (EPIRB)
	navi_EP,
	// Engine room monitoring systems
	navi_ER,
	// Galileo receiver
	navi_GA,
	// Global positioning system (GPS)
	navi_GP,
	// GLONASS receiver
	navi_GL,
	// Global navigation satellite system (GNSS)
	navi_GN,
	// SBAS receiver
	navi_GW,
	// Heading sensors:
	navi_HC,	// compass, magnetic
	navi_HE,	// gyro, north seeking
	navi_HN,	// gyro, non-north seeking
	// Integrated instrumentation
	navi_II,
	// Integrated navigation
	navi_IN,
	// LORAN: LORAN-C
	navi_LC,
	// Radar and/or radar plotting
	navi_RA,
	// Sounder, depth
	navi_SD,
	// Electronic positioning system, other/general
	navi_SN,
	// Sounder, scanning
	navi_SS,
	// Turn rate indicator
	navi_TI,
	// Velocity sensors:
	navi_VD,	// Doppler, other/general
	navi_VM,	// speed log, water, magnetic
	navi_VW,	// speed log, water, mechanical
	// Voyage data recorder
	navi_VR,
	// Transducer
	navi_YX,
	// Timekeepers, time/date
	navi_ZA,	// atomic clock
	navi_ZC,	// chronometer
	navi_ZQ,	// quartz
	navi_ZV,	// radio update
	// Weather instruments
	navi_WI,
	// Proprietary code
	navi_P
};

typedef int navi_talkerid_t;

//
// Local/reference datums
//
enum _navi_datum_t
{
	// Unknown or undefined datum
	navi_datum_NULL = -1,

	// WGS-84
	navi_WGS84,
	// WGS-72
	navi_WGS72,
	// SGS-85
	navi_SGS85,
	// PE-90
	navi_PE90,
	// User defined datum
	navi_UserDefined
};

typedef int navi_datum_t;

//
// Local datum subdivision (from IHO Publication S-60, App. B and C)
//
enum _navi_datum_subdivision_t
{
	// unefined or unsupported local datum
	navi_datumsub_NULL = -1
};

typedef int navi_datum_subdivision_t;

//
// Status
//
enum _navi_status_t
{
	// Data not valid
	navi_status_V = 0,

	// Data valid
	navi_status_A
};

typedef int navi_status_t;

//
// Positioning system Mode Indicator
//
enum _navi_modeindicator_t
{
	// Satellite system used in non-differential
	// mode in position fix (A)
	navi_Autonomous = 0,

	// Satellite sysytem used in differential
	// mode in position fix (D)
	navi_Differential = 1,

	// Estimated (dead reckoning) mode (E)
	navi_Estimated = 2,

	// Manual input mode (M)
	navi_ManualInput = 3,

	// Simulator mode (S)
	navi_Simulator = 4,

	// No fix. Satellite system not used in
	// position fix, or fix not valid (N)
	navi_DataNotValid = 5,

	//
	// Additions to GNS message

	// Satellite system used in precision mode (P)
	navi_Precise = 6,

	// Satellite system used in Real Time
	// Kinematic mode with fixed integers (R)
	navi_RTKinematic = 7,

	// Satellite system used in Real Time
	// Kinematic mode with floating integers (F)
	navi_FloatRTK = 8
};

typedef int navi_modeindicator_t;

//
// GPS quality indicator
//
enum _navi_gpsindicator_t
{
	navi_gps_Invalid = 0,	// Fix not available or invalid
	navi_gps_SpsMode = 1,	// GPS SPS mode, fix valid
	navi_gps_Differential = 2,	// differential GPS, SPS mode, fix valid
	navi_gps_PpsMode = 3,	// GPS PPS mode, fix valid
	navi_gps_FixedRtk = 4,	// Real Time Kinematic. Satellite system used in
							// RTK mode with fixed integers
	navi_gps_FloatRtk = 5,	// Float RTK. Satellite system used in
							// RTK mode with floating integers
	navi_gps_Estimated = 6,	// Estimated (dead reckoning) mode
	navi_gps_Manual = 7,		// Manual input mode
	navi_gps_Simulator = 8	// Simulator mode
};

typedef int navi_gpsindicator_t;

//
// GSA message 2D/3D switching mode
//
enum naviGsaSwitchMode_t
{
	navi_GsaManual = 0,		// manual, forced to operate in 2D or 3D mode
	navi_GsaAutomatic = 1	// automatic, allowed to automatically switch 2D/3D
};

//
// Holds UTC time (hours, minutes and seconds)
//
struct navi_utc_t
{
	int hour, min;
	double sec;
};

//
// Holds UTC date
//
struct navi_date_t
{
	int day, month, year;
};

//
// Offset sign (N/S, E/W)
//
enum _navi_offset_sign_t
{
	// null field
	navi_offsetsign_NULL = - 1,

	// North
	navi_North,
	// South
	navi_South,
	// East
	navi_East,
	// West
	navi_West
};

typedef int navi_offset_sign_t;

//
// Holds offset data
//
struct navi_offset_t
{
	double offset;				// degrees
	navi_offset_sign_t sign;	// N/S or E/W
};

//
// Holds position data
//
struct navi_position_t
{
	double latitude;				// degrees
	navi_offset_sign_t latsign;		// N/S

	double longitude;				// degrees
	navi_offset_sign_t lonsign;		// E/W
};

//
// Holds satellite information for one satellite
//
struct navi_satinfo_t
{
	unsigned vfields;	// valid fields, bitwise or of SATINFO_VALID_xxx
	unsigned id;		// satellite ID number
	unsigned elevation;	// degrees 00-90
	unsigned azimuth;	// degrees true, 000-359
	unsigned snr;		// signal-to-noise ratio, 00-99 dB-Hz, null if not tracking
};

#define SATINFO_VALID_ORIENTATION	0x1
#define SATINFO_VALID_SNR			0x2

//	// Heading/track controller (Autopilot) sentence B
//	struct apb_t
//	{
//	};

//	// Bearing and distance to waypoint, dead reckoning
//	struct bec_t
//	{
//	};

//	// Bearing, origin to destination
//	struct bod_t
//	{
//	};

//	// Bearing and distance to waypoint
//	struct bwc_t
//	{
//	};

//	// Bearing and distance to waypoint, rhumb line
//	struct bwr_t
//	{
//	};

//	// Bearing, waypoint to waypoint
//	struct bww_t
//	{
//	};

//	// Depth below transducer
//	struct dbt_t
//	{
//	};

//	// DECCA position
//	struct dcn_t
//	{
//	};

//	// Depth
//	struct dpt_t
//	{
//	};

//	// Digital selective calling information
//	struct dsc_t
//	{
//	};

//	// Expanded digital selective calling
//	struct dse_t
//	{
//	};

//	// DSC transponder initialise
//	struct dsi_t
//	{
//	};

//	// DSR transponder response
//	struct dsr_t
//	{
//	};

//	// Frequency set information
//	struct fsi_t
//	{
//	};

//	// Geographic position, LORAN-C
//	struct glc_t
//	{
//	};

//
// Geographic position, latitude/longitude
struct gll_t
{
	int tid;				// talker id
	unsigned vfields;		// valid fields, bitwise or of GLL_VALID_xxx
	struct navi_position_t fix;	// latitude, longitude fix
	struct navi_utc_t utc;	// UTC time
	int status;		// status
	int mi;			// mode indicator
};

#define GLL_VALID_POSITION_FIX		0x01
#define GLL_VALID_UTC				0x02

//
// GNSS fix data
struct gns_t
{
	int tid;				// talker id
	unsigned vfields;		// valid fields, bitwise or of GNS_VALID_xxx
	struct navi_utc_t utc;		// UTC time
	struct navi_position_t fix;	// latitude, longitude fix
	int mi[2];				// GPS, GLONASS
	int totalsats;			// Total number of satellites in use, 00-99
	double hdop;			// Horizontal Dilution of Precision
	double antaltitude;		// Antenna altitude, m, re:mean-sea-level (geoid)
	double geoidalsep;		// Geoidal separation, m
	int diffage;			// Age of differential data, seconds
	int id;					// Differential reference station ID, 1-1023
};

#define GNS_VALID_UTC					0x001
#define GNS_VALID_POSITION_FIX			0x002
#define GNS_VALID_MODEINDICATOR			0x004
#define GNS_VALID_TOTALNMOFSATELLITES	0x008
#define GNS_VALID_HDOP					0x010
#define GNS_VALID_ANTENNAALTITUDE		0x020
#define GNS_VALID_GEOIDALSEP			0x040
#define GNS_VALID_AGEOFDIFFDATA			0x080
#define GNS_VALID_DIFFREFSTATIONID		0x100

//
// GNSS range residuals
struct grs_t
{
	int tid;				// talker id
	struct navi_utc_t utc;	// UTC time
	int mode;				// Mode: 
							// 0 = residuals were used to calculate the position
							// given in the matching GGA or GNS sentence
							// 1 = residuals were recomputed after the GGA or GNS
							// position was computed
	struct
	{
		int notnull;		// 0 = null field, 1 = not null
		double residual;	// residual for given satellite ID
	} residuals[12];		// range residuals
};

//
// GNSS DOP and active satellites
struct gsa_t
{
	int tid;				// talker id
	unsigned vfields;		// valid fields, bitwise or of GSA_VALID_xxx
	int switchmode;			// Mode: one of naviGsaSwitchMode_t constants
	int fixmode;			// Mode: 1 = fix not available, 2 = 2D, 3 = 3D
	struct
	{
		int notnull;		// 0 = null field, 1 = not null
		int id;				// ID number of satellite used in solution
	} satellites[12];		// satellites ID numbers array
	double pdop;			// Position dilution of precision
	double hdop;			// Horizontal dilution of precision
	double vdop;			// Vertical dilution of precision
};

#define GSA_VALID_SWITCHMODE	0x01
#define GSA_VALID_FIXMODE		0x02
#define GSA_VALID_PDOP			0x04
#define GSA_VALID_HDOP			0x08
#define GSA_VALID_VDOP			0x10

//
// GNSS pseudorange noise statistics
struct gst_t
{
	int tid;				// talker id
	unsigned vfields;		// valid fields, bitwise or of GST_VALID_xxx
	struct navi_utc_t utc;	// UTC time
	double rms;			// RMS value of the standard deviation
	double devmajor;	// Standard deviation of semi-major axis of error ellipse, m
	double devminor;	// Standard deviation of semi-minor axis of error ellipse, m
	double orientmajor;	// Orientation of semi-major axis of error ellipse,
						// degrees from true north
	double devlaterr;	// Standard deviation of latitude error, m
	double devlonerr;	// Standard deviation of longitude error, m
	double devalterr;	// Standard deviation of altitude error, m
};

#define GST_VALID_RMS				0x1
#define GST_VALID_STDDEVELLIPSE		0x2
#define GST_VALID_DEVLATLONERR		0x4
#define GST_VALID_DEVALTERR			0x8

//
// GNSS satellites in view
struct gsv_t
{
	int tid;			// talker id
	int nmsatellites;	// total number of satellites in view
	struct navi_satinfo_t info[36];	// satellite info array
	int totalnm;	// total number of messages (filled during parsing)
	int msgnm;		// number of received message
};

//	// Heading, deviation and variation
//	struct hdg_t
//	{
//	};

//	// Heading, true
//	struct hdt_t
//	{
//	};

//	// Heading monitor - receive
//	struct hmr_t
//	{
//	};

//	// Heading monitor - set
//	struct hms_t
//	{
//	};

//	// Heading steering command
//	struct hsc_t
//	{
//	};

//	// Heading/track control command
//	struct htc_t
//	{
//	};

//	// Heading/track control data
//	struct htd_t
//	{
//	};

//	// LORAN-C signal data
//	struct lcd_t
//	{
//	};

//	// MKS receiver interface
//	struct msk_t
//	{
//	};

//	// MKS receiver signal status
//	struct mss_t
//	{
//	};

//	// Water temperature
//	struct mtw_t
//	{
//	};

//	// Wind direction and speed
//	struct mwd_t
//	{
//	};

//	// Wind speed and angle
//	struct mwv_t
//	{
//	};

//	// Own ship data
//	struct osd_t
//	{
//	};

//	// Recommended minimum specific LORAN-C data
//	struct rma_t
//	{
//	};

//	// Recommended minimum navigation information
//	struct rmb_t
//	{
//	};

//	// Rate of turn
//	struct rot_t
//	{
//	};

//	// Revolutions
//	struct rpm_t
//	{
//	};

//	// Revolutions
//	struct rpm_t
//	{
//	};

//	// Rudder sensor angle
//	struct rsa_t
//	{
//	};

//	// Radar system data
//	struct rsd_t
//	{
//	};

//	// Routes
//	struct rte_t
//	{
//	};

//	// Scanning frequency information
//	struct sfi_t
//	{
//	};

//	// Multiple data ID
//	struct stn_t
//	{
//	};

//	// Target label
//	struct tlb_t
//	{
//	};

//	// Target latitude and longitude
//	struct tll_t
//	{
//	};

//	// Tracked target message
//	struct ttm_t
//	{
//	};

//	// Dual ground/water speed
//	struct vbw_t
//	{
//	};

//	// Set and drift
//	struct vdr_t
//	{
//	};

//	// Water speed and heading
//	struct vhw_t
//	{
//	};

//	// Distance travelled thourgh the water
//	struct vlw_t
//	{
//	};

//	// Speed, measured parallel to wind
//	struct vpw_t
//	{
//	};

//	// Waypoint closure velocity
//	struct wcv_t
//	{
//	};

//	// Distance, waypoint to waypoint
//	struct wnc_t
//	{
//	};

//	// Waypoint location
//	struct wpl_t
//	{
//	};

//	// Transducer measurements
//	struct xdr_t
//	{
//	};

//	// Cross-track error, measured
//	struct xte_t
//	{
//	};

//	// Cross-track error, dead reckoning
//	struct xtr_t
//	{
//	};

//	// Time and distance to variable point
//	struct zdl_t
//	{
//	};

//	// UTC and time from origin waypoint
//	struct zfo_t
//	{
//	};

//	// UTC and time to destination waypoint
//	struct ztg_t
//	{
//	};

NAVI_END_DECL

#endif // INCLUDE_navi_sentence_h
