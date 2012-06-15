/*
 * generator.c - IEC messages generation utilities
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

#include <iecgenerator.h>
#include <errno.h>

int IecComposeMessage(enum naviSentence_t msgtype, void *msg,
	char *buffer, size_t maxsize)
{
	switch (msgtype)
	{
	case _AAM:
	case _ACK:
	case _ALM:
	case _ALR:
	case _APB:
	case _BEC:
	case _BOD:
	case _BWC:
	case _BWR:
	case _BWW:
	case _DBT:
	case _DCN:
	case _DPT:
	case _DSC:
	case _DSE:
	case _DSI:
	case _DSR:
	case _DTM:
	case _FSI:
	case _GBS:
	case _GGA:
	case _GLC:
	case _GLL:
	case _GNS:
	case _GRS:
	case _GSA:
	case _GST:
	case _GSV:
	case _HDG:
	case _HDT:
	case _HMR:
	case _HMS:
	case _HSC:
	case _HTC:
	case _HTD:
	case _LCD:
	case _MLA:
	case _MSK:
	case _MSS:
	case _MTW:
	case _MWD:
	case _MWV:
	case _OSD:
	case _RMA:
	case _RMB:
	case _RMC:
	case _ROT:
	case _RPM:
	case _RSA:
	case _RSD:
	case _RTE:
	case _SFI:
	case _STN:
	case _TLB:
	case _TLL:
	case _TTM:
	case _TXT:
	case _VBW:
	case _VDR:
	case _VHW:
	case _VLW:
	case _VPW:
	case _VTG:
	case _WCV:
	case _WNC:
	case _WPL:
	case _XDR:
	case _XTE:
	case _XTR:
	case _ZDA:
	case _ZDL:
	case _ZFO:
	case _ZTG:
		break;
	}

	return -ENOSYS;
}

