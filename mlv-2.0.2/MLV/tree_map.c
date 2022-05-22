/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2012 Adrien Boussicault, Marc Zipstein
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

#include "tree_map.h"

#include "tree_set.h"
#include "warning_error.h"
#include "memory_management.h"

struct _MLV_TreeMap {
	MLV_TreeSet* set;
};
typedef struct {
	MLV_Key* key;
	void* data;
	void (* data_destroying_function )( void* data );
} PairKeyData;

PairKeyData* create_pair_key_data(
	MLV_Key* key,
	void* data,
	void (* data_destroying_function )( void* data )
){
	PairKeyData* result = MLV_MALLOC( 1, PairKeyData );
	result->key = key;
	result->data = data;
	result->data_destroying_function = data_destroying_function;
	return result;
}

void free_pair_key_data( PairKeyData* pair ){
	if( pair ){
		MLV_free_key( pair->key );
		if( pair->data_destroying_function ){
			pair->data_destroying_function( pair->data );
		}
	}
	MLV_FREE( pair, PairKeyData );
}

void free_pair_key_data_without_key( PairKeyData* pair ){
	if( pair ){
		if( pair->data_destroying_function ){
			pair->data_destroying_function( pair->data );
		}
	}
	MLV_FREE( pair, PairKeyData );
}


int compare_pairs_key_data( PairKeyData* pair1, PairKeyData* pair2 ){
	return MLV_compare_keys( pair1->key, pair2->key );
}

MLV_TreeMap* MLV_create_tree_map(){
	MLV_TreeMap* result = MLV_MALLOC( 1, MLV_TreeMap );
	result->set = NULL;
	return result;
}

void MLV_add_data_in_tree_map(
	MLV_Key* key, void* data,
	void (* data_destroying_function)( void* data ),
	MLV_TreeMap* tree_map
){
	tree_map->set = MLV_add_data_in_tree_set(
	 	create_pair_key_data(
			key, data, data_destroying_function
		),
		( void (*)( void* ) ) free_pair_key_data,
		( int (*)( void*, void* ) ) compare_pairs_key_data,
		tree_map->set
	);
}

void* MLV_get_data_from_tree_map( MLV_Key* key, MLV_TreeMap* tree_map ){
	PairKeyData* key_data = create_pair_key_data( key, NULL, NULL );
	MLV_TreeSet* elem = MLV_find_tree_set( key_data, tree_map->set );
	PairKeyData* founded_key_data = (PairKeyData*) elem->data;
	free_pair_key_data_without_key( key_data );
	return founded_key_data->data;
}

void free_key_of_pair_key_data( PairKeyData* pair ){
	MLV_free_key( pair->key );
}

void wrapper_free_key_of_pair_key_data( void* pair, void* useless_data ){
	free_key_of_pair_key_data( ( PairKeyData* ) pair );
}

void MLV_init_tree_map( MLV_TreeMap* tree_map ){
	// On supprime les clés
	MLV_foreach_data_tree_set(
		wrapper_free_key_of_pair_key_data,
		NULL,
		tree_map->set
	);
	// On réinitialise la table
	MLV_init_tree_set( tree_map->set );
}


typedef struct {
	void* data_user;
	void (* key_data_function )( MLV_Key* key, void* data, void* data_user );
} Wrapper_data_user;

Wrapper_data_user* create_wrapper_data_user(
	void* data_user,
	void (* key_data_function )( MLV_Key* key, void* data, void* data_user )
){
	Wrapper_data_user* result = MLV_MALLOC( 1, Wrapper_data_user );
	result->data_user = data_user;
	result->key_data_function = key_data_function;
	return result;
}

void free_wrapper_data_user( Wrapper_data_user* data ){
	MLV_FREE( data, Wrapper_data_user );
}

void wrapper_key_data_function(
	void* data,
	void* data_user
){
	PairKeyData* pair = ( PairKeyData* ) data;
	Wrapper_data_user* wrapper_data_user = (Wrapper_data_user*) data_user;
	if( wrapper_data_user->key_data_function ){
		wrapper_data_user->key_data_function(
			pair->key, pair->data, wrapper_data_user->data_user
		);
	}
}

void MLV_foreach_key_data_tree_map(
	void (* key_data_function )( MLV_Key* key, void* data, void* data_user ),
	void* data_user,
	MLV_TreeMap* tree_map
){
	
	Wrapper_data_user* wrapper_data = create_wrapper_data_user(
		data_user, key_data_function
	);
	MLV_foreach_data_tree_set(
		wrapper_key_data_function,
		wrapper_data,
		tree_map->set
	);
	free_wrapper_data_user( wrapper_data );
}

void MLV_clear_tree_map( MLV_TreeMap* tree_map ){
	MLV_clear_tree_set( tree_map->set );
}

void MLV_free_tree_map( MLV_TreeMap* tree_map ){
	MLV_clear_tree_map( tree_map );
	MLV_FREE( tree_map, MLV_TreeMap );
}

void MLV_superficial_free_tree_map( MLV_TreeMap* tree_map ){
	MLV_init_tree_map( tree_map );
	MLV_FREE( tree_map, MLV_TreeMap );
}
