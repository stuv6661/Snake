/**
 * Ce programme montre comment il est possible de récupérer du texte demandé
 * à l'utilisateur à l'aide d'une boîte de saisie.
 *
 * Pour cela le programme utilise la fonction :
 *
 *------------------------------------------------------------------------------
 * MLV_wait_input_box : Suspend l'exécution du programme, affiche deux zonnes de 
 *                   textes.
 *                   La première zone n'est pas modifiable et sert à afficher un
 *                   message d'information. La deuxième est vide et peut être 
 *                   modifiée par l'utilisateur.
 *                   Lorsque l'utilisateur appuie sur la touche entrée, le texte
 *                   qui se trouve dans la zone de texte est renvoyé par la 
 *                   fonction grâce au paramètre text.
 *                   Le texte, la taille et les couleurs des différents éléments
 *                   sont paramétrables grâces aux différents paramètres de la 
 *                   fonction.
 *
 *     MLV_wait_input_box alloue lui même la mémoire associée au texte.
 *     Une fois l'espace mémoire alloué, il ne le libère à aucun moment.
 *     Cette tâche est laissé au programmeur.
 *
 * void MLV_wait_input_box(
 *    int            sommetHautGaucheX,     Coordonnee en X du coin Nord-Ouest 
 *                                          de la boîte de saisie.
 *    int            sommetHautGaucheY,     Coordonnee en Y du coin Nord-Ouest
 *                                          de la boîte de saisie
 *    int            sommetBasDroitX,       Coordonnee en X du coin Sud-Est de
 *                                          la boîte de saisie.
 *    int            sommetBasDroitY,       Coordonnee en Y du coin Sud-Est de
 *                                          la boîte de saisie.
 *    MLV_Color      borderColor,           Couleur de la bordure de la boîte
 *                                          de saisie.
 *    MLV_Color      textColor,             Couleur du texte de la boîte de
 *                                          saisie.
 *    MLV_Color      backgroundColor,       Couleur de fond de la boîte de
 *                                          saisie.
 *    const char*    informativeMessage,    Message à afficher devant la boîte 
 *                                          de saisie.
 *    char**         text                   Adresse où sera placé la réponse
 *                                          donnée par l'utilisateur.
 * );
 *------------------------------------------------------------------------------
 *
 */

#include <MLV/MLV_all.h>
#include <stdlib.h>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){
	char* text;     // adresse du texte où se trouvera la réponse entrée dans
	                // la boîte de saisie par l'utilisateur.
	    // Ici nous n'allouons pas de mémoire. En effet, l'allocation est faite
	    // ultèrieurement par la fonction MLV_wait_input_box().
	    // Nous ne devrons pas oublier de liberer la mémoire à la fin du
	    // programme.
	
	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "beginner - 7 - input box", "input box", 640, 480 );

	//
	// Affiche la question
	//
	MLV_draw_text(
		10, 10,
		"Veuillez entrer un message dans la fenêtre ci-dessous.",
		MLV_COLOR_GREEN
	);
	MLV_actualise_window();

	//
	// Demande la réponse à la question en utilisant une boîte de saisie
	//
	MLV_wait_input_box(
		10,70,
		200,90,
		MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLACK,
		"message : ",
		&text
	);

	//
	// Affiche le texte qui a été tapé par l'utilisateur dans la boîte de 
	// saisie
	//
	MLV_draw_text( 10, 80, text, MLV_COLOR_GREEN );
	MLV_actualise_window();

	//
	// Attend 2 secondes
	//	
	MLV_wait_seconds( 2 );
	
	//
	// Libère la mémoire utilisée
	//	
	free( text );
	
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
