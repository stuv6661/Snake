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

#ifndef __MLV__TREE_MAP_H__
#define __MLV__TREE_MAP_H__

#include "key.h"

typedef struct _MLV_TreeMap MLV_TreeMap;

MLV_TreeMap* MLV_create_tree_map();

void MLV_free_tree_map( MLV_TreeMap* tree_map );

void MLV_superficial_free_tree_map( MLV_TreeMap* tree_map );

void MLV_add_data_in_tree_map(
	MLV_Key* key, void* data,
	void (* data_destroying_function)( void* data ),
	MLV_TreeMap* tree_map
);

void MLV_init_tree_map( MLV_TreeMap* tree_map );

void MLV_clear_tree_map( MLV_TreeMap* tree_map );

void* MLV_get_data_from_tree_map( MLV_Key* key, MLV_TreeMap* tree_map );

void MLV_foreach_key_data_tree_map(
	void (* key_data_function )( MLV_Key* key, void* data, void* data_user ),
	void* data_user,
	MLV_TreeMap* tree_map
);

#endif
