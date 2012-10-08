#
# spec file for package libnavigate
#
# Copyright (c) 2012 Igor Gorbunov <igor.genius@gmail.com>
#

#
Name:           libnavigate
Version:        0.3.0
Release:        1
Summary:        The IEC 61162-1/NMEA 0183 messages generating/parsing library
License:        LGPLv3
Group:          Development/Libraries
URL:            http://github.com/igor-gorbunov/libnavigate
Source0:        %{name}-%{version}.tar.bz2
BuildRequires:  cmake
BuildRequires:  pkgconfig
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%description
libnavigate is a portable C/C++ implementation of utilities for generating/parsing
maritime navigation protocol (IEC 61162-1 2000-07 and NMEA 0183).

%package devel
Summary:        The IEC 61162-1/NMEA 0183 messages generating/parsing library. Development files
Group:          Development/Libraries/C and C++
Requires:       %{name} >= %{version}

%description devel
This package contains all necessary include files and libraries needed
to compile and develop applications that use libnavigate.

%prep
%setup -q

%build
cmake -DCMAKE_C_FLAGS:STRING="%{optflags}" -DCMAKE_INSTALL_PREFIX:PATH=%{_prefix} -DBUILD_CPPBINDINGS=TRUE .
make %{?_smp_mflags}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%install
make install DESTDIR=%{buildroot}

%clean
rm -rf %{buildroot}

%files
%defattr (-,root,root)
%doc AUTHORS ChangeLog COPYING lgpl-3.0.txt NEWS README THANKS TODO
%{_libdir}/%{name}.so.*
%{_libdir}/%{name}.so

%files devel
%defattr (-,root,root)
%{_includedir}/navigate.h
%{_includedir}/navigate++
%{_includedir}/libnavigate*
%{_libdir}/pkgconfig/libnavigate.pc

%changelog
* Mon Oct 8 2012 igor.genius@gmail.com
- Initial version of this file.

