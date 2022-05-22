/**
 * Dans certains cas, il est pratique de pouvoir connaître l'état courant d'une
 * touche d'un clavier ou de la position courante de la souris.
 *
 * Par exemple, dans les applications à temps réel, il n'est pas raisonnable 
 * d'utiliser MLV_get_event pour recupere la position de la souris.
 * En effet, à chaque deplacement de la souris, vous devez récuperer la position
 * de la souris et réaliser un traitement.
 * Or le déplacement de la souris engendre (par secondes) plus dévènements que 
 * l'ordinateur est capable de traiter.
 * Il vaus mieux donc ne pas récuperer les evenements concernant le déplacement
 * de la souris et récuperer, à la place, à chaque tour de boucle, sa position.
 *
 * Dans cette démonstration, nous montrons comment il est possible de récupérer 
 * l'état d'une touche d'un clavier, d'un bouton d'un clavier ou la position 
 * courante de la souris, sans utiliser la fonction MLV_get_event();
 *
 *------------------------------------------------------------------------------
 * MLV_get_keyboard_state : Renvoie l'état (préssé ou relaché) de l'une touche 
 *                          du clavier.
 *
 * MLV_State MLV_get_keyboard_state(
 *     MLV_Keyboard     keyboard_code     Le code de la touche dont il faut 
 *                                        renvoyer l'état.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_get_mouse_position: Renvoie la position courante de la souris. 
 *
 * void MLV_get_mouse_position(
 *     int*     x,    Coordonnée en X de la position de la souris dans la
 *                    fenêtre.
 *     int*     y     Coordonnée en Y de la position de la souris dans la 
 *                    fenêtre.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_get_mouse_button_state: Renvoie l'état (préssé ou relaché) d'un bouton de
 *                             la souris.
 *
 * MLV_State MLV_get_mouse_button_state(
 *     MLV_Button     mouse_button     Le code du bouton de la souris
 * );
 *
 *------------------------------------------------------------------------------
 * 
 */

#include <MLV/MLV_all.h>

#include <stdio.h>

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){

	int width = 640, height=480;

	//
	// On créé et affiche la fenêtre
	//
	MLV_create_window( "medium - 4 events", "4 events", width, height );

	while( 1 ){
		//
		// On commence par nettoyer l'écran
		//
		MLV_clear_window( MLV_COLOR_BLACK );

		//
		// On récupère puis affiche l'état de la touche a
		//
		if( MLV_get_keyboard_state( MLV_KEYBOARD_k ) == MLV_PRESSED ){
			MLV_draw_text(  
				0, 20, "L'utilisateur est en train d'appuyer sur la touche k",
				MLV_COLOR_GREEN
			);
		}else{
			MLV_draw_text( 
				0, 20,
				"L'utilisateur n'est pas en train d'appuyer sur la touche k",
				MLV_COLOR_GREEN
			);
		}
		
		//
		// On récupère puis affiche la position de la souris
		//
		int x,y;
		MLV_get_mouse_position( &x, &y );

		MLV_draw_text(
			0, 40,
			"Position de la souris : (%d, %d)",
			MLV_COLOR_GREEN,
			x, y 
		);


		//
		// On récupère puis affiche l'état du bouton gauche de la souris.
		//
		if( MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED ){
			MLV_draw_text(
				0, 60,
				"L'utilisateur est en train de cliquer sur le bouton gauche de la souris.",
				MLV_COLOR_GREEN
			);
		}else{
			MLV_draw_text(
				0, 60,
				"L'utilisateur n'est pas en train de cliquer sur le bouton gauche de la souris.",
				MLV_COLOR_GREEN
			);
		}

		//
		// On met à jour l'affichage.
		//
		MLV_actualise_window();
	}

	//
	// On libère la fenêtre
	//
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
