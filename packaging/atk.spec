Name:           atk
Summary:        An Accessibility ToolKit
License:        LGPL-2.1+
Group:          System/Libraries
Version:        2.6.0
Release:        2.1
Url:            http://www.gtk.org/
Source:         http://download.gnome.org/sources/atk/2.6/%{name}-%{version}.tar.xz
Source98:       baselibs.conf
BuildRequires:  fdupes
BuildRequires:  gcc-c++
BuildRequires:  glib2-devel >= 2.31.2
BuildRequires:  gobject-introspection-devel
BuildRequires:  translation-update-upstream
%if 0%{?BUILD_FROM_VCS}
BuildRequires:  gnome-common
BuildRequires:  gtk-doc
%endif
Requires:       %{name}-lang = %{version}
Requires:       libatk
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

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
Group:          Development/Libraries/GNOME
Requires:       libatk = %{version}
Requires:       typelib-Atk = %{version}

%description devel
This package contains all necessary include files and libraries needed
to develop applications that require these.

%package doc
Summary:        Additional Package Documentation for atk
Group:          System/Libraries
Requires:       libatk = %{version}
BuildArch:      noarch

%description doc
This package contains additional documentation for the ATK Library.

%prep
%setup -q

%if 0%{?BUILD_FROM_VCS}
[ -x ./autogen.sh ] && NOCONFIGURE=1 ./autogen.sh
%endif

%build
%configure \
%if 0%{?BUILD_FROM_VCS}
  --enable-gtk-doc \
%endif
  --disable-static
make %{?_smp_mflags}

%install
%make_install
%fdupes $RPM_BUILD_ROOT

%post -n libatk -p /sbin/ldconfig

%postun -n libatk -p /sbin/ldconfig

%files -n libatk
%defattr(-, root, root)
%doc AUTHORS COPYING ChangeLog NEWS README
%{_libdir}/lib*.so.*

%files -n typelib-Atk
%defattr(-, root, root)
%{_libdir}/girepository-1.0/Atk-1.0.typelib

%files devel
%defattr(-, root, root)
%{_includedir}/atk-1.0
%{_libdir}/lib*.so
%{_libdir}/pkgconfig/*.pc
%{_datadir}/gir-1.0/*.gir

%files doc
%defattr(-, root, root)
%dir %{_datadir}/gtk-doc
%dir %{_datadir}/gtk-doc/html
%{_datadir}/gtk-doc/html/atk
