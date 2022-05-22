/**
 *
 * Ce programme montre comment il est possible d'ajouter un minuteur lorsque 
 * l'utilisateur est invité à cliquer ou appuyer sur une touche du clavier
 *
 *------------------------------------------------------------------------------
 * MLV_wait_mouse_or_seconds: Suspend l'exécution jusqu'à ce que l'utilisateur 
 *                            clique sur le bouton gauche de la souris où 
 *                            jusqu'à ce qu'un nombre de seconds, passé en 
 *     paramètres, se soient écoulées.
 *
 *     Au moment où l'utilisateur clique, la fonction retourne les coordonnées 
 *     de la position de la souris dans la fenêtre.
 *
 *     Cette fonction renvoie 1 si l'utilisateur cliqué avec le bouton gauche 
 *     de la souris, et 0 si le temps s'est écoulé.
 *
 * int MLV_wait_mouse_or_seconds(
 *     int *    x,         Coordonnée en X de la position de la souris dans la 
 *                         fenêtre.
 *     int *    y,         Coordonnée en Y de la position de la souris dans la 
 *                         fenêtre.
 *     int      seconds    Le nombre de second à attendre avant de quitter la 
 *                         fonction.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_wait_keyboard_or_seconds : Suspend l'exécution jusqu'à ce que 
 *                                l'utilisateur appuie sur une touche du  
 *                                clavier ou jusq'à ce q'un nombre de secondes 
 *     passées en paramètres soient écoulées.
 * 
 *     Lorsque l'utilisateur appuie sur une touche, la fonction retourne trois 
 *     valeurs ( sym, mod et unicode ) correspondant respectivement au code de 
 *     la touche, au mode dans lequel se trouve le clavier (majuscule etc ...) 
 *     et au caractère unicode correspondnant obtenu en combinant le mode du 
 *     clavier et le code de la touche appuyée.
 *
 *     La fonction accepte des valeurs nulles pour les pointeurs sym, mod et 
 *     unicode.
 *     Dans ce cas la fonction ignore les champs en questions.
 *
 *     Cette fonction renvoie 1 si l'utilisateur à utiliser le calvier, 0 si le 
 *     temps s'est écoulé.
 *
 * int MLV_wait_keyboard_or_seconds(
 *     int*    sym,        Code de la touche
 *     int*    mod,        Mode dans lequel se trouve le clavier
 *     int*    unicode,    Caractère codé en unicode de la lettre obtenue en 
 *                         combinant le code et le mode précédent
 *     int     seconds     Le nombre de secondes à attendre
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_wait_keyboard_or_mouse : Suspend l'exécution jusqu'à ce que l'utilisateur
 *                              appuie sur une touche du clavier ou sur le 
 *                              bouton gauche de la souris.
 *
 *     Cette fonction renvoie un entier codant le type de l'évènement qui a été 
 *     récupéré ( clavier ou souris )
 *
 *     Lorsque l'utilisateur appuie sur une touche, la fonction retourne trois 
 *     valeurs ( sym, mod et unicode ) correspondant respectivement au code de 
 *     la touche, au mode dans lequel se trouve le clavier (majuscule etc ...) 
 *     et au caractère unicode correspondnant obtenu en combinant le mode du 
 *     clavier et le code de la touche appuyée.
 *
 *     Lorsque l'utilisateur appuie sur le bouton gauche de la souris, la 
 *     fonction remplit les parametres correspondant aux coordonnées en X et Y 
 *     de la position de la souris sur l'écran. 
 *
 *     Cette fonction renvoie un entier codant le type de l'évènement qui a été
 *     récupéré ( MLV_KEY ou MLV_MOUSE_BUTTON )
 *
 * MLV_Event MLV_wait_keyboard_or_mouse(
 *     int*    sym,        Code de la touche qui a été appuyée ou relachée. 
 *                         La valeur de ce champs est définie par l'énumération:
 *                         MLV_Keyboard_button.
 *     int*    mo,         Mode dans lequel se trouve le clavier lorsqu'une 
 *                         touche est appuyée ou relachée. La valeur de ce 
 *                         champs est définie par l'énumération : 
 *                             MLV_Keyboard_modifier.
 *     int*    unicode,    unicode Caractère codé en unicode de la lettre 
 *                         obtenue en combinant le code et le mode précédent
 *     int*    mouse_x,    Coordonnée en X de la position de la souris
 *     int*    mouse_y     Coordonnée en Y de la position de la souris
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_wait_keyboard_or_mouse_or_seconds : Suspend l'exécution jusqu'à ce que 
 *                                         l'utilisateur appuie sur une touche
 *                                         du clavier, sur le bouton gauche de
 *    la souris ou qu'un certain nombre de secondes passéesn en paramètres se 
 *    soient écoulées.
 *
 *    Cette fonction renvoie un entier codant le type de l'évènement qui a été 
 *    récupéré ( clavier ou souris )
 *
 *     Lorsque l'utilisateur appuie sur une touche, la fonction retourne trois 
 *     valeurs ( sym, mod et unicode ) correspondant respectivement au code de 
 *     la touche, au mode dans lequel se trouve le clavier (majuscule etc ...) 
 *     et au caractère unicode correspondnant obtenu en combinant le mode du 
 *     clavier et le code de la touche appuyée.
 *
 *     Lorsque l'utilisateur appuie sur le bouton gauche de la souris, la 
 *     fonction remplit les parametres correspondant aux coordonnées en X et Y 
 *     de la position de la souris sur l'écran.
 *
 *     Cette fonction renvoie un entier codant le type de l'évènement qui a été
 *     récupéré ( MLV_KEY ou MLV_MOUSE_BUTTON ), ou MLV_NONE si le temps s'est 
 *     écoulé.
 *
 * MLV_Event MLV_wait_keyboard_or_mouse_or_seconds(
 *     int*    sym,        Code de la touche qui a été appuyée ou relachée. 
 *                         La valeur de ce champs est définie par l'énumération:
 *                         MLV_Keyboard_button.
 *     int*    mo,         Mode dans lequel se trouve le clavier lorsqu'une 
 *                         touche est appuyée ou relachée. La valeur de ce 
 *                         champs est définie par l'énumération : 
 *                             MLV_Keyboard_modifier.
 *     int*    unicode,    unicode Caractère codé en unicode de la lettre 
 *                         obtenue en combinant le code et le mode précédent
 *     int*    mouse_x,    Coordonnée en X de la position de la souris
 *     int*    mouse_y     Coordonnée en Y de la position de la souris
 *     int     seconds     Le nombre de secondes à attendre
 * );
 *
 *------------------------------------------------------------------------------
 */

#include <MLV/MLV_all.h>

//
// Cette fonction réinitialise l'acran puis affiche un texte donnée en 
// parametre à l'écran.
//
void afficher_texte( char* texte ){
	int size_interline = 9;
	MLV_clear_window( MLV_COLOR_BLACK );
	MLV_draw_adapted_text_box (
		10, 10, texte, size_interline,
		MLV_COLOR_BLACK, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
        MLV_TEXT_LEFT
	);
	MLV_actualise_window();
}


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){

	MLV_Keyboard_button sym;
	MLV_Keyboard_modifier mod;
	int unicode, mouse_x, mouse_y;
	int temps_attente = 5;

	// taille de l'écran
	int width = 640, height = 480;

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window(
		"beginner - 8 - mouse keyboard timer", "mouse keyboard timer",
		width, height
	);

	//
	// Tant que le temps imparti n'est pas écoulé, l'utilisateur est invité à 
	// appuyer sur une touche du clavier
	//
	afficher_texte(
		"Vous passerez à l'écran suivant en:\n    - appuyant sur une touche du clavier\n    - attendant quelques secondes."
	);
	MLV_wait_keyboard_or_seconds( &sym, &mod, &unicode, temps_attente );

	//
	// Tant que le temps imparti n'est pas écoulé, l'utilisateur est invité à 
	// cliquer sur le bouton gauche de la souris
	//
	afficher_texte(
		"Vous passerez à l'écran suivant en:\n    - cliquant sur la souris\n    - attendant quelques secondes."
	);
	MLV_wait_mouse_or_seconds( &mouse_x, &mouse_y, temps_attente );

	//
	// L'utilisateur est invité à appuyer sur une touche du clavier ou à 
    // cliquer sur le bouton gauche de la souris.
	//
	afficher_texte(
		"Vous passerez à l'écran suivant en:\n    - appuyant sur une touche du clavier\n    - cliquant sur la souris."
	);
	MLV_wait_keyboard_or_mouse( &sym, &mod, &unicode, &mouse_x, &mouse_y );
	
	//
	// Tant que le temps impart n'est pas écoulé, l'utilisateur est invité à 
    // appuyer sur une touche du clavier ou à cliquer sur le bouton gauche de 
	// la souris.
	//
	afficher_texte(
		"Vous passerez à l'écran suivant en:\n    - appuyant sur une touche du clavier\n    - cliquant sur la souris\n    - attendant quelques secondes."
	);
	MLV_wait_keyboard_or_mouse_or_seconds(
		&sym, &mod, &unicode, &mouse_x, &mouse_y, temps_attente
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
