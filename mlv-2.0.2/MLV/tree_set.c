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

#include "tree_set.h"
#include "warning_error.h"
#include "memory_management.h"
#include "mathematics.h"

/*
 * Renvoie la hauteur d'un arbre
 */
int MLV_get_height_tree_set( MLV_TreeSet* tree_set ){
	if( tree_set==NULL ){
		return 0;
	}
	return tree_set->height;
}

/*
 * Cette fonction substitue node par new_node
 * dans le père de node.
 * 
 * Avant :
 *   + <-- father
 *  / \
 *     + <-- node
 *
 * Après :
 *   + <-- father
 *  / \
 *     + <-- new_node
 * 
 * Cette fonction ne modifie pas le contenu de new_node.
 * Cette fonction renvoie un pointeur vers le père.
 * Cette fonction n'accepte pas de node NULL.
 *
 */
MLV_TreeSet* substitute_in_father_tree_Set(
	MLV_TreeSet* node, MLV_TreeSet* new_node
){
	if( node ){
		ERROR_FULL("Node can't be NULL !");
	}
	MLV_TreeSet* father = node->father;
	if( father ){
		if( father->left_son == node ){
			father->left_son = new_node;
		}else{
			father->right_son = new_node;
		}
	}
	new_node->father = father;
	return father;
}

/*
 * Renvoie le noeud de l'arbre de valeur de clé maximale.
 */
MLV_TreeSet* MLV_get_maximal_node_of_tree_set( MLV_TreeSet* tree_set ){
	MLV_TreeSet* result = NULL;
	while( tree_set ){
		result = tree_set;
		tree_set = tree_set->right_son;
	}
	return result;
}

/*
 * TODO
 *
 * Cette fonction retire un noeud de l'arbre.
 * Cette focntion renvoi un pointeur vers le nouvel arbre
 * obtenu.
 *
 */
MLV_TreeSet* remove_node_of_tree_set( MLV_TreeSet* tree_set ){
	NOT_IMPLEMENTED;
	return NULL;
}

/*
 * Cette fonction détruit les données contenues dans un noeud de l'arbre.
 *
 */
void destroy_node_data_of_tree_set( MLV_TreeSet* tree_set ){
	if( tree_set && tree_set->data_destroying_function ){
		tree_set->data_destroying_function( tree_set->data );
	}
}


/*
 * Cette fonction suprime le noeud (en libérant la mémoire), mais 
 * ne suprrime pas la donnée qu'elle contient.
 *
 * Cette fonction renvoie un pointeur vers le nouvel arbre obtenu. 
 */
MLV_TreeSet* destroy_node_of_tree_set( MLV_TreeSet* tree_set ){
	MLV_TreeSet* new_tree;
	new_tree = remove_node_of_tree_set( tree_set );
	MLV_FREE( tree_set, MLV_TreeSet );
	return new_tree;
}

/*
 * Cette fonction détruit les données contenues dans un noeud, puis suprime le noeud
 * de l'arbre et libère la mémoire associée à tree_set.
 *
 * Cette fonction renvoie un pointeur vers le nouvel arbre obtenu. 
 *
 */
MLV_TreeSet* destroy_node_and_his_data_of_tree_set( MLV_TreeSet* tree_set ){
	MLV_TreeSet* new_tree;
	destroy_node_data_of_tree_set( tree_set );
	new_tree = remove_node_of_tree_set( tree_set );
	MLV_FREE( tree_set, MLV_TreeSet );
	return new_tree;
}

/*
 * Cette fonction cherche un noeud ayant une donnée particulière.
 * Cette fonction rencoie le noeud associé à cette donnée.
 */
MLV_TreeSet* MLV_find_tree_set( void* data, MLV_TreeSet* tree_set ){
	if( tree_set == NULL ){
		return NULL;
	}
	int comparaison = tree_set->sorting_function( data, tree_set->data );
	if( comparaison == 0  ){
		return tree_set;
	}else if( comparaison < 0 ){
		return MLV_find_tree_set( data, tree_set->left_son );
	}else{
		return MLV_find_tree_set( data, tree_set->right_son );
	}
}

/*
 * Supprime les données conetenu dans un tree_set et 
 * les remplaces par une autre donnée.
 * La mémoire de l'ancienne donnée est suprimée.
 * 
 */
void change_data_of_node_tree_set(
	void* data,
	void (* data_destroying_function )( void* data ),
	MLV_TreeSet * tree_set
){
	destroy_node_data_of_tree_set( tree_set );
	tree_set->data = data;
	tree_set->data_destroying_function = data_destroying_function;
}

/*
 * Créer un nouveau noeud.
 */
MLV_TreeSet* create_node_tree_set(
	MLV_TreeSet* father, MLV_TreeSet* left_son, MLV_TreeSet* right_son,
	void* data,
	void (* data_destroying_function )( void* data ),
	int (* sorting_function )( void* data1, void* data2 ),
	int height
){
	MLV_TreeSet* result = MLV_MALLOC( 1, MLV_TreeSet );
	result->father = father;
	result->left_son = left_son;
	result->right_son = right_son;
	result->data = data;
	result->data_destroying_function = data_destroying_function;
	result->sorting_function = sorting_function;
	result->height = height;
	return result;
}

/*
 * Cette fonction équilibre localement le sous-arbre tree_set en équilibrant 
 * que sa racine.
 *
 * A l'issue de l'équilibrage, elle met à jour les hauteurs de tous les noeuds
 * du sous-arbre associée à tree_set.
 * Si les fils à tree_set étaient équilibrés, alors, tree_set devient lui aussi 
 * équilibré.
 *
 */
MLV_TreeSet* equilibrate_localy_the_tree_set( MLV_TreeSet* tree_set ){
	if( ! tree_set ) return NULL;
	MLV_TreeSet *A, *B, *C, *D, *E, *F, *G;
	MLV_TreeSet* father = tree_set->father;
	int height_left = MLV_get_height_tree_set( tree_set->left_son );
	int height_right = MLV_get_height_tree_set( tree_set->right_son );
	int comparaison = height_left-height_right;
	// Si les fils ont des tailles qui diffèrent d'au plus 1, alors le sous-arbre
    // est déjà équilibré et il y a rien à faire.
	if( abs( comparaison ) <= 1 ) return tree_set;
	// Le sous arbres n'est pas équilibré.
	// 4 type d'arbres non équilibrés peuvent se présenter
	if( comparaison < 0 ){
		/*     B
		 *   /  \
		 *  A    \
		 *        +
		 */
		B = tree_set;
		A = B->left_son;
		int height_right_left = MLV_get_height_tree_set( B->right_son->left_son );
		int height_right_right = MLV_get_height_tree_set( B->right_son->right_son );
		if( height_right_left > height_right_right ){
			/* 1er type :
             *
			 *      B
			 *     / \
			 *    A   F
			 *       / \
			 *      D   G
			 *     / \
			 *    C   E
			 */
			F = B->right_son;
			D = F->left_son;
			G = F->right_son;
			C = D->left_son;
			E = D->right_son;
		}else{
			/* 2ème type :
             *
             *      B
			 *     / \
			 *    A   D
			 *       / \
			 *      C   F
			 *         / \
			 *         E  G
			 */
			D = B->right_son;
			C = D->left_son;
			F = D->right_son;
			E = F->left_son;
			G = F->right_son;
		}
	}else{
		/*     F
		 *   /  \
		 *  /    G
		 * +
		 */
		F = tree_set;
		G = F->right_son;
		int height_left_left = MLV_get_height_tree_set( F->left_son->left_son );
		int height_left_right = MLV_get_height_tree_set( F->left_son->right_son );
		if( height_left_right > height_left_left ){
			/* 3ème type :
			 *
			 *      F
			 *     / \
			 *    B   G
			 *   / \
			 *  A   D
			 *     / \
			 *    C   E
			 */
			B = F->left_son;
			A = B->left_son;
			D = B->right_son;
			C = D->left_son;
			E = D->right_son;
		}else{
			/* 4ème type :
			 *
			 *       F
			 *      / \
			 *     D   G
			 *    / \
			 *   B   E
			 *  / \
			 * A   C
			 */
			D = F->left_son;
			B = D->left_son;
			E = D->right_son;
			A = B->left_son;
			C = B->right_son;
		}
	}
	/*
	 * On réordonne l'arbre de façon à obtenir
	 *
	 *       D
     *     /   \
	 *   B      F
	 *  / \    / \
     * A   C  E   G
	 */
	A->father = B;
	C->father = B;
	E->father = F;
	G->father = F;

	B->left_son = A;
	B->right_son = C;
	B->father = D;
	B->height = max( A->height, C->height ) + 1;

	F->left_son = E;
	F->right_son = G;
	F->father = D;
	F->height = max( E->height, G->height ) + 1;

	D->left_son = B;
	D->right_son = F;
	D->father = father;
	D->height = max( B->height, F->height ) + 1;

	// On met à jour le père du sous-arbre d'origine
	if( father ){
		if( father->left_son == tree_set ){
			father->left_son = D;
		}else{
			father->right_son = D;
		}
	}
	return D;
}

/*
 * Algorithme d'insertion d'une nouvelle (cle, data) dans un arbre.
 */
MLV_TreeSet* MLV_add_data_in_tree_set(
	void* data,
	void (* data_destroying_function )( void* data ),
	int (* sorting_function )( void* data1, void* data2 ),
	MLV_TreeSet * tree_set
){
	if( tree_set==NULL ){
		return create_node_tree_set(
			NULL, NULL, NULL,
			data,
			data_destroying_function, sorting_function,
			1
		);
	}
	// On cherche l'endroit où il faut insérer le noeud dans l'arbre.
	MLV_TreeSet* current = tree_set;
	MLV_TreeSet* father_of_insertion_point = NULL;
	int comparaison;
	while( current ){
		comparaison = current->sorting_function( data, current->data );
		if( comparaison == 0  ){
			change_data_of_node_tree_set(
				data, data_destroying_function, current
			);
			return tree_set;
		}else if( comparaison < 0 ){
			father_of_insertion_point = current;
			current = current->left_son;
		}else{
			father_of_insertion_point = current;
			current = current->right_son;
		}
	}
	// on créé un nouveau noeud
	current = create_node_tree_set(
		father_of_insertion_point, NULL, NULL,
		data,
		data_destroying_function, sorting_function,
		1
	);
	// On insère le nouveau noeud dans l'arbre.
	// Ici, comme tree_set ne peut pas valoir NULL, 
	// father_of_insertion_point ne peut pas être NULL et 
	// comparaison contient une valeur.
	// Le point d'insertion à donc toujours un père.
	if( comparaison<0 ){
		father_of_insertion_point->left_son = current;
	}else{
		father_of_insertion_point->right_son = current;
	}
	// On équilibre l'arbre.
	// Pour cela on remonte l'arbre en paratn du sommet ajouté jusqu'à la 
	// racine et on rééqulibre localement chaque noeud rencontré.
	current = father_of_insertion_point; // On part du père car le nouveau
										 // noeud est toujours équilibré.
	MLV_TreeSet* new_root; // La nouvelle racine issue du rééquilibrage local.
	while( current ){
		new_root = equilibrate_localy_the_tree_set( current );
		current = new_root->father;
	}
	// Comme father_of_inserion_point n'est pas NULL (voir explication 
	// précédente), current n'est pas NULL. Donc, new_root contient un valeur.
	// D'après equilibrate_localy_the_tree_set, new_root est un arbre équilibré.
	return new_root;
}

/*
 * Execute un fonction sur chaque clé et donné de l'arbre.
 */
void MLV_foreach_data_tree_set(
	void (* data_function )( void* data, void* data_user ),
	void* data_user,
	MLV_TreeSet* tree_set
){
	if( tree_set ){
		if( tree_set->left_son ){
			MLV_foreach_data_tree_set( data_function, data_user, tree_set->left_son );
		}
		if( tree_set->right_son ){
			MLV_foreach_data_tree_set( data_function, data_user, tree_set->right_son );
		}
		data_function( tree_set->data, data_user );
	}
}

/*
 * Execute un fonction sur chaque noeud de l'arbre.
 */
void foreach_node_tree_set(
	void (* node_function)(MLV_TreeSet* tree_set, void* data_user),
	void* data_user,
	MLV_TreeSet* tree_set
){
	if( tree_set ){
		if( tree_set->left_son ){
			foreach_node_tree_set( node_function, data_user, tree_set->left_son );
		}
		if( tree_set->right_son ){
			foreach_node_tree_set( node_function, data_user, tree_set->right_son );
		}
		node_function( tree_set, data_user );
	}
}

/*
 * Un wrapper à utiliser avec foreach_node_tree_set.
 */
void wrapper_destroy_node_data_of_tree_set( MLV_TreeSet* tree_set, void* useless_data ){
	destroy_node_data_of_tree_set( tree_set );
}

/*
 * Un wrapper à utiliser avec foreach_node_tree_set.
 */
void wrapper_remove_node_of_tree_set( MLV_TreeSet* tree_set, void* useless_data ){
	remove_node_of_tree_set( tree_set );
}

/*
 * Un wrapper à utiliser avec foreach_node_tree_set.
 */
void wrapper_destroy_node_and_his_data_of_tree_set( MLV_TreeSet* tree_set, void* useless_data ){
	destroy_node_and_his_data_of_tree_set( tree_set );
}

/*
 * Un wrapper à utiliser avec foreach_node_tree_set.
 */
void wrapper_destroy_node_of_tree_set( MLV_TreeSet* tree_set, void* useless_data ){
	destroy_node_of_tree_set( tree_set );
}

void free_tree_set( MLV_TreeSet* tree_set, void* useless_data ){
	MLV_FREE( tree_set, MLV_TreeSet );
}

/*
 * Cette fonction supprime tous les noeuds de l'abre sans détruire les données.
 */
void MLV_init_tree_set( MLV_TreeSet* tree_set ){
	foreach_node_tree_set( free_tree_set, NULL, tree_set );
}

void deep_free_tree_set( MLV_TreeSet* tree_set, void* useless_data  ){
	destroy_node_data_of_tree_set( tree_set );
	free_tree_set( tree_set, useless_data );
}

/*
 * Cette fonction supprime tous les noeuds de l'abre et détruit les données 
 * associé à l'arbre.
 */
void MLV_clear_tree_set( MLV_TreeSet* tree_set ){
	foreach_node_tree_set( deep_free_tree_set, NULL, tree_set );
}

/*
 * Enlève une donnée de l'esemble.
 * La donnée n'est pas supprimée.
 */
MLV_TreeSet* MLV_remove_data_from_tree_set( void* data, MLV_TreeSet* tree_set ){
	MLV_TreeSet* node = MLV_find_tree_set( data, tree_set );
	return destroy_node_of_tree_set( node );
}

/*
 * Supprime une donnée de l'ensemble.
 * La donnée est supprimée.
 */
MLV_TreeSet* MLV_remove_data_and_data_from_tree_set( void* data, MLV_TreeSet* tree_set ){
	MLV_TreeSet* node = MLV_find_tree_set( data, tree_set );
	destroy_node_data_of_tree_set( node );
	return destroy_node_and_his_data_of_tree_set( node );
}

/*
 * Supprime une donnée de l'ensemble.
 * La donnée est supprimée.
 */
int MLV_is_in_tree_set( void* data, MLV_TreeSet* tree_set ){
	return MLV_find_tree_set( data, tree_set )!=NULL ;
}


