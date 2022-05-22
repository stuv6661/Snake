/**
 *
 * Ce programme montre comment il est possible de récupérer des informations
 * provenant de l'utilisateur lorsqu'il utilise son clavier sans bloquer
 * l'exécution du programme.
 *
 * Pour cela il utilise le système d'évènements de la librairie MLV :
 *
 * À chaque fois qu'un utilisateur déplace la sourris, appuie sur les touches 
 * d'un clavier, ou entre du texte dans une boîte de saisie, un événèment 
 * est créé par la librairie MLV.
 * Cet évènement est placé dans une file d'attente.
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
 *                     MLV_INPUT_BOX       L'utilisateur a écrit une chaîne de
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
 *                  L'utilisateur n'est pas obligé d'utiliser un champs s'il
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
 * 	char**          texte,           Texte récupéré par la boîte de saisie. 
 *                                   L'allocation est affecté par la
 *                                   fonction elle même.
 *                                   La désallocation est à la charge de 
 *                                   l'utilisateur.
 * 	MLV_Input_box** inputbox,        La boîte de saisie qui a récupéré le texte
 * 	int*            mouse_x,         Coordonnée en X de la position de la 
 *                                       souris
 * 	int*            mouse_y,         Coordonnée en Y de la position de la
 *                                       souris
 * 	int*            mouse_button,    Bouton de la souris qui a été appuyé
 *                                       ou relaché.
 *                                       Ce champs est défini par l'énumération
 *                                       MLV_Button
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
#include <stdio.h>

//
// Fonction qui s'occupe de l'affichage de la démonstration.
//
void affichage( int nb, int width, int height ){
	//
	// Nettoie l'écran pour un nouvel affichage
	//
	MLV_clear_window( MLV_COLOR_BLACK );

	//
	// Affiche la consigne
	//
	MLV_draw_text(
		10, 10,
		"Appuyer sur     shift+k     et     relâcher uniquement la touche k     pour quitter !",
		MLV_COLOR_GREEN
	);

	//
	// Affiche le nombre de fois qu'une touche a été appuyée depuis le debut
	// du programme.
	//
	MLV_draw_text(
		10, 40, 
		"Nombre de fois que l'on a appuyé sur une touche : %i",
		MLV_COLOR_GREEN,
		nb
	);

	//
	// Met à jour la fenêtre
	//
	MLV_actualise_window();
}


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh, il faut, 
// pour la déclaration du main, respecter strictement la syntaxe suivante :
//
int main(int argc, char *argv[]){
	int width = 640, height = 460;    //Taille de la fenêtre
	int nb= 0 ;             // Nombre de fois qu'une touche a été appuyée

	// informations conernant les évènements de typeclavier.
	MLV_Keyboard_modifier mod;
	MLV_Keyboard_button sym;
	MLV_Button_state state;
    
	// Variable contenant le code associé au type d'un évènement.
	MLV_Event event;
	
	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window(
		"medium - 1 - keyboard events", "keyboard events", width, height
	);

	//
	// Met a jour l'affichage
	//
	affichage( nb, width, height );

	
	//
	// On compte le nombre de fois que l'utilisateur a appuyé sur une
	// touche.
	// On s'arrête quand la touche q a été rélachée suite à une combinaison 
	// shift+q.
	//
	do {
		//
		// Récupère un évènement dans la file des évènements
		// non traités.
		//
		event = MLV_get_event( 
			&sym, &mod, NULL, 
			NULL, NULL,
			NULL, NULL, NULL,
			&state
		);

		//
		// Traite l'évènement s'il s'agit d'un évènement clavier
		//
		if( event == MLV_KEY ){
			//
			// Compte le nombre de fois qu'une touche a été
			// préssée.
			//
			if( state == MLV_PRESSED ){
				nb ++;
			}

			//
			// Met à jour l'affichage
			//
			affichage( nb , width, height );
		};
	} while(
		!(
			( sym == MLV_KEYBOARD_k ) &&
			MLV_shift_key_was_pressed( mod ) &&
			( state == MLV_RELEASED )
		) 
	);

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
