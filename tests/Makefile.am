# Process this file with automake to produce Makefile.in (in this,
# and all subdirectories).
# Makefile for the top-level directory of GNU hello.
# 
# Copyright 1997, 1998, 2005, 2006, 2007, 2008, 2009, 2010, 2011
# Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

AM_CPPFLAGS = $(DEPS_CFLAGS) -I$(top_srcdir)/include

bin_PROGRAMS = test
test_SOURCES = entry.c
test_LDADD = $(DEPS_LIBS) -lm $(top_srcdir)/src/libnavigate.la

