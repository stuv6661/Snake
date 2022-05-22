/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012 Adrien Boussicault, Marc Zipstein
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

#include <stdio.h>

#include "platform.h"

#ifdef OS_WINDOWS
extern int asprintf (char **, const char *, ...);
#endif

#include "MLV_animation.h"
#include "MLV_path.h"

#include "warning_error.h"
#include "memory_management.h"
#include "tree_map.h"

#include "MLV_xml.h"

////////////////////////////////////////////////
//    Animation structures
///////////////////////////////////////////////

typedef struct {
 	MLV_Image** images; // Layer of images
 	MLV_Sound** sounds; // Layer of images
	unsigned int delay;
} Animation_frame;

struct _MLV_Animation {
	unsigned int max_frames;
	unsigned int nb_frames;
	unsigned int nb_layers;
	unsigned int nb_channels;
	Animation_frame * frames;
};

struct _MLV_Animation_player {
	int* state_sound;
	int* sounds_are_being_played;
	float* volume;
	const MLV_Animation * animation;
	enum { STOP, PLAY, PLAY_REVERT } status;
	unsigned int current_frame;
	unsigned int counter;
};


////////////////////////////////////////////////
//    Animation data
///////////////////////////////////////////////

MLV_Animation* MLV_create_animation(
	unsigned int max_frames, unsigned int nb_layers, unsigned int nb_channels
){
	MLV_Animation* result = MLV_MALLOC( 1, MLV_Animation );
	result->nb_frames = 0;
	result->max_frames = max_frames;
	result->nb_layers = nb_layers;
	result->nb_channels = nb_channels;
	result->frames = MLV_MALLOC( max_frames, Animation_frame );
	int i,j;
	for( i=0; i<max_frames; i++ ){
		if( nb_layers>0 ){
			result->frames[i].images = MLV_MALLOC( nb_layers, MLV_Image* );
			for( j=0; j<nb_layers; j++ ){
				result->frames[i].images[j] = NULL;
			}
		}else{
			result->frames[i].images = NULL;
		}
		if( nb_channels>0 ){
			result->frames[i].sounds = MLV_MALLOC( nb_channels, MLV_Sound* );
			for( j=0; j<nb_channels; j++ ){
				result->frames[i].sounds[j] = NULL;
			}
		}else{
			result->frames[i].sounds = NULL;
		}
	}
	return result;
}

void MLV_free_animation( MLV_Animation* animation ){
	int i;
	for( i=0; i<animation->nb_frames; i++ ){
		MLV_FREE( animation->frames[i].images, MLV_Image* );
		MLV_FREE( animation->frames[i].sounds, MLV_Image* );
	}
	MLV_FREE( animation->frames, Animation_frame );
	MLV_FREE( animation, MLV_Animation );
}

void user_is_modifying_animation(
	MLV_Animation* animation, unsigned int position
){
	if( position < animation->max_frames ){
		if( position >= animation->nb_frames ){
			animation->nb_frames = position+1;
		}
	}else{
		char* text;
		int error = asprintf(
			&text,
			"Tou can-t add or modify an image at the position %d, you have created an animation with only %d images.", 
			position, animation->max_frames 
		);
		if( error==-1){
			ERROR_FULL("Allocation memoy problem.");
		}
		ERROR( text );
		MLV_FREE(text, char);
	}
}

void MLV_change_frame_in_animation(
	MLV_Image** array_of_images, MLV_Sound** array_of_sounds, unsigned int delay,
	MLV_Animation* animation, unsigned int position
){
	user_is_modifying_animation( animation, position );
	if( array_of_images ){
		int layer;
		for( layer=0; layer<animation->nb_layers; layer ++){
			animation->frames[
				position
			].images[layer] = array_of_images[layer];
		}
	}
	if( array_of_sounds ){
		int channel;
		for( channel=0; channel<animation->nb_channels; channel++ ){
			animation->frames[
				position
			].sounds[channel] = array_of_sounds[channel];
		}
	}
	animation->frames[position].delay = delay;
}

void MLV_add_frame_in_animation(
	MLV_Image** array_of_images, MLV_Sound** array_of_sounds, unsigned int delay,
	MLV_Animation* animation
){
	MLV_change_frame_in_animation(
		array_of_images, array_of_sounds, delay, animation, 
		animation->nb_frames
	);
}

void MLV_change_frame_image_in_animation(
	MLV_Image* image, MLV_Animation* animation,
	unsigned int position, unsigned int layer
){
	user_is_modifying_animation( animation, position );
	animation->frames[position].images[layer] = image;
}

void MLV_change_frame_sound_in_animation(
	MLV_Sound* sound, MLV_Animation* animation,
	unsigned int position, unsigned int channel
){
	user_is_modifying_animation( animation, position );
	animation->frames[position].sounds[channel] = sound;
}

void MLV_change_frame_delay_in_animation(
	unsigned int delay, MLV_Animation* animation,
	unsigned int position
){
	user_is_modifying_animation( animation, position );
	animation->frames[position].delay = delay;
}

void MLV_get_frame_from_animation(
	MLV_Animation* animation, unsigned int position, unsigned int layer, 
	MLV_Image** image, unsigned int* delay
){
	TODO
}

int MLV_get_frame_delay_from_animation(
	MLV_Animation* animation, unsigned int position
){
	return animation->frames[position].delay;
}

MLV_Image* MLV_get_frame_image_from_animation(
	MLV_Animation* animation, unsigned int position,
	unsigned int layer
){
	return animation->frames[position].images[layer];
}


////////////////////////////////////////////////
//    Animation engine
///////////////////////////////////////////////

MLV_Animation_player* MLV_create_animation_player(
	MLV_Animation* animation
){
	int nb_channels = animation->nb_channels;
	MLV_Animation_player* result = MLV_MALLOC( 1, MLV_Animation_player );
	if( nb_channels>0 ){
		result->volume = MLV_MALLOC( nb_channels, float );
		result->state_sound = MLV_MALLOC( nb_channels, int );
		result->sounds_are_being_played = MLV_MALLOC( nb_channels, int );
		int channel;
		for( channel=0; channel<nb_channels; channel++ ){
			result->volume[channel]=0;
			result->state_sound[channel] = 0;
			result->sounds_are_being_played[channel] = 0;
		}
	}else{
		result->volume = NULL;
		result->state_sound = NULL;
		result->sounds_are_being_played = NULL;
	}
	result->animation = animation;
	MLV_rewind_animation_player( result );
	return result;
}
void MLV_free_animation_player( MLV_Animation_player* animation_player ){
	MLV_FREE( animation_player->volume, float );
	MLV_FREE( animation_player->state_sound, int );
	MLV_FREE( animation_player->sounds_are_being_played, int );
	MLV_FREE( animation_player, MLV_Animation_player );
}

void MLV_play_animation_player( MLV_Animation_player* animation_player ){
	animation_player->status = PLAY;
}
void MLV_play_revert_animation_player( MLV_Animation_player* animation_player ){
	animation_player->status = PLAY_REVERT;
}
void MLV_stop_animation_player( MLV_Animation_player* animation_player ){
	animation_player->status = STOP;
}
void MLV_rewind_animation_player( MLV_Animation_player* animation_player ){
	animation_player->current_frame = 0;
	animation_player->counter = 0;
	MLV_stop_animation_player( animation_player );
}
void MLV_next_frame( MLV_Animation_player* animation_player ){
	/* Retour à la frame 0 si nous sommes à la dernière */
	if( 
		++animation_player->current_frame == 
			animation_player->animation->nb_frames
	){
		animation_player->current_frame = 0;
	}
   animation_player->counter = 0;
}
void MLV_previous_frame(
	MLV_Animation_player* animation_player
){
	/* Retour à la frame 0 si nous sommes à la dernière */
	if ( --animation_player->current_frame == -1 ){
		animation_player->current_frame = 
			animation_player->animation->nb_frames-1;
	}
   animation_player->counter = 0;
}

void MLV_update_animation_player( MLV_Animation_player* animation_player ){
	const Animation_frame * frame;

	if( animation_player->status == STOP ) return;

	frame = &animation_player->animation->frames[
		animation_player->current_frame
	];

	if (frame->delay == 0) return;

	// Passage à la frame suivante
	if( ++animation_player->counter == frame->delay ){
		switch( animation_player->status ){
			case PLAY:
					MLV_next_frame(animation_player);
				break;
			case PLAY_REVERT:
					MLV_previous_frame(animation_player);
				break;
			default:
				return;
		}
		// Remise à 0 de l'état des sons qui ont déjà été joués.
		int channel;
		if( animation_player->sounds_are_being_played ){
			for(
				channel=0; channel < animation_player->animation->nb_channels;
				channel++
			){
				animation_player->sounds_are_being_played[channel] = 0;
			}
		}
	}
}


void MLV_change_sound_volume_of_animation_player(
	MLV_Animation_player* animation_player, unsigned int channel, float volume
){
	animation_player->volume[channel]=volume;
}


void MLV_turn_off_sound_of_animation_player(
	MLV_Animation_player* animation_player, unsigned int channel
){
	animation_player->state_sound[channel]=0;
}

void MLV_turn_on_sound_of_animation_player(
	MLV_Animation_player* animation_player, unsigned int channel
){
	animation_player->state_sound[channel]=1;
}


////////////////////////////////////////////////
//    Drawing animation
///////////////////////////////////////////////

void MLV_draw_image_from_animation_player(
	MLV_Animation_player* animation_player, unsigned int layer,
	int x, int y
){
	MLV_draw_image( 
		animation_player->animation->frames[
			animation_player->current_frame
		].images[layer],
		x,y
	);
}

void MLV_draw_image_from_animation_player_on_image(
	MLV_Animation_player* animation_player, unsigned int layer,
	MLV_Image* image,
	int x, int y
){
	MLV_draw_image_on_image( 
		animation_player->animation->frames[
			animation_player->current_frame
		].images[layer],
		image,
		x,y
	);
}

void MLV_draw_partial_image_from_animation_player_on_image(
	MLV_Animation_player* animation_player, unsigned int layer,
	int source_x, int source_y, int source_width, int source_height,
	MLV_Image* image,
	int x, int y
){
	MLV_draw_partial_image_on_image(
		animation_player->animation->frames[
			animation_player->current_frame
		].images[layer],
		source_x, source_y, source_width, source_height,
		image,
		x, y
	);
}

void MLV_draw_partial_image_from_animation_player(
	MLV_Animation_player* animation_player, unsigned int layer,
	int source_x, int source_y, int source_width, int source_height,
	MLV_Image* image,
	int x, int y
){
	MLV_draw_partial_image(
		animation_player->animation->frames[
			animation_player->current_frame
		].images[layer],
		source_x, source_y, source_width, source_height,
		x, y
	);
}

////////////////////////////////////////////////
//    Playing sounds of animation
///////////////////////////////////////////////

void MLV_play_sound_from_animation_player(
	MLV_Animation_player* animation_player, unsigned int channel
){
	const Animation_frame* frame = &animation_player->animation->frames[
		animation_player->current_frame
	];
	if(
		animation_player->sounds_are_being_played &&
		! animation_player->sounds_are_being_played[channel]
	){
		MLV_Sound* sound = frame->sounds[channel];
		if( animation_player->state_sound[channel] && sound ){
			MLV_play_sound( sound, animation_player->volume[channel] );
		}
		animation_player->sounds_are_being_played[channel] = 1;
	}
}

void MLV_play_sounds_from_animation_player(
	MLV_Animation_player* animation_player,
	...
){
	va_list pile;
	va_start( pile, animation_player );

	int layer;
	layer = va_arg( pile, int );
	while( layer >= 0 ) {
		MLV_play_sound_from_animation_player(
			animation_player, layer
		);
		layer = va_arg( pile, int );
	}

	va_end( pile );
}

void MLV_play_list_of_sounds_from_animation_player(
	MLV_Animation_player* animation_player, unsigned int* layers,
	unsigned int nb_layers
){
	int i;
	for( i=0; i< nb_layers; i++ ){
		MLV_play_sound_from_animation_player(
			animation_player, layers[i]
		);
	}	
}




////////////////////////////////////////////////
//    Loading animations from files
//    stored in animation books.
///////////////////////////////////////////////

typedef struct _Animation_book_sound {
	char* name;
	MLV_Sound** channels;
} Animation_book_sound;

typedef struct _Animation_book_page {
	int width;
	int height;
	int columns;
	MLV_Image** layers;
} Animation_book_page;

struct _MLV_Animation_book {
	char* xml_file;

	int nb_channels;
	MLV_TreeMap* channel_name_to_id;
	char** channel_names;

	int nb_layers;
	MLV_TreeMap* layer_name_to_id;
	char** layer_names;

	int nb_pages;
	MLV_TreeMap* page_name_to_id;
	char** page_names;
	Animation_book_page* pages;

	int nb_sounds;
	MLV_TreeMap* sound_name_to_id;
	char** sound_names;
	Animation_book_sound* sounds;

	int nb_animations;
	MLV_TreeMap* animation_name_to_id;
	char** animation_names;
	MLV_Animation** animations;

};

int MLV_get_number_of_animations(
	MLV_Animation_book* animation_book
){
	return animation_book->nb_animations;
}

void destroy_int( void* data ){
	int* ptr = (int*) data;
	MLV_FREE( ptr, int );
}

void insert_data_in_map( MLV_TreeMap* map, char* name, int identifiant ){
	int* id = MLV_MALLOC( 1, int );
	*id = identifiant;
	MLV_add_data_in_tree_map(
		MLV_string_to_key(name), id, destroy_int, map
	);
}

MLV_Animation_book* MLV_load_animation_book(
	const char* xml_file,
	const char* image_directory,
	const char* sound_directory
){
	int i;
	MLV_Animation_book* result;

	if( ! MLV_path_exists( xml_file ) ){
		fprintf(
			stderr,
			"The xml file %s doesn't exists.\n",
			xml_file
		);
		return NULL;
	}
	if(
		image_directory &&
		( ! strcmp( image_directory, "" ) ) &&
		MLV_path_exists( image_directory ) 
	){
		fprintf(
			stderr,
			"The image directory %s doesn't exists.\n",
			image_directory
		);
		return NULL;
	}
	if(
		sound_directory &&
		( ! strcmp( sound_directory, "" ) ) &&
		MLV_path_exists( sound_directory ) 
	){
		fprintf(
			stderr,
			"The sound directory %s doesn't exists.\n",
			sound_directory
		);
		return NULL;
	}

	char* dirname = MLV_get_directory_name( xml_file );

	MLV_Xml* xml = MLV_load_xml( xml_file );

	if( !xml ) return NULL;

	result = MLV_MALLOC( 1, MLV_Animation_book );

	result->nb_animations = MLV_get_number_of_objects_from_xml(
		xml, "/animation_book/animation"
	);
	result->animations = MLV_MALLOC(
		result->nb_animations, MLV_Animation*
	);
	result->animation_names = MLV_MALLOC(
		result->nb_animations, char*
	);
	result->animation_name_to_id = MLV_create_tree_map();
	for( i=0; i<result->nb_animations; i++ ){
		if( MLV_get_string_value_from_xml(
			xml, 
			&(result->animation_names[i]),
			"/animation_book/animation[%d]/name", i+1
		) ){
			fprintf(
				stderr,
				"The animation book xml is corrupted. The Field /animation_book/animation[%d]/name doesn't exist.\n",
				i+1
			);
			exit(0);
		};
		insert_data_in_map(
			result->animation_name_to_id, result->animation_names[i], i
		);
	}

	result->nb_layers = MLV_get_number_of_objects_from_xml(
		xml, "/animation_book/layers/layer"
	);
	result->layer_names = MLV_MALLOC(
		result->nb_layers, char*
	);
	result->layer_name_to_id = MLV_create_tree_map();
	for( i=0; i<result->nb_layers; i++ ){
		if(
			MLV_get_string_value_from_xml(
				xml, &(result->layer_names[i]), "/animation_book/layers/layer[%d]", i+1
			)
		){
			fprintf(
				stderr,
				"The animation book xml is corrupted. The Field /animation_book/layers/layer[%d] doesn't exist.\n",
				i+1
			);
			exit(0);
		}
		insert_data_in_map(
			result->layer_name_to_id, result->layer_names[i], i
		);
	}

	result->nb_channels = MLV_get_number_of_objects_from_xml(
		xml, "/animation_book/channels/channel"
	);
	result->channel_names = MLV_MALLOC(
		result->nb_channels, char*
	);
	result->channel_name_to_id = MLV_create_tree_map();
	for( i=0; i<result->nb_channels; i++ ){ 
		if(
			MLV_get_string_value_from_xml(
				xml, 
				&(result->channel_names[i]),
				"/animation_book/channels/channel[%d]", i+1
			)
		){
			fprintf(
				stderr,
				"The animation book xml is corrupted. The Field /animation_book/channels/channel[%d] doesn't exist.\n",
				i+1
			);
			exit(0);
		};
		insert_data_in_map(
			result->channel_name_to_id, result->channel_names[i], i
		);
	}


	result->nb_pages = MLV_get_number_of_objects_from_xml(
		xml, "/animation_book/page"
	);
	result->page_names = MLV_MALLOC(
		result->nb_pages, char*
	);
	result->page_name_to_id = MLV_create_tree_map();
	for( i=0; i<result->nb_pages; i++ ){
		if(
			MLV_get_string_value_from_xml(
				xml, &(result->page_names[i]),"/animation_book/page[%d]/name", i+1
			)
		){
			fprintf(
				stderr,
				"The animation book xml is corrupted. The Field /animation_book/page[%d]/name doesn't exist.\n",
				i+1
			);
			exit(0);
		};
		insert_data_in_map(
			result->page_name_to_id, result->page_names[i], i
		);
	}
	result->pages = MLV_MALLOC(
		result->nb_pages, Animation_book_page
	);

	result->nb_sounds = MLV_get_number_of_objects_from_xml(
		xml, "/animation_book/sound"
	);
	result->sound_names = MLV_MALLOC(
		result->nb_sounds, char*
	);
	result->sound_name_to_id = MLV_create_tree_map();
	for( i=0; i<result->nb_sounds; i++ ){
		if(
			MLV_get_string_value_from_xml(
				xml, &(result->sound_names[i]), "/animation_book/sound[%d]/name", i+1
			)
		){
			fprintf(
				stderr,
				"The animation book xml is corrupted. The Field /animation_book/sound[%d]/name doesn't exist.\n",
				i+1
			);
			exit(0);
		}
		insert_data_in_map(
			result->sound_name_to_id, result->sound_names[i], i
		);
	}
	result->sounds = MLV_MALLOC(
		result->nb_sounds, Animation_book_sound
	);
	
	int nb_layers = result->nb_layers;
	int nb_channels = result->nb_channels;
	int nb_pages = result->nb_pages;
	int nb_sounds = result->nb_sounds;
	int nb_animations = result->nb_animations;

	int id_page;
	for( id_page=0; id_page<nb_pages; id_page++ ){
		if( 
			MLV_get_integer_value_from_xml(
				xml, &(result->pages[id_page].width), "/animation_book/page[%d]/width", id_page+1
			) ||
			MLV_get_integer_value_from_xml(
				xml, &(result->pages[id_page].height), "/animation_book/page[%d]/height", id_page+1
			) || 
			MLV_get_integer_value_from_xml(
				xml, &(result->pages[id_page].columns), "/animation_book/page[%d]/columns", id_page+1
			)
		){
			fprintf(
				stderr,
				"The animation book xml is corrupted. One of those fields /animation_book/page[%d]/width or /animation_book/page[%d]/height or /animation_book/page[%d]/columns are missing or are not integers.\n",
				id_page+1,
				id_page+1,
				id_page+1
			);
			exit(0);
		};
		result->pages[id_page].layers = MLV_MALLOC( nb_layers, MLV_Image* );
		for( i=0; i < nb_layers; i++ ){
			result->pages[id_page].layers[i] = NULL;
		}

		int nb_images = MLV_get_number_of_objects_from_xml(
			xml, "/animation_book/page[%d]/image", id_page+1
		);
		int image;
		for( image=0; image < nb_images; image++ ){
			char* layer;
			char* file;
			if(
				MLV_get_string_value_from_xml(
					xml, &(layer), "/animation_book/page[%d]/image[%d]/layer", id_page+1, 
					image+1
				) ||
				MLV_get_string_value_from_xml(
					xml, &(file), "/animation_book/page[%d]/image[%d]/file", id_page+1,
					image+1
				)
			){
				fprintf(
					stderr,
					"The animation book xml is corrupted. One of those Fields : /animation_book/page[%d]/image[%d]/layer or /animation_book/page[%d]/image[%d]/file are missing.\n",
					id_page+1, image+1,
					id_page+1, image+1
				);
				exit(0);
			}
			MLV_Key* key = MLV_string_to_key( layer );
			int id_layer = *(
				(int*) MLV_get_data_from_tree_map(
					key, result->layer_name_to_id
				)
			);
			MLV_free_key( key );

			char* full_path;
			if( MLV_path_is_absolute( file ) ){
				full_path = MLV_build_path(
					file, NULL
				);
			}else{
				if( image_directory ){
					full_path = MLV_build_path(
						image_directory, file, NULL
					);
				}else{
					full_path = MLV_build_path( dirname, file, NULL );
				}
			}
			if( ! MLV_path_exists( full_path ) ){
				fprintf(
					stderr,
					"The file %s doesn't exist.\n",
					full_path
				);
				exit(0);
			}
			MLV_Image* image = MLV_load_image( full_path );
			if( ! image ){
				fprintf(
					stderr,
					"The file %s is an unknow image or is corrupted.\n",
					full_path
				);
				exit(0);
			}
			result->pages[id_page].layers[ id_layer ] = image;
			MLV_FREE( full_path, char );

			MLV_FREE( layer, char );
			MLV_FREE( file, char );
		}
		
	}


	int id_sound;
	for( id_sound=0; id_sound<nb_sounds; id_sound++ ){
		result->sounds[id_sound].channels = MLV_MALLOC( nb_channels, MLV_Sound* );
		for( i=0; i < nb_channels; i++ ){
			result->sounds[id_sound].channels[i] = NULL;
		}

		int nb_samples = MLV_get_number_of_objects_from_xml(
			xml, "/animation_book/sound[%d]/sample", id_sound+1
		);
		int sample;
		for( sample=0; sample < nb_samples; sample++ ){
			char* channel;
			char* file;
			if(
				MLV_get_string_value_from_xml(
					xml, &(channel), "/animation_book/sound[%d]/sample[%d]/channel", id_sound+1, 
					sample+1
				) ||
				MLV_get_string_value_from_xml(
					xml, &(file), "/animation_book/sound[%d]/sample[%d]/file", id_sound+1,
					sample+1
				)
			){
				fprintf(
					stderr,
					"The animation book xml is corrupted. One of those Fields : /animation_book/sound[%d]/sample[%d]/channel or /animation_book/sound[%d]/sample[%d]/file are missing.\n",
					id_sound+1, sample+1,
					id_sound+1, sample+1
				);
				exit(0);
			}
			MLV_Key* key = MLV_string_to_key( channel );
			int id_channel = *(
				(int*) MLV_get_data_from_tree_map(
					key, result->channel_name_to_id
				)
			);
			MLV_free_key( key );


			char* full_path;
			if( MLV_path_is_absolute( file ) ){
				full_path = MLV_build_path(
					file, NULL
				);
			}else{
				if( sound_directory ){
					full_path = MLV_build_path(
						sound_directory, file, NULL
					);
				}else{
					full_path = MLV_build_path( dirname, file, NULL );
				}
			}
			if( ! MLV_path_exists( full_path ) ){
				fprintf(
					stderr,
					"The file %s doesn't exist.\n",
					full_path
				);
				exit(0);
			}
			MLV_Sound* sound = MLV_load_sound( full_path );
			if( ! sound ){
				fprintf(
					stderr,
					"The sound file %s are unknwon or corrupted.\n",
					full_path
				);
				exit(0);
			}
			result->sounds[id_sound].channels[ id_channel ] = sound;
			MLV_FREE( full_path, char );

			MLV_FREE( channel, char );
			MLV_FREE( file, char );
		}
	}


	int id_animation;
	for( id_animation=0; id_animation<nb_animations; id_animation++ ){
		char* page_name;
		if(
			MLV_get_string_value_from_xml(
				xml, &(page_name), "/animation_book/animation[%d]/page", id_animation+1
			)
		){
			fprintf(
				stderr,
				"The animation book xml is corrupted. The field : /animation_book/animation[%d]/page is missing.\n",
				id_animation+1
			);
			exit(0);
		}
		MLV_Key* key = MLV_string_to_key( page_name );
		int id_page = *(
			(int*) MLV_get_data_from_tree_map(
				key, result->page_name_to_id
			)
		);
		MLV_free_key( key );
		int width = result->pages[id_page].width;
		int height = result->pages[id_page].height;
		int columns = result->pages[id_page].columns;
		int nb_frames = MLV_get_number_of_objects_from_xml(
			xml, "/animation_book/animation[%d]/frame", id_animation+1
		);
		result->animations[
			id_animation
		] = MLV_create_animation( nb_frames, nb_layers, nb_channels );
		int id_frame;
		for( id_frame=0; id_frame < nb_frames; id_frame++ ){
			MLV_Sound** sounds = NULL;
			MLV_Image** images = NULL;
			char* sound;
			MLV_get_string_value_from_xml(
				xml, &(sound), "/animation_book/animation[%d]/frame[%d]/sound",
				id_animation+1,	id_frame+1
			);
			if( sound ){
				MLV_Key* key = MLV_string_to_key( sound );
				int id_sound = *(
					(int*) MLV_get_data_from_tree_map(
						key, result->sound_name_to_id
					)
				);
				MLV_free_key( key );
				sounds = result->sounds[id_sound].channels;
			}
			int panel;
			if(
				MLV_get_integer_value_from_xml(
					xml, &(panel), "/animation_book/animation[%d]/frame[%d]/panel", 
					id_animation+1, id_frame+1 
				)
			){
				fprintf(
					stderr,
					"The animation book xml is corrupted. The field : /animation_book/animation[%d]/frame[%d]/panel is missing or is not an integer.\n",
					id_animation+1,	id_frame+1
				);
				exit(0);
			}
			images = MLV_MALLOC( nb_layers ,MLV_Image* );
			int id_layer;
			for( id_layer=0; id_layer<nb_layers; id_layer++ ){
				int x = (panel%columns)*(width+1);
				int y = (panel/columns)*(height+1);
				if(result->pages[id_page].layers[id_layer]){
					images[id_layer] = MLV_copy_partial_image(
						result->pages[id_page].layers[id_layer],
						x, y, width, height
					);
				}else{
					images[id_layer] = NULL;
				}
			}
			int time;
			if( 
				MLV_get_integer_value_from_xml(
					xml, &(time), "/animation_book/animation[%d]/frame[%d]/time", 
					id_animation+1, id_frame+1 
				)
			){
				fprintf(
					stderr,
					"The animation book xml is corrupted. The field : /animation_book/animation[%d]/frame[%d]/time is missing or is not an integer.\n",
					id_animation+1,	id_frame+1
				);
				exit(0);
			};
			MLV_add_frame_in_animation(
				images, sounds,  time, result->animations[id_animation]
			);
			MLV_FREE( images, MLV_Image* );
			MLV_FREE( sound, char );
		}
	}

	MLV_FREE( dirname, char );
	MLV_free_xml( xml );

	return result;
}

void MLV_free_animation_book(
	MLV_Animation_book* animation_book
){
	if( !animation_book ) return;

	int i;

	int id_animation;
	for( id_animation=0; id_animation < animation_book->nb_animations;
		id_animation++
	){
		MLV_Animation* animation;
		animation = animation_book->animations[id_animation];
		int id_frame;
		for( id_frame=0; id_frame < animation->nb_frames; id_frame++ ){
			int id_layer;
			MLV_Image** images = animation->frames[id_frame].images; 
			for( id_layer=0; id_layer<animation_book->nb_layers; id_layer++ ){
				if( images[id_layer] ){
					MLV_free_image( images[id_layer] );
				}
			}
		}
		MLV_free_animation( animation );
	}


	int id_sound;
	for( id_sound=0; id_sound< animation_book->nb_sounds; id_sound++ ){
		int id_channel;
		for(
			id_channel=0; id_channel < animation_book->nb_channels; 
			id_channel++
		){
			if( animation_book->sounds[id_sound].channels[ id_channel ] ){
				MLV_free_sound(
					animation_book->sounds[id_sound].channels[id_channel]
				);
			}
		}
		MLV_FREE( animation_book->sounds[id_sound].channels, MLV_Image* );
	}
	MLV_free_tree_map( animation_book->sound_name_to_id );
	for( i=0; i<animation_book->nb_sounds; i++ ){
		MLV_FREE( animation_book->sound_names[i], char );
	}
	MLV_FREE( animation_book->sound_names, char* );
	MLV_FREE( animation_book->sounds, Animation_book_sound );

	int id_page;
	for( id_page=0; id_page< animation_book->nb_pages; id_page++ ){
		int id_layer;
		for( id_layer=0; id_layer < animation_book->nb_layers; id_layer++ ){
			if( animation_book->pages[id_page].layers[ id_layer ] ){
				MLV_free_image(
					animation_book->pages[id_page].layers[id_layer]
				);
			}
		}
		MLV_FREE( animation_book->pages[id_page].layers, MLV_Image* );
	}
	MLV_free_tree_map( animation_book->page_name_to_id );
	for( i=0; i<animation_book->nb_pages; i++ ){
		MLV_FREE( animation_book->page_names[i], char );
	}
	MLV_FREE( animation_book->page_names, char* );
	MLV_FREE( animation_book->pages, Animation_book_page );

	MLV_free_tree_map( animation_book->channel_name_to_id );
	for( i=0; i<animation_book->nb_channels; i++ ){
		MLV_FREE( animation_book->channel_names[i], char );
	}
	MLV_FREE( animation_book->channel_names, char* );

	MLV_free_tree_map( animation_book->layer_name_to_id );
	for( i=0; i<animation_book->nb_layers; i++ ){
		MLV_FREE( animation_book->layer_names[i], char );
	}
	MLV_FREE( animation_book->layer_names, char* );

	MLV_free_tree_map( animation_book->animation_name_to_id );
	for( i=0; i<animation_book->nb_animations; i++ ){
		MLV_FREE( animation_book->animation_names[i], char );
	}
	MLV_FREE( animation_book->animation_names, char* );
	MLV_FREE( animation_book->animations, MLV_Animation* );

	MLV_FREE( animation_book, MLV_Animation_book );
}

MLV_Animation* MLV_get_animation_from_id(
	MLV_Animation_book* animation_book,
	int id
){
	return animation_book->animations[id];
}

MLV_Animation* MLV_get_animation_from_name(
	MLV_Animation_book* animation_book,
	const char* name
){
	MLV_Key* key = MLV_string_to_key( name );
	int* id_ptr =(int*) MLV_get_data_from_tree_map(
		key, animation_book->animation_name_to_id
	);
	MLV_free_key( key );
	if( !id_ptr ) return NULL;
	return MLV_get_animation_from_id( animation_book, *id_ptr );
}

const char* MLV_get_name_from_id_animation(
	MLV_Animation_book* animation_book, int id_animation
){
	return animation_book->animation_names[ id_animation ];
}

