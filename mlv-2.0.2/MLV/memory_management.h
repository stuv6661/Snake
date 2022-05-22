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

#ifndef __MLV__MEMORY_MANAGEMENT_H__
#define __MLV__MEMORY_MANAGEMENT_H__

#include <stdlib.h>

#ifndef MEMORY_DEBUG
	#define MLV_MALLOC( size, type ) (type *) malloc( (size) * sizeof( type ) ) 
	#define MLV_CALLOC( nmemb, size, type ) (type *) calloc( nmemb, (size) * sizeof( type ) ) 
	#define MLV_FREE( ptr, type ) free( (ptr) ) 
#else
	#include "memory_debug.h"

	#define MLV_MALLOC( size, type ) (type *) memory_debug_malloc( (size) * sizeof( type ), __LINE__, __FILE__ ) 
	#define MLV_CALLOC( size, type ) (type *) memory_debug_calloc( (size) * sizeof( type ), __LINE__ , __FILE__ ) 
	#define MLV_FREE( ptr, type ) memory_debug_free( (ptr), __LINE__, __FILE__ ) 
#endif

#endif
