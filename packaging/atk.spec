%bcond_with introspection

Name:           atk
Version:        2.8.0
Release:        0
License:        LGPL-2.1+
Summary:        An Accessibility ToolKit
Url:            http://www.gtk.org/
Group:          System/Libraries
Source:         http://download.gnome.org/sources/atk/2.8/%{name}-%{version}.tar.xz
Source98:       baselibs.conf
Source1001: 	atk.manifest
BuildRequires:  fdupes
BuildRequires:  gcc-c++
BuildRequires:  glib2-devel >= 2.35.2
%if %{with introspection}
BuildRequires:  gobject-introspection-devel
%endif
Requires:       libatk

%description
The ATK library provides a set of accessibility interfaces. By
supporting the ATK interfaces, an application or toolkit can be used
with screen readers, magnifiers, and alternate input devices.

%package -n libatk
Summary:        An Accessibility ToolKit
Group:          System/Libraries
Provides:       %{name} = %{version}
Obsoletes:      %{name} < %{version}

%description -n libatk
The ATK library provides a set of accessibility interfaces. By
supporting the ATK interfaces, an application or toolkit can be used
with screen readers, magnifiers, and alternate input devices.

%package -n typelib-Atk
Summary:        An Accessibility ToolKit -- Introspection bindings
Group:          System/Libraries

%description -n typelib-Atk
The ATK library provides a set of accessibility interfaces. By
supporting the ATK interfaces, an application or toolkit can be used
with screen readers, magnifiers, and alternate input devices.

This package provides the GObject Introspection bindings for ATK.

%package devel
Summary:        Include Files and Libraries mandatory for Development
Group:          Development/Gnome
Requires:       libatk = %{version}
%if %{with introspection}
Requires:       typelib-Atk = %{version}
%endif

%description devel
This package contains all necessary include files and libraries needed
to develop applications that require these.


%prep
%setup -q
cp %{SOURCE1001} .

%build
%configure \
  --disable-static
make %{?_smp_mflags}

%install
%make_install
%fdupes %{buildroot}

%post -n libatk -p /sbin/ldconfig

%postun -n libatk -p /sbin/ldconfig

%files -n libatk
%manifest %{name}.manifest
%defattr(-, root, root)
%license COPYING
%{_libdir}/lib*.so.*


%if %{with introspection}
%files -n typelib-Atk
%manifest %{name}.manifest
%defattr(-, root, root)
%{_libdir}/girepository-1.0/Atk-1.0.typelib
%endif

%files devel
%manifest %{name}.manifest
%defattr(-, root, root)
%{_includedir}/atk-1.0
%{_libdir}/lib*.so
%{_libdir}/pkgconfig/*.pc
%if %{with introspection}
%{_datadir}/gir-1.0/*.gir
%endif

%docs_package
