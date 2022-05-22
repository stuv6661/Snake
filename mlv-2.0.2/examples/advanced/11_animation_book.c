/**
 *
 * Ce programme charge un enseble d'animation a partir d'un fichier de 
 * configuration au format xml et d'un certain nombre d'image donnée.
 *
 *------------------------------------------------------------------------------
 * MLV_load_animation_book: Charge en memoire un livre contenant une multitude
 *                          d'animations.
 *
 * Cette fonction renvoie l'adresse de la sructure de données contenant toutes 
 * les animations.
 *
 * MLV_Animation_book* MLV_load_animation_book(
 *      const char*     xml_file,          Fichiers xml.
 *      const char*     image_directory    image_directory Le dossier ou se 
 *                                         trouve toutes les images du livre 
 *                           d'animation. Si NULL est passe en parametre, alors 
 *                           le programme cherche dans le repertoire du fichier
 *                           de configuration du livre  d'animation.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_free_animation_book: Libère la memoire contenue par le livre d'animation.
 *
 * void MLV_free_animation_book(
 *     MLV_Animation_book*     animation_book     Le livre d'animation.
 * );
 *
 *
 *------------------------------------------------------------------------------
 * MLV_get_animation_from_name: Renvoie une animation donnée contenue dans le 
 *                              livre d'animation.
 *
 * Renvoie la séquence d'animation.
 *
 * MLV_Animation_sequence* MLV_get_animation_from_name(
 *     MLV_Animation_book*     animation_book,     animation_book Le livre
 *                                                 d'animation.
 *     const char*             name                Le nom de l'animation
 * );
 *
 *------------------------------------------------------------------------------
 *
 * Pour plus d'information ou de fonction tapez :
 *
 *     man MLV_animation.h
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
	
	MLV_Keyboard_button touche = MLV_KEYBOARD_NONE;
	int width = 640, height = 480;
	int x_walk = 0, y = 0, x_run = 100;

	MLV_init_audio();
	MLV_create_window( "advanced - 9 animation", "animation", width, height );

	MLV_Animation_book *book;
	MLV_Animation *run_animation, *walk_animation;
	MLV_Animation_player* run_animation_player, *walk_animation_player;

	const char* book_file_path = "animation_book.xml";
	book = MLV_load_animation_book( book_file_path, NULL, NULL );
	if( ! book ){
		fprintf( stderr, "Failed to load the file %s\n", book_file_path );
		exit(1);
	}

	walk_animation = MLV_get_animation_from_name( book, "walk" );
	run_animation = MLV_get_animation_from_name( book, "run" );

	walk_animation_player = MLV_create_animation_player( walk_animation );
	run_animation_player = MLV_create_animation_player( run_animation );

	MLV_play_animation_player( walk_animation_player );
	MLV_turn_off_sound_of_animation_player( walk_animation_player, 0 );
	MLV_change_sound_volume_of_animation_player( walk_animation_player, 0, 0.2 );

	MLV_play_animation_player( run_animation_player );
	MLV_turn_off_sound_of_animation_player( run_animation_player, 0 );
	MLV_change_sound_volume_of_animation_player( run_animation_player, 0, 0.2 );

	MLV_change_frame_rate( 24 );

	int sound = 0;
	while( 
		MLV_get_event (
			&touche, NULL, NULL,
			NULL, NULL,
			NULL, NULL, NULL,
			NULL
		) == MLV_NONE ||
		touche != MLV_KEYBOARD_ESCAPE
 	){
		MLV_update_animation_player( run_animation_player );
		MLV_update_animation_player( walk_animation_player );


		MLV_clear_window( MLV_COLOR_BROWN );
		MLV_draw_text( 
			20,150, 
			"Laissez la touche k appuyee pour entendre le son des animations.", 
			MLV_COLOR_BLACK
		);
		MLV_draw_image_from_animation_player(	run_animation_player, 0, x_run, y );
		MLV_draw_image_from_animation_player( walk_animation_player, 0, x_walk, y );
		MLV_actualise_window();
		MLV_play_sound_from_animation_player( run_animation_player, 0 );
		MLV_play_sound_from_animation_player( walk_animation_player, 0 );

		if( touche==MLV_KEYBOARD_k ){
			if( sound ){
				MLV_turn_off_sound_of_animation_player( walk_animation_player, 0 );
				MLV_turn_off_sound_of_animation_player( run_animation_player, 0 );
				sound = 0;
			}else{
				MLV_turn_on_sound_of_animation_player( walk_animation_player, 0 );
				MLV_turn_on_sound_of_animation_player( run_animation_player, 0 );
				sound = 1;
			}
			touche = MLV_KEYBOARD_NONE;
		}

		MLV_delay_according_to_frame_rate();
	}

	MLV_stop_all_sounds();

	MLV_free_animation_player( walk_animation_player );
	MLV_free_animation_player( run_animation_player );
	MLV_free_animation_book( book );

	MLV_free_window();
	MLV_free_audio();

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
