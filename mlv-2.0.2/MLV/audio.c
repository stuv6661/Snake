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

#include "MLV_audio.h"

#include "warning_error.h"

#include "memory_management.h"

#include "data_structure.h"

#include "platform.h"

#if defined( OS_WINDOWS )
#	include <SDL/SDL_mixer.h>
#elif defined( OS_APPLE )
#	include <SDL_mixer/SDL_mixer.h>
#else
#	include <SDL/SDL_mixer.h>
#endif

#include <glib.h>

extern DataMLV* MLV_data;

struct _MLV_Music {
	Mix_Music* music;
};

struct _MLV_Sound {
	Mix_Chunk* sample;
};

struct _MLV_Playlist {
    GList* list_music;
};

#define MLV_AUDIO_BUFFER_SIZE 1024
#define MLV_AUDIO_STEREO 2
#define MLV_AUDIO_NUMBER_OF_MIXING_CHANEL 16

int init_audio( int buffer_size ){
	int result = Mix_OpenAudio( 
		MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MLV_AUDIO_STEREO, buffer_size
	);
	if( !result ){
		Mix_AllocateChannels(MLV_AUDIO_NUMBER_OF_MIXING_CHANEL);
	}
	return result;
}

void MLV_change_number_of_parallel_sounds( unsigned int n ){
		if( ! n ){
			fprintf( stderr, "Incorrect parameter for MLV_change_number_playing_parallel_sounds. The number of parrallel sound can't be null." );
			exit(1);
		}
		Mix_AllocateChannels( n );
}

int MLV_init_audio(){
	return init_audio( MLV_AUDIO_BUFFER_SIZE ); // If the sound are not well 
	                                            // former, increse this value. 
	                          // If the sound have some lags, the you have 
	                          // to decrease this value.
}

int MLV_change_audio_buffer_size( int buffer_size ){
	MLV_free_audio();
	return init_audio( buffer_size );
}

void MLV_free_audio(){
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
	Mix_CloseAudio();
}

MLV_Music* MLV_load_music( const char* file_music ){
	MLV_Music* result = MLV_MALLOC( 1, MLV_Music );
	result->music= Mix_LoadMUS( file_music );
	if(! result->music) {
		MLV_FREE( result, MLV_Music );
		result = NULL;
	}
	return result;
}

void MLV_free_music( MLV_Music* music ){
	if( music ){
		Mix_FreeMusic( music->music );
		MLV_FREE( music, MLV_Music );
	}
}

void MLV_play_music( const MLV_Music* music, float volume, int loop ){
	Mix_VolumeMusic( volume * MIX_MAX_VOLUME );
	MLV_stop_music();
	if( loop ) Mix_PlayMusic( music->music, loop-1 );
}

void MLV_stop_music(){
	Mix_HaltMusic();
}

MLV_Sound* MLV_load_sound( const char* file_sound ){
	MLV_Sound* result = MLV_MALLOC( 1, MLV_Sound );
	result->sample = Mix_LoadWAV( file_sound );
	if(! result->sample ){
		MLV_FREE( result, MLV_Sound );
		result = NULL;
	}else{
		Mix_VolumeChunk( result->sample, MIX_MAX_VOLUME );
	}
	return result;
}

void MLV_free_sound( MLV_Sound* sound ){
	if( sound ){
		Mix_FreeChunk( sound->sample );
		MLV_FREE( sound, MLV_Sound );
	}
}

void MLV_play_sound( const MLV_Sound* sound, float volume ){
	int channel = Mix_PlayChannel( -1, sound->sample, 0 );
	Mix_Volume(channel, volume * MIX_MAX_VOLUME);
}

void MLV_stop_all_sounds(){
	Mix_HaltChannel(-1);
}

