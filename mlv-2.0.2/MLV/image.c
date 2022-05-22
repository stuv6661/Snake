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

#include "MLV_image.h"
#include "data_structure.h"

#include "platform.h"

#ifndef MEMORY_DEBUG
#if defined( OS_WINDOWS )
#	include <SDL/SDL.h>
#	include <SDL/SDL_image.h>
#	include <SDL/SDL_rotozoom.h>
#elif defined( OS_APPLE )
#	include <SDL/SDL.h>
#	include <SDL_image/SDL_image.h>
#	include <SDL/SDL_rotozoom.h>
#else
#	include <SDL/SDL.h>
#	include <SDL/SDL_image.h>
#	include <SDL/SDL_rotozoom.h>
#endif
#else
#include "memory_debug.h"
#endif

#include "warning_error.h"

#include "memory_management.h"

#include "data_structure.h"
#include "image.h"

extern DataMLV* MLV_data; 

SDL_Surface* create_surface( int width, int height ){
	Uint32 rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif
	#if defined( OS_ANDROID )
		return SDL_CreateRGBSurface(
			SDL_SWSURFACE|SDL_SRCALPHA,
			width, height,
			MLV_BPP, rmask, gmask, bmask, amask
		);
	#else
		return SDL_CreateRGBSurface(
			SDL_HWSURFACE|SDL_SRCALPHA,
			width, height,
			MLV_BPP, rmask, gmask, bmask, amask
		);
	#endif
}


MLV_Image* MLV_load_image( const char* file_image ){
	if( MLV_data==NULL ){
		ERROR("Before using MLV_load_image, you have to initialise the MLV library by calling MLV_create_windows.");
	}

	SDL_Surface* surface = IMG_Load( file_image );
	if( surface==NULL ){
		return NULL;
	}

	MLV_Image* image = MLV_MALLOC( 1, MLV_Image );
	image->surface = SDL_DisplayFormatAlpha(
		surface
	);
	
	SDL_FreeSurface( surface );
	return image;
}

int MLV_save_image_as_bmp( const MLV_Image* image,  const char* file_image ){
	return SDL_SaveBMP( image->surface, file_image );
}


void MLV_resize_image( MLV_Image* image, int width, int height ){
	double scalar_x = ((double) width) / ((double) image->surface->w);
	double scalar_y = ((double) height) / ((double) image->surface->h);
	MLV_scale_xy_image( image,  scalar_x, scalar_y );
}

void MLV_vertical_image_mirror( MLV_Image* image ){
	int width, height;
	MLV_get_image_size( image, &width, &height );
	Uint32 *pixel_src, *pixel_dst, tmp;
	int i=0; int j=0;
	for( i=0; i< width/2; i++ ){
		for( j=0; j<height; j++ ){
			pixel_src = ((Uint32*) image->surface->pixels) +
				j*image->surface->pitch/4 + i;
			pixel_dst = ((Uint32*) image->surface->pixels) +
				j*image->surface->pitch/4 + width-1-i;
			tmp = *pixel_dst;
			*pixel_dst = *pixel_src;
			*pixel_src = tmp;
		}
	}
}

void MLV_horizontal_image_mirror( MLV_Image* image ){
	int width, height;
	MLV_get_image_size( image, &width, &height );
	Uint32 *pixel_src, *pixel_dst, tmp;
	int i=0; int j=0;
	for( i=0; i< width; i++ ){
		for( j=0; j<height/2; j++ ){
			pixel_src = ((Uint32*) image->surface->pixels) +
				j*image->surface->pitch/4 + i;
			pixel_dst = ((Uint32*) image->surface->pixels) +
				(height-1-j)*image->surface->pitch/4 + i;
			tmp = *pixel_dst;
			*pixel_dst = *pixel_src;
			*pixel_src = tmp;
		}
	}
}

void MLV_resize_image_with_proportions( MLV_Image* image, int width, int height ){
	double scalar_x = -1.0;
	double scalar_y = -1.0;
	if( width<=0 && height<=0 ) return;
	if( width > 0){
		scalar_x = ((double) width) / ((double) image->surface->w);
	}
	if( height > 0){
		scalar_y = ((double) height) / ((double) image->surface->h);
	}
	if( scalar_x < 0 ){
		scalar_x = scalar_y;
	}
	if( scalar_y < 0 ){
		scalar_y = scalar_x;
	}
	MLV_scale_image( image, ( scalar_x < scalar_y )? scalar_x : scalar_y );
}

void MLV_get_image_size( const MLV_Image* image, int* width, int* height ){
	if( width ){
		*width = image->surface->w;
	}
	if( height ){
		*height = image->surface->h;
	}
}

int MLV_get_image_width( const MLV_Image* image ){
	return image->surface->w;
}

int MLV_get_image_height( const MLV_Image* image ){
	return image->surface->h;
}

void MLV_scale_xy_image( MLV_Image* image, double scalar_x, double scalar_y ){
	MLV_rotate_and_scale_xy_image( image, 0.0, scalar_x, scalar_y );
}

void MLV_rotate_and_scale_xy_image(
	MLV_Image* image, double rotation, double scalar_x, double scalar_y 
){
	SDL_Surface* dst;
	dst = rotozoomSurfaceXY( image->surface, rotation, scalar_x, scalar_y, 0);
	SDL_FreeSurface( image->surface );
	image->surface = dst; 
}

void MLV_scale_image( MLV_Image* image, double scalar ){
	MLV_rotate_and_scale_image( image, 0.0, scalar );
}

void MLV_rotate_image( MLV_Image* image, double rotation ){
	MLV_rotate_and_scale_image( image, rotation, 1.0 );
}

void MLV_rotate_and_scale_image( MLV_Image* image, double rotation, double scalar ){
	SDL_Surface* dst;
	dst = rotozoomSurface( image->surface, rotation, scalar, 0);
	SDL_FreeSurface( image->surface );
	image->surface = dst; 
}

MLV_Image* MLV_create_image( int width, int height ){
	MLV_Image* result = MLV_MALLOC( 1, MLV_Image );
	
	result->surface = create_surface( width, height );

	int i,j;
	for( i=0; i<width; i++ ){
		for( j=0; j<height; j++ ){
			MLV_set_pixel_on_image( i, j, MLV_rgba( 0,0,0,255 ), result  );
		}
	}

	return result;
}

void MLV_free_image( MLV_Image* image ){
	if( image ){
	    SDL_FreeSurface( image->surface );
		MLV_FREE( image, MLV_Image );
	}
}

MLV_Image* MLV_copy_image( const MLV_Image* image ){
	MLV_Image* result = MLV_MALLOC( 1, MLV_Image );
	result->surface = SDL_ConvertSurface( 
		image->surface, image->surface->format, image->surface->flags
	);
	return result;
}

MLV_Image* MLV_copy_partial_image( const MLV_Image* image, int x, int y, int width, int height ){
	MLV_Image* result = MLV_MALLOC( 1, MLV_Image );

	SDL_Surface* tmp = create_surface( width, height );

	result->surface = SDL_DisplayFormatAlpha( tmp );
	SDL_FreeSurface( tmp );	

	SDL_LockSurface( image->surface );
	SDL_LockSurface( result->surface );

	Uint32 *pixel_src, *pixel_dst;
	int i=0; int j=0;
	for( i=0; i< width; i++ ){
		for( j=0; j<height; j++ ){
			pixel_src = ((Uint32*) image->surface->pixels) +
				(y+j)*image->surface->pitch/4 + x+i;
			pixel_dst = ((Uint32*) result->surface->pixels) + 
				j*result->surface->pitch/4 + i;
			*pixel_dst = * pixel_src;
		}
	}
	
	SDL_UnlockSurface( result->surface );
	SDL_UnlockSurface( image->surface );

	return result;
}


void MLV_draw_image( const MLV_Image* image, int x, int y ){
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.h = image->surface->h;
	rectangle.w = image->surface->w;
	SDL_BlitSurface( image->surface, NULL, MLV_data->screen, &rectangle);
}

void MLV_draw_partial_image(
	const MLV_Image* image, int x_source, int y_source, 
	int width_source, int height_source, 
	int x, int y
){
	SDL_Rect rectangle_source;
	rectangle_source.x = x_source;
	rectangle_source.y = y_source;
	rectangle_source.h = height_source;
	rectangle_source.w = width_source;

	SDL_Rect rectangle_dest;
	rectangle_dest.x = x;
	rectangle_dest.y = y;
	rectangle_dest.h = height_source;
	rectangle_dest.w = width_source;

	SDL_BlitSurface( image->surface, &rectangle_source, MLV_data->screen, &rectangle_dest);
}


void MLV_draw_scaled_rotated_image(  MLV_Image* image, int centre_x, int centre_y, double rotation, double scalar ){
	SDL_Surface* dst;
	dst = rotozoomSurface( image->surface, rotation, scalar, 0);
	SDL_Rect rectangle_dest;
	rectangle_dest.x = centre_x;
	rectangle_dest.y = centre_y;
	rectangle_dest.h = dst->h;
	rectangle_dest.w = dst->w;
	SDL_BlitSurface( dst, NULL, MLV_data->screen, &rectangle_dest);
	SDL_FreeSurface( dst );
}

void MLV_draw_rotated_image(  MLV_Image* image, int centre_x, int centre_y, double roation ){
	MLV_draw_scaled_rotated_image( image, centre_x, centre_y, roation, 1.0 );
}

void MLV_draw_scaled_image(  MLV_Image* image, int centre_x, int centre_y, double scalar ){
	MLV_draw_scaled_rotated_image( image, centre_x, centre_y, 0.0, scalar );
}

void MLV_set_alpha_on_image( MLV_Alpha alpha, MLV_Image *image ){
	SDL_Surface* surface = image->surface;
	SDL_LockSurface(surface);

	SDL_PixelFormat *fmt;
	Uint32 *pixel;
	Uint32 alpha32;

	fmt = surface->format;
	int x,y;
	int width, height;
	MLV_get_image_size( image, &width, &height );
	for( x=0; x<width; x++){
		for( y=0; y<height; y++ ){
			pixel = ((Uint32*) surface->pixels)+ y*surface->pitch/4 + x;

			/* set the Alpha component */
			alpha32 = alpha;
			alpha32 = alpha32 >> fmt->Aloss;
			alpha32 = alpha32 << fmt->Ashift;

			*pixel = (
				*pixel & ( fmt->Rmask | fmt->Gmask | fmt->Bmask ) 
			) | alpha32;
		}
	}

	SDL_UnlockSurface(surface);
}

void MLV_set_pixel_on_image(
	int x, int y,
	MLV_Color color, 
	MLV_Image *image
){
	SDL_Surface* surface = image->surface;
	SDL_LockSurface(surface);

	SDL_PixelFormat *fmt;
	Uint32 *pixel;

	fmt = surface->format;
	pixel = ((Uint32*) surface->pixels)+ y*surface->pitch/4 + x;

	Uint8 red, blue, green, alpha;
	MLV_convert_color_to_rgba( color, &red, &green, &blue, &alpha );

	Uint32 red32 = red, blue32 = blue, green32 = green, alpha32 = alpha;

	/* set the Red component */
	red32 = red32 >> fmt->Rloss;
	red32 = red32 << fmt->Rshift;

	/* set the Green component */
	green32 = green32 >> fmt->Gloss;
	green32 = green32 << fmt->Gshift;

	/* set the Blue component */
	blue32 = blue32 >> fmt->Bloss;
	blue32 = blue32 << fmt->Bshift;

	/* set the Alpha component */
	alpha32 = alpha32 >> fmt->Aloss;
	alpha32 = alpha32 << fmt->Ashift;

	*pixel = red32 | green32 | blue32 | alpha32;

	SDL_UnlockSurface(surface);
}


SDL_Surface* MLV_get_image_data( MLV_Image* image ){
	return image->surface;
}


void get_pixel_on_image_unsafe( 
	SDL_Surface* surface,
	int x, int y,
	int* red, int* green, int* blue, int* alpha
){
	/* Extracting color components from a 32-bit color value */
	SDL_PixelFormat *fmt;
	Uint32 temp, pixel;

	fmt = surface->format;
	pixel = *(((Uint32*) surface->pixels)+ y*surface->pitch/4 + x  );

	/* Get Red component */
	if( red ){
		temp = pixel & fmt->Rmask;  /* Isolate red component */
		temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
		*red = temp;
	}

	/* Get Green component */
	if( green ){
		temp = pixel & fmt->Gmask;  /* Isolate green component */
		temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
		*green = temp;
	}

	/* Get Blue component */
	if( blue ){
		temp = pixel & fmt->Bmask;  /* Isolate blue component */
		temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
		*blue = temp;
	}

	/* Get Alpha component */
	if( alpha ){
		temp = pixel & fmt->Amask;  /* Isolate alpha component */
		temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
		temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
		*alpha = temp;
	}
}

void get_pixel_on_image( 
	SDL_Surface* surface,
	int x, int y,
	int* red, int* green, int* blue, int* alpha
){
	SDL_LockSurface(surface);

	get_pixel_on_image_unsafe( 
		surface,
		x, y,
		red, green, blue, alpha
	);
	
	SDL_UnlockSurface(surface);
}

void MLV_get_pixel(
	int x, int y, int* red, int* green, int* blue, int* alpha
){
	get_pixel_on_image( MLV_data->screen, x, y, red, green, blue, alpha	);
}

void MLV_get_pixel_on_image(
	const MLV_Image* image, int x, int y,
	int* red, int* green, int* blue, int* alpha
){
	get_pixel_on_image( image->surface, x, y, red, green, blue, alpha );
}

void MLV_draw_image_on_image(
	const MLV_Image* source_image,
	MLV_Image* destination_image,
	int destination_x, int destination_y
){
	SDL_Rect rectangle;
	rectangle.x = destination_x;
	rectangle.y = destination_y;
	rectangle.h = source_image->surface->h;
	rectangle.w = source_image->surface->w;
	SDL_BlitSurface( source_image->surface, NULL, destination_image->surface , &rectangle);
}

void MLV_draw_partial_image_on_image(
	const MLV_Image* source_image,
	int source_x, int source_y,
	int width, int height,
	MLV_Image* destination_image,
	int destination_x, int destination_y
){
	SDL_Rect rectangle_source,rectangle_destination;

	rectangle_destination.x = destination_x;
	rectangle_destination.y = destination_y;
	rectangle_destination.w = destination_image->surface->w;
	rectangle_destination.h = destination_image->surface->h;

	rectangle_source.x = source_x;
	rectangle_source.y = source_y;
	rectangle_source.w = width;
	rectangle_source.h = height;

	SDL_BlitSurface( 
		source_image->surface, &rectangle_source, 
		destination_image->surface , &rectangle_destination
	);
}

///////////////////////////////////////////////////////////////////////////////
// Save screen                                                               //
///////////////////////////////////////////////////////////////////////////////

void MLV_save_screen(){
    SDL_BlitSurface( MLV_data->screen, NULL, MLV_data->save_screen, &(MLV_data->rectangle));
}

void MLV_load_screen(){
    SDL_BlitSurface( MLV_data->save_screen, NULL, MLV_data->screen, &(MLV_data->rectangle));
}

