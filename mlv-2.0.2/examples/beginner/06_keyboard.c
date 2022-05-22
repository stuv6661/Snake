/**
 *
 * Ce programme montre comment il est possible d'utiliser le clavier.
 * Pour cela, le programme utilise la fonction :
 *
 *------------------------------------------------------------------------------
 * MLV_wait_keyboard : Suspend l'exécution jusqu'à ce que l'utilisateur
 *                     appuie sur une touche du clavier.
 *                     Lorsque l'utilisateur appuie sur une touche, la 
 *                     fonction retourne trois valeurs ( sym, mod et unicode )
 *                     correspondant respectivement au code de la touche, au
 *                     mode dans lequel se trouve le clavier (majuscule etc ...)
 *                     et au caractère unicode obtenu en combinant le mode du
 *                     clavier et le code de la touche appuyée.
 *
 *                     La fonction accepte des valeurs nulles pour les 
 *                     pointeurs sym, mod et unicode.
 *                     Dans ce cas la fonction ignore les champs en question.
 *
 * void MLV_wait_keyboard(
 *     int*        sym,        Code de la touche 
 *     int*        mod,        Mode dans lequel se trouve le clavier
 *     int*        unicode     Caractère codé en unicode de la lettre obtenu
 *                             en combinant le code et le mode de la touche
 * );
 *
 *------------------------------------------------------------------------------
 * Il est possible d'obtenir la liste exaustive des :
 *    - différents codes associées aux différentes touches
 *    - différents modes
 * en consultant respectivement les énumerations 
 *    - MLV_Keyboard_button
 *    - MLV_Keyboard_modifier 
 * du fichier MLV_keyboard.h  ( faire un man MLV_keyboard.h )
 *
 * Pour consulter la documentation du fichier MLV_keyboard.h vous pouvez
 * taper dans le terminal la commande :
 * man MLV_keyboard.h
 *
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
	// Déclaration de la variable qui représentera le code de la touche qui
	// sera appuyée par l'utilisateur.
	//
	MLV_Keyboard_button touche;

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "beginner - 6 - keyboard", "keyboard", 640, 480 );

	//
	// Affiche la consigne
	//
	MLV_draw_text( 10, 10, "Appuyez sur la touche k", MLV_COLOR_GREEN );
	MLV_actualise_window();

	//
	// Attendre que l'utilisateur appuie sur une touche du clavier
	//
	MLV_wait_keyboard( &touche, NULL, NULL );

	//
	// Affiche "Bien !" si l'utilisateur a appuyer sur la touche k sinon
	// affiche un message d'erreur.
	//
	if( touche == MLV_KEYBOARD_k ){
		MLV_draw_text( 10, 30, "Bien !", MLV_COLOR_GREEN );
	}else{
		MLV_draw_text( 
			10, 30, "Vous n'avez pas appuyé sur la touche k",
			MLV_COLOR_GREEN
		);
	}
	MLV_actualise_window();
	
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
