# Process this file with autoconf to produce a configure script.
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AC_PREREQ([2.63])
AC_INIT([libnavigate], [0.1], [igor.genius@gmail.com])

# Must come before AM_INIT_AUTOMAKE.
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE

#LT_PREREQ([2.2.6])
#LT_INIT

AC_CONFIG_SRCDIR([src/parser.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

## Since we use gnulib: gl_EARLY must be called as soon as possible after
## the C compiler is checked.  The others could be later, but we just
## keep everything together.
#gl_EARLY
#gl_INIT

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_HEADER_STDBOOL

# Checks for library functions.

#AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_FILES([Makefile
        src/Makefile])

AC_OUTPUT

