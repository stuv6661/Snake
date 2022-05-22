/**
 *
 * Ce programme montre comment il est possible de faire arrêter proprement un
 * programme lorsque l'utilisateur demande son arrêt en appuyant sur la croix de
 * la fenêtre, ou en envoyant un signal sytème d'arret du programme.
 *
 *------------------------------------------------------------------------------
 * MLV_execute_at_exit : Exécute la fonction de call back donnée en paramètre
 *                       lorsque le système envoie un signal d'arrêt, ou lorsque
 *                       l'utilisateur clique sur la croix de la fenêtre.
 *                       la fonction de call back est alors executée avec en
 *                       paramètre un pointeur vers une structure de donnée qui 
 *                       est aussi donné en paramètre à la fonction 
 *                       MLV_execute_at_exit.
 *
 * void MLV_execute_at_exit(
 *     void (*    function    )(void*),       pointeur de la fonction de call 
 *                                            back qui doit être exécutée. 
 *     void*      data                        Donné à passer en paramètre à la 
 *                                            fonction de call back lors de son
 *                                            exécution.
 * );
 *
 *------------------------------------------------------------------------------
 */

#include <MLV/MLV_all.h>

//
// exit_function est la fonction de call back qui sera appelée par la librairie
// MLV au moment où l'utilisateur demandera à l'application de s'arrêter 
// en utilisant un signal d'arrêt ou en appuyant sur la croix de la 
// fenêtre.
//
void exit_function( void* data ){
	int* arret = (int*)  data;
	*arret = 1;
}

void affichage( int width, int height ){
	int elapsed_time;

	//
	// On nettoie l'écran
	//
	MLV_clear_window( MLV_COLOR_BLACK );

	//
	// Affichage du texte explicatif.
	//	
	MLV_draw_adapted_text_box(
		10, 100,
		"Ce programme ne s'arête pas.\nToutefois, vous pouvez fermer le programme en fermant simplement la fenêtre.\n A ce moment là il est possible,\n à l'aide d'une fonction de rappel,\n d'exécuter un dernier code.",
		9,
		MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		MLV_TEXT_CENTER
	);

	//
	// On recupère le temps d'execution depuis le debut du programme
	// 
	elapsed_time =  MLV_get_time();

	//
	// un message d'impatiente à l'écran
	//
	MLV_draw_text(
		10, 400, 
		"Ca fait %d secondes que j'attends que vous quittiez ce programme.",
		MLV_COLOR_GREEN, elapsed_time/1000
	);

	//
	// Mise à jour de l'affichage
	//
	MLV_actualise_window();
}


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){
	int arret = 0;
	int width = 640, height = 480;
	//
	// On enregistre la fonction de call back exit_function
	// dans la librairie MLV.
	// Cette ligne doit toujours précéder l'appel de la fonction
	// MLV_create_window
	//
	MLV_execute_at_exit( exit_function, &arret );

	//
	// Créé la fenêtre et l'affiche.
	//
	MLV_create_window( "medium - 5 - exit", "exit", width, height );


	//
	// Tant que l'utilisateur ne demande pas un arret du programme,
	// on actualise l'affichage de l'écran.
	//
	while( ! arret ){
		affichage( width, height );
	}

	//
	// Affiche un message d'adieu.
	//
	MLV_draw_adapted_text_box(
		200, 300,
		"Au revoir et à bientôt!",
		9,
		MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		MLV_TEXT_CENTER
	);
	MLV_actualise_window();  // Met à jour l'affichage

	//
	// Attend 2 secondes
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
