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

#ifndef __MLV__TEXT_H__
#define __MLV__TEXT_H__

#include "platform.h"

#ifndef MEMORY_DEBUG
#if defined( OS_WINDOWS )
#	include <SDL/SDL_ttf.h>
#elif defined( OS_APPLE )
#	include <SDL_ttf/SDL_ttf.h>
#else
#	include <SDL/SDL_ttf.h>
#endif
#else
#include "memory_debug.h"
#endif

struct _MLV_Font {
	int size;
	TTF_Font* font;
};

void init_font();

void quit_font();

void drawString(
	SDL_Surface* textBox, int x, int y, 
	const char* message, MLV_Color color, TTF_Font* font 
);

#endif
