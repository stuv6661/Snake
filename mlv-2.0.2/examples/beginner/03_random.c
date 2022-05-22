/**
 *
 * Ce programme montre comment engendrer des entiers, réels et booléens
 * aléatoires.
 *
 * Pour cela, il utilise les fonctions suivantes:
 *
 *------------------------------------------------------------------------------
 * MLV_get_random_boolean:  Renvoie 0 ou 1 aléatoirement.
 *
 * int MLV_get_random_boolean();
 *
 *------------------------------------------------------------------------------
 * MLV_get_random_integer : Renvoie un entier aléatoire choisi dans un 
 *                          intervalle donné en paramètre.
 * 
 * int MLV_get_random_integer(
 *    int    begin,    Borne inférieur de l'intervalle ( inclusif )
 *    int    end       Borne supérieur de l'intervalle ( inclusif )
 * );
 *
 *------------------------------------------------------------------------------
 * MLV_get_random_double : Renvoie un réel aléatoire choisi dans un intervalle 
 *                         donné en paramètre.
 *
 * double MLV_get_random_double(
 *    double    begin,    Borne inférieur de l'intervalle ( inclusif )
 *    double    end       Borne supérieur de l'intervalle ( inclusif )
 * );
 *
 * Ces fonctions sont décrites dans le fichier MLV_random.h.
 * Leurs documentations sont accéssibles en tapant dans le terminal la commande
 * suivante :
 *
 * man MLV_random.h
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
	// Déclaration des variables qui contiendront les
	// nombres aléatoires qui seront engendrés
	//
	int resultat_i, resultat_b;
	double resultat_d;

	//
	// Récupère et affiche un entier aléatoire
	//
	resultat_i = MLV_get_random_integer(3,100);
	printf( "Entier aléatoire entre 3 et 100 : %i\n", resultat_i );

	//
	// Récupère et affiche un réel aléatoire
	//
	resultat_d = MLV_get_random_double( 3.0, 100.0 );
	printf( "Réel aléatoire entre 3.0 et 100.0 : %f\n", resultat_d );

	//
	// Récupère et affiche un booléen aléatoire
	//
	resultat_b = MLV_get_random_boolean();
	printf( "Boolean aléatoire : %i\n", resultat_b );

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
