/*
 * config.h - configuration paramters for libnavigate
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

/*! @file config.h
 *  @brief Contains declarations of utilities used for
 *  retrieving information about libnavigate configuration.
 */

#ifndef INCLUDE_navi_config_h
#define INCLUDE_navi_config_h

#include "generic.h"

NAVI_BEGIN_DECL

//! @brief Generator is available in distribution
#define LIBNAVIGATE_CAPS_GENERATOR		0x00000001
//! @brief Parser is available in distribution
#define LIBNAVIGATE_CAPS_PARSER			0x00000002

//! @brief Get the capabilities of libnavigate distribution
NAVI_EXTERN(unsigned int) naviconf_get_caps(void);

//! @brief Get the floating point precision
NAVI_EXTERN(int) naviconf_get_presicion(void);

//! @brief Set the floating point precision
NAVI_EXTERN(int) naviconf_set_presicion(int precision);

NAVI_END_DECL

#endif // INCLUDE_navi_config_h
