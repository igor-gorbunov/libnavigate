/*
 * generic.h - generic preprocessor definitions for libnavigate
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

/*! @file generic.h
 *  @brief Declares helpful macros.
 *
 *  Contains declarations for helpful macros, used at the other parts
 *  of the program.
 */

#ifndef INCLUDE_navi_generic_h
#define INCLUDE_navi_generic_h

#include <stddef.h>

/*! @def NAVI_BEGIN_DECL
 *  @brief Declares the beginning of function declarations.
 *
 */

/*! @def NAVI_END_DECL
 *  @brief Declares the end of function declarations.
 *
 */

#ifdef __cplusplus

#define NAVI_BEGIN_DECL		extern "C" {
#define NAVI_END_DECL		}

#else

#define NAVI_BEGIN_DECL		/* empty */
#define NAVI_END_DECL		/* empty */

#endif //  __cplusplus

/*! @brief Declares the \a type as extern.
 *
 */
#if defined(navigate_EXPORTS)
	#if defined(__GNUC__) && __GNUC__ >= 4
		#define NAVI_EXTERN(type)		extern __attribute__((visibility("default"))) type
	#elif defined(_MSC_VER)
		#define NAVI_EXTERN(type)		__declspec(dllexport) type
	#else
		#define NAVI_EXTERN(type)		extern type
	#endif // __GNUC__, _MSC_VER or other compiler
#else
	#if defined(__GNUC__) && __GNUC__ >= 4
		#define NAVI_EXTERN(type)		extern __attribute__((visibility("default"))) type
	#elif defined(_MSC_VER)
		#define NAVI_EXTERN(type)		__declspec(dllimport) type
	#else
		#define NAVI_EXTERN(type)		extern type
	#endif // __GNUC__, _MSC_VER or other compiler
#endif // navigate_EXPORTS

#endif // INCLUDE_navi_generic_h
