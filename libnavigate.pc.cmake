prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}/bin
libdir=${prefix}/lib@LIB_SUFFIX@
includedir=${prefix}/include

Name: libnavigate
Description: IEC/NMEA protocol generator/parser
Version: @LIBNAVIGATE_VERSION_STRING@
Libs: -L${libdir} -lnavigate -lm
Cflags: -I${includedir}
