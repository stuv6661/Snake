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

#include "MLV_shape.h"

#include "platform.h"
#include "image.h"

#ifndef MEMORY_DEBUG
#if defined( OS_WINDOWS )
#	include <SDL/SDL_gfxPrimitives.h>
#elif defined( OS_APPLE )
#	include <SDL/SDL_gfxPrimitives.h>
#else
#	include <SDL/SDL_gfxPrimitives.h>
#endif
#else
#include "memory_debug.h"
#endif

#include "data_structure.h"
#include "warning_error.h"

#include "memory_management.h"

#include <stdarg.h>

#include "data_structure.h"

extern DataMLV *MLV_data;


///////////////////////////////////////////////////////////////////////////////
// Drawing operation on images                                               //
///////////////////////////////////////////////////////////////////////////////


void MLV_draw_circle_on_image(int x, int y, int radius, MLV_Color color, MLV_Image* image){
	circleColor( image->surface,	x, y, radius, color );
}

void MLV_draw_filled_circle_on_image(int x, int y, int radius, MLV_Color color, MLV_Image* image){
	filledCircleColor( image->surface, x, y, radius,  color);
}

void MLV_draw_ellipse_on_image(int x, int y, int radius_x, int radius_y, MLV_Color color, MLV_Image* image){
	ellipseColor(image->surface,x,y,radius_x,radius_y,color);      
}

void MLV_draw_filled_ellipse_on_image(int x, int y, int radius_x, int radius_y, MLV_Color color, MLV_Image* image){
	filledEllipseColor(image->surface,x,y,radius_x,radius_y,color);      
}

void MLV_draw_polygon_on_image( const int* vx, const int* vy, int nb_points, MLV_Color color, MLV_Image* image){
	Sint16* tmp_vx = MLV_MALLOC( nb_points, Sint16 );
	Sint16* tmp_vy = MLV_MALLOC( nb_points, Sint16 );
	int i;
	for( i=0; i< nb_points; i++){
		tmp_vx[i] = vx[i];
		tmp_vy[i] = vy[i];
	}
	polygonColor( image->surface, tmp_vx, tmp_vy, nb_points, color);
	MLV_FREE( tmp_vx, Sint16 );
	MLV_FREE( tmp_vy, Sint16 );
}

void MLV_draw_filled_polygon_on_image( const int* vx, const int* vy, int nb_points, MLV_Color color, MLV_Image* image){
	Sint16* tmp_vx = MLV_MALLOC( nb_points, Sint16 );
	Sint16* tmp_vy = MLV_MALLOC( nb_points, Sint16 );
	int i;
	for( i=0; i< nb_points; i++){
		tmp_vx[i] = vx[i];
		tmp_vy[i] = vy[i];
	}
	filledPolygonColor( image->surface, tmp_vx, tmp_vy, nb_points, color);
	MLV_FREE( tmp_vx, Sint16 );
	MLV_FREE( tmp_vy, Sint16 );
}


void MLV_draw_bezier_curve_on_image( const int* vx, const int* vy, int nb_points, MLV_Color color, MLV_Image* image){
	Sint16* tmp_vx = MLV_MALLOC( nb_points, Sint16 );
	Sint16* tmp_vy = MLV_MALLOC( nb_points, Sint16 );
	int i;
	for( i=0; i< nb_points; i++){
		tmp_vx[i] = vx[i];
		tmp_vy[i] = vy[i];
	}
	bezierColor( image->surface, tmp_vx, tmp_vy, nb_points, 6 , color);
	MLV_FREE( tmp_vx, Sint16 );
	MLV_FREE( tmp_vy, Sint16 );
}


void MLV_draw_rectangle_on_image(int x, int y, int width, int height, MLV_Color color, MLV_Image* image){
	rectangleColor(image->surface, x, y, x+width-1, y+height-1, color);
}

void MLV_draw_filled_rectangle_on_image(int x, int y, int width, int height, MLV_Color color, MLV_Image* image){
	boxColor(image->surface, x, y, x+width-1, y+height-1, color);
}

void MLV_draw_line_on_image(int x1, int y1, int x2, int y2, MLV_Color color, MLV_Image* image){
	lineColor( image->surface, x1, y1, x2, y2, color);
}

void draw_pixel_on_sdl_surface( SDL_Surface* surface, int x, int y, MLV_Color color ){
#if 0  // Je ne me souvient plus pourquoi pexelColor ne fonctionnait pas. Je crois que c'est la composante alpha qui pose problème.
	pixelColor(MLV_data->screen, x, y, color);
#else
	SDL_LockSurface(surface);

	SDL_PixelFormat *fmt;
	Uint32 *pixel;

	fmt = surface->format;
	pixel = ((Uint32*) surface->pixels)+ y*surface->pitch/4 + x;

	Uint8 red, blue, green, alpha;
	MLV_convert_color_to_rgba( color, &red, &green, &blue, &alpha );

	int red_image, green_image, blue_image, alpha_image;

	get_pixel_on_image_unsafe( 
		surface, x, y,
		&red_image, &green_image, &blue_image, &alpha_image 
	);

	int inv_alpha = 255 - alpha;
	Uint32 red32 = ( alpha * red + inv_alpha * red_image )/255;
	Uint32 blue32 = ( alpha * blue + inv_alpha * blue_image )/255;
	Uint32 green32 = ( alpha * green + inv_alpha * green_image )/255;
	Uint32 alpha32 = alpha_image;

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
#endif
}

void draw_pixel( MLV_Image* image, int x, int y, MLV_Color color ){
	SDL_Surface* surface = image->surface;
	draw_pixel_on_sdl_surface( surface, x, y, color );
}

void MLV_draw_pixel_on_image(int x, int y, MLV_Color color, MLV_Image* image){
	draw_pixel( image, x, y, color);
}

void MLV_draw_point_on_image(int x, int y, MLV_Color color, MLV_Image* image){
	MLV_draw_pixel_on_image( x, y, color, image);
}



///////////////////////////////////////////////////////////////////////////////
// Drawing operation on iscreen                                              //
///////////////////////////////////////////////////////////////////////////////

void MLV_draw_circle(int x, int y, int radius, MLV_Color color){
	circleColor( MLV_data->screen,	x, y, radius, color );
}

void MLV_draw_filled_circle(int x, int y, int radius, MLV_Color color){
	filledCircleColor( MLV_data->screen, x, y, radius,  color);
}

void MLV_draw_ellipse(int x, int y, int radius_x, int radius_y, MLV_Color color){
	ellipseColor(MLV_data->screen,x,y,radius_x,radius_y,color);      
}

void MLV_draw_filled_ellipse(int x, int y, int radius_x, int radius_y, MLV_Color color){
	filledEllipseColor(MLV_data->screen,x,y,radius_x,radius_y,color);      
}

void MLV_draw_polygon( const int* vx, const int* vy, int nb_points, MLV_Color color){
	Sint16* tmp_vx = MLV_MALLOC( nb_points, Sint16 );
	Sint16* tmp_vy = MLV_MALLOC( nb_points, Sint16 );
	int i;
	for( i=0; i< nb_points; i++){
		tmp_vx[i] = vx[i];
		tmp_vy[i] = vy[i];
	}
	polygonColor( MLV_data->screen, tmp_vx, tmp_vy, nb_points, color);
	MLV_FREE( tmp_vx, Sint16 );
	MLV_FREE( tmp_vy, Sint16 );
}

void MLV_draw_filled_polygon( const int* vx, const int* vy, int nb_points, MLV_Color color){
	Sint16* tmp_vx = MLV_MALLOC( nb_points, Sint16 );
	Sint16* tmp_vy = MLV_MALLOC( nb_points, Sint16 );
	int i;
	for( i=0; i< nb_points; i++){
		tmp_vx[i] = vx[i];
		tmp_vy[i] = vy[i];
	}
	filledPolygonColor( MLV_data->screen, tmp_vx, tmp_vy, nb_points, color);
	MLV_FREE( tmp_vx, Sint16 );
	MLV_FREE( tmp_vy, Sint16 );
}

void MLV_draw_bezier_curve( const int* vx, const int* vy, int nb_points, MLV_Color color){
	Sint16* tmp_vx = MLV_MALLOC( nb_points, Sint16 );
	Sint16* tmp_vy = MLV_MALLOC( nb_points, Sint16 );
	int i;
	for( i=0; i< nb_points; i++){
		tmp_vx[i] = vx[i];
		tmp_vy[i] = vy[i];
	}
	bezierColor( MLV_data->screen, tmp_vx, tmp_vy, nb_points, 6 , color);
	MLV_FREE( tmp_vx, Sint16 );
	MLV_FREE( tmp_vy, Sint16 );
}

void MLV_draw_rectangle(int x, int y, int width, int height, MLV_Color color){
	rectangleColor(MLV_data->screen, x, y, x+width-1, y+height-1, color);
}

void MLV_draw_filled_rectangle(int x, int y, int width, int height, MLV_Color color){
	boxColor(MLV_data->screen, x, y, x+width-1, y+height-1, color);
}

void MLV_draw_line(int x1, int y1, int x2, int y2, MLV_Color color){
	lineColor( MLV_data->screen, x1, y1, x2, y2, color);
}

void MLV_draw_pixel(int x, int y, MLV_Color color){
	draw_pixel_on_sdl_surface( MLV_data->screen, x, y, color );
}

void MLV_draw_point(int x, int y, MLV_Color color){
	MLV_draw_pixel( x, y, color);
}

