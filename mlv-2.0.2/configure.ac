#
#   This file is part of the MLV Library.
#
#   Copyright (C) 2010-2014 Adrien Boussicault, Marc Zipstein
#
#
#    This library is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
#

# Before a public release, do the following version modification :
# - First, in AC_INIT([MLV], [mlvcurrent.mlvrevision.mlvage-dev] remove the -dev
# - if only code has changed then increase mlvrevision
# - if interfaces have been removed or changed then increase mlvcurrent, 
#   set mlvrevision to 0 and mlvage to 0
# - if interfaces have been added then increase mlvcurrent, increase mlvage and 
#   set mlvrevision to 0.
#
# This version follow the libtool version recommendation :
# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
#
define([mlvcurrent], [2])dnl
define([mlvrevision], [0])dnl
define([mlvage], [2])dnl

# We deduce other version numbers
define([mlvmajorversion], m4_eval(mlvcurrent - mlvage))dnl
define([mlvminorversion], m4_eval(mlvage))dnl

AC_INIT([MLV], [mlvcurrent.mlvrevision.mlvage], [adrien.boussicault@labri.fr], [], [http://www-igm.univ-mlv.fr/~boussica/mlv/index.html])

AC_SUBST(MLV_MAJOR_VERSION,[mlvmajorversion])
AC_SUBST(MLV_MINOR_VERSION,[mlvminorversion])
AC_SUBST(MLV_CURRENT,[mlvcurrent])
AC_SUBST(MLV_REVISION,[mlvrevision])
AC_SUBST(MLV_AGE,[mlvage])

AC_SUBST(MLV_REPOSITORY,["git clone git://git.savannah.nongnu.org/mlv.git"])
AC_DEFINE_UNQUOTED([MLV_REPOSITORY],["$MLV_REPOSITORY"],[Define the revision control software])

if test -d .git
then
	rcsrevision=$(git rev-parse HEAD)
	AC_SUBST(MLV_RCS_REVISION,[$rcsrevision])
	echo $MLV_RCS_REVISION > mlv_rcs_revision
else
	rcsrevision=$(cat mlv_rcs_revision)
	AC_SUBST(MLV_RCS_REVISION,[$rcsrevision])
fi
AC_DEFINE_UNQUOTED([MLV_RCS_REVISION],["$MLV_RCS_REVISION"],[Define the revision in the source repository])

AC_SUBST(MLV_SOURCE_REPOSITORY,[http://download.savannah.gnu.org/releases/mlv])
AC_SUBST(MLV_URL,[${PACKAGE_URL}])
AC_DEFINE_UNQUOTED([MLV_SOURCE_REPOSITORY],["$MLV_SOURCE_REPOSITORY"],[Define the address of the MLV repository])

AC_SUBST(MAIL_ADRIEN_BOUSSICAULT,[adrien.boussicault@labri.fr])
AC_SUBST(MAIL_MARC_ZIPSTEIN,[marc.zipstein@univ-mlv.fr])

AC_SUBST(MLV_PACKAGE_REPOSITORY,[${MLV_SOURCE_REPOSITORY}/${PACKAGE_TARNAME}-${PACKAGE_VERSION}])


AC_SUBST(MLV_DEBIAN_VERSION,[${MLV_MAJOR_VERSION}])
AC_SUBST(MLV_DEBIAN_32_BINARY_PACKAGE,[lib${PACKAGE_TARNAME}${MLV_DEBIAN_VERSION}_${PACKAGE_VERSION}-1_i386.deb])
AC_SUBST(MLV_DEBIAN_64_BINARY_PACKAGE,[lib${PACKAGE_TARNAME}${MLV_DEBIAN_VERSION}_${PACKAGE_VERSION}-1_amd64.deb])
AC_SUBST(MLV_DEBIAN_32_DEV_PACKAGE,[lib${PACKAGE_TARNAME}${MLV_DEBIAN_VERSION}-dev_${PACKAGE_VERSION}-1_i386.deb])
AC_SUBST(MLV_DEBIAN_64_DEV_PACKAGE,[lib${PACKAGE_TARNAME}${MLV_DEBIAN_VERSION}-dev_${PACKAGE_VERSION}-1_amd64.deb])
AC_SUBST(MLV_DEBIAN_X_BINARY_PACKAGE,[lib${PACKAGE_TARNAME}${MLV_DEBIAN_VERSION}_${PACKAGE_VERSION}-1_X.deb])
AC_SUBST(MLV_DEBIAN_X_DEV_PACKAGE,[lib${PACKAGE_TARNAME}${MLV_DEBIAN_VERSION}-dev_${PACKAGE_VERSION}-1_X.deb])
AC_SUBST(MLV_WIN_32_BINARIES,[${PACKAGE_TARNAME}-${PACKAGE_VERSION}-win32.zip])
AC_SUBST(MLV_WIN_64_BINARIES,[${PACKAGE_TARNAME}-${PACKAGE_VERSION}-win64.zip])
AC_SUBST(MLV_DEVCPP_32_PACKAGE,[${PACKAGE_TARNAME}-${PACKAGE_VERSION}-dev-cpp.zip])
AC_SUBST(MLV_CODEBLOCKS_32_PACKAGE,[${PACKAGE_TARNAME}-${PACKAGE_VERSION}-code_blocks.zip])

AC_SUBST(MLV_MACOSX_VERSION,[10.10])
AC_SUBST(MLV_MACOSX_PACKAGE,[${PACKAGE_TARNAME}-${PACKAGE_VERSION}_macos-${MLV_MACOSX_VERSION}.pkg])

AC_SUBST(MLV_FEDORA_VERSION,[22])
AC_SUBST(MLV_FEDORA_CODE_VERSION,[fc${MLV_FEDORA_VERSION}])
AC_SUBST(MLV_FEDORA_KEY_PACKAGE,[RPM-GPG-KEY-Boussicault])

AC_SUBST(MLV_FEDORA_32_BINARY_PACKAGE,[${PACKAGE_TARNAME}-${PACKAGE_VERSION}-0.${MLV_FEDORA_CODE_VERSION}.i686.rpm])
AC_SUBST(MLV_FEDORA_32_DEV_PACKAGE,[${PACKAGE_TARNAME}-devel-${PACKAGE_VERSION}-0.${MLV_FEDORA_CODE_VERSION}.i686.rpm])
AC_SUBST(MLV_FEDORA_32_STATIC_PACKAGE,[${PACKAGE_TARNAME}-static-${PACKAGE_VERSION}-0.${MLV_FEDORA_CODE_VERSION}.i686.rpm])
AC_SUBST(MLV_FEDORA_32_SOURCE_PACKAGE,[${PACKAGE_TARNAME}-${PACKAGE_VERSION}-0.${MLV_FEDORA_CODE_VERSION}.src.rpm])

AC_SUBST(MLV_FEDORA_64_BINARY_PACKAGE,[${PACKAGE_TARNAME}-${PACKAGE_VERSION}-0.${MLV_FEDORA_CODE_VERSION}.x86_64.rpm])
AC_SUBST(MLV_FEDORA_64_DEV_PACKAGE,[${PACKAGE_TARNAME}-devel-${PACKAGE_VERSION}-0.${MLV_FEDORA_CODE_VERSION}.x86_64.rpm])
AC_SUBST(MLV_FEDORA_64_STATIC_PACKAGE,[${PACKAGE_TARNAME}-static-${PACKAGE_VERSION}-0.${MLV_FEDORA_CODE_VERSION}.x86_64.rpm])
AC_SUBST(MLV_FEDORA_64_SOURCE_PACKAGE,[${PACKAGE_TARNAME}-${PACKAGE_VERSION}-0.${MLV_FEDORA_CODE_VERSION}.src.rpm])


AC_PREREQ([2.63])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config/m4])
m4_include([config/m4/ax_prog_doxygen.m4])

AM_INIT_AUTOMAKE([-Wall -Werror])
AM_CONFIG_HEADER([MLV/config.h])


#######################################################################
# Configuration options  (part 1)                                     #
#######################################################################
AC_ARG_ENABLE([dev],
	      AS_HELP_STRING([--enable-dev], [If you want to launch the game in the directory of compilation use this option. If you want to install the game don't use this option. This option is generally for developpers.]),
	      [dev=$enableval],
	      [dev=no])
AM_CONDITIONAL([DEV],[test x$dev = xyes])

AC_ARG_ENABLE([debug],
	      AS_HELP_STRING([--enable-debug], [Add debug flags (-g -pg -O0)]),
	      [debug=$enableval],
	      [debug=no])
AM_CONDITIONAL([DEBUG],[test x$debug = xyes])

if test x$debug = xyes
then
AC_SUBST(COMPILE_DEBUG_VERSION_FOR_WINDOW,['yes'])
else
AC_SUBST(COMPILE_DEBUG_VERSION_FOR_WINDOW,['no'])
fi


AC_ARG_ENABLE([memorydebug],
	      AS_HELP_STRING([--enable-memorydebug], [This option is for developpers. This option permit to help the user to debug problem memory.]),
	      [memorydebug=$enableval],
	      [memorydebug=no])
AM_CONDITIONAL([MEMORY_DEBUG],[test x$memorydebug = xyes])

AC_ARG_ENABLE([relativepath],
	      AS_HELP_STRING([--enable-relativepath], [If you want to install the MLV in the same directory than your program using the MLV library, you have to use this option. This option will correctly configure a relative path to find the libraries font from the binary directory. This option is for windows DLL compilations. If you want to change the default relative path for the data directory, you can pass as parameter you prefered path.By default the relative data path is ../share/MLV/data .]),
	      [relativepath=$enableval],
	      [relativepath=no])
AM_CONDITIONAL([RELATIVEPATH],[test x$relativepath != xno])

if test x$debug = xyes
then
	CXXFLAGS="-g -ggdb -pg -O0 ${CXXFLAGS}"
	CFLAGS="-g -ggdb -pg -O0 ${CFLAGS}"
	LDFLAGS="-g -ggdb -pg -O0 ${LDFLAGS}"
else
	if test x$dev = xyes
	then
		CXXFLAGS="-g -O2 ${CXXFLAGS}"
		CFLAGS="-g -O2 ${CFLAGS}"
	fi
fi

#######################################################################
# Configure Compilation flags                                         #
#######################################################################
AM_PROG_AR

AC_PROG_CC
AM_PROG_CC_STDC   # To compile .dll
AC_C_CONST # To compile .dll
AM_PROG_CC_C_O
AC_LIBTOOL_WIN32_DLL # To compile .dll
AC_PROG_OBJC

#######################################################################
# Configuration options  (part 2)                                     #
#######################################################################

if test x$relativepath = xyes
then
	relativepath='../share/MLV/data'
fi

# Fonction verifiant la bonne utilisation des options
if test x$relativepath != xno
then
	if test x$dev != xno
	then
		AC_MSG_ERROR([Option --enable-relativepath and --enable-dev can't be use in the same time.],1)
	fi
fi


AC_SUBST([LANGUAGES],['French English Spanish'])
AC_SUBST([DEFAULT_LANGUAGE],['French'])

AC_ARG_ENABLE([language],
	      AS_HELP_STRING([--enable-language], [The language of the documentation. The possible choose are "French", "English", "Spanish". Default : "French".]),
	      [language=$enableval],
	      [language=${DEFAULT_LANGUAGE}])

for i in ${LANGUAGES}
do
	if test x$i == x${language}
	then
		AC_SUBST([INSTALL_LANGUAGE],[${language}])
	fi
done

if test x${language} != x${INSTALL_LANGUAGE}
then
	AC_MSG_ERROR([Unknown or unsupported Language "$language".  Only "${LANGUAGES}" are supported in this version of this library.])
fi


AC_ARG_ENABLE([all-static],
	      AS_HELP_STRING([--enable-all-static], [If you want to obtain a complete static library, use this option.]),
	      [allstatic=$enableval],
	      [allstatic=no])
AM_CONDITIONAL([ALLSTATIC],[test x$allstatic = xyes])

AC_PROG_LIBTOOL

AM_CONDITIONAL([CROSS_COMPILATION],[test "x$host_os" != "x$build_os"])

#Option de compilation pour tout le monde
CXXFLAGS="-I\${top_srcdir} -Wall ${CXXFLAGS}"
CFLAGS="-I\${top_srcdir} -Wall ${CFLAGS}"

case "$host_os" in
	darwin*)
		AC_SUBST([MLV_CPPFLAGS],['-I${top_srcdir} ${sdl_CFLAGS}'])
		AC_SUBST([MLV_LIBADD],['${top_builddir}/MLV/libMLV.la ${top_builddir}/MLV/libMLVMain.la'])
	;;
	*)
		AC_SUBST([MLV_CPPFLAGS],['-I${top_srcdir}'])
		AC_SUBST([MLV_LIBADD],['${top_builddir}/MLV/libMLV.la'])
	;;
esac

if test x$dev = xyes
then
	AC_SUBST([DATA_PATH],['${abs_top_srcdir}/data'])
else
	if test x$relativepath = xno
	then
		AC_SUBST([DATA_PATH],['${datadir}/MLV/data'])
	else
		AC_SUBST([DATA_PATH],[$relativepath])
	fi
fi

#Special linkage option for OS
#difference beetween host and build ?
#AC_CANONICAL_HOST

case "$host_os" in
	linux*)
	;;
        darwin*)
	;;
	mingw*)
		AC_SUBST([os_LIBS],[-lmingw32])
	;;
	cygwin*)
		CPPFLAGS="-mno-cygwin ${CPPFLAGS}"
		LDFLAGS="-mno-cygwin ${LDFLAGS}"
	;;
        *) AC_MSG_ERROR([Unknown or unsupported OS "$host_os".  Only "linux", "mingw" and "darwin" are supported in this version of the MLV library.]) ;;
esac

AC_CHECK_LIB([m],[cos])

case "$host_os" in
    darwin*)
		if test x$sdl_CFLAGS = x; then
			AC_SUBST([sdl_CFLAGS],['-I/Library/Frameworks/SDL.framework/Headers'])
			AC_SUBST([sdlttf_CFLAGS],[''])
			AC_SUBST([sdlimage_CFLAGS],[''])
			AC_SUBST([sdlmixer_CFLAGS],[''])
		fi
		if test x$sdl_LIBS = x; then
			AC_SUBST([sdl_LIBS],['-framework SDL -framework Cocoa'])
			AC_SUBST([sdlttf_LIBS],['-framework SDL_ttf'])
			AC_SUBST([sdlimage_LIBS],['-framework SDL_image'])
			AC_SUBST([sdlmixer_LIBS],['-framework SDL_mixer'])
		fi	
		AC_SUBST([libsdl_found],[yes])
		AC_SUBST([libsdlttf_found],[yes])
		AC_SUBST([libsdlimage_found],[yes])
		AC_SUBST([libsdlmixer_found],[yes])
		
		AC_CHECK_LIB(
			[SDL_gfx],
			[boxColor],
			AC_SUBST([libsdlgfx_found],[yes])
			AC_SUBST([sdlgfx_LIBS],['-lSDL_gfx -framework SDL -framework cocoa']),
			AC_SUBST([libsdlgfx_found],[no]),
			[-framework SDL -framework cocoa]
		)

		if test x$libsdlgfx_found = xno; then
			echo "Search for SDL_gfx library... no"
			AC_MSG_ERROR([The SDL_gfx library is required to compile the MLV library.],1)
		else
			echo "Search for SDL_gfx library... ${sdlgfx_LIBS}"
		fi
	;;
	*)
		PKG_CHECK_MODULES(sdl, sdl)
		AC_SUBST(sdl_CFLAGS)
		AC_SUBST(sdl_LIBS)

		AC_CHECK_LIB(
			[SDL_ttf],
			[TTF_SetFontStyle],
			AC_SUBST([libsdlttf_found],[yes])
			AC_SUBST([sdlttf_LIBS],[-lSDL_ttf]),
			AC_SUBST([libsdlttf_found],[no])
		)
		if test x$libsdlttf_found = xno; then
			echo "Search for SDL_ttf library... no"
			AC_MSG_ERROR([The SDL_ttf library is required to compile the MLV library.],1)
		else
			echo "Search for SDL_ttf library... ${sdlttf_LIBS}"
		fi
		AC_CHECK_LIB(
			[SDL_image],
			[IMG_Load],
			AC_SUBST([libsdlimage_found],[yes])
			AC_SUBST([sdlimage_LIBS],[-lSDL_image]),
			AC_SUBST([libsdlimage_found],[no])
		)

		if test x$libsdlimage_found = xno; then
			echo "Search for SDL_image library... no"
			AC_MSG_ERROR([The SDL_image library is required to compile the MLV library.],1)
		else
			echo "Search for SDL_image library... ${sdlimage_LIBS}"
		fi

		AC_CHECK_LIB(
			[SDL_mixer],
			[Mix_OpenAudio],
			AC_SUBST([libsdlmixer_found],[yes])
			AC_SUBST([sdlmixer_LIBS],[-lSDL_mixer]),
			AC_SUBST([libsdlmixer_found],[no])
		)

		if test x$libsdlmixer_found = xno; then
			echo "Search for SDL_mixer library... no"
			AC_MSG_ERROR([The SDL_mixer library is required to compile the MLV library.],1)
		else
			echo "Search for SDL_mixer library... ${sdlmixer_LIBS}"
		fi

		AC_CHECK_LIB(
			[SDL_gfx],
			[boxColor],
			AC_SUBST([libsdlgfx_found],[yes])
			AC_SUBST([sdlgfx_LIBS],[-lSDL_gfx]),
			AC_SUBST([libsdlgfx_found],[no])
		)

		if test x$libsdlgfx_found = xno; then
			echo "Search for SDL_gfx library... no"
			AC_MSG_ERROR([The SDL_gfx library is required to compile the MLV library.],1)
		else
			echo "Search for SDL_gfx library... ${sdlgfx_LIBS}"
		fi
	;;
esac



PKG_CHECK_MODULES(glib, glib-2.0)

PKG_CHECK_MODULES(libxml, libxml-2.0)

if test x$debug = xyes || test x$dev = xyes
then
	CXXFLAGS="${CXXFLAGS} -Werror"
	CFLAGS="${CFLAGS} -Werror"
fi

if test x$memorydebug = xyes
then
	CXXFLAGS="-DMEMORY_DEBUG ${CXXFLAGS}"
	CFLAGS="-DMEMORY_DEBUG ${CFLAGS}"
fi

#GENERATION OF DOXYGENE DOCUMENTATION
#AX_PROG_DOXYGEN

AC_SUBST([doxygendir],['$(top_builddir)/doc/api'])
DX_DOXYGEN_FEATURE(ON)
DX_HTML_FEATURE(ON)
#DX_CHM_FEATURE(OFF)
#DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(ON)
#DX_RTF_FEATURE(OFF)
#DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN([$PACKAGE_NAME], [doc/Doxyfile],[${doxygendir}],[${LANGUAGES}])

if test x${DX_DOXYGEN} = x
then
	AC_MSG_ERROR([doxygen is requiered. Please install doxygen.],1)
fi

if test x$allstatic = xyes
then
	LDFLAGS="-all-static ${LDFLAGS}"
fi


case "$host_os" in
	linux*)
		AM_CONDITIONAL([OS_IS_LINUX],[true])
		AM_CONDITIONAL([OS_IS_WIN32],[false])
		AM_CONDITIONAL([OS_IS_APPLE],[false])
	;;
	darwin*)
		AM_CONDITIONAL([OS_IS_LINUX],[false])
		AM_CONDITIONAL([OS_IS_WIN32],[false])
		AM_CONDITIONAL([OS_IS_APPLE],[true])
	;;
	mingw*)
		AM_CONDITIONAL([OS_IS_LINUX],[false])
		AM_CONDITIONAL([OS_IS_WIN32],[true])
		AM_CONDITIONAL([OS_IS_APPLE],[false])
	;;
	cygwin*)
		AM_CONDITIONAL([OS_IS_LINUX],[false])
		AM_CONDITIONAL([OS_IS_WIN32],[true])
		AM_CONDITIONAL([OS_IS_APPLE],[false])
	;;
        *) AC_MSG_ERROR([Unknown or unsupported OS "$host_os".  Only "linux", "mingw" and "darwin" are supported in this version of the MLV library.]) ;;
esac


AC_CONFIG_FILES([
	MLV.pc \
	Makefile \
	MLV/Makefile \
	data/Makefile \
	data/font/Makefile \
	doc/Makefile \
	doc/index.html \
	doc/tp5graph.tex \
	doc/Doxyfooter \
	doc/main_documentation_doxygen.c \
	doc/Doxyheader_English \
	doc/Doxyheader_French \
	doc/Doxyheader_Spanish \
	packaging/Makefile \
	packaging/debian/script_pkg \
	packaging/debian/debian/Makefile \
	packaging/debian/debian/control \
	packaging/debian/debian/libmlv${MLV_DEBIAN_VERSION}-dev.dirs:packaging/debian/debian/libmlv-dev.dirs \
	packaging/debian/debian/libmlv${MLV_DEBIAN_VERSION}-dev.install:packaging/debian/debian/libmlv-dev.install \
	packaging/debian/debian/libmlv${MLV_DEBIAN_VERSION}.dirs:packaging/debian/debian/libmlv.dirs \
	packaging/debian/debian/libmlv${MLV_DEBIAN_VERSION}.install:packaging/debian/debian/libmlv.install \
	packaging/debian/debian/libmlv${MLV_DEBIAN_VERSION}.postinst:packaging/debian/debian/libmlv.postinst \
	packaging/debian/debian/libmlv${MLV_DEBIAN_VERSION}.postrm:packaging/debian/debian/libmlv.postrm \
	packaging/debian/debian/libmlv.symbols \
	packaging/debian/debian/libmlv${MLV_DEBIAN_VERSION}.symbols:packaging/debian/debian/libmlv.symbols \
	packaging/debian/debian/libmlv.shlibs \
	packaging/debian/debian/libmlv${MLV_DEBIAN_VERSION}.shlibs:packaging/debian/debian/libmlv.shlibs \
	packaging/debian/debian/copyright \
	packaging/fedora/rpmbuild/SPECS/mlv.spec \
	packaging/debian/debian/changelog
	packaging/windows/Makefile \
	packaging/windows/cross-compilation/definition_of_environement_variables \
	packaging/windows/cross-compilation/mingw_compilation_for_mlv \
	packaging/windows/create_win32_binaries \
	packaging/windows/create_canonical_developpement_kit \
	packaging/windows/create_dev_cpp_package \
	packaging/windows/create_code_blocks_package \
	packaging/windows/my_project.cbp \
	packaging/windows/my_project.dev \
	Android.mk \
	examples/Makefile \
	examples/beginner/Makefile \
	examples/medium/Makefile \
	examples/advanced/Makefile \
	examples/sandbox/Makefile \
	examples/sandbox/example.c
])

AC_OUTPUT

chmod +x packaging/debian/script_pkg 
chmod +x packaging/windows/cross-compilation/mingw_compilation_for_mlv
chmod +x packaging/windows/create_win32_binaries
chmod +x packaging/windows/create_canonical_developpement_kit
chmod +x packaging/windows/create_dev_cpp_package
chmod +x packaging/windows/create_code_blocks_package
