/**
 *
 * Ce programme change change la taille des fenetres et met le programme en mode 
 * plein écran.
 *
 *------------------------------------------------------------------------------
 * MLV_enable_full_screen : Affiche la fenêtre en plein ecran.
 *                          La résolution de l'image est donné alors par la
 *                          taille de l'image. Pour que l'application soit en 
 *                          plein écran, il faut que la taille de la fenetre soit
 *                          compatible avec la résolution de l'écran.
 *
 * void MLV_enable_full_screen();
 *
 *------------------------------------------------------------------------------
 * MLV_disable_full_screen : Désactve le mode plein écran de la fenêtre.
 *
 * void MLV_disable_full_screen();
 *
 *------------------------------------------------------------------------------
 * MLV_change_window_size : Change la taille de la fenêtre.
 *                          Si la fenetre a configuré en mode plein ecran, 
 *                          l'appliqcation reste alors en mode plein écran. 
 *                          Pour que l'application soit en plein écran, il faut
 *                          que la taille de la fenetre soit compatible avec la 
 *                          résolution de l'écran.
 *                          De plus, en mode plein écran, la taille de la 
 *                          fenêtre correspond à la résolution de l'image sur
 *                          l'écran.
 *
 * void MLV_change_window_size(
 *     unsigned int     width,     la largeur de la fenêtre
 *     unsigned int     height     la hauteur de la fenêtre
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_get_window_height : Retourne la hauteur de la fenêtre.
 *
 * int MLV_get_window_height( );
 * 
 *------------------------------------------------------------------------------
 * MLV_get_window_width : Retourne la largeur de la fenetre.
 *
 * int MLV_get_window_width( );
 *
 *------------------------------------------------------------------------------
 */

#include <MLV/MLV_all.h>
#include <stdio.h>

void affichage(){
	int width = MLV_get_window_width();
	int height = MLV_get_window_height();
	MLV_clear_window( MLV_COLOR_YELLOW );
	MLV_draw_rectangle( 0,0, width, height, MLV_COLOR_RED );
	
	MLV_draw_text(
		10, height/2-70, 
		"Différentes résolutions d'écran vont défiler.",MLV_COLOR_BLACK
	);
	MLV_draw_text(
		10, height/2-50, 
		"Ces résolutions seront testées en mode plein écran et en mode fenêtre.",
		MLV_COLOR_BLACK
	);
	MLV_draw_text(
		10, height/2-30,
		"Veuillez attendre la fin de la démonstration.",MLV_COLOR_BLACK 
	);

	MLV_draw_text(
		10, height/2+0,
		"Résolution : %d X %d",
		MLV_COLOR_BLACK,
		width, height
	);
	if( MLV_is_full_screen() ){
		MLV_draw_text( 10, height/2+20, "Mode : Plein écran" ,MLV_COLOR_BLACK );
	}else{
		MLV_draw_text( 10, height/2+20, "Mode : fenêtre" ,MLV_COLOR_BLACK );
	}
	MLV_draw_text(
		10, height/2+50, "Appuyer sur une touche pour continuer." ,MLV_COLOR_RED
	);

	MLV_actualise_window();
}


//
// Attention ! 
// Pour pouvoir compiler ce programme sous window et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){

	//
	// Créé une fenetre qui n'est pas en mode plein écran
	//
	MLV_create_window( "medium - 8 - full screen", "full screen", 640, 480 );
	affichage();
	MLV_wait_keyboard(NULL,NULL,NULL);

	// On passe en mode plein écran
	MLV_enable_full_screen( );
	affichage();
	MLV_wait_keyboard(NULL,NULL,NULL);

	// On change la taille de la fenetre
	MLV_change_window_size( 550, 160 );
	// On quitte le mode plein écran
	MLV_disable_full_screen( );
	affichage();
	MLV_wait_keyboard(NULL,NULL,NULL);

	// On passe en mode plein écran
	// Ici la résolution de la fenetre n'est pas compatible avec 
	// la résolution de l'ecran.
	// Le programme passe donc en plein écran, mais n'adapte par la taille 
	// de l'image à celle de l'écran
	MLV_enable_full_screen( );
	affichage();
	MLV_wait_keyboard(NULL,NULL,NULL);

	//
	// Ferme la fenêtre
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
