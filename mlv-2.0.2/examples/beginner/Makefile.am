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

EXTRA_DIST=makefile-examples gpl.txt

noinst_PROGRAMS = \
	01_hello_world \
	02_shapes \
	03_random \
	04_texts_and_boxes \
	05_mouse \
	06_keyboard \
	07_input_box \
	08_mouse_keyboard_timer \
	09_colors \
	10_library_informations
	
docbeginnerdir = $(docdir)/examples/beginner

docbeginner_DATA = \
	01_hello_world.c \
	02_shapes.c \
	03_random.c \
	04_texts_and_boxes.c \
	05_mouse.c \
	06_keyboard.c \
	07_input_box.c \
	08_mouse_keyboard_timer.c \
	09_colors.c \
	10_library_informations.c \
	gpl.txt \
	makefile-examples

install-data-hook:
	mv $(DESTDIR)$(docbeginnerdir)/makefile-examples $(DESTDIR)$(docbeginnerdir)/Makefile

uninstall-hook:
	-rm -rf $(DESTDIR)$(docbeginnerdir)/Makefile

AM_CPPFLAGS = ${MLV_CPPFLAGS}
AM_LDFLAGS = ${MLV_LDFLAGS} -static
LIBS += ${MLV_LIBADD}

# To profile MLV functions with gprof
if DEBUG
AM_LDFLAGS += -static
endif

01_hello_world_SOURCES = 01_hello_world.c
02_shapes_SOURCES = 02_shapes.c
03_random_SOURCES = 03_random.c
04_texts_and_boxes_SOURCES = 04_texts_and_boxes.c
05_mouse_SOURCES = 05_mouse.c
06_keyboard_SOURCES = 06_keyboard.c
07_input_box_SOURCES = 07_input_box.c
08_mouse_keyboard_timer_SOURCES = 08_mouse_keyboard_timer.c
09_colors_SOURCES = 09_colors.c
10_library_informations_SOURCES = 10_library_informations.c
