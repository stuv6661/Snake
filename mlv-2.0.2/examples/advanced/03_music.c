/**
 * Ce programme montre comment il est possible de faire jouer de la musique à
 * votre programme.
 * 
 * Cette démonstration  utilise les fonctions suivantes : 
 *
 *------------------------------------------------------------------------------
 * MLV_init_audio : Cette fonction initialise la libraire MLV pour pouvoir jouer
 *                  de la musique et des sons.
 *
 *                  Cette fonction renvoie 0 si l'infrastructure audio a été 
 *                  correctement initialisé, renvoie -1 sinon.
 *
 * int MLV_init_audio();
 * 
 *------------------------------------------------------------------------------
 * MLV_free_audio : Ferme proprement les différents périphériques audios.
 *
 * void MLV_free_audio();
 * 
 *------------------------------------------------------------------------------
 * MLV_load_music : Charge un ficher contenant de la musique en mémoire.
 *
 *                  Cette fonction prends en paramètre le chemin d'acces du 
 *                  fichier contenant la musique et renvoie un pointeur vers 
 *                  l'espace mémoire où a été chargé la musique.
 *
 *                  Les formats de fichier acceptés sont le .ogg, .mp3, .wav,
 *                  etc...
 *
 *                  Cette fonctione renvoie un pointeur vers la musique chargée
 *                  en mémoire, ou NULL si la librairie n'a pas réussi à charger
 *                  la musique en mémoire.
 *
 * MLV_Music* MLV_load_music(
 *     const char*     file_music     Chemin d'accès vers un fichier contenant 
 *                                    de la musique.
 * );
 * 
 *------------------------------------------------------------------------------
 * MLV_free_music : Ferme un morceau de musique chargé en mémoire.
 *
 * void MLV_free_music(
 *     MLV_Music*     music     Le morceau de musique à fermer
 * );
 * 
 *------------------------------------------------------------------------------
 * MLV_play_music : Joue une musique qui est chargée en mémoire.
 *
 * void MLV_play_music(
 *     MLV_Music*     music,     Le morceau de musique à jouer.
 *     float          volume,    Le volume sonore.
 *     int            loop       Le nombre de fois que le morceau doit être 
 *                               joué. Si loop est strivtement négatif, le 
 *                               morceau sera joué indéfiniment.
 * );
 * 
 *------------------------------------------------------------------------------
 * Arrête toutes les musiques.
 *
 * void MLV_stop_music();
 * 
 *------------------------------------------------------------------------------
 *
 * Pour plus d'information tapez la commande :
 * man MLV_audio.h
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
	//
	// Initialise l'infrastructure son de la librairie MLV.
	//
	MLV_init_audio( );

	//
	// Charge en mémoire un fichier contenant un morceau de musique.
	//
	MLV_Music* music = MLV_load_music( "fugue.ogg" );

	//
	// Joue la musique chargée en mémoire.
	//
	MLV_play_music( music, 1.0, -1 );


	//
	// Attend 20 seconde avant la fin du programme.
	//
	MLV_wait_seconds( 20 );

	//
	// Arrête toutes les musiques en cours d'exécution.
	//
	MLV_stop_music();

	//
	// Ferme les morceaux de musiques qui ont été ouverts.
	//
	MLV_free_music( music );

	//
	// Arrête l'infrastructure son de la librairie MLV.
	//
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
