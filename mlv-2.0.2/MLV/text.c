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

#include "MLV_text.h"
#include "MLV_text_va.h"

#include "platform.h"

#ifndef MEMORY_DEBUG
#if defined( OS_WINDOWS )
#	include <SDL/SDL.h>
#	include <SDL/SDL_gfxPrimitives.h>
#	include <SDL/SDL_ttf.h>
#elif defined( OS_APPLE )
#	include <SDL/SDL.h>
#	include <SDL/SDL_gfxPrimitives.h>
#	include <SDL_ttf/SDL_ttf.h>
#else
#	include <SDL/SDL.h>
#	include <SDL/SDL_gfxPrimitives.h>
#	include <SDL/SDL_ttf.h>
#endif
#else
#include "memory_debug.h"
#endif

#include <string.h>

#include "text.h"
#include "MLV_shape.h"

#include "data_structure.h"
#include "image.h"
#include "memory_management.h"

#include "warning_error.h"

#define SIZE_FONT 8

extern DataMLV* MLV_data;

void MLV_get_size_of_text_va(
	const char *text, int *width, int *height, va_list pile
){
	MLV_get_size_of_text_with_font_va(
		text, width, height, MLV_data->defaultFont, pile
	);
}

void MLV_get_size_of_text( const char *text, int *width, int *height, ... ){
	va_list pile;
	va_start( pile, height );
	MLV_get_size_of_text_va( text, width, height, pile );
	va_end( pile );
}

void MLV_get_size_of_text_with_font_va(
	const char *text, int *width, int *height, const MLV_Font* font, 
	va_list pile
){
	char* complete_text;
	if( vasprintf( &complete_text, text, pile )==-1 ){
		ERROR("Unexpected Error.");
	}
	if( strlen( complete_text ) ){
		TTF_SizeUTF8(font->font, complete_text, width, height);
	}else{
		TTF_SizeUTF8(font->font, " ", width, height);
	}
	free( complete_text );
}

void MLV_get_size_of_text_with_font(
	const char *text, int *width, int *height, const MLV_Font* font, ...
){
	va_list pile;
	va_start( pile, font );
	MLV_get_size_of_text_with_font_va( text, width, height, font, pile );
	va_end( pile );
}

void init_font(){
	if ( TTF_Init() < 0 ) {
		fprintf(
			stderr, "Couldn't initialize TTF: %s - file : %s, ligne : %i\n",
			SDL_GetError(), __FILE__, __LINE__
		);
		exit(1);
	}
}

void quit_font(){
	TTF_Quit();
}

MLV_Font* MLV_load_font( const char* file_font, int size ){
	if( !MLV_data ){
		ERROR("To use MLV_load_font, please initialise first the MLV_Library by calling MLV_create_window before MLV_load_font.")
	}
	MLV_Font* font = MLV_MALLOC( 1, MLV_Font );
	font->size = size;
	font->font = TTF_OpenFont( file_font, size );
	if(!font->font) {
		printf(
			"TTF_OpenFont: %s - file : %s, ligne : %i\n",
			TTF_GetError(), __FILE__, __LINE__
		);
		exit(1);
	}
	TTF_SetFontStyle( font->font , TTF_STYLE_NORMAL );
	return font;
}

void MLV_free_font( MLV_Font* font ){
	TTF_CloseFont( font->font );
	MLV_FREE( font, MLV_Font );
}

void convertionColor( MLV_Color src, SDL_Color* dst ){
	src = src >> 8;
	dst->b = (Uint8) src;
	src = src >> 8;
	dst->g = (Uint8) src;
	src = src >> 8;
	dst->r = (Uint8) src;
}

void getDefaultFont( MLV_Font** const font ){
	if( *font ) return;
	*font = MLV_data->defaultFont;
}

void drawString(
	SDL_Surface* textBox, int x, int y, 
	const char* message, MLV_Color color, TTF_Font* font 
){
	SDL_Color sdl_color;
	convertionColor( color, &sdl_color);
	SDL_Surface* text;
	if( strlen( message ) ){
		text = TTF_RenderUTF8_Solid(
			font,
			message,
			sdl_color
		);
	}else{
		text = TTF_RenderUTF8_Solid(
			font,
			" ",
			sdl_color
		);
	}

	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = text->w;
	rectangle.h = text->h;
	SDL_BlitSurface( text, NULL, textBox, &rectangle);
	SDL_FreeSurface( text );
}


void MLV_draw_text_on_image_va(
	int x, int y, const char *text, MLV_Color color, MLV_Image* image,
	va_list pile
){
	MLV_draw_text_with_font_on_image_va(
		x, y, text, MLV_data->defaultFont, color, image, pile
	);
}

void MLV_draw_text_on_image(
	int x, int y, const char *text, MLV_Color color, MLV_Image* image, ...
){
	va_list pile;
	va_start( pile, image );
	MLV_draw_text_on_image_va( x, y, text, color, image, pile );
	va_end( pile );
}

void MLV_draw_text_with_font_on_image_va(
	int x, int y, const char *text, const MLV_Font* font, MLV_Color color, 
	MLV_Image* image, va_list pile
){
	char* complete_text;
	if( vasprintf( &complete_text, text, pile )==-1 ){
		ERROR("Unexpected Error.");
	}
	drawString( image->surface, x, y, complete_text, color, font->font );
	free( complete_text );
}


void MLV_draw_text_with_font_on_image(
	int x, int y, const char *text, const MLV_Font* font, MLV_Color color, 
	MLV_Image* image, ...
){
	va_list pile;
	va_start( pile, image );
	MLV_draw_text_with_font_on_image_va( x, y, text, font, color, image, pile );
	va_end( pile );
}

void MLV_draw_text_va(
	int x, int y, const char *text, MLV_Color color, va_list pile
){
	MLV_draw_text_with_font_va(
		x, y, text, MLV_data->defaultFont, color, pile
	);
}


void MLV_draw_text(int x, int y, const char *text, MLV_Color color, ... ){
	va_list pile;
	va_start( pile, color );
	MLV_draw_text_va( x, y, text, color, pile );
	va_end( pile );
}

void MLV_draw_text_with_font_va(
	int x, int y, const char *text, const MLV_Font* font, MLV_Color color, 
	va_list pile
){
	char* complete_text;
	if( vasprintf( &complete_text, text, pile )==-1 ){
		ERROR("Unexpected Error.");
	}
	drawString( MLV_data->screen, x, y, complete_text, color, font->font );
	free( complete_text );
}

void MLV_draw_text_with_font(
	int x, int y, const char *text, const MLV_Font* font, MLV_Color color, ...
){
	va_list pile;
	va_start( pile, color );
	MLV_draw_text_with_font_va( x, y, text, font, color, pile );
	va_end( pile );
}

int internal_draw_adapted_text_box_size_with_font(
	char* copy,
	const MLV_Font* font, 
	int sizeInterligne,
	int *width, int *height,
	int * width_text
){
	int nb_line=1;
	*width = 0;
	*height = 0;
	if( copy[0] != '\0' ){
		int width_line,height_line;
		char * new = copy;
		char* old = new;
		while( ( new = strchr( new ,'\n') ) ){
			(*new) = '\0';
			++nb_line;
			MLV_get_size_of_text_with_font(
				old, &width_line, &height_line, font
			);
			if( width_line > *width ){
				*width = width_line;
			}
			*height += height_line + sizeInterligne;
			new ++;
			old=new;
		}
		MLV_get_size_of_text_with_font( old, &width_line, &height_line, font );
		if( width_line > *width ){
			*width = width_line;
		}
		*height += height_line + sizeInterligne;
	}
	if( width_text ){
		*width_text = *width;
	}
	//Ajout des bords 
	*width += 2*sizeInterligne;
	*height += sizeInterligne;
	return nb_line;
}

void internal_draw_text_box_with_font( 
	char* copy , 
	const MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	int corner_position_x,
	int corner_position_y,
	int width_text,
	int nb_line,
	SDL_Surface* textBox
){
	char * new = copy;
	char* old = new;
	int position = corner_position_y + sizeInterligne;
	int horizontal_offset = corner_position_x + sizeInterligne;
	int i;
	for( i=0; i<nb_line; i++){
		new = strchr( new ,'\0');
		int width_line,height_line;
		MLV_get_size_of_text_with_font( old, &width_line, &height_line, font );
		switch( text_justification ){
			case MLV_TEXT_CENTER:
				drawString(
					textBox, 
					horizontal_offset + (width_text-width_line)/2, position , 
					old, textColor, font->font
				);
				break;
			case MLV_TEXT_LEFT:
				drawString(
					textBox, 
					horizontal_offset , position , 
					old, textColor, font->font
				);
				break;
			case MLV_TEXT_RIGHT:
				drawString(
					textBox,
					horizontal_offset+width_text-width_line+sizeInterligne,
					position,
					old, textColor, font->font
				);
				break;
			default:
				ERROR("Valeur impossible pour horizontal_position.");
		}
		position += height_line + sizeInterligne;
		new ++;
		old=new;
	}
}

void internal_draw_adapted_text_box_with_font_on_image(
	int x, int y,
	const char* message,
	const MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	SDL_Surface *screen
){
	char* copy = (char*) MLV_MALLOC( (strlen(message)+1), char );
	snprintf(copy, strlen(message)+1, "%s", message);
	int width,height,width_text;

	int nb_line = internal_draw_adapted_text_box_size_with_font(	
		copy, font, sizeInterligne, &width, &height, &width_text
	);
	
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = width;
	rectangle.h = height;

	SDL_Surface* textBox= create_surface(
		width, height
	);
	SDL_SetAlpha(textBox, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
	SDL_SetColorKey(textBox, SDL_SRCCOLORKEY, backgroundColor);

	boxColor( textBox , 0, 0, width-1, height-1, backgroundColor);

	internal_draw_text_box_with_font( 
		copy , 
		font, 
		sizeInterligne,
		borderColor, textColor, backgroundColor,
		text_justification,
		0,
		0,
		width_text,
		nb_line,
		textBox
	);

	rectangleColor( textBox , 0, 0, width-1, height-1, borderColor);

	SDL_BlitSurface( textBox, NULL, screen, &rectangle);
	SDL_FreeSurface( textBox );
	MLV_FREE(copy, char);
}

void MLV_draw_adapted_text_box_with_font_va(
	int x, int y,
	const char* message,
	const MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	va_list pile
){
	char* complete_message;
	if( vasprintf( &complete_message, message, pile )==-1 ){
		ERROR("Unexpected Error.");
	}
	internal_draw_adapted_text_box_with_font_on_image(
		x, y,
		complete_message,
		font, 
		sizeInterligne,
		borderColor, textColor, backgroundColor,
		text_justification,
		MLV_data->screen	
	);
	free( complete_message );
}

void MLV_draw_adapted_text_box_va(
	int x, int y,
	const char* message,
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification, va_list pile
){
	MLV_draw_adapted_text_box_with_font_va(
		x, y, message, MLV_data->defaultFont, sizeInterligne,
		borderColor, textColor, backgroundColor, 
		text_justification, pile
	);
}

void MLV_draw_adapted_text_box(
	int x, int y,
	const char* message,
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification, ...
){
	va_list pile;
	va_start( pile, text_justification );
	MLV_draw_adapted_text_box_va(
		x, y, message, sizeInterligne, borderColor, textColor, backgroundColor,
		text_justification, pile
	);
	va_end( pile );
}

void MLV_draw_adapted_text_box_with_font_on_image_va(
	int x, int y,
	const char* message,
	const MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Image* image, va_list pile
){
	char* complete_message;
	if( vasprintf( &complete_message, message, pile )==-1 ){
		ERROR("Unexpected Error.");
	}
	internal_draw_adapted_text_box_with_font_on_image(
		x, y,
		complete_message,
		font, 
		sizeInterligne,
		borderColor, textColor, backgroundColor,
		text_justification,
		image->surface
	);
	free( complete_message );
}

void MLV_draw_adapted_text_box_on_image_va(
	int x, int y,
	const char* message,
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Image* image, va_list pile
){
	MLV_draw_adapted_text_box_with_font_on_image_va(
		x, y, message, MLV_data->defaultFont, sizeInterligne,
		borderColor, textColor, backgroundColor, 
		text_justification,
		image, pile
	);
}

void MLV_draw_adapted_text_box_on_image(
	int x, int y,
	const char* message,
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Image* image, ...
){
	va_list pile;
	va_start( pile, image );
	MLV_draw_adapted_text_box_on_image_va(
		x, y, message, sizeInterligne,
		borderColor, textColor, backgroundColor, 
		text_justification,
		image, pile
	);
	va_end( pile );
}

int MLV_get_size_of_adapted_text_box_with_font_va(
	const char* message,
	const MLV_Font* font, 
	int sizeInterligne,
	int *result_width, int *result_height,
	va_list pile
){
	char* complete_message;
	if( vasprintf( &complete_message, message, pile )==-1 ){
		ERROR("Unexpected Error.");
	}
	char* copy = (char*) MLV_MALLOC( (strlen(complete_message)+1), char );
	snprintf(copy, strlen(complete_message)+1, "%s", complete_message);
	int result = internal_draw_adapted_text_box_size_with_font(
		copy,
		font, 
		sizeInterligne,
		result_width, result_height,
		NULL
	);
	MLV_FREE(copy, char);
	free( complete_message );
	return result;
}

int MLV_get_size_of_adapted_text_box_va(
	const char* message,
	int sizeInterligne,
	int *result_width, int *result_height,
	va_list pile
){
	return MLV_get_size_of_adapted_text_box_with_font_va(
		message,
		MLV_data->defaultFont,
		sizeInterligne,
		result_width, result_height,
		pile
	);
}

int MLV_get_size_of_adapted_text_box(
	const char* message,
	int sizeInterligne,
	int *result_width, int *result_height,
	...
){
	int result;
	va_list pile;
	va_start( pile, result_height );
	result = MLV_get_size_of_adapted_text_box_va(
		message, sizeInterligne, result_width, result_height, pile
	);
	va_end( pile );
	return result;
}

void MLV_draw_adapted_text_box_with_font(
	int x, int y,
	const char* message,
	const MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification, ...
){
	va_list pile;
	va_start( pile, text_justification );
	MLV_draw_adapted_text_box_with_font_va(
		x, y, message, font, sizeInterligne, borderColor, textColor, 
		backgroundColor, text_justification, pile
	);
	va_end( pile );
}

void MLV_draw_adapted_text_box_with_font_on_image(
	int x, int y,
	const char* message,
	const MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Image* image, ...
){
	va_list pile;
	va_start( pile, image );
	MLV_draw_adapted_text_box_with_font_on_image_va(
		x, y, message, font, sizeInterligne, borderColor, textColor, 
		backgroundColor, text_justification, image, pile
	);
	va_end( pile );
}

int MLV_get_size_of_adapted_text_box_with_font(
	const char* message,
	const MLV_Font* font, 
	int sizeInterligne,
	int *result_width, int *result_height, ...
){
	int result;
	va_list pile;
	va_start( pile, result_height );
	result = MLV_get_size_of_adapted_text_box_with_font_va(
		message, font, sizeInterligne, result_width, result_height, pile
	);
	va_end( pile );
	return result;
}

void internal_draw_text_box_with_font_on_image( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	const MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	SDL_Surface* image
){
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = width;
	rectangle.h = height;

	SDL_Surface* textBox= create_surface(
		width, height
	);
	SDL_SetAlpha(textBox, SDL_SRCALPHA, SDL_ALPHA_OPAQUE);
	SDL_SetColorKey(textBox, SDL_SRCCOLORKEY, backgroundColor);

	boxColor( textBox , 0, 0, width-1, height-1, backgroundColor);

	char* copy = (char*) MLV_MALLOC( (strlen(message)+1), char );
	snprintf(copy, strlen(message)+1, "%s", message);

	int real_width,real_height,width_text;

	int nb_line = internal_draw_adapted_text_box_size_with_font(
		copy, font, sizeInterligne, &real_width, &real_height, &width_text
	);

	int position_corner_x;
	switch( horizontal_position ){
		case  MLV_HORIZONTAL_LEFT:
			position_corner_x = 0;
			break;
		case  MLV_HORIZONTAL_RIGHT:
			position_corner_x = width - real_width;
			break;
		case  MLV_HORIZONTAL_CENTER:
			position_corner_x = (width - real_width)/2;
			break;
		default:
			ERROR("MLV_Vertical_position ne contient pas de bonnes valeurs.");
	}
	int position_corner_y;
	switch( vertical_position ){
		case  MLV_VERTICAL_TOP:
			position_corner_y = 0;
			break;
		case  MLV_VERTICAL_BOTTOM:
			position_corner_y = height - real_height;
			break;
		case  MLV_VERTICAL_CENTER:
			position_corner_y = (height - real_height)/2;
			break;
		default:
			ERROR("MLV_Vertical_position ne contient pas de bonnes valeurs.");
	}
	internal_draw_text_box_with_font( 
		copy , 
		font, 
		sizeInterligne,
		borderColor, textColor, backgroundColor,
		text_justification,
		position_corner_x,
		position_corner_y,
		width_text,
		nb_line,
		textBox
	);

	rectangleColor( textBox , 0, 0, width-1, height-1, borderColor);
	SDL_BlitSurface( textBox, NULL, image, &rectangle);
	SDL_FreeSurface( textBox );
	MLV_FREE(copy, char);
}

void MLV_draw_text_box_with_font_va( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	const MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	va_list pile
){
	char* complete_message;
	if( vasprintf( &complete_message, message, pile )==-1 ){
		ERROR("Unexpected Error.");
	}
	internal_draw_text_box_with_font_on_image( 
		x, y, 
		width, height, 
		complete_message, 
		font, 
		sizeInterligne,
		borderColor, textColor, backgroundColor,
		text_justification,
		horizontal_position,
		vertical_position,
		MLV_data->screen	
	);
	free( complete_message );
}

void MLV_draw_text_box_va( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	va_list pile
){
	MLV_draw_text_box_with_font_va( 
		x, y, width, height, message , MLV_data->defaultFont, sizeInterligne,
		borderColor, textColor, backgroundColor, text_justification,
		horizontal_position, vertical_position, pile
	);
}

void MLV_draw_text_box( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	...
){
	va_list pile;
	va_start( pile, vertical_position );
	MLV_draw_text_box_va( 
		x, y, width, height, message , sizeInterligne, borderColor, textColor, 
		backgroundColor, text_justification, horizontal_position,
		 vertical_position, pile
	);
	va_end( pile );
}

void MLV_draw_text_box_with_font( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	const MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	...
){
	va_list pile;
	va_start( pile, vertical_position );
	MLV_draw_text_box_with_font_va( 
		x, y, width, height, message, font, sizeInterligne,
		borderColor, textColor,  backgroundColor, text_justification, 
		horizontal_position, vertical_position, pile
	);
	va_end( pile );
}

void MLV_draw_text_box_with_font_on_image_va( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	MLV_Image* image,
	va_list pile
){
	char* complete_message;
	if( vasprintf( &complete_message, message, pile )==-1 ){
		ERROR("Unexpected Error.");
	}
	internal_draw_text_box_with_font_on_image( 
		x, y, 
		width, height, 
		complete_message, 
		font, 
		sizeInterligne,
		borderColor, textColor, backgroundColor,
		text_justification,
		horizontal_position,
		vertical_position,
		image->surface
	);
	free( complete_message );
}

void MLV_draw_text_box_with_font_on_image( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	MLV_Font* font, 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	MLV_Image* image,
	...
){
	va_list pile;
	va_start( pile, image );
	MLV_draw_text_box_with_font_on_image_va( 
		x, y, width, height, message, font, sizeInterligne, borderColor, 
		textColor, backgroundColor, text_justification, horizontal_position, 
		vertical_position, image, pile
	);
	va_end( pile );
}

void MLV_draw_text_box_on_image_va( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	MLV_Image* image,
	va_list pile
){
	MLV_draw_text_box_with_font_on_image_va( 
		x, y, width, height, message, MLV_data->defaultFont, sizeInterligne, 
		borderColor, textColor, backgroundColor, text_justification, 
		horizontal_position, vertical_position, image, pile
	);
}


void MLV_draw_text_box_on_image( 
	int x, int y, 
	int width, int height, 
	const char* message , 
	int sizeInterligne,
	MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor,
	MLV_Text_justification text_justification,
	MLV_Horizontal_position horizontal_position,
	MLV_Vertical_position vertical_position,
	MLV_Image* image,
	...
){
	va_list pile;
	va_start( pile, image );
	MLV_draw_text_box_on_image_va( 
		x, y, width, height, message, sizeInterligne, borderColor, textColor, 
		backgroundColor, text_justification, horizontal_position,
		vertical_position, image, pile
	);
	va_end( pile );
}

char* MLV_convert_unicode_to_string( int unicode ){
	gunichar v = unicode;
	gchar* message;

	int size = g_unichar_to_utf8(v,NULL);
	message = (char*) MLV_MALLOC( size + 1, gchar );
	message[ size ] = '\0';
	g_unichar_to_utf8(v, message);

//	const char* encodage;
//	g_get_charset( &encodage );
//	printf("encodage : %s\n",encodage);

//	GError* error;
//
//	gchar* result = g_locale_from_utf8(
//		message,
//		-1,
//		NULL,
//		NULL,
//		&error // pas d'erreur
//	);
//
//
//	MLV_FREE( message, gchar* );
//	return result;
	return message;
}

