/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012,2012 Adrien Boussicault, Marc Zipstein
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
#include "MLV_event.h"
#include "MLV_text.h"

#include "platform.h"
#include "image.h"
#include "input_box.h"
#include "text.h"
#include "list.h"

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

#include "sdlkeyboardtochar.h"
#include "glib.h"

#include <string.h>
#include "warning_error.h"

#include "memory_management.h"

#define SIZE_FONT 8
#define SIZE_BORD 1
#define TIME_CURSOR 1000 //Periode d'oscillation du curseur (ms)

//
// Les fonction avec le suffixe _NST veux dire : No Safe Thread.
// Cela veux dire qu'anvant d'utiliser de telle fonctions, il faut 
// s'assurer la propriété entiere des objet qu'il va modifier.
//

#include "data_structure.h"

extern DataMLV* MLV_data;

struct _MLV_Input_box {
    //Géométrie de la boîte de saisie
    int sommetHautGauche[2];
    int sommetBasDroit[2];
    int width;
    int height;
    SDL_Rect rectangle;
    //Taille de la font du texte
	const MLV_Font* font;
    //Positiononnement du texte
    int bord[2];
    int widthMessage;
    int widthAnswer;
	int heightMessAns;
    //Couleurs de la boîtes de saisie
    MLV_Color borderColor;
    MLV_Color textColor;
    MLV_Color backgroundColor;
    //Rendu de la boîte de saisie
    SDL_Surface* apparence;
    SDL_Surface* answer;
    SDL_Rect answerRectangle;
    //Message d'information
    char* informativeMessage;
    //position du curseur dans la réponse courante
    int positionCursor;
    int lastTime;
    int cursorIsVisible;  //le curseur (qui clignote ) est dans son etat visible
    //La boîte de saisie est active 
    int isListenning;
    //Histroique - le premier élément de l'historique correspond à la 
	//reponse courante de la boîte de saisie
    MLV_List* history;
    MLV_List* positionHistory;
    //Gestion concurentiel de l'accès à la boîte de saisie.
    SDL_sem* semaphore;
};


/*
 *                  bord[0]   withMessage          withAnswer            bord[0]
 *                     <---><-------------><---------------------------><-->
 *                  _   ____________________________________________________
 *    bord[1]      |   |                                                   |
 *                 |_  |   _____________________________________________   |
 *                 |   |   |               |                           |   |
 *  heightMessAns  |   |   | I. Message    |    An|swer                |   |
 *                 |_  |   |_______________|___________________________|   |
 *                 |   |                                                   |
 *    bord[1]      |_  |___________________________________________________|
 *
 *
 * */
#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void recalculateTextPositions_NTS( MLV_Input_box* input_box ){
	int width_message, height_message;
	MLV_get_size_of_text_with_font(
		input_box->informativeMessage,
		&width_message, &height_message, 
		input_box->font
	);
    input_box->widthMessage = width_message; 
    input_box->widthAnswer = input_box->width - input_box->widthMessage - 2 * input_box->bord[0];
    input_box->heightMessAns = ( input_box->font->size > height_message )? 
								input_box->font->size : height_message ; 
//    input_box->heightMessAns = height_message ; 
    input_box->bord[1] = (input_box->height - ( input_box->heightMessAns ) )/2;
    if(input_box->answer){
//		DEBUG("Free answer");
        SDL_FreeSurface( input_box->answer );
    }
    if(  input_box->widthAnswer > 0 ){
//		DEBUG("Create answer");
        input_box->answer = create_surface( input_box->widthAnswer, input_box->heightMessAns );
        input_box->answerRectangle.x = input_box->bord[0] + input_box->widthMessage;
        input_box->answerRectangle.y = input_box->bord[1];
        input_box->answerRectangle.w = input_box->widthAnswer;
        input_box->answerRectangle.h = input_box->heightMessAns;
    }else{
        input_box->answer = NULL;
    }
}

void lock_input_box( MLV_Input_box* input_box ){
    if( SDL_SemWait( input_box->semaphore )  ){
       ERROR_FULL("Probleme de semaphore");
    }
}

void unlock_input_box( MLV_Input_box* input_box ){
    if( SDL_SemPost(  input_box->semaphore ) ){
        ERROR_FULL("Probleme de semaphore");
    }
}

typedef struct _Input_box_information {
    MLV_List* input_box_list;
    MLV_Input_box* input_box_activated;
    SDL_sem* semaphore;
} Input_box_information;

Input_box_information input_box_information;

void lock_input_box_information( ){
    if( SDL_SemWait( input_box_information.semaphore )  ){
		ERROR_FULL( "Probleme de semaphore" );
    }
}

void unlock_input_box_information( ){
    if( SDL_SemPost(  input_box_information.semaphore ) ){
        ERROR_FULL( "Probleme de semaphore" );
    }
}

/*
input_box->history->data
  0                   m                          l-1
---------------------------------------------------------
|   |   |   |   | X | Y |   |   |   |   |   |   |   | \0 |
---------------------------------------------------------
                    |
                 curseur
new

  0                   m                      l-1  l
---------------------------------------------------------
|   |   |   |   | X | c | Y |   |   |   |   |   |   | \0 |
---------------------------------------------------------
                        |
                      curseur
 */
#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void add_carac_input_box_NTS( MLV_Input_box* input_box, char c ){
    int l = strlen(input_box->history->data);
    int m = input_box->positionCursor ;
//	DEBUG("Add History Entry");
    char* new = MLV_MALLOC( ( l + 2 ), char );
    strncpy( new, input_box->history->data , m );
    new[input_box->positionCursor] = c;
    strncpy( new + m + 1 , input_box->history->data + m , l - m );
    new[l + 1] = '\0';
//	DEBUG("Free History Entry");
	MLV_FREE( input_box->history->data, char );
    input_box->history->data = new;
    input_box->positionCursor++;
}

/*
input_box->history->data
  0                   m                          l-1
---------------------------------------------------------
|   |   |   |   | X | Y | Z |   |   |   |   |   |   | \0 |
---------------------------------------------------------
                    |
                 curseur
resultat

  0                   m                           l-1
------------------------------------------------------
|   |   |   |   | X | Z |   |   |   |   |   |   | \0 |
------------------------------------------------------
                    |
                 curseur
 */
#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void suppress_carac_input_box_NTS( MLV_Input_box* input_box ){
    int l = strlen(input_box->history->data);
    int m = input_box->positionCursor ;
    if( l == m ) return;
    memmove( input_box->history->data + m, input_box->history->data + m + 1, l - m );
}

/*
input_box->history->data
  0                   m                          l-1
---------------------------------------------------------
|   |   |   | X | Y | Z |   |   |   |   |   |   |   | \0 |
---------------------------------------------------------
                    |
                 curseur
resulat

  0              m-1  m                           l-1
------------------------------------------------------
|   |   |   | X | Z |   |   |   |   |   |   |   | \0 |
------------------------------------------------------
                |
              curseur
 */
#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void return_deletion_carac_input_box_NTS( MLV_Input_box* input_box ){
    int l = strlen(input_box->history->data);
    int m = input_box->positionCursor ;
    if( m != 0 ){
        memmove( input_box->history->data + m-1, input_box->history->data + m , l - m + 1 );
        input_box->positionCursor--;
    }
}


#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void recalculateSommetBas_NTS( MLV_Input_box* input_box ){
    input_box->sommetBasDroit[0] = input_box->sommetHautGauche[0] + input_box->width;
    input_box->sommetBasDroit[1] = input_box->sommetHautGauche[1] + input_box->height;
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void change_position_input_box_NTS(MLV_Input_box* input_box, int sommetHautGaucheX, int sommetHautGaucheY){
    input_box->sommetHautGauche[0] = sommetHautGaucheX;
    input_box->sommetHautGauche[1] = sommetHautGaucheY;
    input_box->rectangle.x = sommetHautGaucheX;
    input_box->rectangle.y = sommetHautGaucheY;
    recalculateSommetBas_NTS( input_box );
    recalculateTextPositions_NTS( input_box );
}

void MLV_change_position_input_box(MLV_Input_box* input_box, int sommetHautGaucheX, int sommetHautGaucheY){
    lock_input_box( input_box );
    change_position_input_box_NTS( input_box, sommetHautGaucheX, sommetHautGaucheY );
    unlock_input_box( input_box );
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void change_size_input_box_NTS(MLV_Input_box* input_box, int width, int height){
    if( (width < 0) || (height < 0)){
		ERROR_FULL( "Les tailles ne sont pas correctes." );
    }
    input_box->width = width;
    input_box->height =  height;
    input_box->rectangle.w = width;
    input_box->rectangle.h = height;
    if( input_box->apparence ){
//		DEBUG("Free apparence");
        SDL_FreeSurface(input_box->apparence);
    }
//	DEBUG("Create apparence");
    input_box->apparence = create_surface( input_box->width, input_box->height );
    recalculateSommetBas_NTS( input_box );
    recalculateTextPositions_NTS( input_box );
}

void MLV_change_input_box_size(MLV_Input_box* input_box, int width, int height){
    lock_input_box( input_box );
    change_size_input_box_NTS( input_box, width, height);
    unlock_input_box( input_box );
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void change_geometry_input_box_NTS(MLV_Input_box* input_box,  int sommetHautGaucheX, int sommetHautGaucheY, int width, int height){
    change_size_input_box_NTS( input_box, width, height );
    change_position_input_box_NTS( input_box, sommetHautGaucheX, sommetHautGaucheY);
};

void MLV_change_input_box_geometry(MLV_Input_box* input_box,  int sommetHautGaucheX, int sommetHautGaucheY, int width, int height){
    lock_input_box( input_box );
    change_geometry_input_box_NTS( input_box, sommetHautGaucheX, sommetHautGaucheY, width, height);
    unlock_input_box( input_box );
};

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void change_colors_input_box_NTS( MLV_Input_box* input_box,  MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor ){
    input_box->borderColor = borderColor;
    input_box->textColor = textColor;
    input_box->backgroundColor = backgroundColor;
};

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void MLV_change_input_box_colors( MLV_Input_box* input_box,  MLV_Color borderColor, MLV_Color textColor, MLV_Color backgroundColor ){
    lock_input_box( input_box );
    change_colors_input_box_NTS( input_box, borderColor, textColor, backgroundColor );
    unlock_input_box( input_box );
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void desactivate_input_box_NTS( ){
	if( input_box_information.input_box_activated ){
		input_box_information.input_box_activated->isListenning = 0;
		input_box_information.input_box_activated = NULL;
	}
}

void MLV_desactivate_input_box( ){
    lock_input_box_information();
    desactivate_input_box_NTS( );
    unlock_input_box_information();
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void  activate_imput_box_NTS( MLV_Input_box* input_box ){
	desactivate_input_box_NTS( );
	input_box->isListenning = 1;
	input_box_information.input_box_activated = input_box;
}

void MLV_activate_input_box( MLV_Input_box* input_box ){
    lock_input_box_information();
    lock_input_box( input_box );
     activate_imput_box_NTS( input_box );
    unlock_input_box( input_box );
    unlock_input_box_information();
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
int is_in_input_box_NTS( MLV_Input_box* input_box, int x, int y ){
    int result = 0;
    if( (x >= input_box->sommetHautGauche[0]) &&
        (x <= input_box->sommetBasDroit[0]) &&
        (y >= input_box->sommetHautGauche[1]) &&
        (y <= input_box->sommetBasDroit[1]) 
    ) result = 1;
    return result;
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
MLV_Input_box* is_in_an_input_box_NTS( int x, int y ){
    MLV_Input_box* result = NULL;
    MLV_List* list = input_box_information.input_box_list;
    while( list ){
        MLV_Input_box* input_box = (MLV_Input_box*) list->data;
        if( is_in_input_box_NTS( input_box,  x, y ) ){
            result = input_box;
            break;
        }
        list = list->next;
    }
    return result;
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void construct_input_box_NTS( MLV_Input_box* input_box ){
	int width_message_before_input_box, height_message_before_input_box;

    boxColor(
		input_box->apparence, 
		0, 0, input_box->width-1, input_box->height-1, 
		input_box->backgroundColor
	);

	drawString(
		input_box->apparence, 
		input_box->bord[0] , input_box->bord[1], 
		input_box->informativeMessage, 
		input_box->textColor, input_box->font->font
	);

    if( input_box->widthAnswer > 0 ){
        boxColor(
			input_box->answer, 
			0, 0, input_box->widthAnswer-1, input_box->heightMessAns -1,
			input_box->backgroundColor
		);
        char * message = (char*) input_box->history->data ;
        int decalage = 0;
		char* message_before_input_box = MLV_MALLOC( input_box->positionCursor+1, char );
		strncpy( message_before_input_box, message, input_box->positionCursor );
		message_before_input_box[input_box->positionCursor] = '\0';
		MLV_get_size_of_text_with_font(
			message_before_input_box,
			&width_message_before_input_box, &height_message_before_input_box,
			input_box->font
		);
        if( width_message_before_input_box > (input_box->widthAnswer) ){
            decalage = input_box->widthAnswer - width_message_before_input_box -1;
        }
		MLV_FREE( message_before_input_box, char );
		drawString(
			input_box->answer, 
			decalage , 0, 
			message, 
			input_box->textColor, input_box->font->font
		);
        SDL_BlitSurface(
			input_box->answer, NULL,
			input_box->apparence, &(input_box->answerRectangle)
		);
    }

    int time = SDL_GetTicks();
    if( ( time - input_box->lastTime > TIME_CURSOR ) ){
        input_box->lastTime = time;
        input_box->cursorIsVisible = ! input_box->cursorIsVisible;
    };

    if( (! input_box->isListenning) || input_box->cursorIsVisible ){
        int abscisse;
        if( width_message_before_input_box > input_box->widthAnswer ){
            abscisse = input_box->bord[0] + 
				input_box->widthMessage + 
				input_box->widthAnswer -2;
        }else{
            abscisse = input_box->bord[0] + 
				input_box->widthMessage + 
				width_message_before_input_box;
        }
        lineColor(
			input_box->apparence, 
			abscisse , input_box->bord[1],
			abscisse, input_box->bord[1] + input_box->heightMessAns -1,
			input_box->textColor
		);
    }

    rectangleColor(
		input_box->apparence,
		0, 0,
		input_box->width-1, input_box->height-1,
		input_box->borderColor
	);
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void input_box_register_NTS(MLV_Input_box* input_box){
    input_box_information.input_box_list = MLV_prepend_list( input_box_information.input_box_list , input_box );
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void input_box_unregister_NTS(MLV_Input_box* input_box){
    if( input_box_information.input_box_activated == input_box ) desactivate_input_box_NTS();
    input_box_information.input_box_list = MLV_remove_list( input_box_information.input_box_list, input_box );
}

MLV_Input_box* create_input_box_with_font(
	int sommetHautGaucheX, int sommetHautGaucheY,
	int width, int height,
	MLV_Color borderColor, MLV_Color textColor,
	MLV_Color backgroundColor,
	const char* informativeMessage,
	const MLV_Font* font
){
//	DEBUG("Add input_box");
    MLV_Input_box* input_box = MLV_MALLOC( 1, MLV_Input_box );

//	DEBUG("Create semaphore");
    input_box->semaphore = SDL_CreateSemaphore(1);

	input_box->font = font;
    input_box->bord[0] = SIZE_BORD;
//	DEBUG("Add Informative message");
    input_box->informativeMessage = MLV_MALLOC( (strlen(informativeMessage)+1), char );
    strcpy( input_box->informativeMessage, informativeMessage );

    input_box->apparence = NULL;
    input_box->answer = NULL;
    change_geometry_input_box_NTS(input_box, sommetHautGaucheX, sommetHautGaucheY, width, height);

    MLV_change_input_box_colors(input_box, borderColor, textColor, backgroundColor );

//	DEBUG("Add History Entry");
    input_box->history = MLV_prepend_list( NULL, MLV_MALLOC( 1, char ) );
    ((char*) input_box->history->data)[0] = '\0';
    input_box->positionHistory = input_box->history;
    input_box->positionCursor = 0;

    input_box->lastTime = SDL_GetTicks();
    input_box->cursorIsVisible = 1;
    input_box->isListenning = 0;

    lock_input_box_information();
    input_box_register_NTS( input_box );
    unlock_input_box_information();
    return input_box;
}

MLV_Input_box* MLV_create_input_box_with_font_va(
	int sommetHautGaucheX, int sommetHautGaucheY,
	int width, int height,
	MLV_Color borderColor, MLV_Color textColor,
	MLV_Color backgroundColor,
	const char* informativeMessage,
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
	MLV_Input_box* result = create_input_box_with_font(
		sommetHautGaucheX, sommetHautGaucheY, width, height, borderColor, 
		textColor, backgroundColor, complete_informative_message, font
	);
	free( complete_informative_message );
	return result;
}

MLV_Input_box* MLV_create_input_box_with_font(
	int sommetHautGaucheX, int sommetHautGaucheY,
	int width, int height,
	MLV_Color borderColor, MLV_Color textColor,
	MLV_Color backgroundColor,
	const char* informativeMessage,
	const MLV_Font* font, ...
){
	va_list pile;
	va_start( pile, font );
	MLV_Input_box* result = MLV_create_input_box_with_font_va(
		sommetHautGaucheX, sommetHautGaucheY,
		width, height,
		borderColor, textColor,
		backgroundColor,
		informativeMessage,
		font, pile
	);
	va_end( pile );
	return result;
}

MLV_Input_box* MLV_create_input_box_va(
	int sommetHautGaucheX, int sommetHautGaucheY,
	int width, int height,
	MLV_Color borderColor, MLV_Color textColor,
	MLV_Color backgroundColor,
	const char* informativeMessage,
	va_list pile
){
	return MLV_create_input_box_with_font_va(
		sommetHautGaucheX, sommetHautGaucheY,
		width, height,
		borderColor, textColor,
		backgroundColor,
		informativeMessage,
		MLV_data->defaultFont, pile
	);
}

MLV_Input_box* MLV_create_input_box( 
	int sommetHautGaucheX, int sommetHautGaucheY,
	int width, int height,
	MLV_Color borderColor, MLV_Color textColor,
	MLV_Color backgroundColor,
	const char* informativeMessage, ...
){
	va_list pile;
	va_start( pile, informativeMessage );
	MLV_Input_box* result = MLV_create_input_box_va( 
		sommetHautGaucheX, sommetHautGaucheY,
		width, height,
		borderColor, textColor,
		backgroundColor,
		informativeMessage, pile
	);
	va_end( pile );
	return result;
}

void free_NTS( void* data, void* useless ){
//	DEBUG("Free Entry Hystory");
	MLV_FREE( data, char );
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void suppressHistory_NTS( MLV_Input_box* input_box ){
    MLV_foreach_list( input_box->history, free_NTS, NULL );
//	DEBUG("Free history");
    MLV_free_list( input_box->history );
}

void MLV_suppress_history( MLV_Input_box* input_box ){
    lock_input_box( input_box );
    suppressHistory_NTS( input_box );
    unlock_input_box( input_box );
}

void MLV_free_input_box( MLV_Input_box* input_box ){
    lock_input_box_information( );
    lock_input_box( input_box );
    input_box_unregister_NTS( input_box );
//	DEBUG("Free apparence");
    SDL_FreeSurface(input_box->apparence);
//	DEBUG("Free answer");
    SDL_FreeSurface( input_box->answer );
//	DEBUG("Free Informative message");
	MLV_FREE( input_box->informativeMessage, char );
//    MLV_FREE( input_box->history->data, char );
    suppressHistory_NTS( input_box );
//	DEBUG("Free semaphore");
    SDL_DestroySemaphore( input_box->semaphore );
    unlock_input_box_information( );
//	DEBUG("Free input_box");
	MLV_FREE( input_box, MLV_Input_box );
}

void change_informative_message_of_input_box(
	MLV_Input_box* input_box, const char* message
){
    lock_input_box(input_box);
    if( input_box->informativeMessage ){
//		DEBUG("Free Informative message");
		MLV_FREE( input_box->informativeMessage, char );
    }
//	DEBUG("Add Informative message");
    input_box->informativeMessage = MLV_MALLOC( (strlen(message)+1), char );
    strcpy( input_box->informativeMessage, message );
    recalculateTextPositions_NTS( input_box );
    unlock_input_box(input_box);
}

void MLV_change_informative_message_of_input_box_va(
	MLV_Input_box* input_box, const char* message, va_list pile
){
	char* complete_message;
	if( vasprintf( &complete_message, message, pile )==-1 ){
		ERROR("Unexpected Error.");
	}
	change_informative_message_of_input_box(
		input_box, complete_message
	);
	free( complete_message );
}

void MLV_change_informative_message_of_input_box(
	MLV_Input_box* input_box, const char* message, ...
){
	va_list pile;
	va_start( pile, message );
	MLV_change_informative_message_of_input_box_va(
		input_box, message, pile
	);
	va_end( pile );
}

void MLV_draw_input_box( MLV_Input_box* input_box ){
    lock_input_box( input_box );
    construct_input_box_NTS( input_box );
    SDL_BlitSurface( input_box->apparence, NULL, MLV_data->screen, &(input_box->rectangle));
    unlock_input_box( input_box );
}

void MLV_draw_all_input_boxes(){
    lock_input_box_information( );
    MLV_foreach_list( input_box_information.input_box_list, (void (*)(void*,void*)) MLV_draw_input_box , MLV_data->screen);
    unlock_input_box_information( );
}

void init_input_box_mechanism(){
    SDL_EnableUNICODE(SDL_ENABLE);
    input_box_information.semaphore = SDL_CreateSemaphore(1);
    lock_input_box_information();
    input_box_information.input_box_list = NULL;
    input_box_information.input_box_activated=NULL;
    unlock_input_box_information();
}

void quit_input_box_mechanism(){
	SDL_DestroySemaphore(input_box_information.semaphore);
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void replaceEntreeByHistory_NTS( MLV_Input_box* input_box ){
    char* dst = input_box->history->data;
    if( input_box->positionHistory != input_box->history ){
        char* src = (char*) input_box->positionHistory->data;
        if( strlen(dst) >= strlen(src) ){
            strcpy( dst, src );
        }else{
//			DEBUG("Add Hystory Entry");
            input_box->history->data = MLV_MALLOC( (strlen(src) + 1), char );
            strcpy( input_box->history->data, src );
//			DEBUG("Suppress Hystory Entry");
			MLV_FREE( dst, char );
        }
    }else{
        if(dst){
            dst[0] = '\0';
        }
    }
    input_box->positionCursor = strlen(input_box->history->data);
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void goDownInHistory_NTS( MLV_Input_box* input_box ){
    if( input_box->positionHistory->previous ){
        input_box->positionHistory = input_box->positionHistory->previous;
    }else{
        return;
    }
    replaceEntreeByHistory_NTS( input_box );
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void goUpInHistory_NTS( MLV_Input_box* input_box ){
    if( input_box->positionHistory->next ){
        input_box->positionHistory = input_box->positionHistory->next;
    }else{
        return;
    }
    replaceEntreeByHistory_NTS( input_box );
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void make_the_input_box_visible_NTS( MLV_Input_box* input_box ){
    input_box->lastTime = SDL_GetTicks();
    input_box->cursorIsVisible = 1;
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void input_box_move_left_answer_NTS( MLV_Input_box* input_box ){
    if( input_box->positionCursor > 0 ){
        input_box->positionCursor--;
    }
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void input_box_move_right_answer_NTS( MLV_Input_box* input_box ){
    if( input_box->positionCursor < strlen( input_box->history->data ) ){
        input_box->positionCursor++;
    }
}

#ifndef OS_APPLE  // Hack to compile with MAC OS 10.9 (maverick)
inline
#endif
void validate_input_box_NTS( MLV_Input_box* input_box ){
    SDL_Event event;
    event.type = SDL_USEREVENT;
	event.user.code = MLV_INPUT_BOX;
    event.user.data1 = input_box;
    event.user.data2 = input_box->history->data;
    SDL_PushEvent(&event);
    input_box->history = MLV_prepend_list( input_box->history, input_box->history->data );
    input_box->positionHistory = input_box->history;
//	DEBUG("Add Hystory Entry");
    input_box->history->data = MLV_MALLOC( 1, char );
    ((char*)input_box->history->data)[0] = '\0';
    input_box->positionCursor = 0;
}


int input_box_events_filter(const SDL_Event *event) {
    int result = 1;
    lock_input_box_information();
    switch(event->type){
        case SDL_KEYUP :
            {     //Une touche a ete appuyee
                if( input_box_information.input_box_activated ) result = 0;
            }
            break;
        case SDL_KEYDOWN : 
            {   //Une touche a ete appuyee
                // Si la touche echap a ete appuye, on laisse passe l'evenement
                if ( event->key.keysym.sym == SDLK_ESCAPE ) break;
                if( input_box_information.input_box_activated ){
                    lock_input_box( input_box_information.input_box_activated );
                    make_the_input_box_visible_NTS( input_box_information.input_box_activated);
                    //Si la touche est une fleche gauche ou droite on deplace le curseu
                    if( event->key.keysym.sym == SDLK_LEFT ){
                        input_box_move_left_answer_NTS( input_box_information.input_box_activated );
                    }else if( event->key.keysym.sym == SDLK_RIGHT ){
                        input_box_move_right_answer_NTS( input_box_information.input_box_activated );
                    }else if( event->key.keysym.sym == SDLK_UP ){//Si la touche est une fleche bas ou haut on se  deplace dans l'historique
                        goUpInHistory_NTS( input_box_information.input_box_activated );
                    }else if( event->key.keysym.sym == SDLK_DOWN ){
                        goDownInHistory_NTS( input_box_information.input_box_activated );
                    }else if( event->key.keysym.sym == SDLK_DELETE ){//Si la touche est une suppession on supprime une lettre
                        suppress_carac_input_box_NTS( input_box_information.input_box_activated );
                    }else if( event->key.keysym.sym == SDLK_BACKSPACE ){
                        return_deletion_carac_input_box_NTS( input_box_information.input_box_activated );
                    }else if( (event->key.keysym.sym == SDLK_RETURN) || (event->key.keysym.sym == SDLK_KP_ENTER) ){
                        validate_input_box_NTS(input_box_information.input_box_activated);
                    }else if( event->key.keysym.unicode != 0 ){
                    //Si la lettre n'est pas \n On ajoute la lettre au mot courant
                    //Sinon on vide le mot et on cree un evenement du mot qui
					//a ete attrappee par la boite de saisie
					char* character = MLV_convert_unicode_to_string(
						event->key.keysym.unicode
					);
					int i=0;
					while( character[i] != '\0' ){
                    	add_carac_input_box_NTS(
							input_box_information.input_box_activated,
							character[i]
						);
						i++;
					}
					MLV_FREE( character, char );
                    }
                    unlock_input_box( input_box_information.input_box_activated );
                    result = 0;
                }
            }
            break;
        case SDL_MOUSEBUTTONDOWN :
            {     //Si on est dans une zone de boîte de saisie on active 
				  // l'enregistrement des données.
                MLV_Input_box* tmp = is_in_an_input_box_NTS(
                    event->button.x, event->button.y
                );
                if( tmp ){
                    lock_input_box( tmp );
                     activate_imput_box_NTS( tmp );
                    unlock_input_box( tmp );
                    result=0;
                }else{
                    desactivate_input_box_NTS( );
                }
            }
            break;
        default :;
    }
    unlock_input_box_information();
    return result;
}

