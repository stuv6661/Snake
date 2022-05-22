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

EXTRA_DIST= makefile-examples

noinst_PROGRAMS = \
	01_keyboard_events \
	02_mouse_events \
	03_input_box_events \
	04_events \
	05_exit \
	06_colors \
	07_time \
	08_full_screen \
	09_keyboard_accents \
	10_mouse_or_keyboard_access \
	11_keys_codes \
	12_desktop_size

AM_CPPFLAGS = ${MLV_CPPFLAGS}
AM_LDFLAGS = ${MLV_LDFLAGS} -static
LIBS +=  ${MLV_LIBADD}

# To profile MLV functions with gprof
if DEBUG
AM_LDFLAGS += -static
endif

docmediumdir = $(docdir)/examples/medium

docmedium_DATA = \
	01_keyboard_events.c \
	02_mouse_events.c \
	03_input_box_events.c \
	04_events.c \
	05_exit.c \
	06_colors.c \
	07_time.c \
	08_full_screen.c \
	09_keyboard_accents.c \
	10_mouse_or_keyboard_access.c \
	11_keys_codes.c \
	12_desktop_size.c \
	makefile-examples

install-data-hook:
	mv $(DESTDIR)$(docmediumdir)/makefile-examples $(DESTDIR)$(docmediumdir)/Makefile

uninstall-hook:
	-rm -rf $(DESTDIR)$(docmediumdir)/Makefile

01_keyboard_events_SOURCES = 01_keyboard_events.c
02_mouse_events_SOURCES = 02_mouse_events.c
03_input_box_events_SOURCES = 03_input_box_events.c
04_events_SOURCES = 04_events.c
05_exit_SOURCES = 05_exit.c
06_colors_SOURCES = 06_colors.c
07_time_SOURCES = 07_time.c
08_full_screen_SOURCES = 08_full_screen.c
09_keyboard_accents_SOURCES = 09_keyboard_accents.c
10_mouse_or_keyboard_access_SOURCES = 10_mouse_or_keyboard_access.c
11_keys_codes_SOURCES = 11_keys_codes.c
12_desktop_size_SOURCES = 12_desktop_size.c
