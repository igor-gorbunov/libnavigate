/*
 * iecgenerator.h - interface to IEC message generator
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

#ifndef IEC_GENERATOR_H
#define IEC_GENERATOR_H

#include <iecmessage.h>
#include <sys/types.h>

//
// Generator for IEC 61162-1 (2000-07) messages
//
// Generates IEC sentence, given in *msg and identified by msgtype, and
// stores the result to buffer which has the maximum size of maxsize.
// Returns the number of characters stored, or -errno code in case of error
//
int IecComposeMessage(enum naviSentence_t msgtype, void *msg,
	char *buffer, size_t maxsize);

#endif // IEC_GENERATOR_H

