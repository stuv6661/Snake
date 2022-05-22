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

#ifndef __MLV__LIST_H__
#define __MLV__LIST_H__

typedef struct _MLV_List MLV_List;

struct _MLV_List {
	MLV_List* previous;
	MLV_List* next;
	void* data;
};

MLV_List* MLV_prepend_list( MLV_List* list, void* data );

void MLV_free_list( MLV_List* list );

void MLV_foreach_list(
	MLV_List* list,
	void (* function )( void* data, void* user_data ),
	void* user_data 
);

MLV_List* MLV_find_list( MLV_List* list, void* data );

MLV_List* MLV_remove_list( MLV_List* list, void* data );

#endif
