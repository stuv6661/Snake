/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2011,2012 Adrien Boussicault, Marc Zipstein
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

#include "MLV_path.h"

#include "warning_error.h"
#include "memory_management.h"
#include "data_structure.h"

#include <glib.h>
#include <stdarg.h>

char* MLV_get_base_name( const char* path ){
	return g_path_get_basename( path );
}

char* MLV_get_directory_name( const char* path ){
	return g_path_get_dirname( path );
}

int MLV_path_is_absolute( const char* path ){
	return g_path_is_absolute( path );
}

int MLV_path_is_relative( const char* path ){
	return ! MLV_path_is_absolute( path );
}

char* MLV_build_path_v( char** elements ){
	gchar* tmp_res = g_build_filenamev( elements );
	char* result = strdup( tmp_res );
	g_free( tmp_res ); // tmp_res have to be freed with g_free ( 
	                   //     see glib documentation
	                   // )
	return result; 
}

char* MLV_build_path( const char* first_element, ...){
	char *result;

	if( !first_element ) return NULL;

	va_list pile;
	const char* type;
	int compteur; 

	va_start( pile, first_element );
	compteur = 2;
	while(
		(
			type = va_arg( pile, char* )
		) != NULL
	){
		compteur ++;
	}
	va_end( pile );

	char** elements = MLV_MALLOC( compteur, char* );
	elements[0] = strdup( first_element );

	va_start( pile, first_element );
	int i;
	for( i=1; i<compteur; i++ ){
		type = va_arg( pile, const char*);
		if( type ){
			elements[i] = strdup( (const char*) type );
		}else{
			elements[i] = NULL;
		}
	}
	va_end( pile );

	result = MLV_build_path_v( elements );
	
	for( i=0; i<compteur-1; i++ ){
		MLV_FREE( elements[i], char );
	}
	MLV_FREE( elements, char* );
	return result;
}

int MLV_path_is_a_directory( const char* path ){
	return g_file_test( path, G_FILE_TEST_IS_DIR );
}

int MLV_path_is_a_file( const char* path ){
	return g_file_test( path, G_FILE_TEST_IS_REGULAR );
}

int MLV_path_exists( const char* path ){
	return g_file_test( path, G_FILE_TEST_EXISTS );
}

char * MLV_get_current_directory( ){
	return g_get_current_dir();
}

const char * MLV_get_temporary_directory( ){
	return g_get_tmp_dir();
}

const char * MLV_get_home_directory( ){
	return g_get_home_dir();
}

