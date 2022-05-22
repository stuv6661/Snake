/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010 Adrien Boussicault, Marc Zipstein
 *
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MLV__DATA_STRUCTURE_H_
#define __MLV__DATA_STRUCTURE_H_

#include "platform.h"

#ifndef MEMORY_DEBUG
#if defined( OS_WINDOWS )
#	include <SDL/SDL.h>
#	include <SDL/SDL_framerate.h>
#elif defined( OS_APPLE )
#   include <SDL/SDL.h>
#	include <SDL/SDL_framerate.h>
#else
#	include <SDL/SDL.h>
#	include <SDL/SDL_framerate.h>
#endif



#else
#include "memory_management.h"
#endif

#include <glib.h>

#include "MLV_playlist.h"
#include "MLV_text.h"

#include "list.h"

typedef struct _DataMLV {
	SDL_Surface *screen;
	Uint32 width;
	Uint32 height;
	int full_screen_is_enable;
	SDL_Rect rectangle;
	SDL_Surface *save_screen;
	SDL_sem* audio_semaphore;
	SDL_AudioSpec audio_device_spec;
	MLV_List* playing_streaming;
	MLV_List* playlists;
	MLV_List* active_playlists;
	MLV_Font* defaultFont;
	FPSmanager frame_rate_manager;
	FPSmanager frame_rate_manager_for_MLV_wait_event;
} DataMLV;

struct _MLV_Image {
    SDL_Surface * surface;
};

#endif
