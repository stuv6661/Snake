/**
 * Ce programme explique commen utilise l'interface simplifié de la librairie
 * pour lire et recupere des informations contenu dans des fichiers écrits au
 * format xml.
 *
 * -----------------------------------------------------------------------------
 * MLV_load_xml: Charge en mémoire un fichier au format xml.
 *
 * Cette fonction renvoi NULL, lorsque le fichier n'a pas pu être correctement
 * chargé.
 *
 * Cette fonction renvoie le fichier xml lu, anamlysé et chargé.
 *
 * MLV_Xml* MLV_load_xml(
 *     const char*     xml_file_path     Chemin d'accès du fichier xml.
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_get_string_value_from_xml: Permet d'accéder à l'interieur d'un champs 
 :                                donné du fichier xml.
 *
 * Cette fonction peut contenir un nombre variable de paramètres.
 * Comme avec la fonction printf les paramètres suplémentaires, 
 * situées après le paramètre xpath, permettent de construire des
 * requêtes xpath évolué.
 *
 * Par exemple,
 *
 * int id_batiment = 2;
 * char * type_salle = "informatique"
 * int id_salle = 4;
 * char* nom_salle;
 * MLV_get_string_value_from_xml(
 *		xml_data, &(nom_salle),
 *      "/batiment[%d]/salle[type=%s][%d]/nom",
 *      id_batiment, type_salle, id_salle
 * )
 * free( nom_salle ); // on oublie pas de libérer la mémoire après avoir 
 *                    // utilisé nom_salle
 *
 * permet de recupérer le contenu du champ nb_place situé dans la 4eme salle
 * informatique du 2eme batiment.
 *
 * Attention: Il ne faut pas oublier de libérer la mémoire associée au champs 
 *            result
 *
 * Cette fonction renvoie un code erreur si la fonction n'a pa reussie à 
 * extraire la donnée souhaitée du document xml.
 *
 * MLV_Xml_error MLV_get_string_value_from_xml(
 *     MLV_Xml* 	   xml_data,     les données xml.
 *     char**          result,       Un pointeur vers une addresse vide qui 
 *                                   contiendra l'addreese de la chaine de 
 *                                   caractères correspondant au résultat de 
 *                                   la fonction.
 *     const char*     xpath,        Le chemin d'acces
 *     ...                           Les paramètres suplémentaites pour 
 *                                   constuire un chemin d'acces évolué.
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_get_integer_value_from_xml: Permet de recuperer l'entier d'un champs donne
 *                                 du fichier xml.
 *
 * Tout comme la fonction MLV_get_string_value_from_xml, cette fonction peut 
 * contenir un nombre variable de paramètres.
 * Pour plus d'informations, veuillez lire la documentation de la fonction 
 * MLV_get_string_value_from_xml.
 *
 * Cette fonction renvoie un code erreur si la fonction n'a pa reussie à 
 * extraire la donnée souhaitée du document xml.
 *
 * MLV_Xml_error MLV_get_integer_value_from_xml(
 *     MLV_Xml*        xml_data,    les données xml.
 *     int*            result,      Un pointeur vers un entier dans lequel le 
 *                                  résultat de la fonction sera enregistré.
 *     const char*     xpath,       Le chemin d'accesles parametres de la fonction.
 *     ...                          Les paramètres suplémentaites pour 
 *                                  constuire un chemin d'acces évolué.
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_get_double_value_from_xml: Permet de recupere le reel d'un champs donne
 *                                du fichier xml.
 *
 * Tout comme la fonction MLV_get_string_value_from_xml, cette fonction peut 
 * contenir un nombre variable de paramètres.
 * Pour plus d'informations, veuillez lire la documentation de la fonction 
 * MLV_get_string_value_from_xml.
 *
 * Cette fonction renvoie un code erreur si la fonction n'a pa reussie à 
 * extraire la donnée souhaitée du document xml.
 *
 * MLV_Xml_error MLV_get_double_value_from_xml(
 *     MLV_Xml*        xml_data,     les données xml.
 *     double*         result,       Un pointeur vers un réel dans lequel le 
 *                                   résultat de la fonction sera enregistré.
 *     const char*     xpath,        Le chemin d'acces
 *     ...                           Les paramètres suplémentaites pour 
 *                                   constuire un chemin d'acces évolué.
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_free_xml: Libère la mémoire utilisée par les donnees du fichier xml.
 *
 * void MLV_free_xml(
 *     MLV_Xml*     xml_data     les données xml a supprimer.
 * );
 *
 * -----------------------------------------------------------------------------
 *
 *
 */

#include  <MLV/MLV_all.h>
#include  <stdlib.h>

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){

	int annee;
	MLV_Xml* config;
	char* text;
	double reel;
	int nb_copains,i;	

	//
	// On charge en mémoire le fichier XML contenant toutes les informations
	// nécessaires au fonctionnement du programme.
	//	
	config = MLV_load_xml( "informations.xml" );


	//
	// On récupère puis on affiche le texte contenu dans l'élément 
	// informations/nom_programme
	//
	if(
		MLV_get_string_value_from_xml(
			config, &(text), "/informations/nom_programme"
		)
	){
		fprintf( stderr, "Le fichier XML n'est pas valide, l'élément /informations/nom_programme est manquant.\n" );
		exit(1);
	}

	printf("Titre : %s\n", text);
	free(text);

	
	//
	// On récupère puis on affiche l'entier contenu dans l'élément 
	// informations/anne_production
	//
	if(
		MLV_get_integer_value_from_xml(
			config, &(annee), "/informations/annee_production"
		)
	){
		fprintf( stderr, "Le fichier XML n'est pas valide, l'élément /informations/annee_production est manquant ou ne contient pas d'entier.\n" );
		exit(1);
	};

	printf("Annee de production : %d \n", annee);

	
	//
	// On récupère puis on affiche le réél contenu dans l'élément 
	// informations/reel_prefere
	//
	if(
		MLV_get_double_value_from_xml(
			config, &(reel), "/informations/reel_prefere"
		)
	){
		fprintf( stderr, "Le fichier XML n'est pas valide, l'élément /informations/reel_prefere est manquant ou ne contient pas de réel.\n" );
		exit(1);
	}

	printf("Mon réel préféré : %f \n", reel);


	// 
	// On affiche les copines.
	//
	printf("Mes copines sont : \n");
	nb_copains = MLV_get_number_of_objects_from_xml( 
		config, "/informations/amis/ami[@sexe='femme']"
	);
	for( i = 0; i< nb_copains; i++ ){
		if(
			MLV_get_string_value_from_xml(
				config, &(text), "/informations/amis/ami[@sexe='femme'][%d]",
				i+1
			)
		){
			fprintf( stderr, "Le fichier XML n'est pas valide, l'élément /informations/amis/ami[@sexe='femme'][%d] est manquant.\n", i+1 );
			exit(1);
		}
		printf("    - %s \n", text);
		free( text );
	}


	//
	// On libère l'espace alloué pour le fichier xml.
	//
	MLV_free_xml( config );

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
