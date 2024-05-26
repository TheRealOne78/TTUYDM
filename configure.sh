#!/bin/sh

RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
ENDCOLOR="\e[0m"

INFO="["$BLUE"i"$ENDCOLOR"]"
WARN="["$YELLOW"w"$ENDCOLOR"]"
ERR="["$RED"e"$ENDCOLOR"]"

# Check for root
if [ $EUID -ne 0 ]; then
  printf "$ERR Please run this script with super user permission!\n"
  exit 1
fi

# Basic global variables
PKG_MGR=""          # The package manager that will install the dependencies
WILL_INSTALL=false  # Check if anything will be installed, else skip

# List of dependencies
# Common Linux: gcc make cmake spdlog ncurses doxygen
# Debian: gcc make cmake spdlog libncurses-dev doxygen
# RPM-based (Fedora, CentOS): gcc make cmake spdlog ncurses-devel doxygen
# BSD: gcc make cmake spdlog ncurses doxygen

if [ ! -x "$(command -v gcc)" ]; then
  printf "$INFO ${GREEN}gcc${ENDCOLOR} not detected, adding it in the dependencies install queue\n"
  DEPENDENCIES="$DEPENDENCIES gcc"
  DEB_DEPENDENCIES="$DEB_DEPENDENCIES gcc"
  RPM_DEPENDENCIES="$RPM_DEPENDENCIES gcc"
  BSD_DEPENDENCIES="$BSD_DEPENDENCIES gcc"
  WILL_INSTALL=true
fi

if [ ! -x "$(command -v make)" ]; then
  printf "$INFO ${GREEN}make${ENDCOLOR} not detected, adding it in the dependencies install queue\n"
  DEPENDENCIES="$DEPENDENCIES make"
  DEB_DEPENDENCIES="$DEB_DEPENDENCIES make"
  RPM_DEPENDENCIES="$RPM_DEPENDENCIES make"
  BSD_DEPENDENCIES="$BSD_DEPENDENCIES make"
  WILL_INSTALL=true
fi

if [ ! -x "$(command -v cmake)" ]; then
  printf "$INFO ${GREEN}cmake${ENDCOLOR} not detected, adding it in the dependencies install queue\n"
  DEPENDENCIES="$DEPENDENCIES cmake"
  DEB_DEPENDENCIES="$DEB_DEPENDENCIES cmake"
  RPM_DEPENDENCIES="$RPM_DEPENDENCIES cmake"
  BSD_DEPENDENCIES="$BSD_DEPENDENCIES cmake"
  WILL_INSTALL=true
fi

if [ ! -f "/usr/include/spdlog/spdlog.h" ]; then
  printf "$INFO ${GREEN}spdlog${ENDCOLOR} header files not detected, adding it in the dependencies install queue\n"
  DEPENDENCIES="$DEPENDENCIES spdlog"
  DEB_DEPENDENCIES="$DEB_DEPENDENCIES libspdlog-dev"
  RPM_DEPENDENCIES="$RPM_DEPENDENCIES spdlog-devel"
  BSD_DEPENDENCIES="$BSD_DEPENDENCIES spdlog"
  WILL_INSTALL=true
fi

if [ ! -f "/usr/include/ncurses.h" ]; then
  printf "$INFO ${GREEN}ncurses${ENDCOLOR} not detected, adding it in the dependencies install queue\n"
  DEPENDENCIES="$DEPENDENCIES ncurses"
  DEB_DEPENDENCIES="$DEB_DEPENDENCIES libncurses-dev"
  RPM_DEPENDENCIES="$RPM_DEPENDENCIES ncurses-devel"
  BSD_DEPENDENCIES="$BSD_DEPENDENCIES ncurses"
  WILL_INSTALL=true
fi

if [ ! -x "$(command -v doxygen)" ]; then
  printf "$INFO ${GREEN}doxygen${ENDCOLOR} not detected, adding it in the dependencies install queue\n"
  DEPENDENCIES="$DEPENDENCIES doxygen"
  DEB_DEPENDENCIES="$DEB_DEPENDENCIES doxygen"
  RPM_DEPENDENCIES="$RPM_DEPENDENCIES doxygen"
  BSD_DEPENDENCIES="$BSD_DEPENDENCIES doxygen"
  WILL_INSTALL=true
fi

# Choosing the right package manager
## Linux distributions
if [ "$WILL_INSTALL" = "true" ]; then
  ### Debian
  if [ -x "$(command -v apt-get)" ]; then
    printf "$INFO apt-get package manager detected\n"
    PKG_MGR="apt-get"

  ### Arch
  elif [ -x "$(command -v pacman)" ]; then
    printf "$INFO pacman package manager detected\n"
    PKG_MGR="pacman"

  ### Fedora
  elif [ -x "$(command -v dnf)" ]; then
    printf "$INFO dnf package manager detected\n"
    PKG_MGR="dnf"

  ### CentOS
  elif [ -x "$(command -v yum)" ]; then
    printf "$INFO yum package manager detected\n"
    PKG_MGR="yum"

  ### Gentoo
  elif [ -x "$(command -v emerge)" ]; then
    printf "$ERR Portage detected!\n\
$ERR Automatic package instalation with portage may lead to package conflicts.\n\
$ERR Please install$DEPENDENCIES manually and run this file again to compile and install TTUYDM in your system!\n\
$ERR To install these dependencies, try \"sudo emerge --ask $DEPENDENCIES\".\n
$ERR For more info, see https://wiki.gentoo.org/wiki/Emerge and https://wiki.gentoo.org/wiki/Portage\n"
    exit 1

  ## BSD Family
  ### FreeBSD
  elif [ -x "$(command -v pkg)" ]; then
    printf "$INFO pkg package manager detected\n"
    PKG_MGR="pkg"

  ### OpenBSD
  elif [ -x "$(command -v pkg_add)" ]; then
    printf "$INFO pkg_add detected\n"
    printf "$WARN If you are using OpenBSD, you might not have a good desktop experience because of OpenBSD's lack of graphics drivers support for nVidia GPUs.\n"
    PKG_MGR="pkg_add"

  ### NetBSD
  elif [ -x "$(command -v pkgin)" ]; then
    printf "$INFO pkgin package manager detected\n"
    PKG_MGR="pkgin"

  ### No package manager
  else
    printf "$ERR A valid package manager was not found!\n\
  $ERR Please install$DEPENDENCIES manually and run this file again to compile and install TTUYDM in your system!\n"
    exit 1
  fi
  printf "$INFO $PKG_MGR will install the required dependencies\n"

  # Install dependencies
  ## Debian
  if [ $PKG_MGR = "apt-get" ]; then
    $PKG_MGR install -y $DEB_DEPENDENCIES
  ## Arch
  elif [ $PKG_MGR = "pacman" ]; then
    $PKG_MGR -Sy --noconfirm $DEPENDENCIES
  ## RedHat
  elif [ $PKG_MGR = "dnf" ]; then
    $PKG_MGR install -y $RPM_DEPENDENCIES
  ## FreeBSD
  elif [ $PKG_MGR = "pkg" ]; then
    $PKG_MGR install -y $BSD_DEPENDENCIES
  ## OpenBSD
  elif [ $PKG_MGR = "pkg_add" ]; then
    $PKG_MGR $BSD_DEPENDENCIES
  ## NetBSD
  elif [ $PKG_MGR = "pkgin" ]; then
    $PKG_MGR -y install $BSD_DEPENDENCIES
  fi
  if [ $? -eq 0 ]; then
    printf "$INFO Packages installed successfully\n"
  else
    printf "$ERR Error: $PKG_MGR returned with exit code ${?}, aborting!\n"
    exit 1
  fi

else
  printf "$INFO Nothing to install, skipping configure.sh\n"
fi
