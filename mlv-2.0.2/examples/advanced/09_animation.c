/**
 *
 * Ce programme créé une fenêtre et affiche Bonjour.
 *
 * Pour cela le programme  utilise les fonctions suivantes : 
 *
 *------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 */

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){
	int width = 640, height = 480;

	MLV_init_audio();
	MLV_create_window( "advanced - 9 animation", "animation", width, height );

	// On charge les données multimédias en mémoire
	const char* file_path_of_creature = "creature.png";
	MLV_Image* creature = MLV_load_image( file_path_of_creature );
	if( ! creature ){
		fprintf(
			stderr, "It was impossible to load the file %s.\n",
			file_path_of_creature
		);
		exit(1);
	}
	const char* file_path_of_sound = "walk.ogg";
	MLV_Sound* sound = MLV_load_sound( file_path_of_sound );
	if( ! sound ){
		fprintf(
			stderr, "It was impossible to load the file %s.\n",
			file_path_of_sound
		);
		exit(1);
	}

	// On construit une animation avec les donnée multimédias
	// précédement chargées.
	MLV_Animation* animation;
	int nb_frames = 6;
	int nb_layers = 1;
	int nb_channels = 1;
	int w = 79, h = 79;

	MLV_Image* images[4];
	images[0] = MLV_copy_partial_image( creature, 0, 0, w, h );
	images[1] = MLV_copy_partial_image( creature, 1*(w+1), 0, w, h );
	images[2] = MLV_copy_partial_image( creature, 2*(w+1), 0, w, h );
	images[3] = MLV_copy_partial_image( creature, 3*(w+1), 0, w, h );

	animation	= MLV_create_animation(
		nb_frames, nb_layers, nb_channels
	);

	int layer = 0;
	MLV_add_frame_in_animation( 
		images+0, &sound, 4, animation
	);
	MLV_add_frame_in_animation(
		images+1, NULL, 4, animation
	);
	MLV_add_frame_in_animation(
		images+2, &sound, 4, animation
	);
	MLV_add_frame_in_animation(
		images+3, NULL, 4, animation
	);

	// Création d'un lecteur d'animation
	MLV_Animation_player* animation_player = MLV_create_animation_player( animation );

	// On lance la lecture de l'animation
	MLV_play_animation_player( animation_player );

	// On active le son
	MLV_turn_on_sound_of_animation_player( animation_player, 0 );
	MLV_change_sound_volume_of_animation_player( animation_player, 0, 0.2 );

	// On fice le nombre d'image par seconde
	MLV_change_frame_rate( 24 );

	int avance = 0;
	int pas = 4;
	MLV_Keyboard_button touche;
	while( 
		MLV_get_event (
			&touche, NULL, NULL,
			NULL, NULL,
			NULL, NULL, NULL,
			NULL
		) == MLV_NONE ||
		touche != MLV_KEYBOARD_ESCAPE
 	){
		MLV_update_animation_player( animation_player );

		MLV_clear_window( MLV_COLOR_BROWN );
		MLV_draw_filled_rectangle(
			width/2,0, width/2, height, MLV_COLOR_YELLOW
		);
		avance += pas;
		if( avance > width-w ){
			MLV_play_revert_animation_player( animation_player );
			pas = -pas;
		}
		if( avance < 0 ){
			MLV_play_animation_player( animation_player );
			pas = -pas;
		}
		int position_y = 20;
		MLV_draw_image_from_animation_player( animation_player, layer, avance, position_y );
		MLV_actualise_window();
		MLV_play_sound_from_animation_player( animation_player, 0 );
		MLV_delay_according_to_frame_rate();
	}

	MLV_free_animation_player( animation_player );

	MLV_free_animation( animation );

	MLV_free_image( images[0] );
	MLV_free_image( images[1] );
	MLV_free_image( images[2] );
	MLV_free_image( images[3] );

	MLV_free_image( creature );

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
