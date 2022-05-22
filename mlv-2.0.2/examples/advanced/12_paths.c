/**
 * Cette dmonstration explique comment l'utilisateur peut faire pour travailler
 * avec les chemins d'acces des fichiers.
 *
 *------------------------------------------------------------------------------
 * MLV_get_base_name: Renvoie la chaîne de caractères après le dernier séparteur
 *                    / dans un chemin donné en paramètre.
 *
 * Cette fonction renvoie une chaîne de caractère.
 *
 * char* MLV_get_base_name(
 *     const char*     path     Le chemin à analyser.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_get_directory_name: Renvoie la chaîne de caractère s'étendnant jusqu'au 
 *                         dernier séparateur / du chemin donné en paramètre.
 *
 * Cette fonction renvoie une chaîne de caractère.
 *
 * char* MLV_get_directory_name(
 *     const char*     path     Le chemin à analyser.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_path_is_absolute: Teste si un chemin est absolu.
 *
 * Cette fonction renvoie 1 si le chemin est absolue, 0 sinon.
 *
 * int MLV_path_is_absolute(
 *     const char* path     Le chemin à analyser.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_path_is_relative: Teste si un chemin est relatif.
 *
 * Cette fonction renvoie 1 si le chemin est relatif, 0 sinon.
 *
 * int MLV_path_is_relative(
 *     const char*     path     Le chemin à analyser.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_path_exists: Teste si le chemin corespond au chemin d'un fichier ou 
 *                 dossier existant.
 *
 * Cette fonction renvoie renvoie 1 si le chemin est associé à un dossier ou un
 * fichier existant, 0 sinon.
 *
 * int MLV_path_exists(
 *     const char*     path     Le chemin à analyser.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_path_is_a_directory: Vérifie si un chemin est un associé à un répertoire.
 *
 * Cette fonction renvoie 1 si le chemin est associé à un dossier, 0 sinon.
 *
 * int MLV_path_is_a_directory(
 *     const char*     path     Le chemin à analyser.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_path_is_a_file: Vérifie si un chemin est un associé à un fichier.
 *
 * Cette fonction renvoie 1 si le chemin est associé à un fichier, 0 sinon.
 *
 * int MLV_path_is_a_file(
 *     const char*     path     Le chemin à analyser.
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_build_path: Construit en concaténant différents textes, une chaine de 
 *                 caractère représentant un chemin dont les séparateurs 
 *                 corespondent aux spécifications de la plateforme sur laquel 
 *                 s'execute le programme.
 *
 * Cette fonction renvoie le chemin vérifiant les normes de la plateforme hôte.
 *
 * char* MLV_build_path(
 *     const char*     first_element,     La premiere chaîne à concatener
 *     ...                                les autres éléments à concatener
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_get_current_directory: Determine le répertoire courant.
 *
 * Cette fonction renvoie le chemin du répertire courant.
 *
 * const char * MLV_get_current_directory( );
 *
 *------------------------------------------------------------------------------
 * MLV_get_temporary_directory: Determine le répertoire temporaire.
 *
 * Le répertoire temporaire est le repertoire dans lequel les applications ont
 * ont le droit d'ajouter et de modifier des fichiers.
 * Ce répertoire génaralement vidé lorqsue la machine est étteinte.
 *
 * Cette fonction renvoie le chemin du répertire temporaire.
 *
 * const char * MLV_get_temporary_directory( );
 *
 *------------------------------------------------------------------------------
 * MLV_get_home_directory: Determine le répertoire personnel de l'utilisateur 
 *                         courant.
 *
 * Cette fonction renvoie le chemin du répertire personnel.
 *
 * const char * MLV_get_home_directory( );
 *
 *------------------------------------------------------------------------------
 *
 */

#include <MLV/MLV_all.h>
#include <stdio.h>

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){

	printf( "\n" );
	
	const char *current_directory, *temporary_directory, *home_directory;
	
	current_directory = MLV_get_current_directory( );
	printf("Répertoire courant : %s \n", current_directory);

	temporary_directory = MLV_get_temporary_directory( );
	printf( "Répertoire temporaire : %s\n", temporary_directory );

	home_directory = MLV_get_home_directory( );
	printf( "Répertoire personnel : %s\n", home_directory );

	const char* path = "./creature.png";
	if( MLV_path_exists( path ) ){
		printf("Le chemin %s existe.\n", path );
	}else{
		printf("Le chemin %s n'existe pas.i\n", path );
	}

	if( MLV_path_is_a_file( path ) ){
		printf("%s est un fichier.\n", path );
	}else{
		printf("%s n'est pas un fichier.\n", path );
	}

	if( MLV_path_is_a_directory( path ) ){
		printf("%s est un répertoire.\n", path );
	}else{
		printf("%s n'est pas un repertoire.\n", path );
	}

	if(
		MLV_path_is_absolute( path )
  	){
		printf( "%s  est un chemin absolu.\n", path );
	}else{
		printf( "%s est un chemin relatif.\n", path );
	}
	char* build_path = MLV_build_path( current_directory, path, NULL );
	if(
		MLV_path_is_relative( build_path )
  	){
		printf( "%s est un chemin relatif.\n", build_path );
	}else{
		printf( "%s est un chemin absolu.\n", build_path );
	}

	char* basename = MLV_get_base_name( build_path );
	char* dirname = MLV_get_directory_name( build_path );
	printf( "Dans la chemin précédent,\n" );
	printf( "La chaîne de texte se trouvant après le dernier séparateur / est : %s\n", basename );
	printf( "La chaîne de texte s'étendant jusqu'au dernier séparateur / est : %s\n", dirname );

	printf( "\n" );
	
	free( build_path );
	free( basename );
	free( dirname );

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
