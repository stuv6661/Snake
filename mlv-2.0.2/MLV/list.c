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

#include "list.h"
#include "memory_management.h"

MLV_List* MLV_prepend_list( MLV_List* list, void* data ){
	MLV_List* result = MLV_MALLOC( 1, MLV_List );
	if( list ){
		list->previous = result;
	}
	result->previous = NULL;
	result->next = list;
	result->data = data;
	return result; 
}

void MLV_free_list( MLV_List* list ){
	if( list ){
		MLV_free_list( list->next );
		MLV_FREE( list, MLV_List );
	}
}

void MLV_foreach_list(
	MLV_List* list,
	void (* function )( void* data, void* user_data ),
	void* user_data 
){
	while( list ){
		function( list->data, user_data );
		list = list->next;
	}	
}

MLV_List* MLV_find_list( MLV_List* list, void* data ){
	while( list ){
		if( list->data == data ){
			break;
		}
		list = list->next;
	}
	return list;
}

MLV_List* MLV_remove_list( MLV_List* list, void* data ){
	MLV_List* result;
	MLV_List* elem = MLV_find_list( list, data );
	if( elem->previous ){
		elem->previous->next = elem->next;
	}
	if( elem->next ){
		elem->next->previous = elem->previous;
	}
	if( elem==list ){
		result = elem->next;
	}else{
		result = list;
	}
	return result;
}

