#include <MLV/MLV_all.h>

//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
int main( int argc, char *argv[] ){
	//
	// Les playlists ne sont pas encore implémentées.
	//
	printf(
		"Les playlists ne sont pas encore implémentées dans la librairie MLV.\n"
	);

	MLV_create_window( "beginner - 1 - hello world", "hello world", 640, 480 );

	MLV_draw_text(
		10, 120, 
		"Les playlists ne sont pas encore implémentées !",
		MLV_COLOR_MAGENTA
	);

	MLV_actualise_window();

	MLV_wait_seconds( 10 );

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
