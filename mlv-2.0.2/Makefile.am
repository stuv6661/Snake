#
#   This file is part of the MLV Library.
#
#   Copyright (C) 2010 Adrien Boussicault, Marc Zipstein
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

ACLOCAL_AMFLAGS=-Iconfig/m4

include $(top_srcdir)/config/am/aminclude.am

EXTRA_DIST=gpl.txt mlv_rcs_revision

if RELATIVEPATH
SUBDIRS = MLV data doc packaging
else
SUBDIRS = MLV examples data doc packaging
endif


pkgconfigdir= ${libdir}/pkgconfig
pkgconfig_DATA = MLV.pc

man3_MANS = \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_animation.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_audio.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_all.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_color.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_event.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_shape.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_image.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_information.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_keyboard.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_mouse.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_input_box.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_random.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_text.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_text_va.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_time.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_xml.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_xml_va.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_window.h.3 \
	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_path.h.3
#	doc/api/$(INSTALL_LANGUAGE)/man/man3/MLV_playlist.h.3

$(man3_MANS): doc/api/$(INSTALL_LANGUAGE)/html/index.html

doc/api/$(INSTALL_LANGUAGE)/html/index.html: $(top_srcdir)/MLV/MLV_*.h $(top_srcdir)/doc/Doxyfile $(top_builddir)/doc/Doxyfooter $(top_builddir)/doc/Doxyheader_* $(top_builddir)/doc/main_documentation_doxygen.c
	-mkdir -p $(top_builddir)/doc/api
	make doxygen-doc

docapilangdir = $(docdir)/api/$(INSTALL_LANGUAGE)
docapihtmldir = $(docapilangdir)/html

install-data-hook:
	-mkdir -p $(DESTDIR)$(docapilangdir)
	cp -r $(top_builddir)/doc/api/$(INSTALL_LANGUAGE)/html $(DESTDIR)$(docapihtmldir)

uninstall-hook:
	-rm -rf $(DESTDIR)$(docapihtmldir)

clean-local:
	-rm -rf $(top_builddir)/doc/api

