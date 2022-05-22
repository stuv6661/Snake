/**
 *
 * Ce programme explique comment utiliser de nouvelles polices de caractères 
 * pour afficher du texte.
 *
 * La police de caractère par default est DejaVuSerif-Bold. Il n'est pas 
 * possible de changer ou supprimer la police par default mais, les fonctions 
 * suivantes vous explique comment charger une nouvelle police et comment 
 * l'utiliser pour afficher du texte avec cette dernière.
 *
 *------------------------------------------------------------------------------
 * MLV_Font* MLV_load_font : Charge une police de caractères en mémoire. Cette
 *                           police est chargée à partir du chemin d'accés du 
 *                           fichier contenant la police et de la taille de la
 *                           police souhaitée.
 *
 * MLV_Font* MLV_load_font(
 *    const char*    file_font,    Chemin d'accès du fichier contenant la police
 *                                 de caractères  
 *    int            size          Taille de la police de caractères
 * );
 *
 *------------------------------------------------------------------------------
 * void MLV_free_font : Ferme une police de caractères qui a précédement été 
 *                       mis en mémoire.
 *
 * void MLV_free_font(
 *    MLV_Font*    font    La police de caractères à fermer.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_draw_text_with_font : Imprime un texte donné à une position, une police 
 *                           de caractères et une couleur données.
 *
 * void MLV_draw_text_with_font(
 *     int             x,       Coordonnée en X de la position du coin 
 *                              Nord-Ouest de la boîte
 *     int             y,       Coordonnée en Y de la position du coin
 *                              Nord-Ouest de la boîte
 *     const char *    text,    texte à afficher
 *     MLV_Font*       font,    police de caractères à utiliser pour afficher le
 *                              texte
 *     MLV_Color       color    couleur du tracé
 * );
 *
 *------------------------------------------------------------------------------
 */



#include <MLV/MLV_all.h>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// Il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[]){
	//
	// Créé et affiche la fenetre
	//
	MLV_create_window( "advanced - 2 - font", "font", 640, 480 );
	
	//
	// Charge une font en mémoire
	//
	MLV_Font* font = MLV_load_font( "Garuda-Oblique.ttf" , 20 );

	//
	// Affiche un texte avec la font qui vient d'être chargée
	//
	MLV_draw_text_with_font(
		10, 10,
		"Le texte est écrit avec la font Garuda-Oblique.", 
		font, MLV_COLOR_GREEN
	);

	//
	// Met à jour l'affichage de la fenêtre
	//
	MLV_actualise_window();

	//
	// Attend 5 seconde avant la fin du programme.
	//
	MLV_wait_seconds( 5 );


	//
	// Ferme proprement la font qui a été chargée en mémoire durant le 
	// programme.
	//
	MLV_free_font( font );

	//
	// Ferme la fenetre
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
