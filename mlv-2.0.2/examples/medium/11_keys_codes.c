#ifndef _GNU_SOURCE
	#define _GNU_SOURCE
#endif
#include <stdio.h>

#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( __CYGWIN__ )
extern int asprintf (char **, const char *, ...);
#endif

#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>

void draw_sentence( int width, int height ){
	MLV_clear_window( MLV_COLOR_BLACK );
	MLV_draw_adapted_text_box(
		10, 50, 
		"Appuyez sur une touche pour connaître :\n    - son code,\n    - son mode,\n    - son code unicode,\n    - le caractère qui lui est associé.",
		3,
		MLV_COLOR_BLACK, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		MLV_TEXT_LEFT
	);
}

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){

	int width = 640;
	int height = 480;

	MLV_create_window( "beginner - 10 - Le code des touches du clavier", "codes - touches du clavier", width, height );

	draw_sentence( width, height );
	MLV_actualise_window();

	MLV_Keyboard_button sym;
	const char* sym_string;
	MLV_Keyboard_modifier mod;
	char* mod_string;
	int unicode;
	char* character;
	char* text;

	while( 1 ){
		MLV_wait_keyboard( &sym, &mod, &unicode );
		sym_string = MLV_convert_keyboard_button_to_string( sym );
		mod_string = MLV_convert_keyboard_mod_to_string( mod );
		character = MLV_convert_unicode_to_string( unicode );

		if(
			asprintf(
				&text, 
				"Information sur la touche:\n-------------------------\nSym : %s \nMod : %s \nUnicode : %d \nCaractère : %s \n\n",
				sym_string, mod_string, unicode, character
			) == -1
		){
			fprintf( stderr, "Allocation Error - file : %s, line : %d \n", __FILE__, __LINE__);
			exit(1);
		};

		printf( "%s", text );

		draw_sentence( width, height );
		MLV_draw_adapted_text_box(
			10, 160, text, 6,
			MLV_COLOR_BLACK, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
			MLV_TEXT_LEFT
		);
		MLV_actualise_window();

		free( character );
		free( mod_string );
		free( text );
	
	}

	MLV_free_window();

	return 0;
}

/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010-2014 Adrien Boussicault, Marc Zipstein
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
