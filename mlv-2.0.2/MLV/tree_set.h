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

#ifndef __MLV__TREE_SET_H__
#define __MLV__TREE_SET_H__

typedef struct _MLV_TreeSet MLV_TreeSet;

struct _MLV_TreeSet {
	MLV_TreeSet* father;
	MLV_TreeSet* left_son;
	MLV_TreeSet* right_son;
	void* data;
	void (* data_destroying_function )( void* data );
	int (* sorting_function )( void* data1, void*data2 );
	int height;
};

MLV_TreeSet* MLV_add_data_in_tree_set(
	void* data,
	void (* data_destroying_function)( void* data ),
	int (* sorting_function)( void* data1, void* data2 ),
	MLV_TreeSet * tree_set
);

void MLV_init_tree_set( MLV_TreeSet* tree_set );

void MLV_clear_tree_set( MLV_TreeSet* tree_set );

void* MLV_get_data_from_tree_set( void* data, MLV_TreeSet* tree_set );

MLV_TreeSet* MLV_find_tree_set( void* data, MLV_TreeSet* tree_set );

void MLV_foreach_data_tree_set(
	void (* data_function )( void* data, void* data_user ),
	void* data_user,
	MLV_TreeSet* tree_set
);

#endif
