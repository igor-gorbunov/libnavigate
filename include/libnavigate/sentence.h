/*
 * sentence.h - supported IEC message definitions
 *
 * Copyright (C) 2012, 2013 I. S. Gorbunov <igor.genius at gmail.com>
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

/*! @file sentence.h
 *  @brief Declares the common structures and functions.
 *
 *  Contains declarations for structures describing address fields,
 *  approved formatters and supported IEC 61162-1 (2000-07) messages.
 */

#ifndef INCLUDE_navi_sentence_h
#define INCLUDE_navi_sentence_h

#include "generic.h"
#include "errors.h"

NAVI_BEGIN_DECL

//! @brief Maximum message length
//!
//! The maximum number of characters in a sentence shall be 82,
//! consisting of a maximum of 79 characters between the starting
//! delimeter '$' and the terminating delimeter &lt;cr&gt;&lt;lf&gt;.
#define NAVI_SENTENCE_MAXSIZE		82

//! @brief Address field types
enum _navi_addrfield_t
{
	//! Unknown or undefined type
	navi_af_Unknown = -1,

	//! Approved address field
	navi_af_Approved = 0,

	//! Query address field
	navi_af_Query,

	//! Proprietary address field
	navi_af_Proprietary
};

//! @brief Address field type
typedef int navi_addrfield_t;

//! @brief Approved sentence formatters
enum _navi_approved_fmt_t
{
	//! Unknown or undefined sentence formatter
	navi_approvedfmt_Unknown = -1,

	navi_AAM = 0,	//!< waypoint arrival alarm
	navi_ACK,	//!< acknowledgement alarm
	navi_ALM,	//!< GPS almanac data
	navi_ALR,	//!< set alarm state
	navi_APB,	//!< heading/track controller (Autopilot) sentence B
	navi_BEC,	//!< bearing and distance to waypoint, dead reckoning
	navi_BOD,	//!< bearing, origin to destination
	navi_BWC,	//!< bearing and distance to waypoint
	navi_BWR,	//!< bearing and distance to waypoint, rhumb line
	navi_BWW,	//!< bearing, waypoint to waypoint
	navi_DBT,	//!< depth below transducer
	navi_DCN,	//!< DECCA position
	navi_DPT,	//!< depth
	navi_DSC,	//!< digital selective calling information
	navi_DSE,	//!< expanded digital selective calling
	navi_DSI,	//!< DSC transponder initialize
	navi_DSR,	//!< DSC transponder response
	navi_DTM,	//!< datum reference
	navi_FSI,	//!< frequency set information
	navi_GBS,	//!< GNSS satellite fault detection
	navi_GGA,	//!< global positioning system fix data
	navi_GLC,	//!< geographic position, LORAN-C
	navi_GLL,	//!< geographic position, latitude/longitude
	navi_GNS,	//!< GNSS fix data
	navi_GRS,	//!< GNSS range residuals
	navi_GSA,	//!< GNSS DOP and active satellites
	navi_GST,	//!< GNSS pseudorange error statistics
	navi_GSV,	//!< GNSS satellites in view
	navi_HDG,	//!< heading, deviation and variation
	navi_HDT,	//!< heading, true
	navi_HMR,	//!< heading monitor - receive
	navi_HMS,	//!< heading monitor - set
	navi_HSC,	//!< heading steering command
	navi_HTC,	//!< heading/track control command
	navi_HTD,	//!< heading/track control data
	navi_LCD,	//!< LORAN-C signal data
	navi_MLA,	//!< Glonass almanac data
	navi_MSK,	//!< MSK receiver interface
	navi_MSS,	//!< MSK receiver signal status
	navi_MTW,	//!< water temperature
	navi_MWD,	//!< wind direction and speed
	navi_MWV,	//!< wind speed and angle
	navi_OSD,	//!< own ship data
	navi_RMA,	//!< recommended minimum specific LORAN-C data
	navi_RMB,	//!< recommended minimum navigation information
	navi_RMC,	//!< recommended minimum specific GNSS data
	navi_ROT,	//!< rate of turn
	navi_RPM,	//!< revolutions
	navi_RSA,	//!< rudder sensor angle
	navi_RSD,	//!< radar system data
	navi_RTE,	//!< routes
	navi_SFI,	//!< scanning frequency information
	navi_STN,	//!< multiple data ID
	navi_TLB,	//!< target label
	navi_TLL,	//!< target latitude and longitude
	navi_TTM,	//!< tracked target message
	navi_TXT,	//!< text transmission
	navi_VBW,	//!< dual ground/water speed
	navi_VDR,	//!< set and drift
	navi_VHW,	//!< water speed and heading
	navi_VLW,	//!< distance travelled through the water
	navi_VPW,	//!< speed, measured parallel to wind
	navi_VTG,	//!< course over ground and ground speed
	navi_WCV,	//!< waypoint closure velocity
	navi_WNC,	//!< distance, waypoint to waypoint
	navi_WPL,	//!< waypoint location
	navi_XDR,	//!< transducer measurements
	navi_XTE,	//!< cross-track error, measured
	navi_XTR,	//!< cross-track error, dead reckoning
	navi_ZDA,	//!< time and date
	navi_ZDL,	//!< time and distance to variable point
	navi_ZFO,	//!< UTC and time from origin waypoint
	navi_ZTG	//!< UTC and time to destination waypoint
};

//! @brief Approved sentence formatter
typedef int navi_approved_fmt_t;

//! @brief Talker Identifier Mnemonics
enum _navi_talkerid_t
{
	//! Unknown or undefined talker id
	navi_talkerid_Unknown = -1,

	//! Heading/track controller (autopilot)
	navi_AG = 0,	//!< Autopilot general
	navi_AP,		//!< Autopilot magnetic

	//! Automatic identification system
	navi_AI,

	//! Communications:
	navi_CD,	//!< digital selective calling (DSC)
	navi_CR,	//!< data receiver
	navi_CS,	//!< satellite
	navi_CT,	//!< radio-telephone (MF/HF)
	navi_CV,	//!< radio-telephone (VHF)
	navi_CX,	//!< scanning receiver

	//! DECCA navigator
	navi_DE,

	//! Direction finder
	navi_DF,

	//! Electronic chart systems (ECS)
	navi_EC,

	//! Electronic chart display and information system (ECDIS)
	navi_EI,

	//! Emergency position indicating radio beacon (EPIRB)
	navi_EP,

	//! Engine room monitoring systems
	navi_ER,

	//! Galileo receiver
	navi_GA,

	//! Global positioning system (GPS)
	navi_GP,

	//! GLONASS receiver
	navi_GL,

	//! Global navigation satellite system (GNSS)
	navi_GN,

	//! SBAS receiver
	navi_GW,

	//! Heading sensors:
	navi_HC,	//!< compass, magnetic
	navi_HE,	//!< gyro, north seeking
	navi_HN,	//!< gyro, non-north seeking

	//! Integrated instrumentation
	navi_II,

	//! Integrated navigation
	navi_IN,

	//! LORAN: LORAN-C
	navi_LC,

	//! Radar and/or radar plotting
	navi_RA,

	//! Sounder, depth
	navi_SD,

	//! Electronic positioning system, other/general
	navi_SN,

	//! Sounder, scanning
	navi_SS,

	//! Turn rate indicator
	navi_TI,

	//! Velocity sensors:
	navi_VD,	//!< Doppler, other/general
	navi_VM,	//!< speed log, water, magnetic
	navi_VW,	//!< speed log, water, mechanical

	//! Voyage data recorder
	navi_VR,

	//! Transducer
	navi_YX,

	//! Timekeepers, time/date
	navi_ZA,	//!< atomic clock
	navi_ZC,	//!< chronometer
	navi_ZQ,	//!< quartz
	navi_ZV,	//!< radio update

	//! Weather instruments
	navi_WI
};

//! @brief Talker Identifier
typedef int navi_talkerid_t;

//! @brief Approved address field components.
struct approved_field_t
{
	navi_approved_fmt_t afmt;	//!< Approved formatter
	navi_talkerid_t tid;		//!< Talker identifier of the sentence
};

//! @brief Query address field components
struct query_field_t
{
	navi_talkerid_t from;	//!< source talker identifier
	navi_talkerid_t to;		//!< target talker identifier
};

//! @brief Local/reference datums
enum _navi_datum_t
{
	//! Unknown or undefined datum
	navi_datum_NULL = -1,

	//! WGS-84
	navi_WGS84,
	//! WGS-72
	navi_WGS72,
	//! SGS-85
	navi_SGS85,
	//! PE-90
	navi_PE90,
	//! User defined datum
	navi_UserDefined
};

//! @brief Local/reference datum
typedef int navi_datum_t;

//! @brief Local datum subdivisions (from IHO Publication S-60, App. B and C)
enum _navi_datum_subdivision_t
{
	//! unefined or unsupported local datum
	navi_datumsub_NULL = -1
};

//! @brief Local datum subdivision
typedef int navi_datum_subdivision_t;

//! @brief Statuses
enum _navi_status_t
{
	//! Unefined or unsupported status
	navi_status_NULL = -1,

	//! Data not valid
	navi_status_V = 0,

	//! Data valid
	navi_status_A
};

//! @brief Status
typedef int navi_status_t;

//! @brief Positioning system Mode Indicators
enum _navi_modeindicator_t
{
	//! @brief Satellite system used in non-differential
	//! mode in position fix (A)
	navi_Autonomous = 0,

	//! @brief Satellite sysytem used in differential
	//! mode in position fix (D)
	navi_Differential = 1,

	//! @brief Estimated (dead reckoning) mode (E)
	navi_Estimated = 2,

	//! @brief Manual input mode (M)
	navi_ManualInput = 3,

	//! @brief Simulator mode (S)
	navi_Simulator = 4,

	//! @brief No fix. Satellite system not used in
	//! position fix, or fix not valid (N)
	navi_DataNotValid = 5,

	//
	// Additions to GNS message

	//! @brief Satellite system used in precision mode (P)
	navi_Precise = 6,

	//! @brief Satellite system used in Real Time
	//! Kinematic mode with fixed integers (R)
	navi_RTKinematic = 7,

	//! @brief Satellite system used in Real Time
	//! Kinematic mode with floating integers (F)
	navi_FloatRTK = 8
};

//! @brief Positioning system Mode Indicator
typedef int navi_modeindicator_t;

//! @brief GPS quality indicators
enum _navi_gpsindicator_t
{
	navi_gps_Invalid = 0,	//!< Fix not available or invalid
	navi_gps_SpsMode,		//!< GPS SPS mode, fix valid
	navi_gps_Differential,	//!< differential GPS, SPS mode, fix valid
	navi_gps_PpsMode,		//!< GPS PPS mode, fix valid
	navi_gps_FixedRtk,		//!< Real Time Kinematic. Satellite system used in
							//!< RTK mode with fixed integers
	navi_gps_FloatRtk,		//!< Float RTK. Satellite system used in
							//!< RTK mode with floating integers
	navi_gps_Estimated,		//!< Estimated (dead reckoning) mode
	navi_gps_Manual,		//!< Manual input mode
	navi_gps_Simulator		//!< Simulator mode
};

//! @brief GPS quality indicator
typedef int navi_gpsindicator_t;

//! @brief GSA message 2D/3D switching modes
enum _navi_gsaswitchmode_t
{
	navi_gsa_NULL = -1,		//!< undefined or unknown mode

	navi_gsa_Manual = 0,	//!< manual, forced to operate in 2D or 3D mode
	navi_gsa_Automatic		//!< automatic, allowed to automatically switch 2D/3D
};

//! @brief GSA message 2D/3D switching mode
typedef int navi_gsaswitchmode_t;

//! @brief UTC time (hours, minutes and seconds)
struct navi_utc_t
{
	int hour;	//!< UTC hours
	int min;	//!< UTC minutes
	double sec;	//!< UTC seconds
};

//! @brief Fills UTC structure with null values
NAVI_EXTERN(navierr_status_t) navi_init_utc(struct navi_utc_t *utc);

//! @brief Fills UTC structure with given values
NAVI_EXTERN(navierr_status_t) navi_init_utc_from_hhmmss(int hh, int mm,
	double ss, struct navi_utc_t *utc);

//! @brief Checks if the utc structure contains valid values
//!
//! Returns navi_Ok, if the field is not null, otherwise returns navi_Error
//! and sets last error to navi_NullField
NAVI_EXTERN(navierr_status_t) navi_check_validity_utc(const struct navi_utc_t *utc);

//! @brief UTC date
//!
//! Contains UTC day, month and year.
struct navi_date_t
{
	int day;	//!< UTC day
	int month;	//!< UTC month
	int year;	//!< UTC year
};

//! @brief Fills date structure with given values
NAVI_EXTERN(navierr_status_t) navi_init_date(int yy, int mm, int dd,
	struct navi_date_t *date);

//! @brief Offset signs (N/S, E/W, L/R, T/M)
enum _navi_offset_sign_t
{
	//! null field
	navi_offset_NULL = -1,

	//! North
	navi_North,
	//! South
	navi_South,
	//! East
	navi_East,
	//! West
	navi_West,
	//! Left
	navi_Left,
	//! Right
	navi_Right,
	//! True
	navi_True,
	//! Magnetic
	navi_Magnetic
};

//! @brief Offset signs (N/S, E/W, L/R, T/M)
typedef int navi_offset_sign_t;

//! @brief Offset value
struct navi_offset_t
{
	double offset;				//!< degrees, nautical miles or other
	navi_offset_sign_t sign;	//!< N/S, E/W, L/R, M/T, or null field
};

//! @brief Fills offset structure with null value
NAVI_EXTERN(navierr_status_t) navi_init_offset(struct navi_offset_t *ofs);

//! @brief Fills offset structure with given values in degrees
NAVI_EXTERN(navierr_status_t) navi_init_offset_from_degrees(double offset,
	navi_offset_sign_t sign, struct navi_offset_t *ofs);

//! @brief Fills offset structure with given values in radians
NAVI_EXTERN(navierr_status_t) navi_init_offset_from_radians(double offset,
	navi_offset_sign_t sign, struct navi_offset_t *ofs);

//! @brief Checks if the offset structure contains valid values
//!
//! Returns navi_Ok, if the field is not null, otherwise returns navi_Error
//! and sets last error to navi_NullField
NAVI_EXTERN(navierr_status_t) navi_check_validity_offset(const struct navi_offset_t *offset);

//! @brief Positioning data
struct navi_position_t
{
	struct navi_offset_t latitude;		//!< (degrees, N/S) or null field
	struct navi_offset_t longitude;		//!< (degrees, E/W) or null field
};

//! @brief Fills position fix structure with null value
NAVI_EXTERN(navierr_status_t) navi_init_position(struct navi_position_t *fix);

//! @brief Fills position fix structure with given values in degrees.
//!
//! Latitude is provided in the range of [-pi/2, +pi/2] and the result is within
//! [90°S, 90°N].
//! The longitude is provided in the range of [-pi, +2pi) and result is within
//! [180°W, 180°E). Thus, the input range of [0, +pi) is treated as [0, 180°E)
//! and the ranges of [-pi, 0) or [+pi, +2pi] are [180°W, 0]
NAVI_EXTERN(navierr_status_t) navi_init_position_from_degrees(double latitude,
	double longitude, struct navi_position_t *fix);

//! @brief Fills position fix structure with given values in radians.
//!
//! Latitude is provided in the range of [-pi/2, +pi/2] and the result is within
//! [90°S, 90°N].
//! The longitude is provided in the range of [-pi, +2pi) and result is within
//! [180°W, 180°E). Thus, the input range of [0, +pi) is treated as [0, 180°E)
//! and the ranges of [-pi, 0) or [+pi, +2pi] are [180°W, 0]
NAVI_EXTERN(navierr_status_t) navi_init_position_from_radians(double latitude,
	double longitude, struct navi_position_t *fix);

//! @brief Checks if the position structure contains valid values
//!
//! Returns navi_Ok, if the field is not null, otherwise returns navi_Error
//! and sets last error to navi_NullField
NAVI_EXTERN(navierr_status_t) navi_check_validity_position(const struct navi_position_t *fix);

//! @brief Fills variable number with null value
NAVI_EXTERN(navierr_status_t) navi_init_number(double *number);

//! @brief Checks if the variable number is valid
//!
//! Returns navi_Ok, if the field is not null, otherwise returns navi_Error
//! and sets last error to navi_NullField
NAVI_EXTERN(navierr_status_t) navi_check_validity_number(double value);

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
