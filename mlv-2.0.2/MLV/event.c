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

#include "MLV_event.h"
#include "MLV_mouse.h"

#include "platform.h"

#ifndef MEMORY_DEBUG
#if defined( OS_WINDOWS )
#	include <SDL/SDL.h>
#	include <SDL/SDL_framerate.h>
#elif defined( OS_APPLE )
#   include <SDL/SDL.h>
#	include <SDL/SDL_framerate.h>
#else
#	include <SDL/SDL.h>
#	include <SDL/SDL_framerate.h>
#endif
#else
#include "memory_debug.h"
#endif

#include <string.h>

#include "warning_error.h"

#include "memory_management.h"

#include "MLV_time.h"

#include "data_structure.h"

extern DataMLV* MLV_data;


MLV_Event MLV_get_event( 
	MLV_Keyboard_button* key_sym, MLV_Keyboard_modifier* key_mod, int* unicode,
	char** texte, MLV_Input_box** input_box,
	int* mouse_x, int* mouse_y, MLV_Mouse_button* mouse_button,
	MLV_Button_state* state
){
	SDL_Event event;
	int invalidEvent = 1;
	while( invalidEvent ){
		if( SDL_PollEvent( &event ) ){
			switch( event.type ){
				case SDL_KEYDOWN: {
					if( key_sym || key_mod || state ){
						if( key_sym ){
							(*key_sym) = (MLV_Keyboard_button) 
								event.key.keysym.sym;
						}
						if( key_mod ){
							(*key_mod) = (MLV_Keyboard_modifier) 
								event.key.keysym.mod;
						}
						if( unicode ){
							(*unicode) = event.key.keysym.unicode;
						}
						if( state ){
							(*state) = MLV_PRESSED;
						}
						return MLV_KEY;
					}
				};
				break;
				case SDL_KEYUP:{
					if( key_sym || key_mod || state ){
						if( key_sym ){
							(*key_sym) = (MLV_Keyboard_button) 
								event.key.keysym.sym;
						}
						if( key_mod ){
							(*key_mod) = (MLV_Keyboard_modifier) 
								event.key.keysym.mod;
						}
						if( unicode ){
							(*unicode) = event.key.keysym.unicode;
						}
						if( state ){
							(*state) = MLV_RELEASED;
						}
						return MLV_KEY;
					}
				};
				break;
				case SDL_MOUSEMOTION:{
					if( mouse_x || mouse_y ){
						if( mouse_x ){
							(*mouse_x) = event.motion.x;
						}
						if( mouse_y ){
							(*mouse_y) = event.motion.y;
						}
						return MLV_MOUSE_MOTION;
					}
				}
				break;
				case SDL_MOUSEBUTTONUP: {
					if(  mouse_x || mouse_y || mouse_button  || state ){
						if( mouse_x ){
							(*mouse_x) = event.button.x;
						}
						if( mouse_y ){
							(*mouse_y) = event.button.y;
						}
						if( mouse_button ){
							(*mouse_button) = (MLV_Mouse_button) 
								event.button.button;
						}
						if( state ){
							(*state) = MLV_RELEASED;
						}
						return MLV_MOUSE_BUTTON;
					}
				}
				break;
				case SDL_MOUSEBUTTONDOWN: {
					if(  mouse_x || mouse_y || mouse_button  || state ){
						if( mouse_x ){
							(*mouse_x) = event.button.x;
						}
						if( mouse_y ){
							(*mouse_y) = event.button.y;
						}
						if( mouse_button ){
							(*mouse_button) = (MLV_Mouse_button) 
								event.button.button;
						}
						if( state ){
							(*state) = MLV_PRESSED;
						}
						return MLV_MOUSE_BUTTON;
					}
				}
				break;
				case SDL_QUIT:{
				}
				break;
				case SDL_USEREVENT: {
					if( event.user.code == MLV_INPUT_BOX ){
						if( texte || input_box ){
							if( input_box ){
								(*input_box) = event.user.data1;
							}
							if( texte ){
								int size = strlen(event.user.data2)+1;
								(*texte) = MLV_MALLOC( size, char );
								memcpy(
									(*texte), 
									event.user.data2,
									size
								);
							}
							return MLV_INPUT_BOX;
						}
					}
                }
            	break;

				default:;
			}
		}else{
			invalidEvent = 0;
		}
	}
	return MLV_NONE;
}

MLV_Event MLV_wait_event( 
	MLV_Keyboard_button* key_sym, MLV_Keyboard_modifier* key_mod, int* unicode, 
	char** texte, MLV_Input_box** input_box,
	int* mouse_x, int* mouse_y, MLV_Mouse_button* mouse_button,
	MLV_Button_state* state
){
	MLV_Event resultat;
	while( 
		(
			resultat = MLV_get_event( 
				key_sym, key_mod, unicode,
				texte, input_box,
				mouse_x, mouse_y, mouse_button,
				state
			)
		) == MLV_NONE
	) SDL_framerateDelay( &(MLV_data->frame_rate_manager_for_MLV_wait_event) );
	return resultat;
}

MLV_Event MLV_wait_event_or_seconds( 
	MLV_Keyboard_button* key_sym, MLV_Keyboard_modifier* key_mod, int* unicode, 
	char** texte, MLV_Input_box** input_box,
	int* mouse_x, int* mouse_y, MLV_Mouse_button* mouse_button,
	MLV_Button_state* state, int seconds
){
	MLV_Event resultat;
	int time = MLV_get_time();
	while( 
		(
			(
				resultat = MLV_get_event( 
					key_sym, key_mod, unicode,
					texte, input_box,
					mouse_x, mouse_y, mouse_button,
					state
				)
			) == MLV_NONE
		) && (
			MLV_get_time() - time < seconds*1000
		)
	) SDL_framerateDelay( &(MLV_data->frame_rate_manager_for_MLV_wait_event) );
	return resultat;
}


void MLV_flush_event_queue(){
	MLV_get_event( 
		NULL, NULL, NULL,
		NULL, NULL,
		NULL, NULL, NULL,
		NULL
	);
}

MLV_Event MLV_wait_keyboard_or_mouse(
	MLV_Keyboard_button* sym, MLV_Keyboard_modifier* mod, int* unicode,
	int* mouse_x, int* mouse_y
){
	MLV_Event resultat;
	MLV_Button_state state;
	MLV_Mouse_button mouse_button;

	// We remove all existing event from the queue
	MLV_flush_event_queue();

	MLV_Keyboard_button tmp_sym;
	MLV_Keyboard_modifier tmp_mod;
	int tmp_unicode;
	int tmp_mouse_x;
	int tmp_mouse_y;

	//We wait for a new keyboard or mouse event
	while( 
		(
			(
				(
					resultat = MLV_wait_event( 
						&tmp_sym, &tmp_mod, &tmp_unicode,
						NULL, NULL,
						&tmp_mouse_x, &tmp_mouse_y, &mouse_button,
						&state
					)
				) != MLV_KEY
			) && ( 
				( resultat != MLV_MOUSE_BUTTON ) ||
				( mouse_button != MLV_BUTTON_LEFT ) 
			)
		) || (
			state != MLV_PRESSED 
		)
	);

	switch( resultat ){
		case MLV_KEY:
			if( sym ) *sym = tmp_sym;
			if( mod ) *mod = tmp_mod;
			if( unicode ) *unicode = tmp_unicode;
			break;
		case MLV_MOUSE_BUTTON:
			if( mouse_x ) *mouse_x = tmp_mouse_x;
			if( mouse_y ) *mouse_y = tmp_mouse_y;
			break;
		default:
			ERROR("Valeur d'evenements innatendu.");
	}

	return resultat;
}


MLV_Event MLV_wait_keyboard_or_mouse_or_seconds(
	MLV_Keyboard_button* sym, MLV_Keyboard_modifier* mod, int* unicode,
	int* mouse_x, int* mouse_y,
	int seconds
){
	MLV_Event resultat;
	MLV_Button_state state;
	MLV_Mouse_button mouse_button;

	// We remove all existing event from the queue
	MLV_flush_event_queue();

	int time = MLV_get_time();

	MLV_Keyboard_button tmp_sym;
	MLV_Keyboard_modifier tmp_mod;
	int tmp_unicode;
	int tmp_mouse_x;
	int tmp_mouse_y;

	int event_is_not_valid = 0;
	//We wait for a new keyboard or mouse event
	while(
		( 
			event_is_not_valid = (
				(
					(
						resultat = MLV_wait_event_or_seconds( 
							&tmp_sym, &tmp_mod, &tmp_unicode,
							NULL, NULL,
							&tmp_mouse_x, &tmp_mouse_y, &mouse_button,
							&state,
							seconds - (MLV_get_time() - time)/1000
						)
					) != MLV_KEY
				) && ( 
					( resultat != MLV_MOUSE_BUTTON ) ||
					( mouse_button != MLV_BUTTON_LEFT ) 
				)
			) || (
				state != MLV_PRESSED 
			)
		) && (
			(MLV_get_time() - time) < seconds*1000
		)
	);
	if(event_is_not_valid) return MLV_NONE;

	switch( resultat ){
		case MLV_KEY:
			if( sym ) *sym = tmp_sym;
			if( mod ) *mod = tmp_mod;
			if( unicode ) *unicode = tmp_unicode;
			break;
		case MLV_MOUSE_BUTTON:
			if( mouse_x ) *mouse_x = tmp_mouse_x;
			if( mouse_y ) *mouse_y = tmp_mouse_y;
			break;
		default:
			ERROR("Valeur d'evenements innatendu.");
	}
		
	return resultat;
}

const char* MLV_convert_event_to_string( MLV_Event event_code ){
	switch( event_code ){
		case MLV_NONE:
			return "MLV_NONE";
		case MLV_KEY:
			return "MLV_KEY";
		case MLV_INPUT_BOX:
			return "MLV_INPUT_BOX";
		case MLV_MOUSE_BUTTON:
			return "MLV_MOUSE_BUTTON";
		case MLV_MOUSE_MOTION:
			return "MLV_MOUSE_MOTION";
		default:
			ERROR( "Event code unexpected." );
	}
	return NULL;
}

MLV_Event MLV_convert_string_to_event( const char* event_string ){
	if( strcmp( event_string, "MLV_NONE" )==0 ){
		return MLV_NONE;
	}
	if( strcmp( event_string, "MLV_KEY" )==0 ){
		return MLV_KEY;
	}
	if( strcmp( event_string, "MLV_INPUT_BOX" )==0 ){
		return MLV_INPUT_BOX;
	}
	if( strcmp( event_string, "MLV_MOUSE_BUTTON" )==0 ){
		return MLV_MOUSE_BUTTON;
	}
	if( strcmp( event_string, "MLV_MOUSE_MOTION" )==0 ){
		return MLV_MOUSE_MOTION;
	}
	ERROR( "Event name unknown." );
	return -1;
}

const char* MLV_convert_button_state_to_string( MLV_Button_state state_code ){
	switch( state_code ){
		case  MLV_PRESSED :
			return "MLV_PRESSED";
		case MLV_RELEASED :
			return "MLV_RELEASED";
		default:
			ERROR( "Unexpected state code." );
	}
	return NULL;
}

MLV_Button_state MLV_convert_string_to_button_state( const char* state_string ){
	if( strcmp( state_string, "MLV_PRESSED" ) ){
		return MLV_PRESSED;
	}
	if( strcmp( state_string, "MLV_RELEASED" ) ){
		return MLV_RELEASED;
	}
	ERROR( "Unexpected state name." );
	return -1;
}


