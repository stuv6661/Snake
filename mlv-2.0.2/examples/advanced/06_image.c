/**
 * Ce programme montre comment il est possible d'utiliser et d'afficher des
 * images.
 *
 * De nombreux formats d'images sont supportées (png, jpg, bmp).
 *
 * Pour cela, il suffit d'utiliser les fonctions suivantes :
 * 
 *------------------------------------------------------------------------------
 * MLV_load_image : Charge en mémoire une image contenue dans un fichier au 
 *                      format PNG, BMP, JPG, etc ...
 *
 * MLV_Image* MLV_load_image(
 *    const char*    file_image    Chemin d'accès du fichier contenant l'image.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_free_image : Libère la mémoire utilisée par l'image
 *
 * void MLV_free_image(
 *    MLV_Image *    image    image à suprimer de la mémoire
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_resize_image_with_proportions : redimensionne l'image de telle sorte que 
 *                                     les proportions d'origines soient 
 *     respectées et que la hauteur et la largeur de la nouvelle image soient à 
 *     la fois maximales et inférieures ou égales à la hauteur et la largeur 
 *     données en paramètres. 
 *     L'utilisateur peut entrer un entier négatif pour les champs width et 
 *     height. Ces champs ne sont alors pas pris en compte dans le 
 *     redimensionnement de l'image.
 *                                    
 * void MLV_resize_image_with_proportions(
 *    MLV_Image*    image,    image à redimentionner
 *    int           width,    Nouvelle largeur de l'image
 *    int           height    Nouvelle hauteur de l'image
 * );
 *
 *------------------------------------------------------------------------------
 *
 * Il existe de nombreuses fonctions permettant de manipuler les images.
 * Vous trouverez les prototypes de ces fonctions dans le fichier
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
	MLV_Image *image;
	int image_width, image_height;

	//
	// On créé et affiche la fenêtre
	//
	MLV_create_window( "advanced - 6 - image", "image", width, height );

	//
	// On charge en mémoire deux fichiers images.
	//
	image = MLV_load_image( "flower.jpg" );


	//
	// On redimensionne les images de sorte à ce que la taille soit la
	// plus grande comprise dans le cadre widthxheight
	//
	MLV_resize_image_with_proportions( image, width, height);

	//
	// On récupère la nouvelle taille de l'image afin de l'utiliser pour
	// redimensionner la fenêtre.
	//
    MLV_get_image_size( image, &image_width, &image_height );

	//
	// On redimensionne la fenêtre
	//
	MLV_change_window_size( image_width, image_height );

	//
	// On affiche l'image
	//
	MLV_draw_image( image, 0, 0 );

	//
	// Met à jour l'affichage
	//
	MLV_actualise_window();

	//
	// Attend 2 secondes
	//
	MLV_wait_seconds( 60 );

	//
	// Libère l'image qui a été crée
	//
	MLV_free_image( image );

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
