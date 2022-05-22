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

#include "MLV_mouse.h"
#include "MLV_event.h"
#include "MLV_time.h"

#ifndef MEMORY_DEBUG
#include <SDL/SDL.h>
#else
#include "memory_debug.h"
#endif

#include "warning_error.h"

#include "memory_management.h"

void MLV_wait_mouse(int *x, int *y){
	MLV_Button_state state;
	MLV_Mouse_button mouse_button;

	// We remove all existing event from the queue
	MLV_flush_event_queue();

	//We wait for a new mouse event
	while(
		(
			MLV_wait_event(
					NULL, NULL, NULL,
					NULL, NULL,
					x, y, &mouse_button,
					&state
			) != MLV_MOUSE_BUTTON
		) ||
		( mouse_button != MLV_BUTTON_LEFT ) ||
		( state != MLV_PRESSED )
	);
};

int MLV_wait_mouse_or_seconds(int *x, int *y, int seconds){
	MLV_Button_state state;
	MLV_Mouse_button mouse_button;

	// We remove all existing event from the queue
	MLV_flush_event_queue();

	int time = MLV_get_time();

	//We wait for a new mouse event
	int resultat = 0;
	int tmp_x, tmp_y;
	while(
		(	
			resultat = 
			(
				MLV_wait_event_or_seconds(
					NULL, NULL, NULL,
					NULL, NULL,
					&tmp_x, &tmp_y, &mouse_button,
					&state,
					seconds - ( MLV_get_time() - time )/1000
				) != MLV_MOUSE_BUTTON
			) ||
			( mouse_button != MLV_BUTTON_LEFT ) ||
			( state != MLV_PRESSED )
		) && (
			(MLV_get_time() - time) < seconds*1000
		)
	);
	if( 
		! resultat &&
		mouse_button == MLV_BUTTON_LEFT &&
		state == MLV_PRESSED
	){
		if( x ) *x = tmp_x;
		if( y ) *y = tmp_y;
	}
	return !resultat;
}

const char* MLV_convert_mouse_button_to_string( MLV_Mouse_button button_code ){
	switch( button_code ){
		case MLV_BUTTON_LEFT:
			return "MLV_BUTTON_LEFT";
		case MLV_BUTTON_MIDDLE:
			return "MLV_BUTTON_MIDDLE";
		case MLV_BUTTON_RIGHT:
			return "MLV_BUTTON_RIGHT";
		default:
			ERROR("Button code unexpected");
	}
	return NULL;
}

MLV_Mouse_button MLV_convert_string_to_mouse_button( const char* button_string ){
	if( strcmp( button_string, "MLV_BUTTON_LEFT" )==0 ){
		return MLV_BUTTON_LEFT;
	}
	if( strcmp( button_string, "MLV_BUTTON_MIDDLE" )==0 ){
		return MLV_BUTTON_MIDDLE;
	}
	if( strcmp( button_string, "MLV_BUTTON_RIGHT" )==0 ){
		return MLV_BUTTON_RIGHT;
	}
	ERROR("Button name unexpected");
	return -1;
}

void MLV_get_mouse_position( int* x, int* y ){
	SDL_PumpEvents();
	SDL_GetMouseState(x,y);
}

MLV_Button_state MLV_get_mouse_button_state( MLV_Mouse_button mouse_button ){
	SDL_PumpEvents();
	if( SDL_GetMouseState(NULL,NULL) & SDL_BUTTON( mouse_button ) ){
		return MLV_PRESSED;
	}
	return MLV_RELEASED;
}


