/**
 *
 * Ce programme montre comment il est possible de demander à l'utilisateur de 
 * cliquer sur la souris et de récuperer alors les coordonnées de la position de
 * la souris.
 *
 * Pour cela, le programme utilise la fonction :
 *
 *-----------------------------------------------------------------------------
 * MLV_wait_mouse : Suspend l'exécution du programme jusqu'à ce que 
 *                  l'utilisateur clique sur le bouton gauche de la souris.
 *                  Au moment où l'utilisateur clique, la fonction retourne les
 *                  coordonnées de la position de la souris dans la fenêtre.
 *
 * void MLV_wait_mouse(
 *     int *    x,    Coordonnée en X de la position de la souris
 *     int *    y     Coordonnée en Y de la position de la souris
 * );
 *-----------------------------------------------------------------------------
 */

#include <MLV/MLV_all.h>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){
	//
	// Décalaration des variables qui contiendront les positions
	// de la souris.
	//
	int x,y;

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "beginner - 5 - mouse", "mouse", 640, 480 );

	//
	// Affiche la consigne
	//
	MLV_draw_text(
		10, 10,
		"Cliquez sur la fenêtre à l'aide de la souris pour faire apparaître un cercle",
		MLV_COLOR_GREEN
	);
	MLV_actualise_window();

	//
	// Attendre que l'utilisateur clique sur le bouton gauche de la souris
	//
	MLV_wait_mouse(&x, &y);

	//
	// Dessine un cercle à la position du curseur de la souris
	//
	MLV_draw_circle( x, y, 30, MLV_COLOR_RED );
	MLV_actualise_window();
	
	//
	// Attend 1 seconde avant la fin du programme.
	//
	MLV_wait_seconds( 1 );
	
	//
	// Fermer la fenêtre
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
