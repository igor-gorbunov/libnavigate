/*
 * iecsentence.h - supported IEC message definitions
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

#ifndef IEC_SENTENCE_H
#define IEC_SENTENCE_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//
// Supported IEC 61162-1 (2000-07) messages
//

// The maximum number of characters in a sentence shall be 82,
// consisting of a maximum of 79 characters between the starting
// delimeter '$' and the terminating delimeter <cr><lf>.
#define NAVI_SENTENCE_MAXSIZE		82

//
// Possible errors while generation/parsing
//
enum naviError_t
{
	naviError_OK = 0	// no error
};

//
// Approved sentence formatters
//
enum naviSentence_t
{
	naviSentence_Undefined = -1,	// unefined or unsupported sentence

	naviSentence_AAM = 0,	// waypoint arrival alarm
	naviSentence_ACK = 1,	// acknowledgement alarm
	naviSentence_ALM = 2,	// GPS almanac data
	naviSentence_ALR = 3,	// set alarm state
	naviSentence_APB = 4,	// heading/track controller (Autopilot) sentence B
	naviSentence_BEC = 5,	// bearing and distance to waypoint, dead reckoning
	naviSentence_BOD = 6,	// bearing, origin to destination
	naviSentence_BWC = 7,	// bearing and distance to waypoint
	naviSentence_BWR = 8,	// bearing and distance to waypoint, rhumb line
	naviSentence_BWW = 9,	// bearing, waypoint to waypoint
	naviSentence_DBT = 10,	// depth below transducer
	naviSentence_DCN = 11,	// DECCA position
	naviSentence_DPT = 12,	// depth
	naviSentence_DSC = 13,	// digital selective calling information
	naviSentence_DSE = 14,	// expanded digital selective calling
	naviSentence_DSI = 15,	// DSC transponder initialize
	naviSentence_DSR = 16,	// DSC transponder response
	naviSentence_DTM = 17,	// datum reference
	naviSentence_FSI = 18,	// frequency set information
	naviSentence_GBS = 19,	// GNSS satellite fault detection
	naviSentence_GGA = 20,	// global positioning system fix data
	naviSentence_GLC = 21,	// geographic position, LORAN-C
	naviSentence_GLL = 22,	// geographic position, latitude/longitude
	naviSentence_GNS = 23,	// GNSS fix data
	naviSentence_GRS = 24,	// GNSS range residuals
	naviSentence_GSA = 25,	// GNSS DOP and active satellites
	naviSentence_GST = 26,	// GNSS pseudorange error statistics
	naviSentence_GSV = 27,	// GNSS satellites in view
	naviSentence_HDG = 28,	// heading, deviation and variation
	naviSentence_HDT = 29,	// heading, true
	naviSentence_HMR = 30,	// heading monitor - receive
	naviSentence_HMS = 31,	// heading monitor - set
	naviSentence_HSC = 32,	// heading steering command
	naviSentence_HTC = 33,	// heading/track control command
	naviSentence_HTD = 34,	// heading/track control data
	naviSentence_LCD = 35,	// LORAN-C signal data
	naviSentence_MLA = 36,	// Glonass almanac data
	naviSentence_MSK = 37,	// MSK receiver interface
	naviSentence_MSS = 38,	// MSK receiver signal status
	naviSentence_MTW = 39,	// water temperature
	naviSentence_MWD = 40,	// wind direction and speed
	naviSentence_MWV = 41,	// wind speed and angle
	naviSentence_OSD = 42,	// own ship data
	naviSentence_RMA = 43,	// recommended minimum specific LORAN-C data
	naviSentence_RMB = 44,	// recommended minimum navigation information
	naviSentence_RMC = 45,	// recommended minimum specific GNSS data
	naviSentence_ROT = 46,	// rate of turn
	naviSentence_RPM = 47,	// revolutions
	naviSentence_RSA = 48,	// rudder sensor angle
	naviSentence_RSD = 49,	// radar system data
	naviSentence_RTE = 50,	// routes
	naviSentence_SFI = 51,	// scanning frequency information
	naviSentence_STN = 52,	// multiple data ID
	naviSentence_TLB = 53,	// target label
	naviSentence_TLL = 54,	// target latitude and longitude
	naviSentence_TTM = 55,	// tracked target message
	naviSentence_TXT = 56,	// text transmission
	naviSentence_VBW = 57,	// dual ground/water speed
	naviSentence_VDR = 58,	// set and drift
	naviSentence_VHW = 59,	// water speed and heading
	naviSentence_VLW = 60,	// distance travelled through the water
	naviSentence_VPW = 61,	// speed, measured parallel to wind
	naviSentence_VTG = 62,	// course over ground and ground speed
	naviSentence_WCV = 63,	// waypoint closure velocity
	naviSentence_WNC = 64,	// distance, waypoint to waypoint
	naviSentence_WPL = 65,	// waypoint location
	naviSentence_XDR = 66,	// transducer measurements
	naviSentence_XTE = 67,	// cross-track error, measured
	naviSentence_XTR = 68,	// cross-track error, dead reckoning
	naviSentence_ZDA = 69,	// time and date
	naviSentence_ZDL = 70,	// time and distance to variable point
	naviSentence_ZFO = 71,	// UTC and time from origin waypoint
	naviSentence_ZTG = 72	// UTC and time to destination waypoint
};

//
// Talker Identifier Mnemonics
//
enum naviTalkerId_t
{
	naviTalkerId_Undefined = -1,	// unefined or unsupported talker id

	// Heading/track controller (autopilot)
	naviTalkerId_AG = 0,	// general
	naviTalkerId_AP = 1,	// magnetic
	// Automatic identification system
	naviTalkerId_AI = 2,
	// Communications:
	naviTalkerId_CD = 3,	// digital selective calling (DSC)
	naviTalkerId_CR = 4,	// data receiver
	naviTalkerId_CS = 5,	// satellite
	naviTalkerId_CT = 6,	// radio-telephone (MF/HF)
	naviTalkerId_CV = 7,	// radio-telephone (VHF)
	naviTalkerId_CX = 8,	// scanning receiver
	// DECCA navigator
	naviTalkerId_DE = 9,
	// Direction finder
	naviTalkerId_DF = 10,
	// Electronic chart systems (ECS)
	naviTalkerId_EC = 11,
	// Electronic chart display and information system (ECDIS)
	naviTalkerId_EI = 12,
	// Emergency position indicating radio beacon (EPIRB)
	naviTalkerId_EP = 13,
	// Engine room monitoring systems
	naviTalkerId_ER = 14,
	// Galileo receiver
	naviTalkerId_GA = 15,
	// Global positioning system (GPS)
	naviTalkerId_GP = 16,
	// GLONASS receiver
	naviTalkerId_GL = 17,
	// Global navigation satellite system (GNSS)
	naviTalkerId_GN = 18,
	// SBAS receiver
	naviTalkerId_GW = 19,
	// Heading sensors:
	naviTalkerId_HC = 20,	// compass, magnetic
	naviTalkerId_HE = 21,	// gyro, north seeking
	naviTalkerId_HN = 22,	// gyro, non-north seeking
	// Integrated instrumentation
	naviTalkerId_II = 23,
	// Integrated navigation
	naviTalkerId_IN = 24,
	// LORAN: LORAN-C
	naviTalkerId_LC = 25,
	// Proprietary code
	naviTalkerId_P = 26,
	// Radar and/or radar plotting
	naviTalkerId_RA = 27,
	// Sounder, depth
	naviTalkerId_SD = 28,
	// Electronic positioning system, other/general
	naviTalkerId_SN = 29,
	// Sounder, scanning
	naviTalkerId_SS = 30,
	// Turn rate indicator
	naviTalkerId_TI = 31,
	// Velocity sensors:
	naviTalkerId_VD = 32,	// Doppler, other/general
	naviTalkerId_VM = 33,	// speed log, water, magnetic
	naviTalkerId_VW = 34,	// speed log, water, mechanical
	// Voyage data recorder
	naviTalkerId_VR = 35,
	// Transducer
	naviTalkerId_YX = 36,
	// Timekeepers, time/date
	naviTalkerId_ZA = 37,	// atomic clock
	naviTalkerId_ZC = 38,	// chronometer
	naviTalkerId_ZQ = 39,	// quartz
	naviTalkerId_ZV = 40,	// radio update
	// Weather instruments
	naviTalkerId_WI = 41
};

//
// Local/reference datums
//
enum naviDatum_t
{
	_WGS84 = 0,
	_WGS72 = 1,
	_SGS85 = 2,
	_PE90 = 3,
	_UserDefined = 4
};

enum naviOffsetSign_t
{
	_North = 0, // North
	_South = 1,	// South
	_East = 2,	// East
	_West = 3	// West
};

enum naviStatus_t
{
	_DataValid = 0,		// A = data valid
	_DataInvalid = 1	// V = data invalid
};

enum naviModeIndicator_t
{
	// Satellite system used in non-differential mode in position fix
	_Autonomous = 0,

	// Satellite sysytem used in differential mode in position fix
	_Differential = 1,

	// Estimated (dead reckoning) mode
	_Estimated = 2,

	// Manual input mode
	_ManualInput = 3,

	// Simulator mode
	_Simulator = 4,

	// No fix. Satellite system not used in position fix, or fix not valid
	_DataNotValid = 5,

	//
	// Additions to GNS message

	// Satellite system used in precision mode
	_Precise = 6,

	// Satellite system used in Real Time Kinematic mode with fixed integers
	_RTKinematic = 7,

	// Satellite system used in Real Time Kinematic mode with
	// floating integers
	_FloatRTK = 8
};

struct naviUtc_t
{
	int hour, min, sec, msec;
};

struct naviOffset_t
{
	double offset;					// degrees or minutes
	enum naviOffsetSign_t offsign;	// N/S or E/W
};

enum naviLocalDatumSub_t
{
	_ToBeDefined
};

//	// Waypoint arrival alarm
//	struct aam_t
//	{
//	};

//	// Acknowledgement alarm
//	struct ack_t
//	{
//	};

//	// GPS almanac data
//	struct alm_t
//	{
//	};

//	// Set alarm state
//	struct alr_t
//	{
//	};

//	// Heading/track controller (Autopilot) sentence B
//	struct alr_t
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

//
// Datum reference
struct dtm_t
{
	enum naviTalkerId_t tid;
	unsigned vfields;		// valid fields, bitwise or of DTM_VALID_xxx
	enum naviDatum_t ld;			// local datum
	enum naviLocalDatumSub_t lds;	// local datum subdivision code
	struct naviOffset_t latofs;		// latitude offset, min,N/S
	struct naviOffset_t lonofs;		// longitude offset, min,E/W
	double altoffset;				// altitude offset, m
	enum naviDatum_t rd;			// reference datum
};

#define DTM_VALID_LOCALDATUM		0x01
#define DTM_VALID_LOCALDATUMSUB		0x02
#define DTM_VALID_LATOFFSET			0x04
#define DTM_VALID_LONOFFSET			0x08
#define DTM_VALID_ALTITUDEOFFSET	0x10
#define DTM_VALID_REFERENCEDATUM	0x20

//	// Frequency set information
//	struct fsi_t
//	{
//	};

//	// GNSS Satellite fault detection
//	struct gbs_t
//	{
//	};

//	// Global positioning system fix data
//	struct gga_t
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
	enum naviTalkerId_t tid;
	unsigned vfields;		// valid fields, bitwise or of GLL_VALID_xxx
	struct naviOffset_t latitude;	// latitude, degrees,N/S
	struct naviOffset_t longitude;	// longitude, degrees,E/W
	struct naviUtc_t utc;
	enum naviStatus_t status;
	enum naviModeIndicator_t mi;
};

#define GLL_VALID_LATITUDE		0x01
#define GLL_VALID_LONGITUDE		0x02
#define GLL_VALID_UTC			0x04

//
// GNSS fix data
struct gns_t
{
	enum naviTalkerId_t tid;
	unsigned vfields;		// valid fields, bitwise or of GNS_VALID_xxx
	struct naviUtc_t utc;
	struct naviOffset_t latitude;	// latitude, degrees,N/S
	struct naviOffset_t longitude;	// longitude, degrees,E/W
	enum naviModeIndicator_t mi[2];	// GPS, GLONASS
	int totalsats;			// Total number of satellites in use, 00-99
	double hdop;			// Horizontal Dilution of Precision
	double antaltitude;		// Antenna altitude, m, re:mean-sea-level (geoid)
	double geoidalsep;		// Geoidal separation, m
	double diffage;			// Age of differential data
	int id;					// Differential reference station ID
};

#define GNS_VALID_UTC					0x001
#define GNS_VALID_LATITUDE				0x002
#define GNS_VALID_LONGITUDE				0x004
#define GNS_VALID_MODEINDICATOR			0x008
#define GNS_VALID_TOTALNMOFSATELLITES	0x010
#define GNS_VALID_HDOP					0x020
#define GNS_VALID_ANTENNAALTITUDE		0x040
#define GNS_VALID_GEOIDALSEP			0x080
#define GNS_VALID_AGEOFDIFFDATA			0x100
#define GNS_VALID_DIFFREFSTATIONID		0x200

//	// GNSS range residuals
//	struct grs_t
//	{
//	};

//	// GNSS DOP and active satellites
//	struct gsa_t
//	{
//	};

//	// GNSS pseudorange error statistics
//	struct gst_t
//	{
//	};

//	// GNSS satellites in view
//	struct gsv_t
//	{
//	};

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

//	// Glonass almanac data
//	struct mla_t
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

//
// Recommended minimum specific GNSS data
struct rmc_t
{
	enum naviTalkerId_t tid;
	unsigned vfields;		// valid fields, bitwise or of RMC_VALID_xxx
	struct naviUtc_t utc;
	enum naviStatus_t status;
	struct naviOffset_t latitude;	// latitude, degrees,N/S
	struct naviOffset_t longitude;	// longitude, degrees,E/W
	double speed;			// Speed over ground, knots
	double courseTrue;		// Course over ground, degrees true
	int day, month, year;	// Day (01 to 31), Month (01 to 12), Year (UTC)
	struct naviOffset_t magnetic;	// Magnetic variation, degrees,E/W
	enum naviModeIndicator_t mi;
};

#define RMC_VALID_UTC				0x01
#define RMC_VALID_LATITUDE			0x02
#define RMC_VALID_LONGITUDE			0x04
#define RMC_VALID_SPEED				0x08
#define RMC_VALID_COURSETRUE		0x10
#define RMC_VALID_DATE				0x20
#define RMC_VALID_MAGNVARIATION		0x40

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

//	// Text transmission
//	struct txt_t
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

//
// Cource over ground and ground speed
struct vtg_t
{
	enum naviTalkerId_t tid;
	unsigned vfields;		// valid fields, bitwise or of ValidFields_t
	double courseTrue;		// Course over ground, degrees true
	double courseMagn;		// Course over ground, degrees magnetic
	double speed;			// Speed over ground, m/s
	enum naviModeIndicator_t mi;
};

#define VTG_VALID_COURSETRUE	0x01
#define VTG_VALID_COURSEMAGN	0x02
#define VTG_VALID_SPEED			0x04

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

//
// Time and date
struct zda_t
{
	enum naviTalkerId_t tid;
	unsigned vfields;		// valid fields, bitwise or of ValidFields_t
	struct naviUtc_t utc;
	int day, month, year;	// Day (01 to 31), Month (01 to 12), Year (UTC)
	int lzoffset;			// Local zone offset in minutes
};

#define ZDA_VALID_UTC			0x01
#define ZDA_VALID_DAY			0x02
#define ZDA_VALID_MONTH			0x04
#define ZDA_VALID_YEAR			0x08
#define ZDA_VALID_LOCALZONE		0x10

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

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // IEC_SENTENCE_H

