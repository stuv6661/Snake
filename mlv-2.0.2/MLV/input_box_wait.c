/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012 Adrien Boussicault, Marc Zipstein
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

#include <stdio.h>

#include "platform.h"

#ifdef OS_WINDOWS
/* Get va_list.  */
#if __STDC__ || defined __cplusplus || defined _MSC_VER
# include <stdarg.h>
#else
# include <varargs.h>
#endif
extern int vasprintf (char **, const char *, va_list);
#endif

#include "MLV_input_box.h"
#include "MLV_shape.h"
#include "MLV_color.h"
#include "MLV_window.h"
#include "MLV_event.h"
#include "data_structure.h"

#include "warning_error.h"

#include <stdlib.h>

#include "memory_management.h"
#include "image.h"

extern DataMLV* MLV_data;

void MLV_wait_particular_input_box( MLV_Input_box* input_box, char** text){
	MLV_Input_box* tmp_input_box = NULL;
	(*text) = NULL;

	//We activate the input_box
	MLV_activate_input_box( input_box );
	
	// We first flush the event queue
	MLV_flush_event_queue();

	// We wait for a input_box event
	while( ! (*text) ){
		MLV_Event event_type = MLV_get_event( 
			NULL, NULL, NULL,
			text, &tmp_input_box, 
			NULL, NULL, NULL,
			NULL
		);
		if( (event_type==MLV_INPUT_BOX )  && input_box != tmp_input_box ){
			MLV_FREE( (*text), char );
			(*text) = NULL;
		}
		MLV_draw_all_input_boxes();
		MLV_actualise_window();
	}
}

void wait_input_box_with_font(
	int sommetHautGaucheX, int sommetHautGaucheY,
	int sommetBasDroitX, int sommetBasDroitY,
	MLV_Color borderColor, MLV_Color textColor,
	MLV_Color backgroundColor,
	const char* informativeMessage,
	char** text,
	const MLV_Font* font
){
	MLV_Input_box* input_box = MLV_create_input_box_with_font(
		sommetHautGaucheX, sommetHautGaucheY,
		sommetBasDroitX, sommetBasDroitY,
		borderColor, textColor,
		backgroundColor,
		informativeMessage,
		font
	);

	SDL_Surface *save_screen = create_surface( MLV_data->width, MLV_data->height );
	SDL_BlitSurface( MLV_data->screen, NULL, save_screen, &(MLV_data->rectangle));

	MLV_wait_particular_input_box( input_box, text);
	MLV_free_input_box( input_box );

	SDL_BlitSurface( save_screen, NULL, MLV_data->screen, &(MLV_data->rectangle));
	SDL_FreeSurface( save_screen );

	MLV_actualise_window();
}

void MLV_wait_input_box_with_font_va(
	int sommetHautGaucheX, int sommetHautGaucheY,
	int sommetBasDroitX, int sommetBasDroitY,
	MLV_Color borderColor, MLV_Color textColor,
	MLV_Color backgroundColor,
	const char* informativeMessage,
	char** text,
	const MLV_Font* font, va_list pile
){
	char* complete_informative_message;
	if(
		vasprintf( 
			&complete_informative_message, informativeMessage, pile 
		)==-1 
	){
		ERROR("Unexpected Error.");
	}
	wait_input_box_with_font(
		sommetHautGaucheX, sommetHautGaucheY, sommetBasDroitX, sommetBasDroitY,
		borderColor, textColor, backgroundColor, complete_informative_message,
		text, font
	);
	free( complete_informative_message );
}

void MLV_wait_input_box_with_font(
	int sommetHautGaucheX, int sommetHautGaucheY,
	int sommetBasDroitX, int sommetBasDroitY,
	MLV_Color borderColor, MLV_Color textColor,
	MLV_Color backgroundColor,
	const char* informativeMessage,
	char** text,
	const MLV_Font* font, ...
){
	va_list pile;
	va_start( pile, font );
	MLV_wait_input_box_with_font_va(
		sommetHautGaucheX, sommetHautGaucheY, sommetBasDroitX, sommetBasDroitY,
		borderColor, textColor, backgroundColor, informativeMessage,
		text, font, pile
	);
	va_end( pile );
}

void MLV_wait_input_box_va(
	int sommetHautGaucheX, int sommetHautGaucheY,
	int sommetBasDroitX, int sommetBasDroitY,
	MLV_Color borderColor, MLV_Color textColor,
	MLV_Color backgroundColor,
	const char* informativeMessage,
	char** text, va_list pile
){
	MLV_wait_input_box_with_font_va(
		sommetHautGaucheX, sommetHautGaucheY,
		sommetBasDroitX, sommetBasDroitY,
		borderColor, textColor,
		backgroundColor,
		informativeMessage,
		text, MLV_data->defaultFont, pile
	);
}

void MLV_wait_input_box(
	int sommetHautGaucheX, int sommetHautGaucheY,
	int sommetBasDroitX, int sommetBasDroitY,
	MLV_Color borderColor, MLV_Color textColor,
	MLV_Color backgroundColor,
	const char* informativeMessage,
	char** text, ...
){
	va_list pile;
	va_start( pile, text );
	MLV_wait_input_box_va(
		sommetHautGaucheX, sommetHautGaucheY, sommetBasDroitX, sommetBasDroitY,
		borderColor, textColor, backgroundColor, informativeMessage, text, pile
	);
	va_end( pile );
}


