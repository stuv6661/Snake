/**
 *
 * Ce programme montre quelques exemples d'utilisation de la transparence.
 *
 * Nous rapellons que les couleurs sont codées à l'aide de 4 composantes:
 *  R : rouge (red),
 *  G : vert (green),
 *  B : bleu (blue),
 *  A : transparence (alpha),
 * codées chacune sur un octet, c'est à dire par un entier comprit entre 0 et 
 * 256.
 *
 * La transparence joue un role lorsque une image est dessinée à l'écran ou sur 
 * une autre image.
 * Lorsque l'on copie une image, les pixels du résultat final sont obtenus en
 * faisant le barycentre entre le pixel de l'image source avec celui de l'image
 * destination. Les poids des barycentres sont définis par la composante 
 * transparence ( composante alpha ) de l'image source.
 * La transparence de l'image destination reste inchangée.
 *
 * Cela nous donne les formules suivantes:
 *
 * R_dest = (alpha_src/256) * R_src + (1- alpha_src/256) * R_dst
 * V_dest = (alpha_src/256) * V_src + (1- alpha_src/256) * V_dst
 * B_dest = (alpha_src/256) * B_src + (1- alpha_src/256) * B_dst
 * A_dest = A_dest
 * 
 * Ainsi, si l'a composante alpha de l'image source est à 0, 
 * alors la source disparait. Si elle à est 256, alors c'est l'image destination
 * qui disparait.
 *
 * Voici un exiemple avec les couleurs suivantes: 
 *    couleur du pixel source : RGBA( 100,100,100,128 )
 *    couleur du pixel destination : RGBA( 0,10,20,30 )
 *    couleur finale apres copie : RGBA( 50,55,65,30 )
 * Comme la composante alpha est à 128, la couleur finale est donc à moitié
 * celle de l'image source (128/256) et à moitié celle de l'image destination
 * (1-128/256).
 *
 *
 * Fonctions utilisées :
 * 
 *------------------------------------------------------------------------------
 * MLV_set_alpha_on_image : Ajuste les propriétés de transparence de l'image.
 *                       La composante alpja de l'image est remplacée par une
 *                       composante alpha homogene dont la valeur est donnée en
 *                       paramètre.
 *
 * void MLV_set_alpha_on_image(
 *     MLV_Alpha     alpha,     Nouvelle composante alpha de l'image
 *     MLV_Image     *image     Image à modifier
 * );
 *
 *------------------------------------------------------------------------------
 *
 * Il existe de nombreuses fonctions permettant de manipuler les images.
 * Vous trouverez les proptotyes de ces fonctions dans le fichier
 * MLV_image.h.
 *
 * Vous pouvez aussi accéder à ces prototypes et à la documentation de ces
 * fonctions en tapant sur le terminal la commande :
 *     man MLV_image.h
 *
 */

#include <MLV/MLV_all.h>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){
	int width = 640, height = 480;
	MLV_Image *red_image, *blue_image;

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window(
		"advanced - 7 - transparency", "transparency", width, height
	);

	MLV_clear_window( MLV_COLOR_GREEN );

	//
	// Lit un fichier et charge l'image contenu dans le
	// fichier en mémoire.
	//
	blue_image = MLV_load_image( "blue_image.png" );
	red_image = MLV_load_image( "red_image.png" );

	MLV_draw_adapted_text_box(
		100, 40, "avec la composante\nalpha d'origine", 4,
		MLV_COLOR_GREEN,  MLV_COLOR_BLACK, MLV_COLOR_GREEN,
		MLV_TEXT_CENTER
	);

	//
	// Affiche l'image
	//
	MLV_draw_image( blue_image, 47, 113 );
	MLV_draw_image( red_image, 47, 306 );

	//
	// Affiche l'image
	//
	MLV_draw_image( blue_image, 187, 185 );
	MLV_draw_image( red_image, 187, 234 );


	//
	// Suprime la transparence de l'image et la remplace 
	// par une transparence uniforme opaque 
	//
	MLV_set_alpha_on_image( MLV_ALPHA_OPAQUE, red_image );
	MLV_set_alpha_on_image( MLV_ALPHA_OPAQUE, blue_image );

	MLV_draw_adapted_text_box(
		330, 20, "sans la\ncomposante\nalpha", 4,
		MLV_COLOR_GREEN,  MLV_COLOR_BLACK, MLV_COLOR_GREEN,
		MLV_TEXT_CENTER
	);

	//
	// Affiche l'image
	//
	MLV_draw_image( blue_image, 328, 113 );
	MLV_draw_image( red_image, 328, 306 );


	//
	// Suprime la transparence de l'image et la remplace 
	// par une transparence uniforme 
	//
	MLV_set_alpha_on_image( 127, red_image );
	MLV_set_alpha_on_image( 127, blue_image );
	
	MLV_draw_adapted_text_box(
		435, 20, "la composante alpha\nest remplacée par une\ncomposante uniforme", 4,
		MLV_COLOR_GREEN,  MLV_COLOR_BLACK, MLV_COLOR_GREEN,
		MLV_TEXT_CENTER
	);

	//
	// Affiche l'image
	//
	MLV_draw_image( blue_image, 468, 113 );
	MLV_draw_image( red_image, 468, 306 );


	//
	// Met à jour l'affichage
	//
	MLV_actualise_window();

	//
	// Attend 2 secondes
	//
	MLV_wait_seconds( 20 );

	//
	// Libère l'image qui a été crée
	//
	MLV_free_image( blue_image );
	MLV_free_image( red_image );

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
