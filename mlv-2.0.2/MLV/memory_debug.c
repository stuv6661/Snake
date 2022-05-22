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

#include "memory_debug.h"

#include <stdlib.h>
#include <stdio.h>

#define DEBUG_MEMORY_MSG(x) { fprintf(stderr,"Memory Debug : %s \n",(x)); }

#include "memory_management.h"

int memory_debug_n;
SDL_EventFilter memory_debug_filter;
SDL_Event memory_debug_event;

Memory_debug_statistics memory_debug_statistics;

void init_memory_debug(){
	memory_debug_statistics.nb_create_surface = 0;
	memory_debug_statistics.nb_free_surface = 0;
	memory_debug_statistics.nb_init_sdl = 0;
	memory_debug_statistics.nb_close_sdl = 0;
	memory_debug_statistics.nb_create_semaphore = 0;
	memory_debug_statistics.nb_free_semaphore = 0;
	memory_debug_statistics.nb_malloc = 0;
	memory_debug_statistics.nb_free = 0;
	memory_debug_statistics.nb_free_wave = 0;
	memory_debug_statistics.nb_load_wave = 0;
	memory_debug_statistics.nb_open_font = 0;
	memory_debug_statistics.nb_close_font = 0;
	memory_debug_statistics.nb_init_ttf = 0;
	memory_debug_statistics.nb_quit_ttf = 0;
}

void print_memory_statistics(){
	fprintf(stderr,"--------------------------STATISTICS---------------------\n");
	fprintf(stderr,"Memory Debug : nb_create_surface : %i \n", memory_debug_statistics.nb_create_surface);
	fprintf(stderr,"Memory Debug : nb_free_surface : %i \n", memory_debug_statistics.nb_free_surface);
	fprintf(stderr,"Memory Debug : nb_init_sdl : %i \n", memory_debug_statistics.nb_init_sdl);
	fprintf(stderr,"Memory Debug : nb_close_sdl : %i \n", memory_debug_statistics.nb_close_sdl);
	fprintf(stderr,"Memory Debug : nb_create_semaphore : %i \n", memory_debug_statistics.nb_create_semaphore);
	fprintf(stderr,"Memory Debug : nb_free_semaphore : %i \n", memory_debug_statistics.nb_free_semaphore);
	fprintf(stderr,"Memory Debug : nb_malloc : %i \n", memory_debug_statistics.nb_malloc);
	fprintf(stderr,"Memory Debug : nb_calloc : %i \n", memory_debug_statistics.nb_calloc);
	fprintf(stderr,"Memory Debug : nb_free  : %i \n", memory_debug_statistics.nb_free);
	fprintf(stderr,"Memory Debug : nb_free_wave : %i \n", memory_debug_statistics.nb_free_wave);
	fprintf(stderr,"Memory Debug : nb_load_wave  : %i \n", memory_debug_statistics.nb_load_wave);
	fprintf(stderr,"Memory Debug : nb_open_font : %i \n", memory_debug_statistics.nb_open_font);
	fprintf(stderr,"Memory Debug : nb_close_font  : %i \n", memory_debug_statistics.nb_close_font);
	fprintf(stderr,"Memory Debug : nb_init_ttf : %i \n", memory_debug_statistics.nb_init_ttf);
	fprintf(stderr,"Memory Debug : nb_quit_ttf  : %i \n", memory_debug_statistics.nb_quit_ttf);
	fprintf(stderr,"----------------------END-STATISTICS---------------------\n");
}

typedef enum {
	MEMORY_DEBUG_CREATE_SURFACE,
	MEMORY_DEBUG_FREE_SURFACE,
	MEMORY_DEBUG_INIT_SDL,
	MEMORY_DEBUG_CLOSE_SDL,
	MEMORY_DEBUG_CREATE_SEMAPHORE,
	MEMORY_DEBUG_FREE_SEMAPHORE,
	MEMORY_DEBUG_MALLOC,
	MEMORY_DEBUG_CALLOC,
	MEMORY_DEBUG_FREE,
	MEMORY_DEBUG_FREE_WAVE,
	MEMORY_DEBUG_LOAD_WAVE,
	MEMORY_DEBUG_OPEN_FONT,
	MEMORY_DEBUG_CLOSE_FONT,
	MEMORY_DEBUG_QUIT_TTF,
	MEMORY_DEBUG_INIT_TTF
} Memory_debug_statistics_type;

void update_memory_statistics( Memory_debug_statistics_type type ){
	switch( type ){
		case MEMORY_DEBUG_CREATE_SURFACE :
			{
				memory_debug_statistics.nb_create_surface++;
			}
			break;
		case MEMORY_DEBUG_FREE_SURFACE :
			{
				memory_debug_statistics.nb_free_surface++;
			}
			break;
		case MEMORY_DEBUG_INIT_SDL :
			{
				memory_debug_statistics.nb_init_sdl++;
			}
			break;
		case MEMORY_DEBUG_CLOSE_SDL :
			{
				memory_debug_statistics.nb_close_sdl++;
			}
			break;
		case MEMORY_DEBUG_CREATE_SEMAPHORE :
			{
				memory_debug_statistics.nb_create_semaphore++;
			}
			break;
		case MEMORY_DEBUG_FREE_SEMAPHORE :
			{
				memory_debug_statistics.nb_free_semaphore ++;
			}
			break;
		case MEMORY_DEBUG_MALLOC :
			{
				memory_debug_statistics.nb_malloc ++;
			}
			break;
		case MEMORY_DEBUG_CALLOC :
			{
				memory_debug_statistics.nb_calloc ++;
			}
			break;
		case MEMORY_DEBUG_FREE :
			{
				memory_debug_statistics.nb_free ++;
			}
			break;
		case MEMORY_DEBUG_FREE_WAVE :
			{
				memory_debug_statistics.nb_free_wave ++;
			}
			break;
		case MEMORY_DEBUG_LOAD_WAVE :
			{
				memory_debug_statistics.nb_load_wave ++;
			}
			break;
		case MEMORY_DEBUG_OPEN_FONT :
			{
				memory_debug_statistics.nb_open_font ++;
			}
			break;
		case MEMORY_DEBUG_CLOSE_FONT :
			{
				memory_debug_statistics.nb_close_font ++;
			}
			break;
		case MEMORY_DEBUG_QUIT_TTF :
			{
				memory_debug_statistics.nb_quit_ttf ++;
			}
			break;
		case MEMORY_DEBUG_INIT_TTF :
			{
				memory_debug_statistics.nb_init_ttf ++;
			}
			break;
		default:;
	}
}

void close_memory_debug(){
}

void filledCircleColor( SDL_Surface* screen, int x, int y, int radius, Uint32 color){
}

void circleColor( SDL_Surface* screen, int x, int y, int radius, Uint32 color){
}

void ellipseColor( SDL_Surface* screen, int x, int y, int radius_x, int radius_y, Uint32 color ){
}

void filledEllipseColor( SDL_Surface* screen, int x, int y, int radius_x, int radius_y, Uint32 color){
}

void polygonColor( SDL_Surface* screen, Sint16* vx, Sint16* vy, int npoints, Uint32 color){
}

void filledPolygonColor( SDL_Surface* screen, Sint16* vx, Sint16* vy, int npoints, Uint32 color){
}

void rectangleColor( SDL_Surface* screen, int x, int y, int width, int height, Uint32 color){
}

void boxColor( SDL_Surface* screen, int x, int y, int width, int height, Uint32 color){
}

void lineColor( SDL_Surface* screen, int x1, int y1, int x2, int y2, Uint32 color){
}

void pixelColor( SDL_Surface* screen, int x, int y, Uint32 color){
}

void stringColor( SDL_Surface* screen, int x, int y, const char *text, Uint32 color){
}

int SDL_BlitSurface( SDL_Surface* src, SDL_Rect* rectangle_src, SDL_Surface* dst, SDL_Rect* rectangle_dest){
	return 0;
}


int memory_debug_modulo;

int SDL_PollEvent( SDL_Event* event ){
	memory_debug_n = (memory_debug_n+1)%memory_debug_modulo;
	switch( memory_debug_n ){
		case 0:
			{
				DEBUG_MEMORY_MSG("Pas d'evenement") 
				return 0;
			}
		case 1: ;
			{
				DEBUG_MEMORY_MSG("souris deplace 10 10") 
				event->type=SDL_MOUSEMOTION;
				event->motion.which = 0;
				event->motion.state = SDL_RELEASED;
				event->motion.x = 10;
				event->motion.y = 10;
				event->motion.xrel = -90;
				event->motion.yrel = -90;
			};
			break;
		case 2: ;
			{
				DEBUG_MEMORY_MSG("bouton gauche souris tape") 
				event->type=SDL_MOUSEBUTTONDOWN;
				event->button.which = 0;
				event->button.button = SDL_BUTTON_LEFT;
				event->button.state = SDL_PRESSED;
				event->button.x = 10;
				event->button.y = 10;
			};
			break;
		case 3: ;
			{
				DEBUG_MEMORY_MSG("bouton gauche souris relache") 
				event->type=SDL_MOUSEBUTTONUP;
				event->button.which = 0;
				event->button.button = SDL_BUTTON_LEFT;
				event->button.state = SDL_RELEASED;
				event->button.x = 10;
				event->button.y = 10;
			};
			break;
		case 4: ;
			{
				DEBUG_MEMORY_MSG("souris deplace 100") 
				event->type=SDL_MOUSEMOTION;
				event->motion.which = 0;
				event->motion.state = SDL_RELEASED;
				event->motion.x = 100;
				event->motion.y = 100;
				event->motion.xrel = 90;
				event->motion.yrel = 90;
			};
			break;
		case 5: ;
			{
				DEBUG_MEMORY_MSG("bouton gauche souris tape") 
				event->type=SDL_MOUSEBUTTONDOWN;
				event->button.which = 0;
				event->button.button = SDL_BUTTON_LEFT;
				event->button.state = SDL_PRESSED;
				event->button.x = 100;
				event->button.y = 100;
			};
			break;
		case 6: ;
			{
				DEBUG_MEMORY_MSG("bouton gausche souris relache") 
				event->type=SDL_MOUSEBUTTONUP;
				event->button.which = 0;
				event->button.button = SDL_BUTTON_LEFT;
				event->button.state = SDL_RELEASED;
				event->button.x = 100;
				event->button.y = 100;
			};
			break;
		case 7:
			{
				DEBUG_MEMORY_MSG("a tape") 
				event->type=SDL_KEYDOWN;
				event->key.type=SDL_KEYDOWN;
				event->key.which=0;
				event->key.state=SDL_PRESSED;
				event->key.keysym.scancode = 0;
				event->key.keysym.sym=SDLK_a;
				event->key.keysym.mod=KMOD_NONE;
				event->key.keysym.unicode=97;
			};
			break;
		case 8: ;
			{
				DEBUG_MEMORY_MSG("a relache") 
				event->type=SDL_KEYUP;
				event->key.type=SDL_KEYUP;
				event->key.which=0;
				event->key.state=SDL_RELEASED;
				event->key.keysym.scancode = 0;
				event->key.keysym.sym=SDLK_a;
				event->key.keysym.mod=KMOD_NONE;
				event->key.keysym.unicode=97;
			};
			break;
		case 9: ;
			{
				DEBUG_MEMORY_MSG("b tape") 
				event->type=SDL_KEYDOWN;
				event->key.type=SDL_KEYDOWN;
				event->key.which=0;
				event->key.state=SDL_PRESSED;
				event->key.keysym.scancode = 0;
				event->key.keysym.sym=SDLK_b;
				event->key.keysym.mod=KMOD_NONE;
				event->key.keysym.unicode=98;
			};
			break;
		case 10: ;
			{
				DEBUG_MEMORY_MSG("b relache") 
				event->type=SDL_KEYUP;
				event->key.type=SDL_KEYUP;
				event->key.which=0;
				event->key.state=SDL_RELEASED;
				event->key.keysym.scancode = 0;
				event->key.keysym.sym=SDLK_b;
				event->key.keysym.mod=KMOD_NONE;
				event->key.keysym.unicode=98;
			};
			break;
		case 11: ;
			{
				DEBUG_MEMORY_MSG("return tape") 
				event->type=SDL_KEYDOWN;
				event->key.type=SDL_KEYDOWN;
				event->key.which=0;
				event->key.state=SDL_PRESSED;
				event->key.keysym.scancode = 0;
				event->key.keysym.sym=SDLK_RETURN;
				event->key.keysym.mod=KMOD_NONE;
				event->key.keysym.unicode=13;
			};
			break;
		case 12: ;
			{
				DEBUG_MEMORY_MSG("Return relache") 
				event->type=SDL_KEYUP;
				event->key.type=SDL_KEYUP;
				event->key.which=0;
				event->key.state=SDL_RELEASED;
				event->key.keysym.scancode = 0;
				event->key.keysym.sym=SDLK_RETURN;
				event->key.keysym.mod=KMOD_NONE;
				event->key.keysym.unicode=13;
			};
			break;
		case 13:
			{
				DEBUG_MEMORY_MSG("Evenement User") 
				(*event)=memory_debug_event;
			};
			break;
		default: ;
	}
	return memory_debug_filter( event );
}

void SDL_SetAlpha(SDL_Surface* surface, int prop1, int prop2){
}


SDL_Surface* SDL_LoadBMP( const char* path ){
	update_memory_statistics( MEMORY_DEBUG_CREATE_SURFACE );
	return (SDL_Surface*) malloc( sizeof(SDL_Surface) );
}

SDL_Surface* SDL_CreateRGBSurface( int prop1, int w, int h, int resol, int r, int g, int b, int prop2 ){
	update_memory_statistics( MEMORY_DEBUG_CREATE_SURFACE );
	return (SDL_Surface*) malloc( sizeof(SDL_Surface) );
}

void SDL_FreeSurface( SDL_Surface* surface ){
	update_memory_statistics( MEMORY_DEBUG_FREE_SURFACE );
	free( surface );
}

SDL_Surface* rotozoomSurface( SDL_Surface* surface, double rotation, double zoom, int antialias){
	update_memory_statistics( MEMORY_DEBUG_CREATE_SURFACE );
	return (SDL_Surface*) malloc( sizeof(SDL_Surface) );
}


SDL_Surface* rotozoomSurfaceXY( SDL_Surface* surface, double rotation, double zoomx, double zoomy, int antialias){
	update_memory_statistics( MEMORY_DEBUG_CREATE_SURFACE );
	return (SDL_Surface*) malloc( sizeof(SDL_Surface) );
}

char* memory_debug_sdl_init;

int SDL_Init( int flags ){
	memory_debug_n = 0;
	memory_debug_modulo = 14;
	update_memory_statistics( MEMORY_DEBUG_INIT_SDL );
	memory_debug_sdl_init = (char*) malloc( sizeof(char) );
	return 0;
}

void SDL_Quit(){
	update_memory_statistics( MEMORY_DEBUG_CLOSE_SDL );
	free(memory_debug_sdl_init);
}

char* SDL_GetError(){
	return "TOTO";
}

SDL_Surface* SDL_SetVideoMode( int w, int h, int bits, int flags ){
	update_memory_statistics( MEMORY_DEBUG_CREATE_SURFACE );
	return (SDL_Surface*) malloc( sizeof( SDL_Surface ) );
}

void SDL_WM_SetCaption( const char* wind, const char* icon ){
}

void SDL_SetEventFilter( SDL_EventFilter filter ){
	memory_debug_filter = filter;
}

void SDL_Flip( SDL_Surface* surface ){
}

int SDL_SemWait( SDL_sem* semaphore ){
	return 0;
}

int SDL_SemPost( SDL_sem* semaphore ){
	return 0;
}

SDL_sem* SDL_CreateSemaphore( int valeur ){
	update_memory_statistics( MEMORY_DEBUG_CREATE_SEMAPHORE );
	return (SDL_sem*) malloc( sizeof( SDL_sem ) );
}

void SDL_DestroySemaphore( SDL_sem* semaphore ){
	update_memory_statistics( MEMORY_DEBUG_FREE_SEMAPHORE );
	free(semaphore);
}

void SDL_EnableUNICODE( int flags ){
}

int SDL_PushEvent( SDL_Event* event ){
	memory_debug_event = (*event);
	memory_debug_n = memory_debug_modulo - 2 ;
	return 0;
}

int SDL_GetTicks(){
	return 1;
}

void SDL_Delay( int milliseconds ){
}

void* memory_debug_malloc(size_t size, int line, char* file ){
	update_memory_statistics( MEMORY_DEBUG_MALLOC );
	fprintf(stderr, "Memory Debug : malloc ligne : %i, fichier : %s \n", line, file );
	return malloc( size );
}

void* memory_debug_calloc( size_t nmemb, size_t size, int line, char* file ){
	update_memory_statistics( MEMORY_DEBUG_CALLOC );
	fprintf(stderr, "Memory Debug : calloc ligne : %i, fichier : %s \n", line, file );
	return calloc( nmemb, size );
}

void memory_debug_free( void* ptr, int line, char* file ){
	update_memory_statistics( MEMORY_DEBUG_FREE );
	fprintf(stderr, "Memory Debug : free ligne : %i, fichier : %s \n", line, file );
	free( ptr );
}


void SDL_LockAudio(){
}

void SDL_UnlockAudio(){
}

void SDL_MixAudio(Uint8 *dst, Uint8 *src, Uint32 len, int volume){
}

SDL_AudioSpec* SDL_LoadWAV(const char *file, SDL_AudioSpec *spec, Uint8 **audio_buf, Uint32 *audio_len){
	update_memory_statistics( MEMORY_DEBUG_LOAD_WAVE );
	(*audio_buf) = (Uint8*)  malloc( 10000 * sizeof( Uint8 ) );
	(*audio_len) = 10000 * sizeof(Uint8);
	return spec;
}

void SDL_FreeWAV(Uint8 *audio_buf){
	update_memory_statistics( MEMORY_DEBUG_FREE_WAVE );
	free( audio_buf );
}

void SDL_PauseAudio(int pause_on){
}

int SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained){
	return 0;
}

void SDL_CloseAudio(){
}





int SDL_SetColorKey(SDL_Surface *surface, Uint32 flag, Uint32 key){
	return 0;
}




int TTF_SizeUTF8(TTF_Font *font, const char *text, int *w, int *h){
	return 0;
}


char* memory_debug_ttf_init;

int TTF_Init(void){
	update_memory_statistics( MEMORY_DEBUG_INIT_TTF );
	memory_debug_ttf_init = (char*) malloc( sizeof(char) );
	return 0;
}

void TTF_Quit(void){
	update_memory_statistics( MEMORY_DEBUG_QUIT_TTF );
	free( memory_debug_ttf_init );
}

TTF_Font * TTF_OpenFont(const char *file, int ptsize){
	update_memory_statistics( MEMORY_DEBUG_OPEN_FONT );
	return (TTF_Font*) malloc( sizeof(TTF_Font) );
}

void TTF_SetFontStyle(TTF_Font *font, int style){
}

void TTF_CloseFont(TTF_Font *font){
	update_memory_statistics( MEMORY_DEBUG_CLOSE_FONT );
	free( font );
}

SDL_Surface * TTF_RenderUTF8_Solid(TTF_Font *font, const char *text, SDL_Color fg){
	update_memory_statistics( MEMORY_DEBUG_CREATE_SURFACE );
	return (SDL_Surface*) malloc( sizeof(SDL_Surface) );
}


