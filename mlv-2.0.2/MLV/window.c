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

#include "MLV_window.h"
#include "MLV_color.h"
#include "MLV_shape.h"

#include "config.h"

#include "text.h"

#include "input_box.h"
#include "MLV_color.h"
#include "MLV_audio.h"
#include <stdio.h>
#include <stdlib.h>

#include "platform.h"

#ifndef MEMORY_DEBUG
#if defined( OS_WINDOWS )
#	include <SDL/SDL.h>
#	include <SDL/SDL_gfxPrimitives.h>
#elif defined( OS_APPLE )
#	include <SDL/SDL.h>
#	include <SDL/SDL_gfxPrimitives.h>
#else
#	include <SDL/SDL.h>
#	include <SDL/SDL_gfxPrimitives.h>
#endif
#else
#include "memory_debug.h"
#endif

#include "warning_error.h"

#include "data_structure.h"
#include "image.h"
#include "memory_management.h"

#define SIZE_DEFAULT_FONT 12

int mlv_sdl_is_initialised = 0;
Uint32 mlv_width_of_desktop = 0;
Uint32 mlv_height_of_desktop = 0;

DataMLV *MLV_data = NULL;
void (*MLV_call_back_function_for_exit)(void*) = NULL;
void *MLV_call_back_data = NULL;

int events_filter(const SDL_Event *event){
	if( event->type == SDL_QUIT ){
		if( MLV_call_back_function_for_exit ){
			(*(MLV_call_back_function_for_exit))(MLV_call_back_data);
			return 1;
		}else{
			exit(0);
		}
	}
	return input_box_events_filter(event);
}


/**************************************************************************/
/* Initialisation and closing functions for default font                  */
/**************************************************************************/
void initialize_default_font(
	const char* path_to_font, unsigned int size_font
){
	if( !MLV_data ){
		ERROR("The MLV library has not been yet initialised. To initialise the \
MLV Library, create a new window with the MLV_create_window function."
		);
	}
	MLV_data->defaultFont = MLV_load_font( path_to_font, size_font ); 
}

void free_default_font(){
	if( !MLV_data ){
		ERROR("The MLV library has not been yet initialised. To initialise the \
MLV Library, create a new window with the MLV_create_window function."
		);
	}
	MLV_free_font( MLV_data->defaultFont );
}



/**************************************************************************/
/* Creation d'un fenetre graphique                                        */
/**************************************************************************/
void initialise_graphic_window(
	unsigned int width, unsigned int height, int full_screen_is_required
){
	#if defined( OS_ANDROID )
		Uint32 video_mode_flags = SDL_SWSURFACE | SDL_SRCALPHA;
	#else
		Uint32 video_mode_flags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_SRCALPHA;
	#endif
	if( full_screen_is_required ){
		video_mode_flags |= SDL_FULLSCREEN;
	}
	MLV_data->full_screen_is_enable = full_screen_is_required;

	if( MLV_data->screen ){
		SDL_FreeSurface( MLV_data->screen );
	}

	MLV_data->screen = SDL_SetVideoMode( width, height, MLV_BPP, video_mode_flags );
	width = MLV_data->screen->w;
	height = MLV_data->screen->h;

	MLV_data->width = width;
	MLV_data->height = height;
	MLV_data->rectangle.x = 0;
	MLV_data->rectangle.y = 0;
	MLV_data->rectangle.w = width;
	MLV_data->rectangle.h = height;
	if( MLV_data->save_screen ){
		SDL_FreeSurface( MLV_data->screen );
	}
	MLV_data->save_screen = create_surface( width, height ); // do we have to use SDL_ALPHA_OPAQUE here ?
	if ( MLV_data->screen == NULL ){
		fprintf(stderr,"Unable to set %dx%d video: %s\n", width, height, SDL_GetError());
		exit(1);
	}

	/**************************************************************************/
	/* Initialisation de la couleur du fond de la fenetre en noir.            */
	/**************************************************************************/
	MLV_draw_filled_rectangle(0,0,width,height,MLV_COLOR_BLACK);
	MLV_actualise_window();
}


void initialise_sdl(){
	if( ! mlv_sdl_is_initialised ){
		if(
			SDL_Init(
				SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO 
	#if defined( OS_LINUX ) // SDL thread is not supported on Windows and MacOSX
				| SDL_INIT_EVENTTHREAD  // Cette option est importante !
									  // Elle permet de faire en sorte 
					  // que le filtrage des évenements soit fait dés 
					  // réception d'un evenement de la part de l'OS
					  // Si cette option n'est pas activée, le filtre 
					  // d'evenement est applique seulement après un 
					  // appel à poll_event. Dans ce cas la gestion
					  // de l'arret automatique du programme après 
					  // utilisation de la croix des fenetre ne 
					  // fonctione plus correctement. En effet, si 
					  // l'utilisateur n'utilise pas de fonction mettant
					  // en jeu des évènement, le filtre n'est jamais
					  // appelé et le mécanisme d'arret automatique 
					  // non plus.
	#endif
			) <0 
		){
			printf("Unable to init SDL: %s\n", SDL_GetError());
			exit(1);
		}
	}
}

void initialise_size_of_desktop(){
	initialise_sdl();
	if( mlv_width_of_desktop==0 || mlv_height_of_desktop==0 ){
		const SDL_VideoInfo* info = SDL_GetVideoInfo();	
		mlv_width_of_desktop = info->current_w;
		mlv_height_of_desktop = info->current_h;
	}
}

void MLV_create_window_with_default_font(
	const char* window_name, const char* icone_name, 
	unsigned int width, unsigned int height,
	const char* path_to_font, unsigned int size_font
){
	if( MLV_data ){
		ERROR("The MLV library has yet been initialised.");
	}
	/**************************************************************************/
	/* Initialisation de la strcutre de MLV                                   */
	/**************************************************************************/
	MLV_data = MLV_MALLOC( 1, DataMLV );
	MLV_data->screen = NULL;
	MLV_data->save_screen = NULL;

	/**************************************************************************/
	/* Initialisation de la libriaire SDL pour l'uilisation de la video et du */
	/*   temps                                                                */
	/**************************************************************************/
	initialise_sdl();

	/**************************************************************************/
	/* Save the size of the desktop                                           */
	/**************************************************************************/
	initialise_size_of_desktop();

	/**************************************************************************/
	/* Creation d'un fenetre graphique                                        */
	/**************************************************************************/
	initialise_graphic_window( width, height, 0 );

	/**************************************************************************/
	/* Configuration des noms de la fenetre                                   */
	/**************************************************************************/
	SDL_WM_SetCaption(window_name, icone_name);

	/**************************************************************************/
	/* Configuration du mechanisme permettant d'utiliser les boîtes de saisie */
	/**************************************************************************/
	init_input_box_mechanism();

	/**************************************************************************/
	/* Configuration des fonts                                                */
	/**************************************************************************/
	init_font();
	
	/**************************************************************************/
	/* Création d'une font par default                                        */
	/**************************************************************************/
	initialize_default_font( path_to_font, size_font );

	/**************************************************************************/
	/* Initialise the Framerate Manager                                       */
	/**************************************************************************/
	SDL_initFramerate( &(MLV_data->frame_rate_manager) );
	SDL_setFramerate( &(MLV_data->frame_rate_manager), 100 );

	/**************************************************************************/
	/* Initialise the internal Framerate Manager for MLV_wait_event           */
	/**************************************************************************/
	SDL_initFramerate( &(MLV_data->frame_rate_manager_for_MLV_wait_event) );
	SDL_setFramerate( &(MLV_data->frame_rate_manager_for_MLV_wait_event), 24 );

	SDL_SetEventFilter(events_filter);
}

void MLV_create_window(
	const char* window_name, const char* icone_name, 
	unsigned int width, unsigned int height
){
	MLV_create_window_with_default_font(
		window_name, icone_name, width, height,
		DATA_PATH "/font/DejaVuSerif-Bold.ttf" , SIZE_DEFAULT_FONT
	);
}

void MLV_change_default_font(
	const char* path_to_font, unsigned int size_font
){
	free_default_font();
	initialize_default_font( path_to_font, size_font );
}

void MLV_enable_full_screen(){
	initialise_graphic_window( MLV_data->width, MLV_data->height, 1 );
}

void MLV_create_full_screen_window(
	const char* window_name, const char* icone_name,
	unsigned int width, unsigned int height
){
	MLV_create_window( window_name, icone_name, width, height );
	MLV_enable_full_screen();
}

void MLV_create_full_screen_window_with_default_font(
	const char* window_name, const char* icone_name, 
	unsigned int width, unsigned int height,
	const char* path_to_font, unsigned int size_font
){
	MLV_create_window_with_default_font(
		window_name, icone_name, width, height, path_to_font, size_font
	);
	MLV_enable_full_screen();
}

void MLV_disable_full_screen(){
	initialise_graphic_window( MLV_data->width, MLV_data->height, 0 );
}

int MLV_is_full_screen(){
	return MLV_data->full_screen_is_enable;
}

void MLV_change_window_size( unsigned int with, unsigned int height ){
	initialise_graphic_window( with, height, MLV_data->full_screen_is_enable );
}

void MLV_change_window_caption(
	const char* window_name, const char* icone_name
){
	SDL_WM_SetCaption( window_name, icone_name );
}

void MLV_get_window_size( unsigned int* width, unsigned int* height ){
	*width = MLV_data->width;
	*height = MLV_data->height;
}

int MLV_get_window_height(){
	return MLV_data->height;
}

int MLV_get_window_width(){
	return MLV_data->width;
}

void MLV_clear_window( MLV_Color color ){
	MLV_draw_filled_rectangle(
		0, 0, MLV_get_window_width( ), MLV_get_window_height( ), color
	);
}

void MLV_free_window(){
	if( ! MLV_data ){
		ERROR("No window has been created.");
	}
	SDL_FreeSurface(MLV_data->screen);
	SDL_FreeSurface(MLV_data->save_screen);
	free_default_font();
	quit_font();
	MLV_FREE( MLV_data, DataMLV );
	MLV_data = NULL;
	SDL_Quit();
	quit_input_box_mechanism();
}

void MLV_update_window(){
	if( (! MLV_data ) || (! MLV_data->screen) ){
		ERROR("A window can't be displayed whitout being created.");
	}
	SDL_Flip(MLV_data->screen);
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void MLV_actualise_window(){
	MLV_update_window();
}

void MLV_execute_at_exit( void (*function)(void*), void* data ){
	if( MLV_data ){
		ERROR("The mlv window is yet initialized. The function execute_at_exit() must be executed before the create_window() function.");
	}
	if( MLV_call_back_function_for_exit ){
		ERROR("The call back function for exiting program is yet initialized.");
	}
	MLV_call_back_function_for_exit = function;
	MLV_call_back_data = data;
}

void MLV_get_desktop_size( unsigned int* width, unsigned int* height ){
	initialise_size_of_desktop();
	*width = mlv_width_of_desktop;
	*height = mlv_height_of_desktop;
}

int MLV_get_desktop_height( ){
	initialise_size_of_desktop();
	return mlv_height_of_desktop;
}

int MLV_get_desktop_width( ){
	initialise_size_of_desktop();
	return mlv_width_of_desktop;
}
