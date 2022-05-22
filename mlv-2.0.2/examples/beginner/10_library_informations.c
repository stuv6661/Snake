/**
 *
 * Ce programme a pour but de presenter les fonctions permettant de récuperer
 * des informations concernant la librairie.
 *
 * Ce programme présente aussi rapidement la licence sous laquelle est distribuée
 * la librairie MLV.
 * 
 *------------------------------------------------------------------------------
 * MLV_get_package_name : Renvoie le nom de la librairie.
 *
 * const char* MLV_get_package_name( );
 *
 *------------------------------------------------------------------------------
 * MLV_get_version : Renvoie la version de la librairie
 *
 * const char* MLV_get_version( );
 *
 *------------------------------------------------------------------------------
 * MLV_get_licence : Renvoie la licence de la librairie.
 *
 * const char* MLV_get_licence( );
 *
 *------------------------------------------------------------------------------
 * MLV_get_web_distribution : Renvoie l'addresse internet où l'on peut trouver 
 *                            les code source de la librairie.
 *
 * const char* MLV_get_web_distribution( );
 *
 *------------------------------------------------------------------------------
 *
 * Pour plus d'information veuillez taper la commande
 * man MLV_information.h
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
	//
	// Déclaration et initialisation de la variable qui codera
	// la taille entre deux lignes dans un texte
	//
	int taille_interlinge = 9;

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window(
		"beginner - 10 - library informations", "library informations", 640, 480
	);

	//
	// Affiche quelques informations concernant la librairie MLV
	//
	MLV_draw_adapted_text_box(
		10,10,
		"Nom de la bibliothèque : %s     Depôt : %s\nVersion : %s  ( révision : %s  )\nLicence : %s\nAddresse internet où se trouve le code source de la bibliothèque :\n    %s\n\nCette bibliothèque est distibuée sous le terme de la licence %s. Vous trouverez une\ncopie de cette licence dans le fichier gpl.txt du répertoire courant.\n\nLa licence %s  garantit à l'utilisateur les droits suivants :\n    1. La liberté d'exécuter le logiciel, pour n'importe quel usage ;\n    2. La liberté d'étudier le fonctionnement d'un programme et de l'adapter \n        à ses besoins, ce qui passe par l'accès aux codes sources ;\n    3. La liberté de redistribuer des copies ;\n    4. La liberté de rendre publiques des versions modifiées pour en faire \n       bénéficier la communauté.\n\nLa licence GPL impose aussi quelques devoirs. Par exemple, si vous distribuez un\n programme utilisant MLV, vous devez le faire sous une licence compatible GPL.",
		taille_interlinge,
		MLV_COLOR_BLACK, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		MLV_TEXT_LEFT,
		MLV_get_package_name(),
		MLV_get_repository( ),
		MLV_get_version(),
		MLV_get_revision_of_revision_control_software( ),
		MLV_get_licence(),
		MLV_get_web_distribution(),
		MLV_get_licence(),
		MLV_get_licence()
	);

	//
	// Met à jour de l'affichage
	//
	MLV_actualise_window();
	
	//
	// Attends que l'utilisateur appuye sur la touche echap pour quitter.
	//
	MLV_Keyboard_button touche=MLV_KEYBOARD_NONE;
	while( touche != MLV_KEYBOARD_ESCAPE ){
		MLV_wait_keyboard(&touche,NULL,NULL);
	}

	//
	// Ferme la fenêtre
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
