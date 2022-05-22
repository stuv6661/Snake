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

#include "MLV_playlist.h"

#include "MLV_audio.h"

#include "data_structure.h"
#include "list.h"
#include "memory_management.h"

#include "warning_error.h"

#ifndef MEMORY_DEBUG
#include <SDL/SDL.h>
#else
#include "memory_debug.h"
#endif

extern DataMLV* MLV_data;

typedef struct _Music_item {
	int interne;
	MLV_Music* music;
} Music_item;

struct _MLV_Playlist {
	MLV_List* music_items;
	int playing;
	int current;
	int size;
	SDL_sem* semaphore;
	double volume;
	int loop;
};

void MLV_init_playlists(){
	MLV_data->playlists = NULL;
	MLV_data->active_playlists = NULL;
}

void MLV_close_playlists(){
    MLV_List* playlists = NULL;
	MLV_List* tmp = MLV_data->playlists;
	while(tmp){
		playlists = MLV_prepend_list(
			playlists,
			tmp->data	
		);
		tmp = tmp->next;
	}
	MLV_foreach_list(
		playlists,
		(void (*)(void*,void*)) MLV_close_playlist
		, NULL
	);
    MLV_free_list( MLV_data->playlists );
    MLV_free_list( MLV_data->active_playlists );
}

MLV_Playlist* MLV_create_playlist( int loop ){
	MLV_Playlist* playlist = MLV_MALLOC( 1, MLV_Playlist );
	playlist->music_items = NULL;
    playlist->semaphore = SDL_CreateSemaphore(1);
	playlist->volume = 1.0;
	playlist->size = 0;
	playlist->loop = loop;
	if( SDL_SemWait( MLV_data->audio_semaphore )  ){
		ERROR_FULL("Probleme de semaphore");
	}
	MLV_data->playlists = MLV_prepend_list(
		MLV_data->playlists,
		playlist	
	);
	if( SDL_SemPost( MLV_data->audio_semaphore ) ){
		ERROR_FULL("Probleme de semaphore");
	}
	return playlist;
}

void MLV_close_playlist( MLV_Playlist* playlist ){
	if( SDL_SemWait( MLV_data->audio_semaphore )  ){
		ERROR_FULL("Probleme de semaphore");
	}
	MLV_data->playlists = MLV_remove_list( MLV_data->playlists, playlist );
	if( SDL_SemPost( MLV_data->audio_semaphore ) ){
		ERROR_FULL("Probleme de semaphore");
	}
	MLV_playlist_clear( playlist );
    MLV_free_list( playlist->music_items );
    SDL_DestroySemaphore( playlist->semaphore );
}

void MLV_playlist_add( MLV_Playlist* playlist, const char* file_music ){
	Music_item* item = MLV_MALLOC(1, Music_item);
	item->interne = 1;
	item->music = MLV_load_music( file_music );
	if( SDL_SemWait( playlist->semaphore )  ){
		ERROR_FULL("Probleme de semaphore");
	}
	playlist->music_items = MLV_prepend_list(
		playlist->music_items,
		item
	);
	playlist->size ++;
	if( SDL_SemPost( playlist->semaphore ) ){
		ERROR_FULL("Probleme de semaphore");
	}
}

void MLV_playlist_add_sheet_music( MLV_Playlist* playlist, MLV_Music* music ){
	Music_item* item = MLV_MALLOC(1, Music_item);
	item->interne = 0;
	item->music = music;
	if( SDL_SemWait( playlist->semaphore )  ){
		ERROR_FULL("Probleme de semaphore");
	}
	playlist->music_items = MLV_prepend_list(
		playlist->music_items,
		item
	);
	if( SDL_SemPost( playlist->semaphore ) ){
		ERROR_FULL("Probleme de semaphore");
	}
}

void MLV_playlist_remove( MLV_Playlist* playlist, int index ){
	TODO
}

void MLV_playlist_clear( MLV_Playlist* playlist ){
	TODO
}

void MLV_playlist_volume( MLV_Playlist* playlist, double volume ){
	if( SDL_SemWait( playlist->semaphore )  ){
		ERROR_FULL("Probleme de semaphore");
	}
	playlist->volume = volume;
	if( SDL_SemPost( playlist->semaphore ) ){
		ERROR_FULL("Probleme de semaphore");
	}
}

void MLV_playlist_play( MLV_Playlist* playlist ){
	if( SDL_SemWait( playlist->semaphore )  ){
		ERROR_FULL("Probleme de semaphore");
	}
	playlist->playing = 1;
	if( SDL_SemPost( playlist->semaphore ) ){
		ERROR_FULL("Probleme de semaphore");
	}
}

void MLV_playlist_pause( MLV_Playlist* playlist ){
	if( SDL_SemWait( playlist->semaphore )  ){
		ERROR_FULL("Probleme de semaphore");
	}
	playlist->playing = 0;
	if( SDL_SemPost( playlist->semaphore ) ){
		ERROR_FULL("Probleme de semaphore");
	}
}

void MLV_playlist_stop( MLV_Playlist* playlist ){
	TODO
}

void MLV_playlist_next( MLV_Playlist* playlist ){
	TODO
}

void MLV_playlist_previous( MLV_Playlist* playlist ){
	TODO
}

void MLV_playlist_first( MLV_Playlist* playlist ){
	TODO
}

void MLV_playlist_last( MLV_Playlist* playlist ){
	TODO
}

void MLV_playlist_index( MLV_Playlist* playlist, int index){
	TODO
}

