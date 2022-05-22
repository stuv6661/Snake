/**
 *
 * Ce programme montre comment il est possible de récupérer des informations
 * provenant de l'utilisateur lorsqu'il utilise son clavier, sa souris ou
 * lorsqu'il valide une chaîne de caractères à l'aide d'une boîte de saisie
 * sans bloquer l'exécution du programme.
 *
 * Pour cela il utilise le système d'évènements de la librairie MLV :
 *
 * À chaque fois qu'un utilisateur déplace la sourris, appuie sur les touches 
 * d'un clavier, ou entre du texte dans une boîte de siaise, un événèment est 
 * créé par la librairie MLV. Cet évènement est placé dans une file 
 * d'attente.
 * Il est possible de récupérer toutes les informations concernant ces 
 * évènements en appelant la fonction MLV_get_event().
 * Cette fonction supprime le dernier évènement de la pile, l'analyse et 
 * renvoie, à l'aide de ses paramètres et de sa valeur de retour,
 * toutes les informations le concernant.
 *
 * Voici en détail le fonctionnement de la fonction MLV_get_event :
 *
 *------------------------------------------------------------------------------
 * MLV_get_event : Cette fonction récupère un évènement dans la file d'attente,
 *                 remplit en fonction de l'évènement récupéré une partie des
 *                 paramètres de la fonction et renvoie un entier codant le
 *                 type de l'évènement qui a été récupéré.
 *
 *                 Le type des évènements est défini par :
 *                     MLV_Event
 *                 et peut valoir les valeurs suivantes:
 *                     Valeur              Signification
 *                     ------              --------------
 *                     MLV_NONE            Aucun évènement récupéré
 *                     MLV_KEY             Une touche du clavier a été appuyé ou
 *                                         relachée.
 *                     MLV_INPUT_BOX       L'utilisateur à écrit une chaîne de
 *                                         caractères et validée cette chaine
 *                                         par la touche entrée.
 *                     MLV_MOUSE_BUTTON    Un des boutons de la souris a été
 *                                         appuyé.
 *                     MLV_MOUS_MOTION     La souris a été déplacée.
 *
 *                  Voici un tableau qui donne les champs modifiés en fonction 
 *                  de l'évènement qui a été récupéré.
 *
 *                     Type Evenement      Paramètres modifiés
 *                     --------------      -------------------
 *                     MLV_NONE            AUCUN
 *                     MLV_KEY             key_sym, key_mod, state
 *                     MLV_INPUT_BOX       texte, input_box
 *                     MLV_MOUSE_BUTTON    mouse_x, mouse_y, mouse_button, state
 *                     MLV_MOUSE_MOTION    mouse_x, mouse_y
 *
 *                  L'utilisateur n'est pas obligé d'utiliser un champs si il
 *                  n'en a pas l'utilité. Dans ce cas, il peut mettre la valeur
 *                  NULL. Le champs est alors ignoré.
 *
 * MLV_Event MLV_get_event( 
 * 	int*            key_sym,         Code de la touche qui a été appuyée ou
 *                                       relachée.
 *                                       La valeur de ce champs est définie par
 *                                       l'énumération :
 *                                           MLV_Keyboard_button.
 *                                       Les différentes valeurs possibles sont
 *                                       listées dans le fichier
 *                                           MLV_keyboard.h.
 *                                       Il est possible de récupérer cette 
 *                                       liste en tapant sur la ligne de 
 *                                       commande:
 *                                           man MLV_keyboard.h
 * 	int*            key_mod,         Mode dans lequel se trouve le clavier
 *                                       lorsqu'une touche est appuyée ou 
 *                                       relachée.
 *                                       La valeur de ce champs est définie par
 *                                       l'énumération :
 *                                           MLV_Keyboard_modifier.
 *                                       Les différentes valeurs possibles sont
 *                                       listées dans le fichier :
 *                                           MLV_keyboard.h.
 *                                       Il est possible de récupérer cette 
 *                                       liste en tapant sur la ligne de 
 *                                       commande:
 *                                           man MLV_keyboard.h
 * 	char**          texte,           Texte récupéré par la boîte de saisie
 * 	MLV_Input_box** input_box,       La boîte de saisie qui a récupéré le texte
 * 	int*            mouse_x,         Coordonnée en X de la position de la 
 *                                       souris
 * 	int*            mouse_y,         Coordonnée en Y de la position de la
 *                                       souris
 * 	int*            mouse_button,    Bouton de la souris qui a été appuyé
 *                                       ou relaché.
 *                                       Ce champs est défini par l'énumération
 *                                       MLV_Mouse_button
 *                                       et peux valoir les valeurs suivantes :
 *                                           MLV_BUTTON_LEFT
 *                                           MLV_BUTTON_MIDDLE
 *                                           MLV_BUTTON_RIGHT
 * 	int*            state            Etat de la touche concernée par
 *                                       l'évènement. La valeur de ce champs
 *                                       est définie par l'énumération:
 *                                           MLV_Button_state
 *                                       et peut valoir les valeurs suivantes:
 *                                           MLV_PRESSED
 *                                           MLV_RELEASED
 * );
 *
 *------------------------------------------------------------------------------
 */

#include <MLV/MLV_all.h>

#include <stdlib.h>
#include <stdio.h>

//
// Fonction qui s'occupe de l'affiche de la démonstration.
//
void affichage(
	int nb_touche, int nb_mouse_click, int nb_mouse_motion,
	int x, int y, char* texte1, char* texte2,
	int width, int height
){
	int taille_interlinge = 5;

	//
	// Nettoie l'écran pour un nouvel affichage
	//
	MLV_clear_window( MLV_COLOR_BLACK );

	//
	// Dessine toutes les boîtes de saisie.
	//
	MLV_draw_all_input_boxes();
	
	//
	// Affiche un message d'information
	//
	MLV_draw_adapted_text_box(
		10,160,
		"Lorsque vous cliquez sur une boîte de saisie,\nles évènements concernant le clavier et la souris\nne sont plus transmis à l'utilisateur.",
		taille_interlinge,
		MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		MLV_TEXT_LEFT
	);

	//
	// Affiche le nombre de fois qu'une touche a été appuyée depuis le debut
	// du programme.
	//
	MLV_draw_text(
		10, 40,
		"Nombre de fois que l'on a appuyé sur une touche : %i",
		MLV_COLOR_GREEN, nb_touche
	);

	//
	// Affiche le nombre de fois que l'utilisateur à bougé la souris
	//
	MLV_draw_text(
		10, 60,
		"Nombre de fois que la souris a bougé : %i",
		MLV_COLOR_GREEN, nb_mouse_motion
	);

	//
	// Affiche le nombre de fois que l'utilisateur a cliqué avec la souris
	//
	MLV_draw_text(
		10, 80,
		"Nombre de click de souris : %i",
		MLV_COLOR_GREEN, nb_mouse_click
	);

	//
	// Affiche la position de la souris sur l'écran
	//
	MLV_draw_text(
		x, y,
		"(%d,%d)",
		MLV_COLOR_GREEN, x, y
	);

	//
	// Affiche le texte récupéré par la première boîte de saisie.
	//
	MLV_draw_text(
		10, 140,
		texte1,
		MLV_COLOR_GREEN
	);

	//
	// Affiche le texte récupéré par la seconde boîte de saisie.
	//
	MLV_draw_text(
		220, 140,
		texte2,
		MLV_COLOR_GREEN
	);

	//
	// Met à jour la fenêtre
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
	int width = 640, height = 460;    //Taille de la fenêtre

	// informations conernant les évènements de type clavier.
	MLV_Keyboard_button sym=MLV_KEYBOARD_NONE;
	MLV_Keyboard_modifier mod=MLV_KEYBOARD_KMOD_NONE;
	MLV_Button_state state;

	int x=0,y=0;            // Position de la souris
	char* texte = NULL;		// Texte qui sera recupéré par la boîte de saisie
	char *texte1, *texte2;		// Texte qui sera recupéré par la boîte de saisie
	MLV_Input_box *input_box = NULL, *input_box_1, *input_box_2;
	MLV_Event event = MLV_NONE;        //Évènenemt
	
	int nb_touche = 0;   // Nombre de fois que l'utilsateur a appuyé sur une 
	                     // touche du clavier
	int nb_mouse_click = 0; // Nombre de fois que l'utilisateur a cliqué sur la
	                        // souris
	int nb_mouse_motion = 0; // Nombre de fois que l'utilisateur a déplacé la 
	                         // souris
	int quit = 0;

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "medium - 4 events", "4 events", width, height );

	//
	// Créé la première boîte de saise.
	//
	input_box_1 = MLV_create_input_box(
		10, 100,
		200, 30, 
		MLV_COLOR_BLUE, MLV_COLOR_GREEN,
		MLV_COLOR_BLACK, " Saisie 1 : "
	);
	texte1 = (char*) malloc( sizeof(char) ); *texte1 = '\0';

	//
	// Créé la seconde boîte de saisie.
	//
	input_box_2 = MLV_create_input_box(
		220, 100,
		200, 30, 
		MLV_COLOR_BLUE, MLV_COLOR_GREEN,
		MLV_COLOR_BLACK, " Saisie 2 : "
	);
	texte2 = (char*) malloc( sizeof(char) ); *texte2 = '\0';

	//
	// Met a jour l'affichage
	//
	affichage(
		nb_touche, nb_mouse_click, nb_mouse_motion, x, y,
		texte1, texte2, width, height
	);

	//
	// Tant que la touche shift+q n'a pas été appuyée puis relachée,
	// on compte le nombre de fois que l'utilisateur a appuyé sur une
	// touche.
	//
	do {
		//
		// Récupère un évènement dans la file des évènements
		// non traités.
		//
		event = MLV_get_event( 
			&sym, &mod, NULL,
			&texte, &input_box,
			&x, &y, NULL,
			&state
		);

		//
		// Traitetement des évènements
		//
		switch( event ){
			case MLV_NONE : // Aucun évènement récupéré
				break;
			case MLV_KEY : // L'utilisateur a utilisé le clavier
				//
				// On incrémente le compteur du nombre de fois
				// que l'utilisateur à appuyé sur le clavier
				// si une touche a été appuyée
				//
				if( state == MLV_PRESSED ){
					nb_touche = nb_touche + 1;
				}
				break;
			case MLV_INPUT_BOX : // L'utilisateur a utilisé une boîte de saisie.
				//
				// Si le texte a été récupéré par la première boîte de saisie
				// input_box_1, on met à jour le texte
				// correspondant à la première boîte de saisie.
				//
				if( input_box == input_box_1 ){
					free( texte1 );
					texte1 = texte;
				}
				//
				// Si le texte a été récupéré par la deuxième  boîte de saisie
				// , on met à jour le texte
				// correspondant à la deuxième boîte de saisie.
				//
				if( input_box == input_box_2 ){
					free( texte2 );
					texte2 = texte;
				}
				break;
			case MLV_MOUSE_BUTTON : // L'utilisateur a utilisé un 
			                        // bouton de la souris
				//
				// On incrémente le compteur du nombre de fois
				// que l'utilisateur a appuyé sur la touche 
				// de la souris
				//
				if( state == MLV_PRESSED ){
					nb_mouse_click = nb_mouse_click + 1;
				}
				break;
			case MLV_MOUSE_MOTION : // L'utilisateur a déplacé la souris
				//
				// On incrémente le compteur du nombre de fois
				// que l'utilisateur a déplacé la souris
				//
				nb_mouse_motion = nb_mouse_motion + 1;
				break;
			default :
				fprintf(
					stderr,
					"Erreur : la valeur de l'évènement récupéré est impossible."
				);
				quit = 1;
		}

		//
		// Mis à jour de l'affichage
		//
		affichage(
			nb_touche, nb_mouse_click, nb_mouse_motion, x, y,
			texte1, texte2, width, height
		);
	} while( ! quit );

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
