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

#include "key.h"

#include "warning_error.h"
#include "memory_management.h"
#include <string.h>

struct _MLV_Key {
	void* value;
	void (* value_destroying_function )( void* value );
	int (* compare_values )( void* value1, void* value2 );
};

MLV_Key* MLV_create_key(
	void* value,
	void (* value_destroying_function )( void* data ),
	int (* compare_values )( void* value1, void* value2 )
){
	MLV_Key* key = MLV_MALLOC( 1, MLV_Key );
	key->value = value;
	key->value_destroying_function = value_destroying_function;
	key->compare_values = compare_values;
	return key;
}

void MLV_free_key( MLV_Key* key ){
	if( key ){
		if( key->value_destroying_function ){
			key->value_destroying_function( key->value );
		}
		MLV_FREE( key, MLV_Key );
	}
}

int MLV_compare_keys( MLV_Key* key1, MLV_Key* key2 ){
	return key1->compare_values( key1->value, key2->value );
}

void free_string( char* text ){
	MLV_FREE( text, char );
}

int compare_strings( char* text1, char* text2 ){
	return strcmp( text1, text2 );
}

MLV_Key* MLV_string_to_key( const char* text ){
    size_t l = strlen( text );
    char* text_copy = MLV_MALLOC( ( l + 1 ), char );
    strncpy( text_copy, text, l+1);
	return MLV_create_key(
		text_copy, 
		( void (*)( void* ) ) free_string,
		( int (*)( void*, void* ) ) compare_strings
	);
}

void free_integer( int* integer ){
	MLV_FREE( integer, int );
}

int compare_integers( int* int1, int* int2 ){
	return (*int1) - (*int2);
}

MLV_Key* MLV_integer_to_key( int integer ){
	int* value = MLV_MALLOC( 1, int );
	*value = integer;
	return MLV_create_key(
		value, 
		( void (*)( void* ) ) free_integer,
		(int (*)( void*, void* )) compare_integers
	);
}

void* MLV_get_value_from_key( MLV_Key* key ){
	return key->value;
}
