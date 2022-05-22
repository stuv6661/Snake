/**
 *
 * Ce programme montre comment il est possible de récupéré les caractères 
 * accentués provenant d'une entree clavier.
 *
 * Pour cela, le programme utilise la fonction :
 *
 *------------------------------------------------------------------------------
 * MLV_convert_unicode_to_string : Transforme un caractère en format unicode en
 *                                 chaine de caractères compatible avec le 
 *                                 codage local.
 *
 *         Cette fonction renvoie un pointeur vers une nouvelle chaine de 
 *         caractère. Il ne faut donc pas oublier oublier de libérer l'espace 
 *         allouer apès utilisation de la chaîne de caractère. 
 * 
 * char* MLV_convert_unicode_to_string(
 *     int unicode    Caractère en format unicode 
 * );
 *
 *------------------------------------------------------------------------------
 *
 */

#include <MLV/MLV_all.h>
#include <stdlib.h>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){
	//
	// Déclaration de la variable qui représentera le code de la touche qui
	// sera appuyée par l'utilisateur.
	//
	int unicode;
	MLV_Keyboard_button touche = MLV_KEYBOARD_NONE;
	char* text;
	int width, height;
	width = 640;
	height = 480;

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window(
		"medium - 9 - keyboard accents", "keyboard accents", width, height
	);

	//
	// Affiche la consigne
	//
	MLV_draw_text(
		10, 10, 
		"Vous pouvez faire apparaitre les caractères accentué !",
		MLV_COLOR_GREEN
	);
	MLV_actualise_window();

	//
	// Attendre que l'utilisateur appuie sur une touche du clavier
	//
	while( touche != MLV_KEYBOARD_ESCAPE  ){
		MLV_wait_keyboard( &touche, NULL, &unicode );

		// On efface l'écran
		MLV_draw_filled_rectangle( 0, 50, width, height, MLV_COLOR_BLACK );

		// On impime le caractère avec les accents
		text = MLV_convert_unicode_to_string( unicode );
		MLV_draw_text( 10, 100, text, MLV_COLOR_GREEN );

		free( text );

		MLV_actualise_window();
	}
	
	//
	// Attend 2 seconde avant la fin du programme.
	//
	MLV_wait_seconds( 2 );
	
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
