/**
 * Le but de ce programme est de donner un outil simple permettant d'obtenir 
 * rapidement le code d'une couleur donnée.
 *
 * Dans la librairie MLV, le type d'une couleur est MLV_Color. Il s'agit en fait
 * d'en entier codé sur 4 octets, soit 32 bits. Le premier octet code la
 * la composante rouge de la couleur, le deuxième la composante verte, la
 * troisième la composante bleue et la dernière, la composante alpha 
 * (transparence).
 *
 * Pour obtenir l'entie qui code une couleur, vous pouvez utiliser la fonction
 * suivante:
 *
 * -----------------------------------------------------------------------------
 * MLV_rgba : Convertit une couleur codée sur 4 entier de 8 bits représentant 
 *            les composantes rouge, bleue et verte en un entier 32 bits.
 *
 * Cette fonction renvoit un entier codé sur 32 bits.
 *
 * MLV_Color MLV_rgba(
 *     Uint8     red,      La composante rouge de la couleur
 *     Uint8     green,    La composante verte de la couleur
 *     Uint8     blue,     La composante bleue de la couleur
 *     Uint8     alpha     La composante alpha de la couleur
 * );
 *
 * -----------------------------------------------------------------------------
 *
 * Le code source suivant ne constitue pas un tutoriel.
 * De surcroit, il n'utilise aucune nouvelle fonctionnalité de la librairie MLV.
 */

// This definition are needed by the nearbyint function
// This definition must appear before #include<stdio.h> and #include<math.h>
// see the manpages documentation of nearbyint for more information
#define _ISOC99_SOURCE

#include <math.h>
#include<stdio.h>

#include <MLV/MLV_all.h>

typedef struct _Color {
	int red;
	int green;
	int blue;
} Color;

typedef struct _Point {
	int x;
	int y;
} Point;

typedef struct _Triangle {
	Point R;
	Point G;
	Point B;
} Triangle;

typedef struct _Graphics {
	int width;
	int height;
	int width_box;
	int height_box;
	int height_bar;
	Triangle triangle;
} Graphics;

void saturate_color(
	const Color* color,
	Color* result 
){
	int max = 1;
	if( (color->red != 0.0 ) || ( color->green != 0.0 ) || ( color->blue != 0.0 ) ){
		max = color->red;
		if( max < color->blue ) max = color->blue;
		if( max < color->green ) max = color->green;
	}
	result->red = (255 * color->red)/max;
	result->green = (255 * color->green)/max;
	result->blue = (255 * color->blue)/max;
}

typedef enum {
	INSIDE,
	OUTSIDE
} Position_in_the_triangle;

Position_in_the_triangle get_color_of_triangle(
	const Point *cursor, const Triangle * triangle, Color *result
){
	double rx,ry,gx,gy,bx,by;
	double determinant;
	double a,b,c;
	Position_in_the_triangle position;

	rx = triangle->R.x - cursor->x; 
	gx = triangle->G.x - cursor->x; 
	bx = triangle->B.x - cursor->x; 
	ry = triangle->R.y - cursor->y; 
	gy = triangle->G.y - cursor->y; 
	by = triangle->B.y - cursor->y; 
	determinant = -(by - gy)*rx + (bx - gx)*ry - bx*gy + by*gx;
	a = (-bx*gy + by*gx)/determinant;
	b = (bx*ry - by*rx)/determinant;
	c = (-gx*ry + gy*rx)/determinant;
	if(
		( a < 0.0 ) || ( b < 0.0 ) || ( c < 0.0 )
	){
		a = 1/3.0;
		b = 1/3.0;
		c = 1/3.0;
		position = OUTSIDE;
	}else{
		position = INSIDE;
	}

	int nuance = 255;
	result->red = nearbyint( nuance * a );
	result->green = nearbyint( nuance * b );
	result->blue = nearbyint( nuance * c );
	return position;
}

void get_color_of_bar(
	const Point* cursor, const Graphics* graphics,
	const  Color* bar_color, Color* result
){

	Color satured_color;
	saturate_color( bar_color, &satured_color );

	double nuance = (cursor->x)/ (double) graphics->width;
	result->red = nearbyint( nuance * satured_color.red );
	result->green = nearbyint( nuance * satured_color.green );
	result->blue = nearbyint( nuance * satured_color.blue );
}

typedef enum {
	TRIANGLE,
	BAR
} Click_position;

Click_position get_color(
	const Point* cursor,
	const Graphics* graphics,
	const Color * bar_color,
	Color * result
){
	if( cursor->y >= graphics->height- graphics->height_bar ){
		get_color_of_bar(	cursor, graphics, bar_color, result	);
		return BAR;
	}else{
		get_color_of_triangle( cursor, &(graphics->triangle), result );
		return TRIANGLE;
	}
}

void draw_text(
	const Color *color, const Graphics * graphics, int y_translation
){
	int text_width,text_height;
	MLV_get_size_of_text(
		"R:%d, G:%d, B:%d, A:%d ",
		&text_width, &text_height,
		color->red, color->green, color->blue, MLV_ALPHA_OPAQUE
	);
	
	MLV_draw_text(
		graphics->width - graphics->width_box - text_width,
		(graphics->height_box/2) - (text_height/2) + y_translation ,
		"R:%d, G:%d, B:%d, A:%d ",
		MLV_COLOR_RED,
		color->red, color->green, color->blue, MLV_ALPHA_OPAQUE
	);
}


void draw_foreground(
	const Point *cursor, const Graphics * graphics, const Color* bar_color
){
	MLV_load_screen();

	Color cursor_color;

	get_color( cursor, graphics, bar_color, &cursor_color );

	MLV_draw_filled_rectangle( 
		graphics->width-graphics->width_box,0,
		graphics->width_box,graphics->height_box,
		MLV_rgba(
			cursor_color.red, cursor_color.green, cursor_color.blue,
			MLV_ALPHA_OPAQUE 
		)
	);

	draw_text( &cursor_color, graphics, 0 );

	MLV_actualise_window();
}

void draw_background(
	const Graphics * graphics,
	const Color* bar_color,
	const Color* selection_color
){
	int width = graphics->width;
	int height = graphics->height;
	int height_bar = graphics->height_bar;
	Point point;
	Color color;
	MLV_clear_window( MLV_COLOR_BLACK );
	for( point.x = 0; point.x< width; point.x++){
		for( point.y=0; point.y<height;point.y++ ){
			if(
				get_color_of_triangle(
					&point,	&(graphics->triangle), &color
				) == INSIDE
			){
				MLV_draw_point( 
					point.x, point.y,
					MLV_rgba(
						color.red, color.green, color.blue,
						MLV_ALPHA_OPAQUE
					)
				);
			}
		}
	}
	int i;
	
	Color bar_color_satured;
	saturate_color( bar_color, &bar_color_satured );
	
	for( i=0; i<width; i++ ){
		MLV_Color color = MLV_rgba(
			(bar_color_satured.red*i)/width , 
			(bar_color_satured.green*i)/width, 
			(bar_color_satured.blue*i)/width,
			MLV_ALPHA_OPAQUE 
		); 
		MLV_draw_line( i, height-height_bar, i, height, color );
	}
	MLV_draw_filled_rectangle(
		graphics->width-graphics->width_box,
		graphics->height_box, graphics->width_box,graphics->height_box,
		MLV_rgba(
			selection_color->red, selection_color->green, selection_color->blue,
			MLV_ALPHA_OPAQUE
		)
	);

	draw_text( selection_color, graphics, graphics->height_box );

	MLV_save_screen();
}

void set_triangle( Graphics * graphics, int posx, int posy, int size ){
	int height = size*sqrt(3)/2.0;
	graphics->triangle.R.x = posx;
	graphics->triangle.R.y = posy + height;
	graphics->triangle.G.x = posx + size;
	graphics->triangle.G.y = posy + height;
	graphics->triangle.B.x = posx + size/2;
	graphics->triangle.B.y = posy;
}

int main( int argc, char *argv[] ){
	Graphics graphics;
		graphics.width=640; graphics.height=480;
		graphics.width_box=120; graphics.height_box=80;
		graphics.height_bar = 40;
		set_triangle( &graphics, 50, 100, 300 );
	Point cursor; cursor.x = 0; cursor.y = 0;
	MLV_Button_state state;
	MLV_Keyboard_button key;
	Color selection_color; 
	get_color_of_triangle( &cursor, &(graphics.triangle), &selection_color );
	Color bar_color = selection_color;

	MLV_Event event = MLV_NONE;

	MLV_create_window( 
		"medium - 6 - colors", "colors", graphics.width, graphics.height
	);

	draw_background( &graphics, &bar_color, &selection_color );
	draw_foreground( &cursor, &graphics, &bar_color );
	int continue_to_run = 0;
	while( ! continue_to_run ){
		while(
			(
				event = MLV_get_event( 
					&key, NULL, NULL,
					NULL, NULL,
					&(cursor.x), &(cursor.y), NULL,
					&state
				) 
			) != MLV_NONE
		){
			switch( event ){
				case MLV_MOUSE_MOTION :
					break;
				case MLV_MOUSE_BUTTON :
					if( state == MLV_PRESSED ){
						if(
							get_color( 
								&cursor, &graphics, &bar_color,	&selection_color 
							) == TRIANGLE
						){
							bar_color = selection_color;
						}
						printf(
							"MLV_rgba( %d , %d , %d, MLV_ALPHA_OPAQUE )\n",
							selection_color.red, selection_color.green, 
							selection_color.blue
						);

						draw_background( &graphics, &bar_color, &selection_color );
						draw_foreground( &cursor, &graphics, &bar_color );
					};
					break;
				case MLV_KEY :
					if( key == MLV_KEYBOARD_ESCAPE ){
						continue_to_run = 1;
					}
					break;
				default:;
			}
		}
		draw_foreground( &cursor, &graphics, &bar_color );
		MLV_delay_according_to_frame_rate();
	}
	MLV_free_window();

	return 0;
}

/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012,2013 Adrien Boussicault, Marc Zipstein
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
