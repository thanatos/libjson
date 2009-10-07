prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
includedir=${prefix}/include

Name: libjson
Description: C++ JSON Library
Version: @VERSION@
URL: http://github.com/thanatos/libjson
Libs: -L${libdir} -ljson
Cflags: -I${includedir}/libjson
