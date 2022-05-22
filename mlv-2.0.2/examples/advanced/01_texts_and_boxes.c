/**
 * Ce programme explique comment récupérer la taille des boîtes de textes avant 
 * de les afficher.
 *
 * Pour cela, le programme utilise les fonctions suivantes:
 *
 *------------------------------------------------------------------------------
 * MLV_get_size_of_text : Calcule la taille de la ligne qui sera affiché à l'écran
 *
 * void MLV_get_size_of_text(
 *     const char *    text,     Texte qui dit être affiché
 *     int *           width,    largeur du texte
 *     int *           height    hauteur du texte
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_get_size_of_adapted_text_box : Calcule la taille de la boîte de texte qui
 *                                    serait obtenue si vous utilisez la 
 *                                    fonction MLV_adapted_box_size.
 *
 * int MLV_get_size_of_adapted_text_box(
 *     const char*    message,           texte qui sera affiché lorsque vous 
 *                                       utiliserez MLV_adapted_box.
 *     int            sizeInterligne,    Taille de l'interligne
 *     int *          result_width,      Largeur de la boîte que vous obtiendrez
 *                                       en utilisant MLV_adapted_box.
 *     int *          result_height      Hauteur de la boîte que vous obtiendrez
 *                                       en utilisant MLV_adapted_box.
 * );
 *
 *------------------------------------------------------------------------------
 */

#include <MLV/MLV_all.h>

//
// Fonction affichant les côtes d'une boîte de texte. Les paramètres sont 
// la position du sommet Nord-Ouest ( paramètres x et y ) et la taille de la 
// boîte de texte ( paramètres width et height ).
//
void print_cote( int O, int N, int width, int height, MLV_Color color ){
	int espace = 3;
	int sizeLine = 10;
	int S = N + height -1;
	int E = O + width - 1;

	MLV_draw_line(O, N - espace, O, N - espace - sizeLine , color);
	MLV_draw_line(E, N - espace, E, N - espace - sizeLine , color);
	MLV_draw_line(O, S + espace, O, S + espace + sizeLine , color);
	MLV_draw_line(E, S + espace, E, S + espace + sizeLine , color);

	MLV_draw_line(O - espace, N, O - espace - sizeLine, N, color);
	MLV_draw_line(O - espace, S, O - espace - sizeLine, S, color);
	MLV_draw_line(E + espace, N, E + espace + sizeLine, N, color);
	MLV_draw_line(E + espace, S, E + espace + sizeLine, S, color);
}

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){
	int width = 640, height = 480;
	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window(
		"advanced - 1 - texts and boxes", "texts and boxes", width, height );

	// texte à afficher dans une boîte
	const char* text = "Voici une boite de texte, centré par rapport à la fenetre.";
	// Taille de la future boite qui affichera le texte.
	int width_text, height_text; 
	//
	// Récupère la taile de la boite de texte qui affichera le texte
	// contenu dans la variable text.
	//
	MLV_get_size_of_text( text, &width_text, &height_text );
	int positionX = (width-width_text)/2, positionY = 100;

	//
	// Affichage du texte
	//
	MLV_draw_text( positionX, positionY, text, MLV_COLOR_GREEN );
	//
	// Affichage les côtes du texte.
	//
	print_cote( positionX, positionY, width_text, height_text, MLV_COLOR_GREEN );

	//
	// Second texte à afficher
	//
	const char *text_box = "Voici une boîte de texte.\nCette Boîte de texte est elle aussi centré horizontalement dans la fenetre.";

	int width_box = 0 , height_box = 0, size_interligne = 9;

	//
	// Récupère la taille de la boite de texte qui affichera le texte
	// contenu dans la variable text_box.
	//
	MLV_get_size_of_adapted_text_box(
		text_box,
		size_interligne,
		&width_box, &height_box
	);
	//
	// Calcul la position idéale pour la boîte de texte
	//
	int positionBoxX = (width-width_box)/2, positionBoxY = 300;

	//
	// Affiche la boîte de texte.
	//
	MLV_draw_adapted_text_box(
		positionBoxX, positionBoxY,
		text_box,
		size_interligne,
		MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		MLV_TEXT_CENTER
	);
	//
	// Affiche les côtes de la boîte de texte.
	//
	print_cote(
		positionBoxX, positionBoxY, width_box, height_box, MLV_COLOR_GREEN
	);

	//
	//  Met à jour l'affichage de la fenêtre
	//
	MLV_actualise_window();

	//
	// Attend 15 secondes
	//
	MLV_wait_seconds( 15 );

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
