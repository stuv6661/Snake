/**
 * Ce programme montre comment il est possible de faire jouer des échantillons 
 * sonores à votre programme.
 *
 * Cette démonstration utilise les fonctions suivantes : 
 *
 *------------------------------------------------------------------------------
 * MLV_load_sound : Charge un ficher contenant un échantillon sonore en mémoire.
 *
 *                  Cette fonction prends en paramètre le chemin d'acces du 
 *                  fichier contenant l'échantillon sonore et renvoie un 
 *                  pointeur vers l'espace mémoire où a été chargé l'échantillon
 *                  sonore.
 *
 *                  Les formats de fichier accepté sont les suivants : WAVE, 
 *                  AIFF, RIFF, OGG, and VOC.
 *
 *                  Cette fonction renvoie Null si le fichier n'a put être 
 *                  chargé en mémoire, un pointeur vers l'échantllon sonore.
 *
 * MLV_Sound* MLV_load_sound(
 *     const char*     file_sound     Chemin d'accès vers un fichier contenant
 *                                    d'échantillon sonore.
 * );
 * 
 *------------------------------------------------------------------------------
 * Ferme un échantillon sonore chargé en mémoire.
 *
 * void MLV_free_sound(
 *      MLV_Sound*     sound     L'échantillon sonore à fermer
 * );
 * 
 *------------------------------------------------------------------------------
 * Joue un échantillon sonore chargée en mémoire.
 *
 * void MLV_play_sound(
 *      MLV_Sound*     sound,     L'échantillon sonore à jouer.
 *      float          volume     Le volume sonore.
 * );
 * 
 *------------------------------------------------------------------------------
 * Arrête tous les échantillons sonores.
 *
 * void MLV_stop_all_sound();
 *
 *------------------------------------------------------------------------------
 *
 * POur plus d'informations, veuillez taper la commande suivante :
 * man MLV_ausio.h
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
	MLV_Keyboard_button touche;
	MLV_Sound* sound;
	
	//
	// Créer ne fenetre
	//
	MLV_create_window( "advanced - 4 - sound", "sound", 640, 480 );

	//
	// Initialise l'infrastructure son de la librairie MLV.
	//
	if( MLV_init_audio() ){
		fprintf(
			stderr,
			"L'infrasctructure audio de la librairie MLV ne s'est pas \
correctement initialisé."
		);
		exit(1);
	}

	//
	// Charge en mémoire un fichier contenant un morceau de musique.
	//
	sound = MLV_load_sound( "gallop.ogg" );

	//
	// Affiche la consigne
	//	
	MLV_draw_text( 
		10,100, 
		"Appuyer sur une touche pour faire jouer du son.", 
		MLV_COLOR_GREEN
	);
	MLV_draw_text(
		10,160,
		"Pour quitter, appuyer sur la touche echap.",
		MLV_COLOR_GREEN
	);
	MLV_actualise_window();

	//
	// Des que l'utilisateur appuye sur une touche, on joue de la musique.
	// Tant que l'utilisateur n'appuye pas sur echap, le programe continue 
	// à tourner
	//
	touche=MLV_KEYBOARD_NONE;
	while( touche != MLV_KEYBOARD_ESCAPE ){
		MLV_wait_keyboard( &touche, NULL, NULL);
		MLV_play_sound( sound, 1.0 );
	}

	//
	// Arrête toutes les échantillons.
	//
	MLV_stop_all_sounds();

	//
	// Ferme les morceaux de musiques qui ont été ouverts.
	//
	MLV_free_sound( sound );

	//
	// Arrête l'infrastructure son de la librairie MLV.
	//
	MLV_free_audio();

	//
	// Ferme la fenetre
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
