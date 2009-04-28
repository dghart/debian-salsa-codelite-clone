Name:           codelite
Version:        1.0.2782
Release:        1%{?dist}
License:        GPLv2+
Group:          Development/Tools
Summary:        CodeLite is a powerful open-source, cross platform code editor for C/C++
URL:            http://codelite.sourceforge.net
Source:         http://downloads.sourceforge.net/%{name}/%{name}-%{version}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: wxGTK xterm
BuildRequires: wxGTK-devel

%description
CodeLite uses a sophisticated, yet intuitive interface which allows 
users to easily create, build and debug complex projects.

%prep
%setup -q

%build
./configure --prefix=%{_prefix} --plugins-dir=%{_libdir}/%{name}
%{__make} 

%install
%{__rm} -rf $RPM_BUILD_ROOT
%{__make} DESTDIR=$RPM_BUILD_ROOT install
desktop-file-install  --delete-original       \
    --copy-generic-name-to-name                              \
          --dir $RPM_BUILD_ROOT%{_datadir}/applications            \
                $RPM_BUILD_ROOT%{_datadir}/applications/codelite.desktop
%clean
%{__rm} -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc AUTHORS LICENSE COPYING 
%{_bindir}/codelite
%{_bindir}/codelite_indexer
%{_bindir}/le_dos2unix.sh
%{_bindir}/le_exec.sh
%{_bindir}/le_killproc.sh
%{_datadir}/codelite
%{_datadir}/applications/codelite.desktop
%{_libdir}/%{name}

%changelog
* Tue Feb 24 2009 Jess Portnoy <kernel01@gmail.com> 1.0.2782-1
- Spec file: Added call to desktop-file-install and %doc
  code: fixed perms and other rpmlint issues.
* Sat Feb 21 2009 Jess Portnoy <kernel01@gmail.com> 1.0.2781-1
- Reworked the rpm package to satisfy Fedora Core conventions.

