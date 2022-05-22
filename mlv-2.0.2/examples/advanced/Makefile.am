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

EXTRA_DIST= \
	informations.xml \
	animation_book.xml \
	Garuda-Oblique.ttf \
	fugue.ogg \
	walk.ogg \
	gallop.ogg \
	flower.jpg \
	blue_image.png \
	red_image.png \
	map.png \
	creature.png \
	Location_European_nation_states.svg \
	france.png \
	greece.png \
	italy.png \
	portugal.png \
	spain.png \
	COPYRIGHT \
	makefile-examples


noinst_PROGRAMS = \
	01_texts_and_boxes \
	02_font \
	03_music \
	04_sound \
	05_playlist \
	06_image \
	07_transparency \
	08_zone_click \
	09_animation \
	10_read_xml_file \
	11_animation_book\
	12_paths

AM_CPPFLAGS = ${MLV_CPPFLAGS}
AM_LDFLAGS = ${MLV_LDFLAGS} -static
LIBS +=  ${MLV_LIBADD}

# To profile MLV functions with gprof
if DEBUG
AM_LDFLAGS += -static
endif

docadvanceddir = $(docdir)/examples/advanced

docadvanced_DATA = \
	01_texts_and_boxes.c \
	02_font.c \
	03_music.c \
	04_sound.c \
	05_playlist.c \
	06_image.c \
	07_transparency.c \
	08_zone_click.c \
	09_animation.c \
	10_read_xml_file.c \
	11_animation_book.c \
	12_paths.c \
	animation_book.xml \
	informations.xml \
	Garuda-Oblique.ttf \
	fugue.ogg \
	gallop.ogg \
	walk.ogg \
	flower.jpg \
	blue_image.png \
	red_image.png \
	map.png \
	creature.png \
	france.png \
	greece.png \
	italy.png \
	portugal.png \
	spain.png \
	COPYRIGHT \
	makefile-examples

install-data-hook:
	mv $(DESTDIR)$(docadvanceddir)/makefile-examples $(DESTDIR)$(docadvanceddir)/Makefile

uninstall-hook:
	-rm -rf $(DESTDIR)$(docadvanceddir)/Makefile


01_texts_and_boxes_SOURCES = 01_texts_and_boxes.c
02_font_SOURCES = 02_font.c
03_music_SOURCES = 03_music.c
04_sound_SOURCES = 04_sound.c
05_playlist_SOURCES = 05_playlist.c
06_image_SOURCES = 06_image.c
07_transparency_SOURCES = 07_transparency.c
08_zone_click_SOURCES = 08_zone_click.c
09_animation_SOURCES = 09_animation.c
10_read_xml_file_SOURCES = 10_read_xml_file.c
11_animation_book_SOURCES = 11_animation_book.c
12_paths_SOURCES = 12_paths.c
