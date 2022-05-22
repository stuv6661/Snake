/**
 * Ce programme montre comment il est possible d'utiliser deux types de boîte de
 * texte.
 *
 * La première est une boîte dont la taille s'adapte à celle du texte.
 * Cette boîte se créé à l'aide de la fonction MLV_draw_adapted_text_box.
 *
 * La deuxième est une boîte dont la taille est fixée par l'utilisateur.
 * Cette boîte s'obtient à l'aide de la fonction MLV_draw_text_box.
 *
 *------------------------------------------------------------------------------
 * MLV_draw_adapted_text_box : Dessine une boîte contenant du texte.
 *                             La taille de la boîte dessinée s'adapte à la
 *                             taille du texte.
 *                             Les différentes couleurs de la boîte et du texte,
 *                             ainsi que la taille des interlignes sont
 *                             paramétrables.
 *
 *                             Il est possible de préciser la justiifcation du
 *                             texte à l'aide du champs : text_justification
 *                             
 * void MLV_draw_adapted_text_box(
 *     int            x,                 Coordonnée en X de la position du coin
 *                                       Nord-Ouest de la boîte
 *     int            y,                 Coordonnée en X de la position du coin
 *                                       Nord-Ouest de la boîte
 *     const char*    message,           Texte à afficher
 *     int            sizeInterligne,    Taille de l'interligne
 *     MLV_Color      borderColor,       Couleur des bordures
 *     MLV_Color      textColor,         Couleur du texte
 *     MLV_Color      backgroundColor,   Couleur du fond de la boîte
 *     MLV_Text_justification    text_justification,    Justification du texte.
 *                                                      Valeurs possibles : 
 *                                                          MLV_TEXT_CENTER
 *                                                          MLV_TEXT_LEFT
 *                                                          MLV_TEXT_RIGHT 
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_draw_text_box : Dessine une boîte de taille donnée par l'utilisateur et 
 *                     contenant un texte donné par l'utilisateur.
 *
 *                     Les différentes couleurs de la boîte et du texte,
 *                     ainsi que la taille de l'interligne sont paramétrables.
 *
 *                     Il est possible de préciser la justification du
 *                     texte contenu dans la boîte.
 *
 *                     De même , il est possible de préciser la position du 
 *                     texte à l'intérieur de la boîte.
 *                     
 *                     Cette fonction ne remet pas en forme le texte. Cela 
 *                     veux dire que si le texte est trop grand alors il 
 *                     depassera de la boîte et les parties qui depassent ne 
 *                     seront pas affichées.
 *
 * void MLV_draw_text_box( 
 *    int            x,                  Coordonnée en X de la position du coin
 *                                       Nord-Ouest de la boîte
 *    int            y,                  Coordonnée en Y de la position du coin
 *                                       Nord-Ouest de la boîte
 *    int            width,              Hauteur de la boîte
 *    int            height,             Largeur de la boîte
 *    const char*    message,            Texte à afficher
 *    int            sizeInterligne,     Taille de l'interligne
 *    MLV_Color      borderColor,        Couleur des bordures
 *    MLV_Color      textColor,          Couleur du texte
 *    MLV_Color      backgroundColor,    Couleur du fond de la boîte.
 *    MLV_Text_justification     text_justification,    Justification du texte.
 *                                                      Valeurs possibles : 
 *                                                          MLV_TEXT_CENTER
 *                                                          MLV_TEXT_LEFT
 *                                                          MLV_TEXT_RIGHT 
 *    MLV_Horizontal_position    horizontal_position,   Position horizontale du 
 *                                                      texte dans la boîte.
 *                                                      Valeurs possibles : 
 *                                                         MLV_HORIZONTAL_CENTER
 *                                                         MLV_HORIZONTAL_LEFT
 *                                                         MLV_HORIZONTAL_RIGHT
 *    MLV_Vertical_position      vertical_position      Position verticale du 
 *                                                      texte dans la boîte.
 *                                                      Valeurs possibles : 
 *                                                          MLV_VERTICAL_CENTER
 *                                                          MLV_VERTICAL_TOP
 *                                                          MLV_VERTICAL_BOTTOM 
 * );
 *
 *------------------------------------------------------------------------------
 *
 * Il existe d'autres fonctions pour mettre en forme du texte. 
 * Vous trouverez une documentation de ces fonctions en tapant sur le terminal 
 * la commande suivante :
 *
 * man MLV_text.h
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
	// Déclaration et initialisation de la variable qui codera
	// la distance entre deux lignes dans un texte
	//
	int taille_interlinge = 9;

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window(
		"beginner - 4 - texts and boxes", "texts and boxes", 640, 480
	);

	//
	// Affiche du texte sans boîte
	//
	MLV_draw_text(
		10, 10, 
		"Simple texte. Avec draw_text() vous ne devez pas utiliser de retour à la ligne.",
		MLV_COLOR_MAGENTA
	);


	//
	// Affiche du texte dans une boîte dont la taille s'adapte au texte
	// Le texte est justifié au centre dans la boîte
	//
	MLV_draw_adapted_text_box(
		10,50,
		"Exemple de boîte dont le contour\ns'adapte\nà la taille du texte.",
		taille_interlinge,
		MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		MLV_TEXT_CENTER
	);

	//
	// Affiche du texte dans une boîte dont la taille s'adapte au texte
	// Le texte est justifié à gauche dans la boîte
	//
	MLV_draw_adapted_text_box(
		10,150,
		"Même chose,\nmais le texte\nest justifié à gauche\nde la fenêtre.",
		taille_interlinge,
		MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		MLV_TEXT_LEFT
	);

	//
	// Affiche du texte dans une boîte de taille fixe.
	// Le texte est justifié à gauche, horizontalement et verticalement
	// centré.
	//
	MLV_draw_text_box(
		10,280,
		600,150,
		"Cette fois-ci,\nla taille de la boîte ne correspond pas à l'espace couvert par le texte.\nLa boîte est ici plus grande.",
		taille_interlinge,
		MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		MLV_TEXT_LEFT,
		MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER
	);

	//
	// Met à jour l'affichage de la fenêtre.
	//
	MLV_actualise_window();

	//
	// Attend 15 seconde avant la fin du programme.
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
