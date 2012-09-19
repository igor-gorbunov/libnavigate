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

#include "generic.h"

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
enum naviFormatter_t
{
	navi_AAM,	// waypoint arrival alarm
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

//
// Talker Identifier Mnemonics
//
enum naviTalkerId_t
{
	// Heading/track controller (autopilot)
	navi_AG,	// general
	navi_AP,	// magnetic
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

//
// Local/reference datums
//
enum
{
	navi_WGS84,
	navi_WGS72,
	navi_SGS85,
	navi_PE90,
	navi_UserDefined
};

//
// Local datum subdivision (from IHO Publication S-60, App. B and C)
//
enum
{
	navi_Null = -1	// unefined or unsupported local datum
};

//
// Status of PVT solution
//
enum
{
	navi_DataValid = 0,		// A = data valid
	navi_DataInvalid = 1	// V = data invalid
};

//
// Positioning system Mode Indicator
//
enum
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

//
// Holds UTC time (hours, minutes, seconds and
// decimal fraction of seconds)
//
NAVI_ALIGNED(struct, navi_utc_t)
{
	int hour, min;
	double sec;
};

//
// Holds UTC date
//
NAVI_ALIGNED(struct, navi_date_t)
{
	int day, month, year;
};

//
// Offset sign (N/S, E/W)
//
enum
{
	navi_North,		// N
	navi_South,		// S
	navi_East,		// E
	navi_West		// W
};

//
// Holds offset data (x.x,a)
//
NAVI_ALIGNED(struct, navi_offset_t)
{
	double offset;	// degrees/minutes
	int sign;		// N/S or E/W
};

//
// Holds position data
//
NAVI_ALIGNED(struct, navi_position_t)
{
	double latitude;	// degrees
	int latsign;		// N/S
	double longitude;	// degrees
	int lonsign;		// E/W
};

//
// Holds GPS almanac data for one satellite
//
NAVI_ALIGNED(struct, navi_gpsalm_t)
{
	unsigned vfields;		// valid fields, bitwise or of GPSALM_VALID_xxx
	unsigned satelliteprn;	// 01 to 32
	unsigned gpsweek;		// 0 to 9999
	unsigned svhealth;		// SV health
	unsigned e;				// eccentricity
	unsigned toa;			// almanac reference time
	unsigned sigmai;		// inclination angle
	unsigned omegadot;		// rate of right ascension
	unsigned sqrtsemiaxis;	// root of semi-major axis
	unsigned omega;			// argument of perigee
	unsigned omega0;		// longitude of ascension node
	unsigned m0;			// mean anomaly
	unsigned af0;			// clock parameter
	unsigned af1;			// clock parameter
};

#define GPSALM_VALID_SATELLITEPRN		0x0001
#define GPSALM_VALID_GPSWEEK			0x0002
#define GPSALM_VALID_SVHEALTH			0x0004
#define GPSALM_VALID_E					0x0008
#define GPSALM_VALID_TOA				0x0010
#define GPSALM_VALID_SIGMAI				0x0020
#define GPSALM_VALID_OMEGADOT			0x0040
#define GPSALM_VALID_SQRTSEMIAXIS		0x0080
#define GPSALM_VALID_OMEGA				0x0100
#define GPSALM_VALID_OMEGA0				0x0200
#define GPSALM_VALID_M0					0x0400
#define GPSALM_VALID_AF0				0x0800
#define GPSALM_VALID_AF1				0x1000

//	// Waypoint arrival alarm
//	struct aam_t
//	{
//	};

//	// Acknowledgement alarm
//	struct ack_t
//	{
//	};

// GPS almanac data
NAVI_ALIGNED(struct, alm_t)
{
	int tid;				// talker id
	int nmsatellites;		// number of satellites in the almlist array
	struct navi_gpsalm_t almlist[32];	// almanacs of GPS satellites
	int totalnm;	// total number of messages (filled during parsing)
	int msgnm;		// number of received message
};

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
NAVI_ALIGNED(struct, dtm_t)
{
	int tid;				// talker id
	unsigned vfields;		// valid fields, bitwise or of DTM_VALID_xxx
	int locdatum;			// local datum
	int locdatumsub;		// local datum subdivision code
	struct navi_offset_t latofs;	// latitude offset, min, N/S
	struct navi_offset_t lonofs;	// longitude offset, min, E/W
	double altoffset;		// altitude offset, m
	int refdatum;			// reference datum
};

#define DTM_VALID_LOCALDATUM		0x01
#define DTM_VALID_LOCALDATUMSUB		0x02
#define DTM_VALID_OFFSET			0x04
#define DTM_VALID_ALTOFFSET			0x08
#define DTM_VALID_REFDATUM			0x10

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
NAVI_ALIGNED(struct, gll_t)
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
NAVI_ALIGNED(struct, gns_t)
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
	double diffage;			// Age of differential data
	int id;					// Differential reference station ID
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
NAVI_ALIGNED(struct, rmc_t)
{
	int tid;				// talker id
	unsigned vfields;		// valid fields, bitwise or of RMC_VALID_xxx
	struct navi_utc_t utc;	// UTC time
	int status;				// status
	struct navi_position_t fix;	// latitude, longitude fix
	double speed;				// Speed over ground, knots
	double courseTrue;			// Course over ground, degrees true
	struct navi_date_t date;	// Day (01 to 31), Month (01 to 12), Year (UTC)
	struct navi_offset_t magnetic;	// Magnetic variation, degrees,E/W
	int mi;						// mode indicator
};

#define RMC_VALID_UTC				0x01
#define RMC_VALID_POSITION_FIX		0x02
#define RMC_VALID_SPEED				0x04
#define RMC_VALID_COURSETRUE		0x08
#define RMC_VALID_DATE				0x10
#define RMC_VALID_MAGNVARIATION		0x20

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
NAVI_ALIGNED(struct, vtg_t)
{
	int tid;			// talker id
	unsigned vfields;	// valid fields, bitwise or of ValidFields_t
	double courseTrue;	// Course over ground, degrees true
	double courseMagn;	// Course over ground, degrees magnetic
	double speed;		// Speed over ground, m/s
	int mi;				// Mode indicator
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
NAVI_ALIGNED(struct, zda_t)
{
	int tid;				// talker id
	unsigned vfields;		// valid fields, bitwise or of ValidFields_t
	struct navi_utc_t utc;	// UTC time
	struct navi_date_t date;	// Day (01 to 31), Month (01 to 12), Year (UTC)
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

NAVI_END_DECL

#endif // INCLUDE_navi_sentence_h
