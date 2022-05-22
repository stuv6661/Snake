/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2012 Adrien Boussicault, Marc Zipstein
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

#ifndef __MLV__IMAGE_H__
#define __MLV__IMAGE_H__

#include "platform.h"

#if defined( __MLV_ANDROID__ )
#	define MLV_16_BPP 16
#else
#	define MLV_32_BPP 32
#endif

#if defined( MLV_32_BPP )
#	define MLV_BPP 32
#elif defined( MLV_16_BPP )
#	define MLV_BPP 16
#endif

#ifndef MEMORY_DEBUG
#if defined( OS_WINDOWS )
#	include <SDL/SDL.h>
#elif defined( OS_APPLE )
#	include <SDL/SDL.h>
#else
#	include <SDL/SDL.h>
#endif
#else
#include "memory_debug.h"
#endif

SDL_Surface* create_surface( int width, int height );
void get_pixel_on_image_unsafe( SDL_Surface* surface, int x, int y,
	int* red, int* green, int* blue, int* alpha
);

#endif
