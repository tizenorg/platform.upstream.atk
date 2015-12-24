%bcond_with introspection
%define baseline 2.12
%define api_level 1.0
%define api_level_alpha 10


Name:           atk
Version:        2.12.0
Release:        0
License:        LGPL-2.0+
Summary:        An Accessibility ToolKit
Url:            http://www.gtk.org/
#X-Vc-Url:      git://git.gnome.org/atk
Group:          System/Libraries
Source:         http://download.gnome.org/sources/%{name}/%{baseline}/%{name}-%{version}.tar.xz
Source98:       baselibs.conf
Source1001:     %{name}.manifest
BuildRequires:  gettext-tools
BuildRequires:  gnome-common
BuildRequires:  gtk-doc
BuildRequires:  fdupes
BuildRequires:  gcc-c++
BuildRequires:  glib2-devel >= 2.35.2
%if %{with introspection}
BuildRequires:  gobject-introspection-devel
%endif
Requires:       lib%{name}

%description
The ATK library provides a set of accessibility interfaces. By
supporting the ATK interfaces, an application or toolkit can be used
with screen readers, magnifiers, and alternate input devices.

%package -n lib%{name}
Summary:        An Accessibility ToolKit
Group:          System/Libraries
Provides:       %{name} = %{version}
Obsoletes:      %{name} < %{version}

%description -n lib%{name}
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
Group:          System/Libraries
Requires:       lib%{name} = %{version}-%{release}
%if %{with introspection}
Requires:       typelib-Atk = %{version}-%{release}
%endif

%description devel
This package contains all necessary include files and libraries needed
to develop applications that require these.


%prep
%setup -q
cp %{SOURCE1001} .

%build
NOCONFIGURE=1 ./autogen.sh

%configure \
  --disable-static

%__make %{?_smp_mflags}


%install
%make_install
install -d %{buildroot}/usr/share/help

%find_lang %{name}%{api_level_alpha}
fdupes %{buildroot}

%post -n lib%{name} -p /sbin/ldconfig

%postun -n lib%{name} -p /sbin/ldconfig

%files -n lib%{name}
%manifest %{name}.manifest
%defattr(-, root, root)
%license COPYING
%{_libdir}/lib*.so.*


%if %{with introspection}
%files -n typelib-Atk
%manifest %{name}.manifest
%defattr(-, root, root)
%{_libdir}/girepository-%{api_level}/Atk-%{api_level}.typelib
%endif

%files devel
%manifest %{name}.manifest
%defattr(-, root, root)
%{_includedir}/%{name}-%{api_level}
%{_libdir}/lib*.so
%{_libdir}/pkgconfig/*.pc
%if %{with introspection}
%{_datadir}/gir-%{api_level}/*.gir
%endif


%lang_package -f %{name}%{api_level_alpha}
