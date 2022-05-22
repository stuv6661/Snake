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

mlv_includedir=${includedir}/MLV

if OS_IS_APPLE 
lib_LTLIBRARIES = libMLV.la libMLVMain.la
else
lib_LTLIBRARIES = libMLV.la
endif

libMLV_la_SOURCES = \
	animation.c \
	audio.c \
	color.c \
	event.c \
	shapes.c \
	image.c \
	informations.c \
	keyboard.c \
	mouse.c \
	path.c \
	playlist.c \
	input_box.c \
	input_box_wait.c \
	random.c \
	sdlkeyboardtochar.c \
	text.c \
	time.c \
	xml.c \
	list.c \
	mathematics.c \
	key.c \
	tree_set.c \
	tree_map.c \
	window.c

if OS_IS_APPLE 
libMLVMain_la_SOURCES = \
	SDLMain.m
endif

if MEMORY_DEBUG
libMLV_la_SOURCES += memory_debug.c
endif

if MEMORY_DEBUG
libMLV_la_CFLAGS = ${libxml_CFLAGS} ${glib_CFLAGS} -DDATA_PATH=\"${DATA_PATH}\"
libMLV_la_LIBADD = ${libxml_LIBS} ${glib_LIBS} 
else
libMLV_la_CFLAGS = ${sdl_CFLAGS} ${sdlttf_CFLAGS} ${sdlimage_CFLAGS} ${sdlmixer_CFLAGS} ${libxml_CFLAGS} ${glib_CFLAGS} -DDATA_PATH=\"${DATA_PATH}\"
libMLV_la_LIBADD =  ${sdl_LIBS} ${libxml_LIBS} ${glib_LIBS} ${sdlttf_LIBS} ${sdlgfx_LIBS} ${sdlimage_LIBS} ${sdlmixer_LIBS}
endif
libMLV_la_LDFLAGS = -version-info $(MLV_CURRENT):$(MLV_REVISION):$(MLV_AGE) 

# To Compile .DLL
if RELATIVEPATH
libMLV_la_LDFLAGS += -no-undefined
endif

mlv_include_HEADERS = \
	MLV_audio.h \
	MLV_all.h \
	MLV_animation.h \
	MLV_color.h \
	MLV_device_with_buttons.h \
	MLV_event.h \
	MLV_shape.h \
	MLV_image.h \
	MLV_information.h \
	MLV_input_box_va.h \
	MLV_keyboard.h \
	MLV_mouse.h \
	MLV_path.h \
	MLV_playlist.h \
	MLV_input_box.h \
	MLV_random.h \
	MLV_text.h \
	MLV_text_va.h \
	MLV_time.h \
	MLV_xml.h \
	MLV_xml_va.h \
	MLV_window.h

noinst_HEADERS = \
	image.h \
	data_structure.h \
	memory_debug.h \
	memory_management.h \
	platform.h \
	input_box.h \
	sdlkeyboardtochar.h \
	text.h \
	warning_error.h \
	mathematics.h \
	list.h \
	key.h \
	tree_set.h \
	tree_map.h \
	SDLMain.h

