/*
 * navigate.h - the main include header file for libnavigate
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

/*! \file navigate.h
 *  \brief This is the main include header file for libnavigate.
 *
 * When one intends to use libnavigate in his project he must include this file.
 */

#ifndef INCLUDE_navi_navigate_h
#define INCLUDE_navi_navigate_h

#include "libnavigate/config.h"
#include "libnavigate/errors.h"
#include "libnavigate/common.h"

#include "libnavigate/aam.h"
#include "libnavigate/ack.h"
#include "libnavigate/alm.h"
#include "libnavigate/alr.h"
#include "libnavigate/dtm.h"
#include "libnavigate/gbs.h"
#include "libnavigate/gga.h"
#include "libnavigate/gll.h"
#include "libnavigate/gns.h"
#include "libnavigate/grs.h"
#include "libnavigate/gsa.h"
#include "libnavigate/gst.h"
#include "libnavigate/gsv.h"
#include "libnavigate/mla.h"
#include "libnavigate/rmc.h"
#include "libnavigate/txt.h"
#include "libnavigate/vtg.h"
#include "libnavigate/zda.h"

#include <libnavigate/proprietarymsg.h>

#include "libnavigate/generator.h"
#include "libnavigate/parser.h"

#endif // INCLUDE_navi_navigate_h
