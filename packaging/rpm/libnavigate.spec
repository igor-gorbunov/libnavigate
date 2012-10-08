#
# spec file for package libnavigate
#
# Copyright (c) 2012 Igor Gorbunov <igor.genius@gmail.com>
#

%define _name			libnavigate

%define _version_major	0
%define _version_minor	3
%define _version_patch	0

%define _version	%{_version_major}.%{_version_minor}.%{_version_patch}

%define _source		%{_name}-%{version}.tar.bz2

#%define _prefix		/usr/local

#%define _build		i686-pc-linux-gnu

#
Name:           %{_name}
Version:        %{_version}
Release:        2
Summary:        The IEC 61162-1/NMEA 0183 messages generating/parsing library
License:        LGPLv3
Group:          Development/Libraries
URL:            http://github.com/igor-gorbunov/libnavigate
Source0:        %{_source}
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
%doc %{_prefix}/share/doc/navigate-%{_version_major}.%{_version_minor}/AUTHORS
%doc %{_prefix}/share/doc/navigate-%{_version_major}.%{_version_minor}/ChangeLog
%doc %{_prefix}/share/doc/navigate-%{_version_major}.%{_version_minor}/COPYING
%doc %{_prefix}/share/doc/navigate-%{_version_major}.%{_version_minor}/lgpl-3.0.txt
%doc %{_prefix}/share/doc/navigate-%{_version_major}.%{_version_minor}/NEWS
%doc %{_prefix}/share/doc/navigate-%{_version_major}.%{_version_minor}/README
%doc %{_prefix}/share/doc/navigate-%{_version_major}.%{_version_minor}/THANKS
%doc %{_prefix}/share/doc/navigate-%{_version_major}.%{_version_minor}/TODO
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

