/**
 *
 * Ce programme affiche différentes informations de temps.
 *
 * Pour cela le programme  utilise les fonctions suivantes : 
 *
 *------------------------------------------------------------------------------
 * MLV_get_time : Renvoie le nombre de millisecondes écoulées depuis le début de
 *                l'initialisation de la librairie MLV
 *                ( avec MLV_create_window ).
 *
 * int MLV_get_time(
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_get_date : Donne la date du jour (seconde/heure/jour/mois/annee).
 *
 *                L'année est donnée depuis l'an 0.
 *
 *                Une valeur nulle peut être passé en paramètre de la fonction.
 *                Dans ce cas, le paramètre est ignorée par la fonction.
 *
 *                Cette fonction utilise la fonction ctime présent dane time.h.
 *                Vous pouvez utilisez cette fonction directement à la place de
 *                MLV_get_date()
 *                Faites    man time.h  ou  man ctime  pour plus d'informations.
 *
 *     Cette fonction Renvoie 1 si le decalage heure d'hivers-été a été pris en
 *     compte, 0 si il ne l'a pas été et -1 si l'information n'est pas
 *     disponible.
 *
 * int MLV_get_date(
 *     int*     seconds,            Le nombre de secondes écoulées depuis le 
 *                                  dernier changement de minute.
 *     int*     minutes,            Le nombre de minutes écoulées depuis le
 *                                  dernier changement d'heure
 *     int*     hours,              Le nombre d'heures écoulées depuis minuit.
 *     int*     day,                Le quantième du mois
 *     int*     month,              Le nombre de mois écoulés depuis le début de
 *                                  l'année.
 *     int*     year,               Le nombre d'année depuis l'an 0.
 *     int*     day_of_the_week     Le jour de la semaine ( 0: Lundi, 1:Mardi,
 *                                  ..., 6:Dimanche).
 * );
 *
 *------------------------------------------------------------------------------
 */

#include <MLV/MLV_all.h>
#include <stdio.h>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){
	int elapsed_time;
	int seconds, minutes, hours, day, month, year, day_of_the_week;
	const char* days[7] ={ 
		"Dimanche", "Lundi", "Mardi", "Mercredi","Jeudi", "Vendredi", "Samedi"
	};
	const char* months[12] ={ 
		"Janvier", "Févier", "Mars", "Avril","Mai", "Juin", "Juillet",
		"Août", "Septembre", "Octobre", "Novembre", "Décembre"
	};

	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "medium - 7 - time", "time", 640, 480 );

	while( 1 ){

		MLV_clear_window( MLV_COLOR_BLACK );

		//
		// On récupère le temps écoulé depuis le debut de l'éxécution du 
		// programme
		//
		elapsed_time =  MLV_get_time();
		//
		// On affiche l'infomration obtenue
		//
		MLV_draw_text(
			10, 120, 
			"Temps écoulé depuis le debut du programme : %d ms",
			MLV_COLOR_GREEN, elapsed_time
		);


		//
		// On récupère la date d'aujourd'hui et l'heure courante
		//
		MLV_get_date(
			&seconds, &minutes, &hours,
			&day, &month, &year,
			&day_of_the_week
		);
		//
		// On affiche les jours
		//
		MLV_draw_text(
			10, 240, 
			"Date :  %s, %.2d %s %d",
			MLV_COLOR_GREEN,
			days[day_of_the_week], day, months[month], year			
		);
		//
		// On affiche l'heure
		//
		MLV_draw_text(
			10, 260, 
			"Heure :  %d h %.2d : %.2d",
			MLV_COLOR_GREEN,
			hours, minutes, seconds			
		);

		//
		// On met à jour l'affichage
		//		
		MLV_actualise_window();

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
