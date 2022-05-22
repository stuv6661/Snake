/**
 * Ce programme explique comment, si elle n'est pas utilisée pour réaliser des 
 * effets de transparence, il est possible d'utiliser la composante alpha d'une 
 * image pour réaliser des zones de selection.
 *
 * Attention, si vous ouvrez les images utilisées par cette démonstration avec
 * un éditeur d'image, vous obtiendrez une image vide.
 * En effet, nous avons détourné la composante alpha pour un autre usage. 
 * Dans notre cas elle varie entre 0 et 4. L'image disparait donc par rapport au
 * fond. Si vous voulez voir l'image dans votre éditeur d'image, vous devez 
 * suprimer la composante alpha.
 *
 * Dans la pratique, vous n'êtes pas obligé d'utiliser la composante alpha pour
 * réaliser une zone de selection. Vous pouvez utiliser plmusieurs images, une 
 * pour l'affichage et une pour définir les zones de selection.
 * Ainsi, vous conservez la composante alpha pour réaliser des effets de 
 * transparence évolués.
 *
 *
 * Pour cela, le programme utilise les fonctions suivantes:
 *
 *------------------------------------------------------------------------------
 * MLV_get_pixel : Renvoie la couleur du pixel présent à une position donnée 
 *                 d'une image donnée.
 *
 *                 Les paramètres red, blue, green et alpha peuvent être égale 
 *                 à NULL. Dans ce cas, ils sont ignorés.
 *
 * void MLV_get_pixel(
 *     MLV_Image*     image,     Image à inspecter.
 *     int            x,         Coordonnée en X de la position du pixel à
 *                               inspecter
 *     int            y,         Coordonnée en Y de la position du pixel à
 *                               inspecter
 *     int*           red,       Composante rouge du pixel
 *     int*           green,     Composante verte du pixel
 *     int*           blue,      Composante vleue du pixel
 *     int*           alpha      Composante alpha (transparence) du pixel
 * );
 *
 *------------------------------------------------------------------------------
 */

#include  <MLV/MLV_all.h>
#define DEBUG(x) fprintf( stderr, "DEBUG : %s - line : %d- file : %s \n", x, __LINE__, __FILE__ );

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){

	MLV_Event event_type=MLV_NONE;
	MLV_Keyboard_button touche;
	int width=640,height=480;
	int red;
	int x,y;
	int w, h;
	int id_country;
	MLV_Image *map, *map_display, *country_layer;

	//
	// On associe à chaque valeur de la composante rouge du fichier map.png,
	// un nom de pays.
	//
	#define NB_COUNTRY 5
	int nb_country = NB_COUNTRY;
	const char* id_to_country[ NB_COUNTRY+1 ][ 2 ] = {
		{ "", "" },
		{ "Espagne", "spain.png" },
		{ "France", "france.png" },
		{ "Grèce", "greece.png" },
		{ "Italie", "italy.png" },
		{ "Portugal", "portugal.png" } 
	};

	//
	// On créé la fenêtre
	//
	MLV_create_window(
		"advanced - 8 - zone click", "zone click", width, height
	);

	//
	// On charge en mémoire deux fois la même image:
	// La version chargée dans la variable map va servir à connaitre la position
	// des différents pays en utilsant la valeur de la composante rouge.
	// La version chargée dans la variable map_display va servir pour
	// l'affichage. Pour cela, on modifie la composante rouge de l'image de
	// façon qu'elle soit homogènement opaque.
	//
	map_display = MLV_load_image("map.png");

	//
	// On réajuste la taille de la fenêtre pour qu'elle soit adaptée à celle de
	// l'image.
	//
	MLV_get_image_size( map_display, &width, &height );
	MLV_change_window_size( width, height );

	map = MLV_create_image( width, height );
	MLV_draw_filled_rectangle_on_image(
		0, 0, width, height, MLV_rgba(0,0,0,MLV_ALPHA_OPAQUE), map
	);

	// On créé une carte contenant tous les pays
	for( id_country=1; id_country < nb_country+1; id_country++ ){
		const char* file_name = id_to_country[id_country][1];
		country_layer = MLV_load_image( file_name );
		if( ! country_layer ){
			fprintf( stderr, "Impossible de lire le fichier %s", file_name );
			exit(0);
		}
		for( w = 0; w < width; w++ ){
			for( h = 0; h < height; h++ ){
				MLV_get_pixel_on_image(
					country_layer, w, h, &red, NULL, NULL, NULL 
				);
				if( red != 0 ){
					MLV_set_pixel_on_image(
						w, h, MLV_rgba( 
							id_country, id_country, id_country,
							MLV_ALPHA_OPAQUE 
						), map 
					);
				}
			}
		}
		MLV_free_image( country_layer );
	} 
	
	//
	// Initialisation de l'affichage
	//
	MLV_draw_image( map_display, 0, 0 );
	MLV_actualise_window();

	//
	// Dès que l'utilisateur clique sur l'image, on affiche le nom du pays
	// correspondant à la zone cliquée.
	// Si l'utilisateur appuie sur une touche du clavier, on quitte
	//
	while( event_type!=MLV_KEY || touche != MLV_KEYBOARD_ESCAPE ){
		event_type = MLV_wait_keyboard_or_mouse( &touche, NULL, NULL, &x, &y );
		if( event_type == MLV_MOUSE_BUTTON ){
			MLV_draw_image( map_display, 0, 0 );
			MLV_get_pixel_on_image( map, x, y, &id_country, NULL, NULL, NULL );
			if( 1 <= id_country && id_country <= nb_country ){
				MLV_draw_text(
					x, y, id_to_country[id_country][0], MLV_COLOR_BLACK
				);
			}
			MLV_actualise_window();
		}
	}

	//
	// On libère l'espace mémoire allouée aux images
	//
	MLV_free_image( map );
	MLV_free_image( map_display );

	//
	// On ferme la fenêtre
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
