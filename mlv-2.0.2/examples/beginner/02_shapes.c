/**
 *
 * Ce programme montre comment il est possible de dessiner les figures
 * géométriques suivantes :
 *
 * cercle
 * disque ( cercle plein )
 * ellipse
 * ellipse pleine
 * rectangle
 * rectangle plein
 * ligne
 * point
 * Courbe de Bézier
 * polygone
 * polygone plein
 *
 * Pour cela le programme utilise les fonctions suivantes :
 *
 *------------------------------------------------------------------------------
 * MLV_draw_circle: Dessine un cercle à une position et un rayon spécifiés en
 *                  paramètres.
 *   
 * void MLV_draw_circle(
 *    int        x,         Coordonnée en X du centre du cercle
 *    int        y,         Coordonnée en Y du centre du cercle
 *    int        radius,    Rayon du cercle
 *    MLV_Color  color      Couleur du tracé
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_draw_filled_circle : Dessine un disque plein dont le centre et le rayon
 *                          sont passés en parametres.
 *
 * void MLV_draw_filled_circle(
 *    int         x,          Coordonnée en X du centre du cercle
 *    int         y,          Coordonnée en Y du centre du cercle
 *    int         radius,     Rayon du cercle
 *    MLV_Color   color       Couleur du tracé
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_draw_ellipse : Dessine une ellipse dont la position, les rayons et la
 *                    couleur sont passés en paramètres.
 * 
 * MLV_draw_ellipse(
 *     int       x,         Coordonnée en X du centre de l'ellipse
 *     int       y,         Coordonnée en Y du centre de l'ellipse
 *     int       radius_x,  Rayon en X de l'ellipse
 *     int       radius_y,  Rayon en Y de l'ellipse
 *     MLV_Color color      Couleur du tracé
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_draw_filled_ellipse : Dessine une ellipse pleine dont la position, les 
 *                           rayons et la couleur sont passés en paramètres.
 *
 * void MLV_draw_filled_ellipse(
 *     int       x,         Coordonnee en X du centre de l'ellipse
 *     int       y,         Coordonnee en Y du centre de l'ellipse
 *     int       radius_x,  Rayon en X de l'ellipse
 *     int       radius_y,  Rayon en Y de l'ellipse
 *     MLV_Color color      Couleur du tracé
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_draw_rectangle : Dessine un rectangle dont la taille, la couleur et la
 *                      position du sommet Nord-Ouest sont données en 
 *                      paramètres.
 *
 * void MLV_draw_rectangle(
 *     int       x,       Coordonnée en X du sommet Nord-Ouest du rectangle
 *     int       y,       Coordonnée en Y du sommet Nord-Ouest du rectangle
 *     int       width,   Largeur du rectangle
 *     int       height,  Hauteur du rectangle
 *     MLV_Color color    Couleur du tracé
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_draw_filled_rectangle : Dessine un rectangle dont la taille, la couleur 
 *                             et la position du sommet Nord-Ouest sont données
 *                             en paramètres.
 * void MLV_draw_filled_rectangle(
 *     int       x,       Coordonnée en X du sommet Nord-Ouest du rectangle
 *     int       y,       Coordonnée en Y du sommet Nord-Ouest du rectangle
 *     int       width,   Largeur du rectangle
 *     int       height,  Hauteur du rectangle
 *     MLV_Color color    Couleur du tracé
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_draw_line : Dessine une ligne dont les coordonnées des deux extrémités
 *                 sont passées en paramètres. 
 * void MLV_draw_line(
 *    int       x1,       Coordonnée en X de la première extrémité de la ligne
 *    int       y1,       Coordonnée en Y de la première extrémité de la ligne
 *    int       x2,       Coordonnée en X de la deuxième extrémité de la ligne
 *    int       y2,       Coordonnée en Y de la deuxième extrémité de la ligne
 *    MLV_Color color     Couleur du tracé
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_draw_point : Dessine un point dont les coordonées sont passées
 *                  en paramètres.
 *
 * void MLV_draw_point(
 *    int       x,      Coordonnée en X du point
 *    int       y,      Coordonnée en Y du point
 *    MLV_Color color   Couleur du tracé
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_draw_bezier_curve: Dessine une courbe de Bézier à partir d'une liste de
 * sommets.
 *
 * void MLV_draw_bezier_curve( 
 *    const int*    vx,         La liste des coordonnées en X des différents 
 *                              sommets de la courbe.
 *    const int*    vy,         La liste des coordonnées en Y des différents
 *                              sommets de la courbe.
 *    int           npoints,    Le nombre de sommets de la courbe de Bézier.
 *    MLV_Color     color       La couleur du tracé
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_draw_polygon: Dessine un polygone à partir d'une liste de sommets.
 *
 * void MLV_draw_polygon( 
 *    const int*    vx,         La liste des coordonnées en X des différents
 *                              sommets du polygone.
 *    const int*    vy,         La liste des coordonnées en Y des différents
 *                              sommets du polygone.
 *    int           npoints,    Le nombre de sommets du polygone.
 *    MLV_Color     color       La couleur du tracé
 * );
 *
 * -----------------------------------------------------------------------------
 * MLV_draw_polygon: Dessine un polygone plein à partir d'une liste de sommets.
 *
 * void MLV_draw_filled_polygon( 
 *    const int*    vx,         La liste des coordonnées en X des différents
 *                              sommets du polygone.
 *    const int*    vy,         La liste des coordonnées en Y des différents
 *                              sommets du polygone.
 *    int           npoints,    Le nombre de sommets du polygone.
 *    MLV_Color     color       La couleur du tracé
 * );
 *
 * -----------------------------------------------------------------------------
 *
 * Il existe d'autres fonctions de dessin. Vous les trouverez en consultant 
 * le fichier MLV_shape.h ou en tapant dans le terminal la commande :
 *
 * man MLV_shape.h
 */

#include <MLV/MLV_all.h>


//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main(int argc, char *argv[]){
	//
	// Créé et affiche la fenêtre
	//
	MLV_create_window( "beginner - 2 - shapes", "shapes", 640, 480 );
	
	//
	// Dessine des cercles, ellipses, rectangles, lignes et points
	//
	MLV_draw_circle( 20, 20, 10, MLV_COLOR_PURPLE );
	MLV_draw_filled_circle( 50, 20, 10, MLV_COLOR_BROWN );
	MLV_draw_ellipse( 100, 20, 30, 10, MLV_COLOR_CYAN );
	MLV_draw_filled_ellipse( 170, 20, 30, 10, MLV_COLOR_PINK );
	MLV_draw_rectangle( 10, 50, 40, 20, MLV_COLOR_BLUE );
	MLV_draw_filled_rectangle( 70, 50, 40, 20, MLV_COLOR_GREEN );
	MLV_draw_line( 120, 50, 160, 90 , MLV_COLOR_WHITE );
	MLV_draw_point( 10, 110, MLV_COLOR_RED );

	//
	// Dessine une courbe de Bézier avec ses sommets
	//
	int coordonnee_x[4] = { 10, 50, 90, 130 };
	int coordonnee_y[4] = { 150, 190, 150, 190 };
	MLV_draw_bezier_curve( coordonnee_x, coordonnee_y, 4, MLV_COLOR_RED );
	MLV_draw_circle( coordonnee_x[0], coordonnee_y[0], 3, MLV_COLOR_GREEN );
	MLV_draw_circle( coordonnee_x[1], coordonnee_y[1], 3, MLV_COLOR_GREEN );
	MLV_draw_circle( coordonnee_x[2], coordonnee_y[2], 3, MLV_COLOR_GREEN );
	MLV_draw_circle( coordonnee_x[3], coordonnee_y[3], 3, MLV_COLOR_GREEN );

	//Dessine un polygone avec ses sommets
	int coordonnee1_x[4] = { 200, 240, 320, 280 };
	int coordonnee1_y[4] = { 150, 190, 190, 150 };
	MLV_draw_filled_polygon( coordonnee1_x, coordonnee1_y, 4, MLV_COLOR_BLUE );
	MLV_draw_polygon( coordonnee1_x, coordonnee1_y, 4, MLV_COLOR_RED );
	MLV_draw_circle( coordonnee1_x[0], coordonnee1_y[0], 3, MLV_COLOR_GREEN );
	MLV_draw_circle( coordonnee1_x[1], coordonnee1_y[1], 3, MLV_COLOR_GREEN );
	MLV_draw_circle( coordonnee1_x[2], coordonnee1_y[2], 3, MLV_COLOR_GREEN );
	MLV_draw_circle( coordonnee1_x[3], coordonnee1_y[3], 3, MLV_COLOR_GREEN );

	//
	// Affiche du texte
	//
	MLV_draw_text(
		10, 120, 
		"Juste au dessus de cette ligne, il y a un pixel rouge.",
		MLV_COLOR_MAGENTA
	);

	//
	// Met à jour l'affichage.
	//
	MLV_actualise_window();

	//
	// Attend 10 secondes avant la fin du programme.
	//
	MLV_wait_seconds( 10 );

	//
	// Fermer la fenêtre
	//
	MLV_free_window();
MLV_actualise_window();MLV_actualise_window();MLV_actualise_window();	return 0;
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
