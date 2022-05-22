/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012 Adrien Boussicault, Marc Zipstein
 *
 *
 *    This library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "MLV_color.h"

#include "memory_management.h"

#include "warning_error.h"

/******************************************************************************/
/* RGBA : Converti une couleur RGBA encodee à l'aide de 4 entiers 8 bits en   */
/*                  en une couleur encodee a l'aide d'1 entier 16 bits.       */
/*                                                                            */
/*                  Dans la bibliothèque SDL_GFX les couleurs sont encodées sur  */
/*                  32 bits : 8 bits pour la composante en rouge de           */
/*                  l'image (R), 8 bits pour la composante verte (G), 8 bit   */
/*                  pour la composante bleu (B) et enfin 8 bits pour la       */
/*                  composante alpha qui correspond a la transparence (A)     */
/*                                                                            */
/* MLV_Color                              Couleur codee sur un entier 32 bits */
/* rgba (                                                                     */
/*    Uint8 red,                    Composante rouge de la couleur            */
/*    Uint8 greene,                 Composante verte de la couleur            */
/*    Uint8 blue,                   Composante bleu de la couleur             */
/*    Uint8 alpha)                  Transparence de la couleur                */
/******************************************************************************/
MLV_Color MLV_rgba(
    Uint8 red,
    Uint8 green,
    Uint8 blue,
    Uint8 alpha
){
    return (((((( (MLV_Color) red) << 8) + green) << 8) + blue) << 8) + alpha;
}

MLV_Color MLV_convert_rgba_to_color(
	Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha
){
	return MLV_rgba( red, green, blue, alpha );
}

void MLV_convert_color_to_rgba(
	MLV_Color color, Uint8* red, Uint8* green, Uint8* blue, Uint8* alpha
){
	*alpha = color;
	color = color >> 8; *blue = color;
	color = color >> 8; *green = color;
	color = color >> 8; *red = color;
}

const char* MLV_convert_color_to_string( MLV_Color color ){
	if( color == MLV_COLOR_SNOW ){
		return "MLV_COLOR_SNOW";
	}
	if( color == MLV_COLOR_GHOST_WHITE ){
		return "MLV_COLOR_GHOST_WHITE";
	}
	if( color == MLV_COLOR_GHOSTWHITE ){
		return "MLV_COLOR_GHOSTWHITE";
	}
	if( color == MLV_COLOR_WHITE_SMOKE ){
		return "MLV_COLOR_WHITE_SMOKE";
	}
	if( color == MLV_COLOR_WHITESMOKE ){
		return "MLV_COLOR_WHITESMOKE";
	}
	if( color == MLV_COLOR_GAINSBORO ){
		return "MLV_COLOR_GAINSBORO";
	}
	if( color == MLV_COLOR_FLORAL_WHITE ){
		return "MLV_COLOR_FLORAL_WHITE";
	}
	if( color == MLV_COLOR_FLORALWHITE ){
		return "MLV_COLOR_FLORALWHITE";
	}
	if( color == MLV_COLOR_OLD_LACE ){
		return "MLV_COLOR_OLD_LACE";
	}
	if( color == MLV_COLOR_OLDLACE ){
		return "MLV_COLOR_OLDLACE";
	}
	if( color == MLV_COLOR_LINEN ){
		return "MLV_COLOR_LINEN";
	}
	if( color == MLV_COLOR_ANTIQUE_WHITE ){
		return "MLV_COLOR_ANTIQUE_WHITE";
	}
	if( color == MLV_COLOR_ANTIQUEWHITE ){
		return "MLV_COLOR_ANTIQUEWHITE";
	}
	if( color == MLV_COLOR_PAPAYA_WHIP ){
		return "MLV_COLOR_PAPAYA_WHIP";
	}
	if( color == MLV_COLOR_PAPAYAWHIP ){
		return "MLV_COLOR_PAPAYAWHIP";
	}
	if( color == MLV_COLOR_BLANCHED_ALMOND ){
		return "MLV_COLOR_BLANCHED_ALMOND";
	}
	if( color == MLV_COLOR_BLANCHEDALMOND ){
		return "MLV_COLOR_BLANCHEDALMOND";
	}
	if( color == MLV_COLOR_BISQUE ){
		return "MLV_COLOR_BISQUE";
	}
	if( color == MLV_COLOR_PEACH_PUFF ){
		return "MLV_COLOR_PEACH_PUFF";
	}
	if( color == MLV_COLOR_PEACHPUFF ){
		return "MLV_COLOR_PEACHPUFF";
	}
	if( color == MLV_COLOR_NAVAJO_WHITE ){
		return "MLV_COLOR_NAVAJO_WHITE";
	}
	if( color == MLV_COLOR_NAVAJOWHITE ){
		return "MLV_COLOR_NAVAJOWHITE";
	}
	if( color == MLV_COLOR_MOCCASIN ){
		return "MLV_COLOR_MOCCASIN";
	}
	if( color == MLV_COLOR_CORNSILK ){
		return "MLV_COLOR_CORNSILK";
	}
	if( color == MLV_COLOR_IVORY ){
		return "MLV_COLOR_IVORY";
	}
	if( color == MLV_COLOR_LEMON_CHIFFON ){
		return "MLV_COLOR_LEMON_CHIFFON";
	}
	if( color == MLV_COLOR_LEMONCHIFFON ){
		return "MLV_COLOR_LEMONCHIFFON";
	}
	if( color == MLV_COLOR_SEASHELL ){
		return "MLV_COLOR_SEASHELL";
	}
	if( color == MLV_COLOR_HONEYDEW ){
		return "MLV_COLOR_HONEYDEW";
	}
	if( color == MLV_COLOR_MINT_CREAM ){
		return "MLV_COLOR_MINT_CREAM";
	}
	if( color == MLV_COLOR_MINTCREAM ){
		return "MLV_COLOR_MINTCREAM";
	}
	if( color == MLV_COLOR_AZURE ){
		return "MLV_COLOR_AZURE";
	}
	if( color == MLV_COLOR_ALICE_BLUE ){
		return "MLV_COLOR_ALICE_BLUE";
	}
	if( color == MLV_COLOR_ALICEBLUE ){
		return "MLV_COLOR_ALICEBLUE";
	}
	if( color == MLV_COLOR_LAVENDER ){
		return "MLV_COLOR_LAVENDER";
	}
	if( color == MLV_COLOR_LAVENDER_BLUSH ){
		return "MLV_COLOR_LAVENDER_BLUSH";
	}
	if( color == MLV_COLOR_LAVENDERBLUSH ){
		return "MLV_COLOR_LAVENDERBLUSH";
	}
	if( color == MLV_COLOR_MISTY_ROSE ){
		return "MLV_COLOR_MISTY_ROSE";
	}
	if( color == MLV_COLOR_MISTYROSE ){
		return "MLV_COLOR_MISTYROSE";
	}
	if( color == MLV_COLOR_WHITE ){
		return "MLV_COLOR_WHITE";
	}
	if( color == MLV_COLOR_BLACK ){
		return "MLV_COLOR_BLACK";
	}
	if( color == MLV_COLOR_DARK_SLATE_GRAY ){
		return "MLV_COLOR_DARK_SLATE_GRAY";
	}
	if( color == MLV_COLOR_DARKSLATEGRAY ){
		return "MLV_COLOR_DARKSLATEGRAY";
	}
	if( color == MLV_COLOR_DARK_SLATE_GREY ){
		return "MLV_COLOR_DARK_SLATE_GREY";
	}
	if( color == MLV_COLOR_DARKSLATEGREY ){
		return "MLV_COLOR_DARKSLATEGREY";
	}
	if( color == MLV_COLOR_DIM_GRAY ){
		return "MLV_COLOR_DIM_GRAY";
	}
	if( color == MLV_COLOR_DIMGRAY ){
		return "MLV_COLOR_DIMGRAY";
	}
	if( color == MLV_COLOR_DIM_GREY ){
		return "MLV_COLOR_DIM_GREY";
	}
	if( color == MLV_COLOR_DIMGREY ){
		return "MLV_COLOR_DIMGREY";
	}
	if( color == MLV_COLOR_SLATE_GRAY ){
		return "MLV_COLOR_SLATE_GRAY";
	}
	if( color == MLV_COLOR_SLATEGRAY ){
		return "MLV_COLOR_SLATEGRAY";
	}
	if( color == MLV_COLOR_SLATE_GREY ){
		return "MLV_COLOR_SLATE_GREY";
	}
	if( color == MLV_COLOR_SLATEGREY ){
		return "MLV_COLOR_SLATEGREY";
	}
	if( color == MLV_COLOR_LIGHT_SLATE_GRAY ){
		return "MLV_COLOR_LIGHT_SLATE_GRAY";
	}
	if( color == MLV_COLOR_LIGHTSLATEGRAY ){
		return "MLV_COLOR_LIGHTSLATEGRAY";
	}
	if( color == MLV_COLOR_LIGHT_SLATE_GREY ){
		return "MLV_COLOR_LIGHT_SLATE_GREY";
	}
	if( color == MLV_COLOR_LIGHTSLATEGREY ){
		return "MLV_COLOR_LIGHTSLATEGREY";
	}
	if( color == MLV_COLOR_GRAY ){
		return "MLV_COLOR_GRAY";
	}
	if( color == MLV_COLOR_GREY ){
		return "MLV_COLOR_GREY";
	}
	if( color == MLV_COLOR_LIGHT_GREY ){
		return "MLV_COLOR_LIGHT_GREY";
	}
	if( color == MLV_COLOR_LIGHTGREY ){
		return "MLV_COLOR_LIGHTGREY";
	}
	if( color == MLV_COLOR_LIGHT_GRAY ){
		return "MLV_COLOR_LIGHT_GRAY";
	}
	if( color == MLV_COLOR_LIGHTGRAY ){
		return "MLV_COLOR_LIGHTGRAY";
	}
	if( color == MLV_COLOR_MIDNIGHT_BLUE ){
		return "MLV_COLOR_MIDNIGHT_BLUE";
	}
	if( color == MLV_COLOR_MIDNIGHTBLUE ){
		return "MLV_COLOR_MIDNIGHTBLUE";
	}
	if( color == MLV_COLOR_NAVY ){
		return "MLV_COLOR_NAVY";
	}
	if( color == MLV_COLOR_NAVY_BLUE ){
		return "MLV_COLOR_NAVY_BLUE";
	}
	if( color == MLV_COLOR_NAVYBLUE ){
		return "MLV_COLOR_NAVYBLUE";
	}
	if( color == MLV_COLOR_CORNFLOWER_BLUE ){
		return "MLV_COLOR_CORNFLOWER_BLUE";
	}
	if( color == MLV_COLOR_CORNFLOWERBLUE ){
		return "MLV_COLOR_CORNFLOWERBLUE";
	}
	if( color == MLV_COLOR_DARK_SLATE_BLUE ){
		return "MLV_COLOR_DARK_SLATE_BLUE";
	}
	if( color == MLV_COLOR_DARKSLATEBLUE ){
		return "MLV_COLOR_DARKSLATEBLUE";
	}
	if( color == MLV_COLOR_SLATE_BLUE ){
		return "MLV_COLOR_SLATE_BLUE";
	}
	if( color == MLV_COLOR_SLATEBLUE ){
		return "MLV_COLOR_SLATEBLUE";
	}
	if( color == MLV_COLOR_MEDIUM_SLATE_BLUE ){
		return "MLV_COLOR_MEDIUM_SLATE_BLUE";
	}
	if( color == MLV_COLOR_MEDIUMSLATEBLUE ){
		return "MLV_COLOR_MEDIUMSLATEBLUE";
	}
	if( color == MLV_COLOR_LIGHT_SLATE_BLUE ){
		return "MLV_COLOR_LIGHT_SLATE_BLUE";
	}
	if( color == MLV_COLOR_LIGHTSLATEBLUE ){
		return "MLV_COLOR_LIGHTSLATEBLUE";
	}
	if( color == MLV_COLOR_MEDIUM_BLUE ){
		return "MLV_COLOR_MEDIUM_BLUE";
	}
	if( color == MLV_COLOR_MEDIUMBLUE ){
		return "MLV_COLOR_MEDIUMBLUE";
	}
	if( color == MLV_COLOR_ROYAL_BLUE ){
		return "MLV_COLOR_ROYAL_BLUE";
	}
	if( color == MLV_COLOR_ROYALBLUE ){
		return "MLV_COLOR_ROYALBLUE";
	}
	if( color == MLV_COLOR_BLUE ){
		return "MLV_COLOR_BLUE";
	}
	if( color == MLV_COLOR_DODGER_BLUE ){
		return "MLV_COLOR_DODGER_BLUE";
	}
	if( color == MLV_COLOR_DODGERBLUE ){
		return "MLV_COLOR_DODGERBLUE";
	}
	if( color == MLV_COLOR_DEEP_SKY_BLUE ){
		return "MLV_COLOR_DEEP_SKY_BLUE";
	}
	if( color == MLV_COLOR_DEEPSKYBLUE ){
		return "MLV_COLOR_DEEPSKYBLUE";
	}
	if( color == MLV_COLOR_SKY_BLUE ){
		return "MLV_COLOR_SKY_BLUE";
	}
	if( color == MLV_COLOR_SKYBLUE ){
		return "MLV_COLOR_SKYBLUE";
	}
	if( color == MLV_COLOR_LIGHT_SKY_BLUE ){
		return "MLV_COLOR_LIGHT_SKY_BLUE";
	}
	if( color == MLV_COLOR_LIGHTSKYBLUE ){
		return "MLV_COLOR_LIGHTSKYBLUE";
	}
	if( color == MLV_COLOR_STEEL_BLUE ){
		return "MLV_COLOR_STEEL_BLUE";
	}
	if( color == MLV_COLOR_STEELBLUE ){
		return "MLV_COLOR_STEELBLUE";
	}
	if( color == MLV_COLOR_LIGHT_STEEL_BLUE ){
		return "MLV_COLOR_LIGHT_STEEL_BLUE";
	}
	if( color == MLV_COLOR_LIGHTSTEELBLUE ){
		return "MLV_COLOR_LIGHTSTEELBLUE";
	}
	if( color == MLV_COLOR_LIGHT_BLUE ){
		return "MLV_COLOR_LIGHT_BLUE";
	}
	if( color == MLV_COLOR_LIGHTBLUE ){
		return "MLV_COLOR_LIGHTBLUE";
	}
	if( color == MLV_COLOR_POWDER_BLUE ){
		return "MLV_COLOR_POWDER_BLUE";
	}
	if( color == MLV_COLOR_POWDERBLUE ){
		return "MLV_COLOR_POWDERBLUE";
	}
	if( color == MLV_COLOR_PALE_TURQUOISE ){
		return "MLV_COLOR_PALE_TURQUOISE";
	}
	if( color == MLV_COLOR_PALETURQUOISE ){
		return "MLV_COLOR_PALETURQUOISE";
	}
	if( color == MLV_COLOR_DARK_TURQUOISE ){
		return "MLV_COLOR_DARK_TURQUOISE";
	}
	if( color == MLV_COLOR_DARKTURQUOISE ){
		return "MLV_COLOR_DARKTURQUOISE";
	}
	if( color == MLV_COLOR_MEDIUM_TURQUOISE ){
		return "MLV_COLOR_MEDIUM_TURQUOISE";
	}
	if( color == MLV_COLOR_MEDIUMTURQUOISE ){
		return "MLV_COLOR_MEDIUMTURQUOISE";
	}
	if( color == MLV_COLOR_TURQUOISE ){
		return "MLV_COLOR_TURQUOISE";
	}
	if( color == MLV_COLOR_CYAN ){
		return "MLV_COLOR_CYAN";
	}
	if( color == MLV_COLOR_LIGHT_CYAN ){
		return "MLV_COLOR_LIGHT_CYAN";
	}
	if( color == MLV_COLOR_LIGHTCYAN ){
		return "MLV_COLOR_LIGHTCYAN";
	}
	if( color == MLV_COLOR_CADET_BLUE ){
		return "MLV_COLOR_CADET_BLUE";
	}
	if( color == MLV_COLOR_CADETBLUE ){
		return "MLV_COLOR_CADETBLUE";
	}
	if( color == MLV_COLOR_MEDIUM_AQUAMARINE ){
		return "MLV_COLOR_MEDIUM_AQUAMARINE";
	}
	if( color == MLV_COLOR_MEDIUMAQUAMARINE ){
		return "MLV_COLOR_MEDIUMAQUAMARINE";
	}
	if( color == MLV_COLOR_AQUAMARINE ){
		return "MLV_COLOR_AQUAMARINE";
	}
	if( color == MLV_COLOR_DARK_GREEN ){
		return "MLV_COLOR_DARK_GREEN";
	}
	if( color == MLV_COLOR_DARKGREEN ){
		return "MLV_COLOR_DARKGREEN";
	}
	if( color == MLV_COLOR_DARK_OLIVE_GREEN ){
		return "MLV_COLOR_DARK_OLIVE_GREEN";
	}
	if( color == MLV_COLOR_DARKOLIVEGREEN ){
		return "MLV_COLOR_DARKOLIVEGREEN";
	}
	if( color == MLV_COLOR_DARK_SEA_GREEN ){
		return "MLV_COLOR_DARK_SEA_GREEN";
	}
	if( color == MLV_COLOR_DARKSEAGREEN ){
		return "MLV_COLOR_DARKSEAGREEN";
	}
	if( color == MLV_COLOR_SEA_GREEN ){
		return "MLV_COLOR_SEA_GREEN";
	}
	if( color == MLV_COLOR_SEAGREEN ){
		return "MLV_COLOR_SEAGREEN";
	}
	if( color == MLV_COLOR_MEDIUM_SEA_GREEN ){
		return "MLV_COLOR_MEDIUM_SEA_GREEN";
	}
	if( color == MLV_COLOR_MEDIUMSEAGREEN ){
		return "MLV_COLOR_MEDIUMSEAGREEN";
	}
	if( color == MLV_COLOR_LIGHT_SEA_GREEN ){
		return "MLV_COLOR_LIGHT_SEA_GREEN";
	}
	if( color == MLV_COLOR_LIGHTSEAGREEN ){
		return "MLV_COLOR_LIGHTSEAGREEN";
	}
	if( color == MLV_COLOR_PALE_GREEN ){
		return "MLV_COLOR_PALE_GREEN";
	}
	if( color == MLV_COLOR_PALEGREEN ){
		return "MLV_COLOR_PALEGREEN";
	}
	if( color == MLV_COLOR_SPRING_GREEN ){
		return "MLV_COLOR_SPRING_GREEN";
	}
	if( color == MLV_COLOR_SPRINGGREEN ){
		return "MLV_COLOR_SPRINGGREEN";
	}
	if( color == MLV_COLOR_LAWN_GREEN ){
		return "MLV_COLOR_LAWN_GREEN";
	}
	if( color == MLV_COLOR_LAWNGREEN ){
		return "MLV_COLOR_LAWNGREEN";
	}
	if( color == MLV_COLOR_GREEN ){
		return "MLV_COLOR_GREEN";
	}
	if( color == MLV_COLOR_CHARTREUSE ){
		return "MLV_COLOR_CHARTREUSE";
	}
	if( color == MLV_COLOR_MEDIUM_SPRING_GREEN ){
		return "MLV_COLOR_MEDIUM_SPRING_GREEN";
	}
	if( color == MLV_COLOR_MEDIUMSPRINGGREEN ){
		return "MLV_COLOR_MEDIUMSPRINGGREEN";
	}
	if( color == MLV_COLOR_GREEN_YELLOW ){
		return "MLV_COLOR_GREEN_YELLOW";
	}
	if( color == MLV_COLOR_GREENYELLOW ){
		return "MLV_COLOR_GREENYELLOW";
	}
	if( color == MLV_COLOR_LIME_GREEN ){
		return "MLV_COLOR_LIME_GREEN";
	}
	if( color == MLV_COLOR_LIMEGREEN ){
		return "MLV_COLOR_LIMEGREEN";
	}
	if( color == MLV_COLOR_YELLOW_GREEN ){
		return "MLV_COLOR_YELLOW_GREEN";
	}
	if( color == MLV_COLOR_YELLOWGREEN ){
		return "MLV_COLOR_YELLOWGREEN";
	}
	if( color == MLV_COLOR_FOREST_GREEN ){
		return "MLV_COLOR_FOREST_GREEN";
	}
	if( color == MLV_COLOR_FORESTGREEN ){
		return "MLV_COLOR_FORESTGREEN";
	}
	if( color == MLV_COLOR_OLIVE_DRAB ){
		return "MLV_COLOR_OLIVE_DRAB";
	}
	if( color == MLV_COLOR_OLIVEDRAB ){
		return "MLV_COLOR_OLIVEDRAB";
	}
	if( color == MLV_COLOR_DARK_KHAKI ){
		return "MLV_COLOR_DARK_KHAKI";
	}
	if( color == MLV_COLOR_DARKKHAKI ){
		return "MLV_COLOR_DARKKHAKI";
	}
	if( color == MLV_COLOR_KHAKI ){
		return "MLV_COLOR_KHAKI";
	}
	if( color == MLV_COLOR_PALE_GOLDENROD ){
		return "MLV_COLOR_PALE_GOLDENROD";
	}
	if( color == MLV_COLOR_PALEGOLDENROD ){
		return "MLV_COLOR_PALEGOLDENROD";
	}
	if( color == MLV_COLOR_LIGHT_GOLDENROD_YELLOW ){
		return "MLV_COLOR_LIGHT_GOLDENROD_YELLOW";
	}
	if( color == MLV_COLOR_LIGHTGOLDENRODYELLOW ){
		return "MLV_COLOR_LIGHTGOLDENRODYELLOW";
	}
	if( color == MLV_COLOR_LIGHT_YELLOW ){
		return "MLV_COLOR_LIGHT_YELLOW";
	}
	if( color == MLV_COLOR_LIGHTYELLOW ){
		return "MLV_COLOR_LIGHTYELLOW";
	}
	if( color == MLV_COLOR_YELLOW ){
		return "MLV_COLOR_YELLOW";
	}
	if( color == MLV_COLOR_GOLD ){
		return "MLV_COLOR_GOLD";
	}
	if( color == MLV_COLOR_LIGHT_GOLDENROD ){
		return "MLV_COLOR_LIGHT_GOLDENROD";
	}
	if( color == MLV_COLOR_LIGHTGOLDENROD ){
		return "MLV_COLOR_LIGHTGOLDENROD";
	}
	if( color == MLV_COLOR_GOLDENROD ){
		return "MLV_COLOR_GOLDENROD";
	}
	if( color == MLV_COLOR_DARK_GOLDENROD ){
		return "MLV_COLOR_DARK_GOLDENROD";
	}
	if( color == MLV_COLOR_DARKGOLDENROD ){
		return "MLV_COLOR_DARKGOLDENROD";
	}
	if( color == MLV_COLOR_ROSY_BROWN ){
		return "MLV_COLOR_ROSY_BROWN";
	}
	if( color == MLV_COLOR_ROSYBROWN ){
		return "MLV_COLOR_ROSYBROWN";
	}
	if( color == MLV_COLOR_INDIAN_RED ){
		return "MLV_COLOR_INDIAN_RED";
	}
	if( color == MLV_COLOR_INDIANRED ){
		return "MLV_COLOR_INDIANRED";
	}
	if( color == MLV_COLOR_SADDLE_BROWN ){
		return "MLV_COLOR_SADDLE_BROWN";
	}
	if( color == MLV_COLOR_SADDLEBROWN ){
		return "MLV_COLOR_SADDLEBROWN";
	}
	if( color == MLV_COLOR_SIENNA ){
		return "MLV_COLOR_SIENNA";
	}
	if( color == MLV_COLOR_PERU ){
		return "MLV_COLOR_PERU";
	}
	if( color == MLV_COLOR_BURLYWOOD ){
		return "MLV_COLOR_BURLYWOOD";
	}
	if( color == MLV_COLOR_BEIGE ){
		return "MLV_COLOR_BEIGE";
	}
	if( color == MLV_COLOR_WHEAT ){
		return "MLV_COLOR_WHEAT";
	}
	if( color == MLV_COLOR_SANDY_BROWN ){
		return "MLV_COLOR_SANDY_BROWN";
	}
	if( color == MLV_COLOR_SANDYBROWN ){
		return "MLV_COLOR_SANDYBROWN";
	}
	if( color == MLV_COLOR_TAN ){
		return "MLV_COLOR_TAN";
	}
	if( color == MLV_COLOR_CHOCOLATE ){
		return "MLV_COLOR_CHOCOLATE";
	}
	if( color == MLV_COLOR_FIREBRICK ){
		return "MLV_COLOR_FIREBRICK";
	}
	if( color == MLV_COLOR_BROWN ){
		return "MLV_COLOR_BROWN";
	}
	if( color == MLV_COLOR_DARK_SALMON ){
		return "MLV_COLOR_DARK_SALMON";
	}
	if( color == MLV_COLOR_DARKSALMON ){
		return "MLV_COLOR_DARKSALMON";
	}
	if( color == MLV_COLOR_SALMON ){
		return "MLV_COLOR_SALMON";
	}
	if( color == MLV_COLOR_LIGHT_SALMON ){
		return "MLV_COLOR_LIGHT_SALMON";
	}
	if( color == MLV_COLOR_LIGHTSALMON ){
		return "MLV_COLOR_LIGHTSALMON";
	}
	if( color == MLV_COLOR_ORANGE ){
		return "MLV_COLOR_ORANGE";
	}
	if( color == MLV_COLOR_DARK_ORANGE ){
		return "MLV_COLOR_DARK_ORANGE";
	}
	if( color == MLV_COLOR_DARKORANGE ){
		return "MLV_COLOR_DARKORANGE";
	}
	if( color == MLV_COLOR_CORAL ){
		return "MLV_COLOR_CORAL";
	}
	if( color == MLV_COLOR_LIGHT_CORAL ){
		return "MLV_COLOR_LIGHT_CORAL";
	}
	if( color == MLV_COLOR_LIGHTCORAL ){
		return "MLV_COLOR_LIGHTCORAL";
	}
	if( color == MLV_COLOR_TOMATO ){
		return "MLV_COLOR_TOMATO";
	}
	if( color == MLV_COLOR_ORANGE_RED ){
		return "MLV_COLOR_ORANGE_RED";
	}
	if( color == MLV_COLOR_ORANGERED ){
		return "MLV_COLOR_ORANGERED";
	}
	if( color == MLV_COLOR_RED ){
		return "MLV_COLOR_RED";
	}
	if( color == MLV_COLOR_HOT_PINK ){
		return "MLV_COLOR_HOT_PINK";
	}
	if( color == MLV_COLOR_HOTPINK ){
		return "MLV_COLOR_HOTPINK";
	}
	if( color == MLV_COLOR_DEEP_PINK ){
		return "MLV_COLOR_DEEP_PINK";
	}
	if( color == MLV_COLOR_DEEPPINK ){
		return "MLV_COLOR_DEEPPINK";
	}
	if( color == MLV_COLOR_PINK ){
		return "MLV_COLOR_PINK";
	}
	if( color == MLV_COLOR_LIGHT_PINK ){
		return "MLV_COLOR_LIGHT_PINK";
	}
	if( color == MLV_COLOR_LIGHTPINK ){
		return "MLV_COLOR_LIGHTPINK";
	}
	if( color == MLV_COLOR_PALE_VIOLET_RED ){
		return "MLV_COLOR_PALE_VIOLET_RED";
	}
	if( color == MLV_COLOR_PALEVIOLETRED ){
		return "MLV_COLOR_PALEVIOLETRED";
	}
	if( color == MLV_COLOR_MAROON ){
		return "MLV_COLOR_MAROON";
	}
	if( color == MLV_COLOR_MEDIUM_VIOLET_RED ){
		return "MLV_COLOR_MEDIUM_VIOLET_RED";
	}
	if( color == MLV_COLOR_MEDIUMVIOLETRED ){
		return "MLV_COLOR_MEDIUMVIOLETRED";
	}
	if( color == MLV_COLOR_VIOLET_RED ){
		return "MLV_COLOR_VIOLET_RED";
	}
	if( color == MLV_COLOR_VIOLETRED ){
		return "MLV_COLOR_VIOLETRED";
	}
	if( color == MLV_COLOR_MAGENTA ){
		return "MLV_COLOR_MAGENTA";
	}
	if( color == MLV_COLOR_VIOLET ){
		return "MLV_COLOR_VIOLET";
	}
	if( color == MLV_COLOR_PLUM ){
		return "MLV_COLOR_PLUM";
	}
	if( color == MLV_COLOR_ORCHID ){
		return "MLV_COLOR_ORCHID";
	}
	if( color == MLV_COLOR_MEDIUM_ORCHID ){
		return "MLV_COLOR_MEDIUM_ORCHID";
	}
	if( color == MLV_COLOR_MEDIUMORCHID ){
		return "MLV_COLOR_MEDIUMORCHID";
	}
	if( color == MLV_COLOR_DARK_ORCHID ){
		return "MLV_COLOR_DARK_ORCHID";
	}
	if( color == MLV_COLOR_DARKORCHID ){
		return "MLV_COLOR_DARKORCHID";
	}
	if( color == MLV_COLOR_DARK_VIOLET ){
		return "MLV_COLOR_DARK_VIOLET";
	}
	if( color == MLV_COLOR_DARKVIOLET ){
		return "MLV_COLOR_DARKVIOLET";
	}
	if( color == MLV_COLOR_BLUE_VIOLET ){
		return "MLV_COLOR_BLUE_VIOLET";
	}
	if( color == MLV_COLOR_BLUEVIOLET ){
		return "MLV_COLOR_BLUEVIOLET";
	}
	if( color == MLV_COLOR_PURPLE ){
		return "MLV_COLOR_PURPLE";
	}
	if( color == MLV_COLOR_MEDIUM_PURPLE ){
		return "MLV_COLOR_MEDIUM_PURPLE";
	}
	if( color == MLV_COLOR_MEDIUMPURPLE ){
		return "MLV_COLOR_MEDIUMPURPLE";
	}
	if( color == MLV_COLOR_THISTLE ){
		return "MLV_COLOR_THISTLE";
	}
	if( color == MLV_COLOR_SNOW1 ){
		return "MLV_COLOR_SNOW1";
	}
	if( color == MLV_COLOR_SNOW2 ){
		return "MLV_COLOR_SNOW2";
	}
	if( color == MLV_COLOR_SNOW3 ){
		return "MLV_COLOR_SNOW3";
	}
	if( color == MLV_COLOR_SNOW4 ){
		return "MLV_COLOR_SNOW4";
	}
	if( color == MLV_COLOR_SEASHELL1 ){
		return "MLV_COLOR_SEASHELL1";
	}
	if( color == MLV_COLOR_SEASHELL2 ){
		return "MLV_COLOR_SEASHELL2";
	}
	if( color == MLV_COLOR_SEASHELL3 ){
		return "MLV_COLOR_SEASHELL3";
	}
	if( color == MLV_COLOR_SEASHELL4 ){
		return "MLV_COLOR_SEASHELL4";
	}
	if( color == MLV_COLOR_ANTIQUEWHITE1 ){
		return "MLV_COLOR_ANTIQUEWHITE1";
	}
	if( color == MLV_COLOR_ANTIQUEWHITE2 ){
		return "MLV_COLOR_ANTIQUEWHITE2";
	}
	if( color == MLV_COLOR_ANTIQUEWHITE3 ){
		return "MLV_COLOR_ANTIQUEWHITE3";
	}
	if( color == MLV_COLOR_ANTIQUEWHITE4 ){
		return "MLV_COLOR_ANTIQUEWHITE4";
	}
	if( color == MLV_COLOR_BISQUE1 ){
		return "MLV_COLOR_BISQUE1";
	}
	if( color == MLV_COLOR_BISQUE2 ){
		return "MLV_COLOR_BISQUE2";
	}
	if( color == MLV_COLOR_BISQUE3 ){
		return "MLV_COLOR_BISQUE3";
	}
	if( color == MLV_COLOR_BISQUE4 ){
		return "MLV_COLOR_BISQUE4";
	}
	if( color == MLV_COLOR_PEACHPUFF1 ){
		return "MLV_COLOR_PEACHPUFF1";
	}
	if( color == MLV_COLOR_PEACHPUFF2 ){
		return "MLV_COLOR_PEACHPUFF2";
	}
	if( color == MLV_COLOR_PEACHPUFF3 ){
		return "MLV_COLOR_PEACHPUFF3";
	}
	if( color == MLV_COLOR_PEACHPUFF4 ){
		return "MLV_COLOR_PEACHPUFF4";
	}
	if( color == MLV_COLOR_NAVAJOWHITE1 ){
		return "MLV_COLOR_NAVAJOWHITE1";
	}
	if( color == MLV_COLOR_NAVAJOWHITE2 ){
		return "MLV_COLOR_NAVAJOWHITE2";
	}
	if( color == MLV_COLOR_NAVAJOWHITE3 ){
		return "MLV_COLOR_NAVAJOWHITE3";
	}
	if( color == MLV_COLOR_NAVAJOWHITE4 ){
		return "MLV_COLOR_NAVAJOWHITE4";
	}
	if( color == MLV_COLOR_LEMONCHIFFON1 ){
		return "MLV_COLOR_LEMONCHIFFON1";
	}
	if( color == MLV_COLOR_LEMONCHIFFON2 ){
		return "MLV_COLOR_LEMONCHIFFON2";
	}
	if( color == MLV_COLOR_LEMONCHIFFON3 ){
		return "MLV_COLOR_LEMONCHIFFON3";
	}
	if( color == MLV_COLOR_LEMONCHIFFON4 ){
		return "MLV_COLOR_LEMONCHIFFON4";
	}
	if( color == MLV_COLOR_CORNSILK1 ){
		return "MLV_COLOR_CORNSILK1";
	}
	if( color == MLV_COLOR_CORNSILK2 ){
		return "MLV_COLOR_CORNSILK2";
	}
	if( color == MLV_COLOR_CORNSILK3 ){
		return "MLV_COLOR_CORNSILK3";
	}
	if( color == MLV_COLOR_CORNSILK4 ){
		return "MLV_COLOR_CORNSILK4";
	}
	if( color == MLV_COLOR_IVORY1 ){
		return "MLV_COLOR_IVORY1";
	}
	if( color == MLV_COLOR_IVORY2 ){
		return "MLV_COLOR_IVORY2";
	}
	if( color == MLV_COLOR_IVORY3 ){
		return "MLV_COLOR_IVORY3";
	}
	if( color == MLV_COLOR_IVORY4 ){
		return "MLV_COLOR_IVORY4";
	}
	if( color == MLV_COLOR_HONEYDEW1 ){
		return "MLV_COLOR_HONEYDEW1";
	}
	if( color == MLV_COLOR_HONEYDEW2 ){
		return "MLV_COLOR_HONEYDEW2";
	}
	if( color == MLV_COLOR_HONEYDEW3 ){
		return "MLV_COLOR_HONEYDEW3";
	}
	if( color == MLV_COLOR_HONEYDEW4 ){
		return "MLV_COLOR_HONEYDEW4";
	}
	if( color == MLV_COLOR_LAVENDERBLUSH1 ){
		return "MLV_COLOR_LAVENDERBLUSH1";
	}
	if( color == MLV_COLOR_LAVENDERBLUSH2 ){
		return "MLV_COLOR_LAVENDERBLUSH2";
	}
	if( color == MLV_COLOR_LAVENDERBLUSH3 ){
		return "MLV_COLOR_LAVENDERBLUSH3";
	}
	if( color == MLV_COLOR_LAVENDERBLUSH4 ){
		return "MLV_COLOR_LAVENDERBLUSH4";
	}
	if( color == MLV_COLOR_MISTYROSE1 ){
		return "MLV_COLOR_MISTYROSE1";
	}
	if( color == MLV_COLOR_MISTYROSE2 ){
		return "MLV_COLOR_MISTYROSE2";
	}
	if( color == MLV_COLOR_MISTYROSE3 ){
		return "MLV_COLOR_MISTYROSE3";
	}
	if( color == MLV_COLOR_MISTYROSE4 ){
		return "MLV_COLOR_MISTYROSE4";
	}
	if( color == MLV_COLOR_AZURE1 ){
		return "MLV_COLOR_AZURE1";
	}
	if( color == MLV_COLOR_AZURE2 ){
		return "MLV_COLOR_AZURE2";
	}
	if( color == MLV_COLOR_AZURE3 ){
		return "MLV_COLOR_AZURE3";
	}
	if( color == MLV_COLOR_AZURE4 ){
		return "MLV_COLOR_AZURE4";
	}
	if( color == MLV_COLOR_SLATEBLUE1 ){
		return "MLV_COLOR_SLATEBLUE1";
	}
	if( color == MLV_COLOR_SLATEBLUE2 ){
		return "MLV_COLOR_SLATEBLUE2";
	}
	if( color == MLV_COLOR_SLATEBLUE3 ){
		return "MLV_COLOR_SLATEBLUE3";
	}
	if( color == MLV_COLOR_SLATEBLUE4 ){
		return "MLV_COLOR_SLATEBLUE4";
	}
	if( color == MLV_COLOR_ROYALBLUE1 ){
		return "MLV_COLOR_ROYALBLUE1";
	}
	if( color == MLV_COLOR_ROYALBLUE2 ){
		return "MLV_COLOR_ROYALBLUE2";
	}
	if( color == MLV_COLOR_ROYALBLUE3 ){
		return "MLV_COLOR_ROYALBLUE3";
	}
	if( color == MLV_COLOR_ROYALBLUE4 ){
		return "MLV_COLOR_ROYALBLUE4";
	}
	if( color == MLV_COLOR_BLUE1 ){
		return "MLV_COLOR_BLUE1";
	}
	if( color == MLV_COLOR_BLUE2 ){
		return "MLV_COLOR_BLUE2";
	}
	if( color == MLV_COLOR_BLUE3 ){
		return "MLV_COLOR_BLUE3";
	}
	if( color == MLV_COLOR_BLUE4 ){
		return "MLV_COLOR_BLUE4";
	}
	if( color == MLV_COLOR_DODGERBLUE1 ){
		return "MLV_COLOR_DODGERBLUE1";
	}
	if( color == MLV_COLOR_DODGERBLUE2 ){
		return "MLV_COLOR_DODGERBLUE2";
	}
	if( color == MLV_COLOR_DODGERBLUE3 ){
		return "MLV_COLOR_DODGERBLUE3";
	}
	if( color == MLV_COLOR_DODGERBLUE4 ){
		return "MLV_COLOR_DODGERBLUE4";
	}
	if( color == MLV_COLOR_STEELBLUE1 ){
		return "MLV_COLOR_STEELBLUE1";
	}
	if( color == MLV_COLOR_STEELBLUE2 ){
		return "MLV_COLOR_STEELBLUE2";
	}
	if( color == MLV_COLOR_STEELBLUE3 ){
		return "MLV_COLOR_STEELBLUE3";
	}
	if( color == MLV_COLOR_STEELBLUE4 ){
		return "MLV_COLOR_STEELBLUE4";
	}
	if( color == MLV_COLOR_DEEPSKYBLUE1 ){
		return "MLV_COLOR_DEEPSKYBLUE1";
	}
	if( color == MLV_COLOR_DEEPSKYBLUE2 ){
		return "MLV_COLOR_DEEPSKYBLUE2";
	}
	if( color == MLV_COLOR_DEEPSKYBLUE3 ){
		return "MLV_COLOR_DEEPSKYBLUE3";
	}
	if( color == MLV_COLOR_DEEPSKYBLUE4 ){
		return "MLV_COLOR_DEEPSKYBLUE4";
	}
	if( color == MLV_COLOR_SKYBLUE1 ){
		return "MLV_COLOR_SKYBLUE1";
	}
	if( color == MLV_COLOR_SKYBLUE2 ){
		return "MLV_COLOR_SKYBLUE2";
	}
	if( color == MLV_COLOR_SKYBLUE3 ){
		return "MLV_COLOR_SKYBLUE3";
	}
	if( color == MLV_COLOR_SKYBLUE4 ){
		return "MLV_COLOR_SKYBLUE4";
	}
	if( color == MLV_COLOR_LIGHTSKYBLUE1 ){
		return "MLV_COLOR_LIGHTSKYBLUE1";
	}
	if( color == MLV_COLOR_LIGHTSKYBLUE2 ){
		return "MLV_COLOR_LIGHTSKYBLUE2";
	}
	if( color == MLV_COLOR_LIGHTSKYBLUE3 ){
		return "MLV_COLOR_LIGHTSKYBLUE3";
	}
	if( color == MLV_COLOR_LIGHTSKYBLUE4 ){
		return "MLV_COLOR_LIGHTSKYBLUE4";
	}
	if( color == MLV_COLOR_SLATEGRAY1 ){
		return "MLV_COLOR_SLATEGRAY1";
	}
	if( color == MLV_COLOR_SLATEGRAY2 ){
		return "MLV_COLOR_SLATEGRAY2";
	}
	if( color == MLV_COLOR_SLATEGRAY3 ){
		return "MLV_COLOR_SLATEGRAY3";
	}
	if( color == MLV_COLOR_SLATEGRAY4 ){
		return "MLV_COLOR_SLATEGRAY4";
	}
	if( color == MLV_COLOR_LIGHTSTEELBLUE1 ){
		return "MLV_COLOR_LIGHTSTEELBLUE1";
	}
	if( color == MLV_COLOR_LIGHTSTEELBLUE2 ){
		return "MLV_COLOR_LIGHTSTEELBLUE2";
	}
	if( color == MLV_COLOR_LIGHTSTEELBLUE3 ){
		return "MLV_COLOR_LIGHTSTEELBLUE3";
	}
	if( color == MLV_COLOR_LIGHTSTEELBLUE4 ){
		return "MLV_COLOR_LIGHTSTEELBLUE4";
	}
	if( color == MLV_COLOR_LIGHTBLUE1 ){
		return "MLV_COLOR_LIGHTBLUE1";
	}
	if( color == MLV_COLOR_LIGHTBLUE2 ){
		return "MLV_COLOR_LIGHTBLUE2";
	}
	if( color == MLV_COLOR_LIGHTBLUE3 ){
		return "MLV_COLOR_LIGHTBLUE3";
	}
	if( color == MLV_COLOR_LIGHTBLUE4 ){
		return "MLV_COLOR_LIGHTBLUE4";
	}
	if( color == MLV_COLOR_LIGHTCYAN1 ){
		return "MLV_COLOR_LIGHTCYAN1";
	}
	if( color == MLV_COLOR_LIGHTCYAN2 ){
		return "MLV_COLOR_LIGHTCYAN2";
	}
	if( color == MLV_COLOR_LIGHTCYAN3 ){
		return "MLV_COLOR_LIGHTCYAN3";
	}
	if( color == MLV_COLOR_LIGHTCYAN4 ){
		return "MLV_COLOR_LIGHTCYAN4";
	}
	if( color == MLV_COLOR_PALETURQUOISE1 ){
		return "MLV_COLOR_PALETURQUOISE1";
	}
	if( color == MLV_COLOR_PALETURQUOISE2 ){
		return "MLV_COLOR_PALETURQUOISE2";
	}
	if( color == MLV_COLOR_PALETURQUOISE3 ){
		return "MLV_COLOR_PALETURQUOISE3";
	}
	if( color == MLV_COLOR_PALETURQUOISE4 ){
		return "MLV_COLOR_PALETURQUOISE4";
	}
	if( color == MLV_COLOR_CADETBLUE1 ){
		return "MLV_COLOR_CADETBLUE1";
	}
	if( color == MLV_COLOR_CADETBLUE2 ){
		return "MLV_COLOR_CADETBLUE2";
	}
	if( color == MLV_COLOR_CADETBLUE3 ){
		return "MLV_COLOR_CADETBLUE3";
	}
	if( color == MLV_COLOR_CADETBLUE4 ){
		return "MLV_COLOR_CADETBLUE4";
	}
	if( color == MLV_COLOR_TURQUOISE1 ){
		return "MLV_COLOR_TURQUOISE1";
	}
	if( color == MLV_COLOR_TURQUOISE2 ){
		return "MLV_COLOR_TURQUOISE2";
	}
	if( color == MLV_COLOR_TURQUOISE3 ){
		return "MLV_COLOR_TURQUOISE3";
	}
	if( color == MLV_COLOR_TURQUOISE4 ){
		return "MLV_COLOR_TURQUOISE4";
	}
	if( color == MLV_COLOR_CYAN1 ){
		return "MLV_COLOR_CYAN1";
	}
	if( color == MLV_COLOR_CYAN2 ){
		return "MLV_COLOR_CYAN2";
	}
	if( color == MLV_COLOR_CYAN3 ){
		return "MLV_COLOR_CYAN3";
	}
	if( color == MLV_COLOR_CYAN4 ){
		return "MLV_COLOR_CYAN4";
	}
	if( color == MLV_COLOR_DARKSLATEGRAY1 ){
		return "MLV_COLOR_DARKSLATEGRAY1";
	}
	if( color == MLV_COLOR_DARKSLATEGRAY2 ){
		return "MLV_COLOR_DARKSLATEGRAY2";
	}
	if( color == MLV_COLOR_DARKSLATEGRAY3 ){
		return "MLV_COLOR_DARKSLATEGRAY3";
	}
	if( color == MLV_COLOR_DARKSLATEGRAY4 ){
		return "MLV_COLOR_DARKSLATEGRAY4";
	}
	if( color == MLV_COLOR_AQUAMARINE1 ){
		return "MLV_COLOR_AQUAMARINE1";
	}
	if( color == MLV_COLOR_AQUAMARINE2 ){
		return "MLV_COLOR_AQUAMARINE2";
	}
	if( color == MLV_COLOR_AQUAMARINE3 ){
		return "MLV_COLOR_AQUAMARINE3";
	}
	if( color == MLV_COLOR_AQUAMARINE4 ){
		return "MLV_COLOR_AQUAMARINE4";
	}
	if( color == MLV_COLOR_DARKSEAGREEN1 ){
		return "MLV_COLOR_DARKSEAGREEN1";
	}
	if( color == MLV_COLOR_DARKSEAGREEN2 ){
		return "MLV_COLOR_DARKSEAGREEN2";
	}
	if( color == MLV_COLOR_DARKSEAGREEN3 ){
		return "MLV_COLOR_DARKSEAGREEN3";
	}
	if( color == MLV_COLOR_DARKSEAGREEN4 ){
		return "MLV_COLOR_DARKSEAGREEN4";
	}
	if( color == MLV_COLOR_SEAGREEN1 ){
		return "MLV_COLOR_SEAGREEN1";
	}
	if( color == MLV_COLOR_SEAGREEN2 ){
		return "MLV_COLOR_SEAGREEN2";
	}
	if( color == MLV_COLOR_SEAGREEN3 ){
		return "MLV_COLOR_SEAGREEN3";
	}
	if( color == MLV_COLOR_SEAGREEN4 ){
		return "MLV_COLOR_SEAGREEN4";
	}
	if( color == MLV_COLOR_PALEGREEN1 ){
		return "MLV_COLOR_PALEGREEN1";
	}
	if( color == MLV_COLOR_PALEGREEN2 ){
		return "MLV_COLOR_PALEGREEN2";
	}
	if( color == MLV_COLOR_PALEGREEN3 ){
		return "MLV_COLOR_PALEGREEN3";
	}
	if( color == MLV_COLOR_PALEGREEN4 ){
		return "MLV_COLOR_PALEGREEN4";
	}
	if( color == MLV_COLOR_SPRINGGREEN1 ){
		return "MLV_COLOR_SPRINGGREEN1";
	}
	if( color == MLV_COLOR_SPRINGGREEN2 ){
		return "MLV_COLOR_SPRINGGREEN2";
	}
	if( color == MLV_COLOR_SPRINGGREEN3 ){
		return "MLV_COLOR_SPRINGGREEN3";
	}
	if( color == MLV_COLOR_SPRINGGREEN4 ){
		return "MLV_COLOR_SPRINGGREEN4";
	}
	if( color == MLV_COLOR_GREEN1 ){
		return "MLV_COLOR_GREEN1";
	}
	if( color == MLV_COLOR_GREEN2 ){
		return "MLV_COLOR_GREEN2";
	}
	if( color == MLV_COLOR_GREEN3 ){
		return "MLV_COLOR_GREEN3";
	}
	if( color == MLV_COLOR_GREEN4 ){
		return "MLV_COLOR_GREEN4";
	}
	if( color == MLV_COLOR_CHARTREUSE1 ){
		return "MLV_COLOR_CHARTREUSE1";
	}
	if( color == MLV_COLOR_CHARTREUSE2 ){
		return "MLV_COLOR_CHARTREUSE2";
	}
	if( color == MLV_COLOR_CHARTREUSE3 ){
		return "MLV_COLOR_CHARTREUSE3";
	}
	if( color == MLV_COLOR_CHARTREUSE4 ){
		return "MLV_COLOR_CHARTREUSE4";
	}
	if( color == MLV_COLOR_OLIVEDRAB1 ){
		return "MLV_COLOR_OLIVEDRAB1";
	}
	if( color == MLV_COLOR_OLIVEDRAB2 ){
		return "MLV_COLOR_OLIVEDRAB2";
	}
	if( color == MLV_COLOR_OLIVEDRAB3 ){
		return "MLV_COLOR_OLIVEDRAB3";
	}
	if( color == MLV_COLOR_OLIVEDRAB4 ){
		return "MLV_COLOR_OLIVEDRAB4";
	}
	if( color == MLV_COLOR_DARKOLIVEGREEN1 ){
		return "MLV_COLOR_DARKOLIVEGREEN1";
	}
	if( color == MLV_COLOR_DARKOLIVEGREEN2 ){
		return "MLV_COLOR_DARKOLIVEGREEN2";
	}
	if( color == MLV_COLOR_DARKOLIVEGREEN3 ){
		return "MLV_COLOR_DARKOLIVEGREEN3";
	}
	if( color == MLV_COLOR_DARKOLIVEGREEN4 ){
		return "MLV_COLOR_DARKOLIVEGREEN4";
	}
	if( color == MLV_COLOR_KHAKI1 ){
		return "MLV_COLOR_KHAKI1";
	}
	if( color == MLV_COLOR_KHAKI2 ){
		return "MLV_COLOR_KHAKI2";
	}
	if( color == MLV_COLOR_KHAKI3 ){
		return "MLV_COLOR_KHAKI3";
	}
	if( color == MLV_COLOR_KHAKI4 ){
		return "MLV_COLOR_KHAKI4";
	}
	if( color == MLV_COLOR_LIGHTGOLDENROD1 ){
		return "MLV_COLOR_LIGHTGOLDENROD1";
	}
	if( color == MLV_COLOR_LIGHTGOLDENROD2 ){
		return "MLV_COLOR_LIGHTGOLDENROD2";
	}
	if( color == MLV_COLOR_LIGHTGOLDENROD3 ){
		return "MLV_COLOR_LIGHTGOLDENROD3";
	}
	if( color == MLV_COLOR_LIGHTGOLDENROD4 ){
		return "MLV_COLOR_LIGHTGOLDENROD4";
	}
	if( color == MLV_COLOR_LIGHTYELLOW1 ){
		return "MLV_COLOR_LIGHTYELLOW1";
	}
	if( color == MLV_COLOR_LIGHTYELLOW2 ){
		return "MLV_COLOR_LIGHTYELLOW2";
	}
	if( color == MLV_COLOR_LIGHTYELLOW3 ){
		return "MLV_COLOR_LIGHTYELLOW3";
	}
	if( color == MLV_COLOR_LIGHTYELLOW4 ){
		return "MLV_COLOR_LIGHTYELLOW4";
	}
	if( color == MLV_COLOR_YELLOW1 ){
		return "MLV_COLOR_YELLOW1";
	}
	if( color == MLV_COLOR_YELLOW2 ){
		return "MLV_COLOR_YELLOW2";
	}
	if( color == MLV_COLOR_YELLOW3 ){
		return "MLV_COLOR_YELLOW3";
	}
	if( color == MLV_COLOR_YELLOW4 ){
		return "MLV_COLOR_YELLOW4";
	}
	if( color == MLV_COLOR_GOLD1 ){
		return "MLV_COLOR_GOLD1";
	}
	if( color == MLV_COLOR_GOLD2 ){
		return "MLV_COLOR_GOLD2";
	}
	if( color == MLV_COLOR_GOLD3 ){
		return "MLV_COLOR_GOLD3";
	}
	if( color == MLV_COLOR_GOLD4 ){
		return "MLV_COLOR_GOLD4";
	}
	if( color == MLV_COLOR_GOLDENROD1 ){
		return "MLV_COLOR_GOLDENROD1";
	}
	if( color == MLV_COLOR_GOLDENROD2 ){
		return "MLV_COLOR_GOLDENROD2";
	}
	if( color == MLV_COLOR_GOLDENROD3 ){
		return "MLV_COLOR_GOLDENROD3";
	}
	if( color == MLV_COLOR_GOLDENROD4 ){
		return "MLV_COLOR_GOLDENROD4";
	}
	if( color == MLV_COLOR_DARKGOLDENROD1 ){
		return "MLV_COLOR_DARKGOLDENROD1";
	}
	if( color == MLV_COLOR_DARKGOLDENROD2 ){
		return "MLV_COLOR_DARKGOLDENROD2";
	}
	if( color == MLV_COLOR_DARKGOLDENROD3 ){
		return "MLV_COLOR_DARKGOLDENROD3";
	}
	if( color == MLV_COLOR_DARKGOLDENROD4 ){
		return "MLV_COLOR_DARKGOLDENROD4";
	}
	if( color == MLV_COLOR_ROSYBROWN1 ){
		return "MLV_COLOR_ROSYBROWN1";
	}
	if( color == MLV_COLOR_ROSYBROWN2 ){
		return "MLV_COLOR_ROSYBROWN2";
	}
	if( color == MLV_COLOR_ROSYBROWN3 ){
		return "MLV_COLOR_ROSYBROWN3";
	}
	if( color == MLV_COLOR_ROSYBROWN4 ){
		return "MLV_COLOR_ROSYBROWN4";
	}
	if( color == MLV_COLOR_INDIANRED1 ){
		return "MLV_COLOR_INDIANRED1";
	}
	if( color == MLV_COLOR_INDIANRED2 ){
		return "MLV_COLOR_INDIANRED2";
	}
	if( color == MLV_COLOR_INDIANRED3 ){
		return "MLV_COLOR_INDIANRED3";
	}
	if( color == MLV_COLOR_INDIANRED4 ){
		return "MLV_COLOR_INDIANRED4";
	}
	if( color == MLV_COLOR_SIENNA1 ){
		return "MLV_COLOR_SIENNA1";
	}
	if( color == MLV_COLOR_SIENNA2 ){
		return "MLV_COLOR_SIENNA2";
	}
	if( color == MLV_COLOR_SIENNA3 ){
		return "MLV_COLOR_SIENNA3";
	}
	if( color == MLV_COLOR_SIENNA4 ){
		return "MLV_COLOR_SIENNA4";
	}
	if( color == MLV_COLOR_BURLYWOOD1 ){
		return "MLV_COLOR_BURLYWOOD1";
	}
	if( color == MLV_COLOR_BURLYWOOD2 ){
		return "MLV_COLOR_BURLYWOOD2";
	}
	if( color == MLV_COLOR_BURLYWOOD3 ){
		return "MLV_COLOR_BURLYWOOD3";
	}
	if( color == MLV_COLOR_BURLYWOOD4 ){
		return "MLV_COLOR_BURLYWOOD4";
	}
	if( color == MLV_COLOR_WHEAT1 ){
		return "MLV_COLOR_WHEAT1";
	}
	if( color == MLV_COLOR_WHEAT2 ){
		return "MLV_COLOR_WHEAT2";
	}
	if( color == MLV_COLOR_WHEAT3 ){
		return "MLV_COLOR_WHEAT3";
	}
	if( color == MLV_COLOR_WHEAT4 ){
		return "MLV_COLOR_WHEAT4";
	}
	if( color == MLV_COLOR_TAN1 ){
		return "MLV_COLOR_TAN1";
	}
	if( color == MLV_COLOR_TAN2 ){
		return "MLV_COLOR_TAN2";
	}
	if( color == MLV_COLOR_TAN3 ){
		return "MLV_COLOR_TAN3";
	}
	if( color == MLV_COLOR_TAN4 ){
		return "MLV_COLOR_TAN4";
	}
	if( color == MLV_COLOR_CHOCOLATE1 ){
		return "MLV_COLOR_CHOCOLATE1";
	}
	if( color == MLV_COLOR_CHOCOLATE2 ){
		return "MLV_COLOR_CHOCOLATE2";
	}
	if( color == MLV_COLOR_CHOCOLATE3 ){
		return "MLV_COLOR_CHOCOLATE3";
	}
	if( color == MLV_COLOR_CHOCOLATE4 ){
		return "MLV_COLOR_CHOCOLATE4";
	}
	if( color == MLV_COLOR_FIREBRICK1 ){
		return "MLV_COLOR_FIREBRICK1";
	}
	if( color == MLV_COLOR_FIREBRICK2 ){
		return "MLV_COLOR_FIREBRICK2";
	}
	if( color == MLV_COLOR_FIREBRICK3 ){
		return "MLV_COLOR_FIREBRICK3";
	}
	if( color == MLV_COLOR_FIREBRICK4 ){
		return "MLV_COLOR_FIREBRICK4";
	}
	if( color == MLV_COLOR_BROWN1 ){
		return "MLV_COLOR_BROWN1";
	}
	if( color == MLV_COLOR_BROWN2 ){
		return "MLV_COLOR_BROWN2";
	}
	if( color == MLV_COLOR_BROWN3 ){
		return "MLV_COLOR_BROWN3";
	}
	if( color == MLV_COLOR_BROWN4 ){
		return "MLV_COLOR_BROWN4";
	}
	if( color == MLV_COLOR_SALMON1 ){
		return "MLV_COLOR_SALMON1";
	}
	if( color == MLV_COLOR_SALMON2 ){
		return "MLV_COLOR_SALMON2";
	}
	if( color == MLV_COLOR_SALMON3 ){
		return "MLV_COLOR_SALMON3";
	}
	if( color == MLV_COLOR_SALMON4 ){
		return "MLV_COLOR_SALMON4";
	}
	if( color == MLV_COLOR_LIGHTSALMON1 ){
		return "MLV_COLOR_LIGHTSALMON1";
	}
	if( color == MLV_COLOR_LIGHTSALMON2 ){
		return "MLV_COLOR_LIGHTSALMON2";
	}
	if( color == MLV_COLOR_LIGHTSALMON3 ){
		return "MLV_COLOR_LIGHTSALMON3";
	}
	if( color == MLV_COLOR_LIGHTSALMON4 ){
		return "MLV_COLOR_LIGHTSALMON4";
	}
	if( color == MLV_COLOR_ORANGE1 ){
		return "MLV_COLOR_ORANGE1";
	}
	if( color == MLV_COLOR_ORANGE2 ){
		return "MLV_COLOR_ORANGE2";
	}
	if( color == MLV_COLOR_ORANGE3 ){
		return "MLV_COLOR_ORANGE3";
	}
	if( color == MLV_COLOR_ORANGE4 ){
		return "MLV_COLOR_ORANGE4";
	}
	if( color == MLV_COLOR_DARKORANGE1 ){
		return "MLV_COLOR_DARKORANGE1";
	}
	if( color == MLV_COLOR_DARKORANGE2 ){
		return "MLV_COLOR_DARKORANGE2";
	}
	if( color == MLV_COLOR_DARKORANGE3 ){
		return "MLV_COLOR_DARKORANGE3";
	}
	if( color == MLV_COLOR_DARKORANGE4 ){
		return "MLV_COLOR_DARKORANGE4";
	}
	if( color == MLV_COLOR_CORAL1 ){
		return "MLV_COLOR_CORAL1";
	}
	if( color == MLV_COLOR_CORAL2 ){
		return "MLV_COLOR_CORAL2";
	}
	if( color == MLV_COLOR_CORAL3 ){
		return "MLV_COLOR_CORAL3";
	}
	if( color == MLV_COLOR_CORAL4 ){
		return "MLV_COLOR_CORAL4";
	}
	if( color == MLV_COLOR_TOMATO1 ){
		return "MLV_COLOR_TOMATO1";
	}
	if( color == MLV_COLOR_TOMATO2 ){
		return "MLV_COLOR_TOMATO2";
	}
	if( color == MLV_COLOR_TOMATO3 ){
		return "MLV_COLOR_TOMATO3";
	}
	if( color == MLV_COLOR_TOMATO4 ){
		return "MLV_COLOR_TOMATO4";
	}
	if( color == MLV_COLOR_ORANGERED1 ){
		return "MLV_COLOR_ORANGERED1";
	}
	if( color == MLV_COLOR_ORANGERED2 ){
		return "MLV_COLOR_ORANGERED2";
	}
	if( color == MLV_COLOR_ORANGERED3 ){
		return "MLV_COLOR_ORANGERED3";
	}
	if( color == MLV_COLOR_ORANGERED4 ){
		return "MLV_COLOR_ORANGERED4";
	}
	if( color == MLV_COLOR_RED1 ){
		return "MLV_COLOR_RED1";
	}
	if( color == MLV_COLOR_RED2 ){
		return "MLV_COLOR_RED2";
	}
	if( color == MLV_COLOR_RED3 ){
		return "MLV_COLOR_RED3";
	}
	if( color == MLV_COLOR_RED4 ){
		return "MLV_COLOR_RED4";
	}
	if( color == MLV_COLOR_DEEPPINK1 ){
		return "MLV_COLOR_DEEPPINK1";
	}
	if( color == MLV_COLOR_DEEPPINK2 ){
		return "MLV_COLOR_DEEPPINK2";
	}
	if( color == MLV_COLOR_DEEPPINK3 ){
		return "MLV_COLOR_DEEPPINK3";
	}
	if( color == MLV_COLOR_DEEPPINK4 ){
		return "MLV_COLOR_DEEPPINK4";
	}
	if( color == MLV_COLOR_HOTPINK1 ){
		return "MLV_COLOR_HOTPINK1";
	}
	if( color == MLV_COLOR_HOTPINK2 ){
		return "MLV_COLOR_HOTPINK2";
	}
	if( color == MLV_COLOR_HOTPINK3 ){
		return "MLV_COLOR_HOTPINK3";
	}
	if( color == MLV_COLOR_HOTPINK4 ){
		return "MLV_COLOR_HOTPINK4";
	}
	if( color == MLV_COLOR_PINK1 ){
		return "MLV_COLOR_PINK1";
	}
	if( color == MLV_COLOR_PINK2 ){
		return "MLV_COLOR_PINK2";
	}
	if( color == MLV_COLOR_PINK3 ){
		return "MLV_COLOR_PINK3";
	}
	if( color == MLV_COLOR_PINK4 ){
		return "MLV_COLOR_PINK4";
	}
	if( color == MLV_COLOR_LIGHTPINK1 ){
		return "MLV_COLOR_LIGHTPINK1";
	}
	if( color == MLV_COLOR_LIGHTPINK2 ){
		return "MLV_COLOR_LIGHTPINK2";
	}
	if( color == MLV_COLOR_LIGHTPINK3 ){
		return "MLV_COLOR_LIGHTPINK3";
	}
	if( color == MLV_COLOR_LIGHTPINK4 ){
		return "MLV_COLOR_LIGHTPINK4";
	}
	if( color == MLV_COLOR_PALEVIOLETRED1 ){
		return "MLV_COLOR_PALEVIOLETRED1";
	}
	if( color == MLV_COLOR_PALEVIOLETRED2 ){
		return "MLV_COLOR_PALEVIOLETRED2";
	}
	if( color == MLV_COLOR_PALEVIOLETRED3 ){
		return "MLV_COLOR_PALEVIOLETRED3";
	}
	if( color == MLV_COLOR_PALEVIOLETRED4 ){
		return "MLV_COLOR_PALEVIOLETRED4";
	}
	if( color == MLV_COLOR_MAROON1 ){
		return "MLV_COLOR_MAROON1";
	}
	if( color == MLV_COLOR_MAROON2 ){
		return "MLV_COLOR_MAROON2";
	}
	if( color == MLV_COLOR_MAROON3 ){
		return "MLV_COLOR_MAROON3";
	}
	if( color == MLV_COLOR_MAROON4 ){
		return "MLV_COLOR_MAROON4";
	}
	if( color == MLV_COLOR_VIOLETRED1 ){
		return "MLV_COLOR_VIOLETRED1";
	}
	if( color == MLV_COLOR_VIOLETRED2 ){
		return "MLV_COLOR_VIOLETRED2";
	}
	if( color == MLV_COLOR_VIOLETRED3 ){
		return "MLV_COLOR_VIOLETRED3";
	}
	if( color == MLV_COLOR_VIOLETRED4 ){
		return "MLV_COLOR_VIOLETRED4";
	}
	if( color == MLV_COLOR_MAGENTA1 ){
		return "MLV_COLOR_MAGENTA1";
	}
	if( color == MLV_COLOR_MAGENTA2 ){
		return "MLV_COLOR_MAGENTA2";
	}
	if( color == MLV_COLOR_MAGENTA3 ){
		return "MLV_COLOR_MAGENTA3";
	}
	if( color == MLV_COLOR_MAGENTA4 ){
		return "MLV_COLOR_MAGENTA4";
	}
	if( color == MLV_COLOR_ORCHID1 ){
		return "MLV_COLOR_ORCHID1";
	}
	if( color == MLV_COLOR_ORCHID2 ){
		return "MLV_COLOR_ORCHID2";
	}
	if( color == MLV_COLOR_ORCHID3 ){
		return "MLV_COLOR_ORCHID3";
	}
	if( color == MLV_COLOR_ORCHID4 ){
		return "MLV_COLOR_ORCHID4";
	}
	if( color == MLV_COLOR_PLUM1 ){
		return "MLV_COLOR_PLUM1";
	}
	if( color == MLV_COLOR_PLUM2 ){
		return "MLV_COLOR_PLUM2";
	}
	if( color == MLV_COLOR_PLUM3 ){
		return "MLV_COLOR_PLUM3";
	}
	if( color == MLV_COLOR_PLUM4 ){
		return "MLV_COLOR_PLUM4";
	}
	if( color == MLV_COLOR_MEDIUMORCHID1 ){
		return "MLV_COLOR_MEDIUMORCHID1";
	}
	if( color == MLV_COLOR_MEDIUMORCHID2 ){
		return "MLV_COLOR_MEDIUMORCHID2";
	}
	if( color == MLV_COLOR_MEDIUMORCHID3 ){
		return "MLV_COLOR_MEDIUMORCHID3";
	}
	if( color == MLV_COLOR_MEDIUMORCHID4 ){
		return "MLV_COLOR_MEDIUMORCHID4";
	}
	if( color == MLV_COLOR_DARKORCHID1 ){
		return "MLV_COLOR_DARKORCHID1";
	}
	if( color == MLV_COLOR_DARKORCHID2 ){
		return "MLV_COLOR_DARKORCHID2";
	}
	if( color == MLV_COLOR_DARKORCHID3 ){
		return "MLV_COLOR_DARKORCHID3";
	}
	if( color == MLV_COLOR_DARKORCHID4 ){
		return "MLV_COLOR_DARKORCHID4";
	}
	if( color == MLV_COLOR_PURPLE1 ){
		return "MLV_COLOR_PURPLE1";
	}
	if( color == MLV_COLOR_PURPLE2 ){
		return "MLV_COLOR_PURPLE2";
	}
	if( color == MLV_COLOR_PURPLE3 ){
		return "MLV_COLOR_PURPLE3";
	}
	if( color == MLV_COLOR_PURPLE4 ){
		return "MLV_COLOR_PURPLE4";
	}
	if( color == MLV_COLOR_MEDIUMPURPLE1 ){
		return "MLV_COLOR_MEDIUMPURPLE1";
	}
	if( color == MLV_COLOR_MEDIUMPURPLE2 ){
		return "MLV_COLOR_MEDIUMPURPLE2";
	}
	if( color == MLV_COLOR_MEDIUMPURPLE3 ){
		return "MLV_COLOR_MEDIUMPURPLE3";
	}
	if( color == MLV_COLOR_MEDIUMPURPLE4 ){
		return "MLV_COLOR_MEDIUMPURPLE4";
	}
	if( color == MLV_COLOR_THISTLE1 ){
		return "MLV_COLOR_THISTLE1";
	}
	if( color == MLV_COLOR_THISTLE2 ){
		return "MLV_COLOR_THISTLE2";
	}
	if( color == MLV_COLOR_THISTLE3 ){
		return "MLV_COLOR_THISTLE3";
	}
	if( color == MLV_COLOR_THISTLE4 ){
		return "MLV_COLOR_THISTLE4";
	}
	if( color == MLV_COLOR_GRAY0 ){
		return "MLV_COLOR_GRAY0";
	}
	if( color == MLV_COLOR_GREY0 ){
		return "MLV_COLOR_GREY0";
	}
	if( color == MLV_COLOR_GRAY1 ){
		return "MLV_COLOR_GRAY1";
	}
	if( color == MLV_COLOR_GREY1 ){
		return "MLV_COLOR_GREY1";
	}
	if( color == MLV_COLOR_GRAY2 ){
		return "MLV_COLOR_GRAY2";
	}
	if( color == MLV_COLOR_GREY2 ){
		return "MLV_COLOR_GREY2";
	}
	if( color == MLV_COLOR_GRAY3 ){
		return "MLV_COLOR_GRAY3";
	}
	if( color == MLV_COLOR_GREY3 ){
		return "MLV_COLOR_GREY3";
	}
	if( color == MLV_COLOR_GRAY4 ){
		return "MLV_COLOR_GRAY4";
	}
	if( color == MLV_COLOR_GREY4 ){
		return "MLV_COLOR_GREY4";
	}
	if( color == MLV_COLOR_GRAY5 ){
		return "MLV_COLOR_GRAY5";
	}
	if( color == MLV_COLOR_GREY5 ){
		return "MLV_COLOR_GREY5";
	}
	if( color == MLV_COLOR_GRAY6 ){
		return "MLV_COLOR_GRAY6";
	}
	if( color == MLV_COLOR_GREY6 ){
		return "MLV_COLOR_GREY6";
	}
	if( color == MLV_COLOR_GRAY7 ){
		return "MLV_COLOR_GRAY7";
	}
	if( color == MLV_COLOR_GREY7 ){
		return "MLV_COLOR_GREY7";
	}
	if( color == MLV_COLOR_GRAY8 ){
		return "MLV_COLOR_GRAY8";
	}
	if( color == MLV_COLOR_GREY8 ){
		return "MLV_COLOR_GREY8";
	}
	if( color == MLV_COLOR_GRAY9 ){
		return "MLV_COLOR_GRAY9";
	}
	if( color == MLV_COLOR_GREY9 ){
		return "MLV_COLOR_GREY9";
	}
	if( color == MLV_COLOR_GRAY10 ){
		return "MLV_COLOR_GRAY10";
	}
	if( color == MLV_COLOR_GREY10 ){
		return "MLV_COLOR_GREY10";
	}
	if( color == MLV_COLOR_GRAY11 ){
		return "MLV_COLOR_GRAY11";
	}
	if( color == MLV_COLOR_GREY11 ){
		return "MLV_COLOR_GREY11";
	}
	if( color == MLV_COLOR_GRAY12 ){
		return "MLV_COLOR_GRAY12";
	}
	if( color == MLV_COLOR_GREY12 ){
		return "MLV_COLOR_GREY12";
	}
	if( color == MLV_COLOR_GRAY13 ){
		return "MLV_COLOR_GRAY13";
	}
	if( color == MLV_COLOR_GREY13 ){
		return "MLV_COLOR_GREY13";
	}
	if( color == MLV_COLOR_GRAY14 ){
		return "MLV_COLOR_GRAY14";
	}
	if( color == MLV_COLOR_GREY14 ){
		return "MLV_COLOR_GREY14";
	}
	if( color == MLV_COLOR_GRAY15 ){
		return "MLV_COLOR_GRAY15";
	}
	if( color == MLV_COLOR_GREY15 ){
		return "MLV_COLOR_GREY15";
	}
	if( color == MLV_COLOR_GRAY16 ){
		return "MLV_COLOR_GRAY16";
	}
	if( color == MLV_COLOR_GREY16 ){
		return "MLV_COLOR_GREY16";
	}
	if( color == MLV_COLOR_GRAY17 ){
		return "MLV_COLOR_GRAY17";
	}
	if( color == MLV_COLOR_GREY17 ){
		return "MLV_COLOR_GREY17";
	}
	if( color == MLV_COLOR_GRAY18 ){
		return "MLV_COLOR_GRAY18";
	}
	if( color == MLV_COLOR_GREY18 ){
		return "MLV_COLOR_GREY18";
	}
	if( color == MLV_COLOR_GRAY19 ){
		return "MLV_COLOR_GRAY19";
	}
	if( color == MLV_COLOR_GREY19 ){
		return "MLV_COLOR_GREY19";
	}
	if( color == MLV_COLOR_GRAY20 ){
		return "MLV_COLOR_GRAY20";
	}
	if( color == MLV_COLOR_GREY20 ){
		return "MLV_COLOR_GREY20";
	}
	if( color == MLV_COLOR_GRAY21 ){
		return "MLV_COLOR_GRAY21";
	}
	if( color == MLV_COLOR_GREY21 ){
		return "MLV_COLOR_GREY21";
	}
	if( color == MLV_COLOR_GRAY22 ){
		return "MLV_COLOR_GRAY22";
	}
	if( color == MLV_COLOR_GREY22 ){
		return "MLV_COLOR_GREY22";
	}
	if( color == MLV_COLOR_GRAY23 ){
		return "MLV_COLOR_GRAY23";
	}
	if( color == MLV_COLOR_GREY23 ){
		return "MLV_COLOR_GREY23";
	}
	if( color == MLV_COLOR_GRAY24 ){
		return "MLV_COLOR_GRAY24";
	}
	if( color == MLV_COLOR_GREY24 ){
		return "MLV_COLOR_GREY24";
	}
	if( color == MLV_COLOR_GRAY25 ){
		return "MLV_COLOR_GRAY25";
	}
	if( color == MLV_COLOR_GREY25 ){
		return "MLV_COLOR_GREY25";
	}
	if( color == MLV_COLOR_GRAY26 ){
		return "MLV_COLOR_GRAY26";
	}
	if( color == MLV_COLOR_GREY26 ){
		return "MLV_COLOR_GREY26";
	}
	if( color == MLV_COLOR_GRAY27 ){
		return "MLV_COLOR_GRAY27";
	}
	if( color == MLV_COLOR_GREY27 ){
		return "MLV_COLOR_GREY27";
	}
	if( color == MLV_COLOR_GRAY28 ){
		return "MLV_COLOR_GRAY28";
	}
	if( color == MLV_COLOR_GREY28 ){
		return "MLV_COLOR_GREY28";
	}
	if( color == MLV_COLOR_GRAY29 ){
		return "MLV_COLOR_GRAY29";
	}
	if( color == MLV_COLOR_GREY29 ){
		return "MLV_COLOR_GREY29";
	}
	if( color == MLV_COLOR_GRAY30 ){
		return "MLV_COLOR_GRAY30";
	}
	if( color == MLV_COLOR_GREY30 ){
		return "MLV_COLOR_GREY30";
	}
	if( color == MLV_COLOR_GRAY31 ){
		return "MLV_COLOR_GRAY31";
	}
	if( color == MLV_COLOR_GREY31 ){
		return "MLV_COLOR_GREY31";
	}
	if( color == MLV_COLOR_GRAY32 ){
		return "MLV_COLOR_GRAY32";
	}
	if( color == MLV_COLOR_GREY32 ){
		return "MLV_COLOR_GREY32";
	}
	if( color == MLV_COLOR_GRAY33 ){
		return "MLV_COLOR_GRAY33";
	}
	if( color == MLV_COLOR_GREY33 ){
		return "MLV_COLOR_GREY33";
	}
	if( color == MLV_COLOR_GRAY34 ){
		return "MLV_COLOR_GRAY34";
	}
	if( color == MLV_COLOR_GREY34 ){
		return "MLV_COLOR_GREY34";
	}
	if( color == MLV_COLOR_GRAY35 ){
		return "MLV_COLOR_GRAY35";
	}
	if( color == MLV_COLOR_GREY35 ){
		return "MLV_COLOR_GREY35";
	}
	if( color == MLV_COLOR_GRAY36 ){
		return "MLV_COLOR_GRAY36";
	}
	if( color == MLV_COLOR_GREY36 ){
		return "MLV_COLOR_GREY36";
	}
	if( color == MLV_COLOR_GRAY37 ){
		return "MLV_COLOR_GRAY37";
	}
	if( color == MLV_COLOR_GREY37 ){
		return "MLV_COLOR_GREY37";
	}
	if( color == MLV_COLOR_GRAY38 ){
		return "MLV_COLOR_GRAY38";
	}
	if( color == MLV_COLOR_GREY38 ){
		return "MLV_COLOR_GREY38";
	}
	if( color == MLV_COLOR_GRAY39 ){
		return "MLV_COLOR_GRAY39";
	}
	if( color == MLV_COLOR_GREY39 ){
		return "MLV_COLOR_GREY39";
	}
	if( color == MLV_COLOR_GRAY40 ){
		return "MLV_COLOR_GRAY40";
	}
	if( color == MLV_COLOR_GREY40 ){
		return "MLV_COLOR_GREY40";
	}
	if( color == MLV_COLOR_GRAY41 ){
		return "MLV_COLOR_GRAY41";
	}
	if( color == MLV_COLOR_GREY41 ){
		return "MLV_COLOR_GREY41";
	}
	if( color == MLV_COLOR_GRAY42 ){
		return "MLV_COLOR_GRAY42";
	}
	if( color == MLV_COLOR_GREY42 ){
		return "MLV_COLOR_GREY42";
	}
	if( color == MLV_COLOR_GRAY43 ){
		return "MLV_COLOR_GRAY43";
	}
	if( color == MLV_COLOR_GREY43 ){
		return "MLV_COLOR_GREY43";
	}
	if( color == MLV_COLOR_GRAY44 ){
		return "MLV_COLOR_GRAY44";
	}
	if( color == MLV_COLOR_GREY44 ){
		return "MLV_COLOR_GREY44";
	}
	if( color == MLV_COLOR_GRAY45 ){
		return "MLV_COLOR_GRAY45";
	}
	if( color == MLV_COLOR_GREY45 ){
		return "MLV_COLOR_GREY45";
	}
	if( color == MLV_COLOR_GRAY46 ){
		return "MLV_COLOR_GRAY46";
	}
	if( color == MLV_COLOR_GREY46 ){
		return "MLV_COLOR_GREY46";
	}
	if( color == MLV_COLOR_GRAY47 ){
		return "MLV_COLOR_GRAY47";
	}
	if( color == MLV_COLOR_GREY47 ){
		return "MLV_COLOR_GREY47";
	}
	if( color == MLV_COLOR_GRAY48 ){
		return "MLV_COLOR_GRAY48";
	}
	if( color == MLV_COLOR_GREY48 ){
		return "MLV_COLOR_GREY48";
	}
	if( color == MLV_COLOR_GRAY49 ){
		return "MLV_COLOR_GRAY49";
	}
	if( color == MLV_COLOR_GREY49 ){
		return "MLV_COLOR_GREY49";
	}
	if( color == MLV_COLOR_GRAY50 ){
		return "MLV_COLOR_GRAY50";
	}
	if( color == MLV_COLOR_GREY50 ){
		return "MLV_COLOR_GREY50";
	}
	if( color == MLV_COLOR_GRAY51 ){
		return "MLV_COLOR_GRAY51";
	}
	if( color == MLV_COLOR_GREY51 ){
		return "MLV_COLOR_GREY51";
	}
	if( color == MLV_COLOR_GRAY52 ){
		return "MLV_COLOR_GRAY52";
	}
	if( color == MLV_COLOR_GREY52 ){
		return "MLV_COLOR_GREY52";
	}
	if( color == MLV_COLOR_GRAY53 ){
		return "MLV_COLOR_GRAY53";
	}
	if( color == MLV_COLOR_GREY53 ){
		return "MLV_COLOR_GREY53";
	}
	if( color == MLV_COLOR_GRAY54 ){
		return "MLV_COLOR_GRAY54";
	}
	if( color == MLV_COLOR_GREY54 ){
		return "MLV_COLOR_GREY54";
	}
	if( color == MLV_COLOR_GRAY55 ){
		return "MLV_COLOR_GRAY55";
	}
	if( color == MLV_COLOR_GREY55 ){
		return "MLV_COLOR_GREY55";
	}
	if( color == MLV_COLOR_GRAY56 ){
		return "MLV_COLOR_GRAY56";
	}
	if( color == MLV_COLOR_GREY56 ){
		return "MLV_COLOR_GREY56";
	}
	if( color == MLV_COLOR_GRAY57 ){
		return "MLV_COLOR_GRAY57";
	}
	if( color == MLV_COLOR_GREY57 ){
		return "MLV_COLOR_GREY57";
	}
	if( color == MLV_COLOR_GRAY58 ){
		return "MLV_COLOR_GRAY58";
	}
	if( color == MLV_COLOR_GREY58 ){
		return "MLV_COLOR_GREY58";
	}
	if( color == MLV_COLOR_GRAY59 ){
		return "MLV_COLOR_GRAY59";
	}
	if( color == MLV_COLOR_GREY59 ){
		return "MLV_COLOR_GREY59";
	}
	if( color == MLV_COLOR_GRAY60 ){
		return "MLV_COLOR_GRAY60";
	}
	if( color == MLV_COLOR_GREY60 ){
		return "MLV_COLOR_GREY60";
	}
	if( color == MLV_COLOR_GRAY61 ){
		return "MLV_COLOR_GRAY61";
	}
	if( color == MLV_COLOR_GREY61 ){
		return "MLV_COLOR_GREY61";
	}
	if( color == MLV_COLOR_GRAY62 ){
		return "MLV_COLOR_GRAY62";
	}
	if( color == MLV_COLOR_GREY62 ){
		return "MLV_COLOR_GREY62";
	}
	if( color == MLV_COLOR_GRAY63 ){
		return "MLV_COLOR_GRAY63";
	}
	if( color == MLV_COLOR_GREY63 ){
		return "MLV_COLOR_GREY63";
	}
	if( color == MLV_COLOR_GRAY64 ){
		return "MLV_COLOR_GRAY64";
	}
	if( color == MLV_COLOR_GREY64 ){
		return "MLV_COLOR_GREY64";
	}
	if( color == MLV_COLOR_GRAY65 ){
		return "MLV_COLOR_GRAY65";
	}
	if( color == MLV_COLOR_GREY65 ){
		return "MLV_COLOR_GREY65";
	}
	if( color == MLV_COLOR_GRAY66 ){
		return "MLV_COLOR_GRAY66";
	}
	if( color == MLV_COLOR_GREY66 ){
		return "MLV_COLOR_GREY66";
	}
	if( color == MLV_COLOR_GRAY67 ){
		return "MLV_COLOR_GRAY67";
	}
	if( color == MLV_COLOR_GREY67 ){
		return "MLV_COLOR_GREY67";
	}
	if( color == MLV_COLOR_GRAY68 ){
		return "MLV_COLOR_GRAY68";
	}
	if( color == MLV_COLOR_GREY68 ){
		return "MLV_COLOR_GREY68";
	}
	if( color == MLV_COLOR_GRAY69 ){
		return "MLV_COLOR_GRAY69";
	}
	if( color == MLV_COLOR_GREY69 ){
		return "MLV_COLOR_GREY69";
	}
	if( color == MLV_COLOR_GRAY70 ){
		return "MLV_COLOR_GRAY70";
	}
	if( color == MLV_COLOR_GREY70 ){
		return "MLV_COLOR_GREY70";
	}
	if( color == MLV_COLOR_GRAY71 ){
		return "MLV_COLOR_GRAY71";
	}
	if( color == MLV_COLOR_GREY71 ){
		return "MLV_COLOR_GREY71";
	}
	if( color == MLV_COLOR_GRAY72 ){
		return "MLV_COLOR_GRAY72";
	}
	if( color == MLV_COLOR_GREY72 ){
		return "MLV_COLOR_GREY72";
	}
	if( color == MLV_COLOR_GRAY73 ){
		return "MLV_COLOR_GRAY73";
	}
	if( color == MLV_COLOR_GREY73 ){
		return "MLV_COLOR_GREY73";
	}
	if( color == MLV_COLOR_GRAY74 ){
		return "MLV_COLOR_GRAY74";
	}
	if( color == MLV_COLOR_GREY74 ){
		return "MLV_COLOR_GREY74";
	}
	if( color == MLV_COLOR_GRAY75 ){
		return "MLV_COLOR_GRAY75";
	}
	if( color == MLV_COLOR_GREY75 ){
		return "MLV_COLOR_GREY75";
	}
	if( color == MLV_COLOR_GRAY76 ){
		return "MLV_COLOR_GRAY76";
	}
	if( color == MLV_COLOR_GREY76 ){
		return "MLV_COLOR_GREY76";
	}
	if( color == MLV_COLOR_GRAY77 ){
		return "MLV_COLOR_GRAY77";
	}
	if( color == MLV_COLOR_GREY77 ){
		return "MLV_COLOR_GREY77";
	}
	if( color == MLV_COLOR_GRAY78 ){
		return "MLV_COLOR_GRAY78";
	}
	if( color == MLV_COLOR_GREY78 ){
		return "MLV_COLOR_GREY78";
	}
	if( color == MLV_COLOR_GRAY79 ){
		return "MLV_COLOR_GRAY79";
	}
	if( color == MLV_COLOR_GREY79 ){
		return "MLV_COLOR_GREY79";
	}
	if( color == MLV_COLOR_GRAY80 ){
		return "MLV_COLOR_GRAY80";
	}
	if( color == MLV_COLOR_GREY80 ){
		return "MLV_COLOR_GREY80";
	}
	if( color == MLV_COLOR_GRAY81 ){
		return "MLV_COLOR_GRAY81";
	}
	if( color == MLV_COLOR_GREY81 ){
		return "MLV_COLOR_GREY81";
	}
	if( color == MLV_COLOR_GRAY82 ){
		return "MLV_COLOR_GRAY82";
	}
	if( color == MLV_COLOR_GREY82 ){
		return "MLV_COLOR_GREY82";
	}
	if( color == MLV_COLOR_GRAY83 ){
		return "MLV_COLOR_GRAY83";
	}
	if( color == MLV_COLOR_GREY83 ){
		return "MLV_COLOR_GREY83";
	}
	if( color == MLV_COLOR_GRAY84 ){
		return "MLV_COLOR_GRAY84";
	}
	if( color == MLV_COLOR_GREY84 ){
		return "MLV_COLOR_GREY84";
	}
	if( color == MLV_COLOR_GRAY85 ){
		return "MLV_COLOR_GRAY85";
	}
	if( color == MLV_COLOR_GREY85 ){
		return "MLV_COLOR_GREY85";
	}
	if( color == MLV_COLOR_GRAY86 ){
		return "MLV_COLOR_GRAY86";
	}
	if( color == MLV_COLOR_GREY86 ){
		return "MLV_COLOR_GREY86";
	}
	if( color == MLV_COLOR_GRAY87 ){
		return "MLV_COLOR_GRAY87";
	}
	if( color == MLV_COLOR_GREY87 ){
		return "MLV_COLOR_GREY87";
	}
	if( color == MLV_COLOR_GRAY88 ){
		return "MLV_COLOR_GRAY88";
	}
	if( color == MLV_COLOR_GREY88 ){
		return "MLV_COLOR_GREY88";
	}
	if( color == MLV_COLOR_GRAY89 ){
		return "MLV_COLOR_GRAY89";
	}
	if( color == MLV_COLOR_GREY89 ){
		return "MLV_COLOR_GREY89";
	}
	if( color == MLV_COLOR_GRAY90 ){
		return "MLV_COLOR_GRAY90";
	}
	if( color == MLV_COLOR_GREY90 ){
		return "MLV_COLOR_GREY90";
	}
	if( color == MLV_COLOR_GRAY91 ){
		return "MLV_COLOR_GRAY91";
	}
	if( color == MLV_COLOR_GREY91 ){
		return "MLV_COLOR_GREY91";
	}
	if( color == MLV_COLOR_GRAY92 ){
		return "MLV_COLOR_GRAY92";
	}
	if( color == MLV_COLOR_GREY92 ){
		return "MLV_COLOR_GREY92";
	}
	if( color == MLV_COLOR_GRAY93 ){
		return "MLV_COLOR_GRAY93";
	}
	if( color == MLV_COLOR_GREY93 ){
		return "MLV_COLOR_GREY93";
	}
	if( color == MLV_COLOR_GRAY94 ){
		return "MLV_COLOR_GRAY94";
	}
	if( color == MLV_COLOR_GREY94 ){
		return "MLV_COLOR_GREY94";
	}
	if( color == MLV_COLOR_GRAY95 ){
		return "MLV_COLOR_GRAY95";
	}
	if( color == MLV_COLOR_GREY95 ){
		return "MLV_COLOR_GREY95";
	}
	if( color == MLV_COLOR_GRAY96 ){
		return "MLV_COLOR_GRAY96";
	}
	if( color == MLV_COLOR_GREY96 ){
		return "MLV_COLOR_GREY96";
	}
	if( color == MLV_COLOR_GRAY97 ){
		return "MLV_COLOR_GRAY97";
	}
	if( color == MLV_COLOR_GREY97 ){
		return "MLV_COLOR_GREY97";
	}
	if( color == MLV_COLOR_GRAY98 ){
		return "MLV_COLOR_GRAY98";
	}
	if( color == MLV_COLOR_GREY98 ){
		return "MLV_COLOR_GREY98";
	}
	if( color == MLV_COLOR_GRAY99 ){
		return "MLV_COLOR_GRAY99";
	}
	if( color == MLV_COLOR_GREY99 ){
		return "MLV_COLOR_GREY99";
	}
	if( color == MLV_COLOR_GRAY100 ){
		return "MLV_COLOR_GRAY100";
	}
	if( color == MLV_COLOR_GREY100 ){
		return "MLV_COLOR_GREY100";
	}
	if( color == MLV_COLOR_DARK_GREY ){
		return "MLV_COLOR_DARK_GREY";
	}
	if( color == MLV_COLOR_DARKGREY ){
		return "MLV_COLOR_DARKGREY";
	}
	if( color == MLV_COLOR_DARK_GRAY ){
		return "MLV_COLOR_DARK_GRAY";
	}
	if( color == MLV_COLOR_DARKGRAY ){
		return "MLV_COLOR_DARKGRAY";
	}
	if( color == MLV_COLOR_DARK_BLUE ){
		return "MLV_COLOR_DARK_BLUE";
	}
	if( color == MLV_COLOR_DARKBLUE ){
		return "MLV_COLOR_DARKBLUE";
	}
	if( color == MLV_COLOR_DARK_CYAN ){
		return "MLV_COLOR_DARK_CYAN";
	}
	if( color == MLV_COLOR_DARKCYAN ){
		return "MLV_COLOR_DARKCYAN";
	}
	if( color == MLV_COLOR_DARK_MAGENTA ){
		return "MLV_COLOR_DARK_MAGENTA";
	}
	if( color == MLV_COLOR_DARKMAGENTA ){
		return "MLV_COLOR_DARKMAGENTA";
	}
	if( color == MLV_COLOR_DARK_RED ){
		return "MLV_COLOR_DARK_RED";
	}
	if( color == MLV_COLOR_DARKRED ){
		return "MLV_COLOR_DARKRED";
	}
	if( color == MLV_COLOR_LIGHT_GREEN ){
		return "MLV_COLOR_LIGHT_GREEN";
	}
	if( color == MLV_COLOR_LIGHTGREEN ){
		return "MLV_COLOR_LIGHTGREEN";
	}
	ERROR( "Unexepcted color code" );
	return NULL;
}

MLV_Color MLV_convert_string_to_color( const char* color_name ){
	if( strcmp( color_name, "MLV_COLOR_SNOW" )==0 ){
		return MLV_COLOR_SNOW;
	} 
	if( strcmp( color_name, "MLV_COLOR_GHOST_WHITE" )==0 ){
		return MLV_COLOR_GHOST_WHITE;
	} 
	if( strcmp( color_name, "MLV_COLOR_GHOSTWHITE" )==0 ){
		return MLV_COLOR_GHOSTWHITE;
	} 
	if( strcmp( color_name, "MLV_COLOR_WHITE_SMOKE" )==0 ){
		return MLV_COLOR_WHITE_SMOKE;
	} 
	if( strcmp( color_name, "MLV_COLOR_WHITESMOKE" )==0 ){
		return MLV_COLOR_WHITESMOKE;
	} 
	if( strcmp( color_name, "MLV_COLOR_GAINSBORO" )==0 ){
		return MLV_COLOR_GAINSBORO;
	} 
	if( strcmp( color_name, "MLV_COLOR_FLORAL_WHITE" )==0 ){
		return MLV_COLOR_FLORAL_WHITE;
	} 
	if( strcmp( color_name, "MLV_COLOR_FLORALWHITE" )==0 ){
		return MLV_COLOR_FLORALWHITE;
	} 
	if( strcmp( color_name, "MLV_COLOR_OLD_LACE" )==0 ){
		return MLV_COLOR_OLD_LACE;
	} 
	if( strcmp( color_name, "MLV_COLOR_OLDLACE" )==0 ){
		return MLV_COLOR_OLDLACE;
	} 
	if( strcmp( color_name, "MLV_COLOR_LINEN" )==0 ){
		return MLV_COLOR_LINEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_ANTIQUE_WHITE" )==0 ){
		return MLV_COLOR_ANTIQUE_WHITE;
	} 
	if( strcmp( color_name, "MLV_COLOR_ANTIQUEWHITE" )==0 ){
		return MLV_COLOR_ANTIQUEWHITE;
	} 
	if( strcmp( color_name, "MLV_COLOR_PAPAYA_WHIP" )==0 ){
		return MLV_COLOR_PAPAYA_WHIP;
	} 
	if( strcmp( color_name, "MLV_COLOR_PAPAYAWHIP" )==0 ){
		return MLV_COLOR_PAPAYAWHIP;
	} 
	if( strcmp( color_name, "MLV_COLOR_BLANCHED_ALMOND" )==0 ){
		return MLV_COLOR_BLANCHED_ALMOND;
	} 
	if( strcmp( color_name, "MLV_COLOR_BLANCHEDALMOND" )==0 ){
		return MLV_COLOR_BLANCHEDALMOND;
	} 
	if( strcmp( color_name, "MLV_COLOR_BISQUE" )==0 ){
		return MLV_COLOR_BISQUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_PEACH_PUFF" )==0 ){
		return MLV_COLOR_PEACH_PUFF;
	} 
	if( strcmp( color_name, "MLV_COLOR_PEACHPUFF" )==0 ){
		return MLV_COLOR_PEACHPUFF;
	} 
	if( strcmp( color_name, "MLV_COLOR_NAVAJO_WHITE" )==0 ){
		return MLV_COLOR_NAVAJO_WHITE;
	} 
	if( strcmp( color_name, "MLV_COLOR_NAVAJOWHITE" )==0 ){
		return MLV_COLOR_NAVAJOWHITE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MOCCASIN" )==0 ){
		return MLV_COLOR_MOCCASIN;
	} 
	if( strcmp( color_name, "MLV_COLOR_CORNSILK" )==0 ){
		return MLV_COLOR_CORNSILK;
	} 
	if( strcmp( color_name, "MLV_COLOR_IVORY" )==0 ){
		return MLV_COLOR_IVORY;
	} 
	if( strcmp( color_name, "MLV_COLOR_LEMON_CHIFFON" )==0 ){
		return MLV_COLOR_LEMON_CHIFFON;
	} 
	if( strcmp( color_name, "MLV_COLOR_LEMONCHIFFON" )==0 ){
		return MLV_COLOR_LEMONCHIFFON;
	} 
	if( strcmp( color_name, "MLV_COLOR_SEASHELL" )==0 ){
		return MLV_COLOR_SEASHELL;
	} 
	if( strcmp( color_name, "MLV_COLOR_HONEYDEW" )==0 ){
		return MLV_COLOR_HONEYDEW;
	} 
	if( strcmp( color_name, "MLV_COLOR_MINT_CREAM" )==0 ){
		return MLV_COLOR_MINT_CREAM;
	} 
	if( strcmp( color_name, "MLV_COLOR_MINTCREAM" )==0 ){
		return MLV_COLOR_MINTCREAM;
	} 
	if( strcmp( color_name, "MLV_COLOR_AZURE" )==0 ){
		return MLV_COLOR_AZURE;
	} 
	if( strcmp( color_name, "MLV_COLOR_ALICE_BLUE" )==0 ){
		return MLV_COLOR_ALICE_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_ALICEBLUE" )==0 ){
		return MLV_COLOR_ALICEBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_LAVENDER" )==0 ){
		return MLV_COLOR_LAVENDER;
	} 
	if( strcmp( color_name, "MLV_COLOR_LAVENDER_BLUSH" )==0 ){
		return MLV_COLOR_LAVENDER_BLUSH;
	} 
	if( strcmp( color_name, "MLV_COLOR_LAVENDERBLUSH" )==0 ){
		return MLV_COLOR_LAVENDERBLUSH;
	} 
	if( strcmp( color_name, "MLV_COLOR_MISTY_ROSE" )==0 ){
		return MLV_COLOR_MISTY_ROSE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MISTYROSE" )==0 ){
		return MLV_COLOR_MISTYROSE;
	} 
	if( strcmp( color_name, "MLV_COLOR_WHITE" )==0 ){
		return MLV_COLOR_WHITE;
	} 
	if( strcmp( color_name, "MLV_COLOR_BLACK" )==0 ){
		return MLV_COLOR_BLACK;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_SLATE_GRAY" )==0 ){
		return MLV_COLOR_DARK_SLATE_GRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSLATEGRAY" )==0 ){
		return MLV_COLOR_DARKSLATEGRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_SLATE_GREY" )==0 ){
		return MLV_COLOR_DARK_SLATE_GREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSLATEGREY" )==0 ){
		return MLV_COLOR_DARKSLATEGREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_DIM_GRAY" )==0 ){
		return MLV_COLOR_DIM_GRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_DIMGRAY" )==0 ){
		return MLV_COLOR_DIMGRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_DIM_GREY" )==0 ){
		return MLV_COLOR_DIM_GREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_DIMGREY" )==0 ){
		return MLV_COLOR_DIMGREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATE_GRAY" )==0 ){
		return MLV_COLOR_SLATE_GRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATEGRAY" )==0 ){
		return MLV_COLOR_SLATEGRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATE_GREY" )==0 ){
		return MLV_COLOR_SLATE_GREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATEGREY" )==0 ){
		return MLV_COLOR_SLATEGREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_SLATE_GRAY" )==0 ){
		return MLV_COLOR_LIGHT_SLATE_GRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSLATEGRAY" )==0 ){
		return MLV_COLOR_LIGHTSLATEGRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_SLATE_GREY" )==0 ){
		return MLV_COLOR_LIGHT_SLATE_GREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSLATEGREY" )==0 ){
		return MLV_COLOR_LIGHTSLATEGREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY" )==0 ){
		return MLV_COLOR_GRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY" )==0 ){
		return MLV_COLOR_GREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_GREY" )==0 ){
		return MLV_COLOR_LIGHT_GREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTGREY" )==0 ){
		return MLV_COLOR_LIGHTGREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_GRAY" )==0 ){
		return MLV_COLOR_LIGHT_GRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTGRAY" )==0 ){
		return MLV_COLOR_LIGHTGRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_MIDNIGHT_BLUE" )==0 ){
		return MLV_COLOR_MIDNIGHT_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MIDNIGHTBLUE" )==0 ){
		return MLV_COLOR_MIDNIGHTBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_NAVY" )==0 ){
		return MLV_COLOR_NAVY;
	} 
	if( strcmp( color_name, "MLV_COLOR_NAVY_BLUE" )==0 ){
		return MLV_COLOR_NAVY_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_NAVYBLUE" )==0 ){
		return MLV_COLOR_NAVYBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_CORNFLOWER_BLUE" )==0 ){
		return MLV_COLOR_CORNFLOWER_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_CORNFLOWERBLUE" )==0 ){
		return MLV_COLOR_CORNFLOWERBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_SLATE_BLUE" )==0 ){
		return MLV_COLOR_DARK_SLATE_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSLATEBLUE" )==0 ){
		return MLV_COLOR_DARKSLATEBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATE_BLUE" )==0 ){
		return MLV_COLOR_SLATE_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATEBLUE" )==0 ){
		return MLV_COLOR_SLATEBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUM_SLATE_BLUE" )==0 ){
		return MLV_COLOR_MEDIUM_SLATE_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMSLATEBLUE" )==0 ){
		return MLV_COLOR_MEDIUMSLATEBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_SLATE_BLUE" )==0 ){
		return MLV_COLOR_LIGHT_SLATE_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSLATEBLUE" )==0 ){
		return MLV_COLOR_LIGHTSLATEBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUM_BLUE" )==0 ){
		return MLV_COLOR_MEDIUM_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMBLUE" )==0 ){
		return MLV_COLOR_MEDIUMBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_ROYAL_BLUE" )==0 ){
		return MLV_COLOR_ROYAL_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_ROYALBLUE" )==0 ){
		return MLV_COLOR_ROYALBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_BLUE" )==0 ){
		return MLV_COLOR_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DODGER_BLUE" )==0 ){
		return MLV_COLOR_DODGER_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DODGERBLUE" )==0 ){
		return MLV_COLOR_DODGERBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DEEP_SKY_BLUE" )==0 ){
		return MLV_COLOR_DEEP_SKY_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DEEPSKYBLUE" )==0 ){
		return MLV_COLOR_DEEPSKYBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_SKY_BLUE" )==0 ){
		return MLV_COLOR_SKY_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_SKYBLUE" )==0 ){
		return MLV_COLOR_SKYBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_SKY_BLUE" )==0 ){
		return MLV_COLOR_LIGHT_SKY_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSKYBLUE" )==0 ){
		return MLV_COLOR_LIGHTSKYBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_STEEL_BLUE" )==0 ){
		return MLV_COLOR_STEEL_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_STEELBLUE" )==0 ){
		return MLV_COLOR_STEELBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_STEEL_BLUE" )==0 ){
		return MLV_COLOR_LIGHT_STEEL_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSTEELBLUE" )==0 ){
		return MLV_COLOR_LIGHTSTEELBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_BLUE" )==0 ){
		return MLV_COLOR_LIGHT_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTBLUE" )==0 ){
		return MLV_COLOR_LIGHTBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_POWDER_BLUE" )==0 ){
		return MLV_COLOR_POWDER_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_POWDERBLUE" )==0 ){
		return MLV_COLOR_POWDERBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALE_TURQUOISE" )==0 ){
		return MLV_COLOR_PALE_TURQUOISE;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALETURQUOISE" )==0 ){
		return MLV_COLOR_PALETURQUOISE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_TURQUOISE" )==0 ){
		return MLV_COLOR_DARK_TURQUOISE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKTURQUOISE" )==0 ){
		return MLV_COLOR_DARKTURQUOISE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUM_TURQUOISE" )==0 ){
		return MLV_COLOR_MEDIUM_TURQUOISE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMTURQUOISE" )==0 ){
		return MLV_COLOR_MEDIUMTURQUOISE;
	} 
	if( strcmp( color_name, "MLV_COLOR_TURQUOISE" )==0 ){
		return MLV_COLOR_TURQUOISE;
	} 
	if( strcmp( color_name, "MLV_COLOR_CYAN" )==0 ){
		return MLV_COLOR_CYAN;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_CYAN" )==0 ){
		return MLV_COLOR_LIGHT_CYAN;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTCYAN" )==0 ){
		return MLV_COLOR_LIGHTCYAN;
	} 
	if( strcmp( color_name, "MLV_COLOR_CADET_BLUE" )==0 ){
		return MLV_COLOR_CADET_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_CADETBLUE" )==0 ){
		return MLV_COLOR_CADETBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUM_AQUAMARINE" )==0 ){
		return MLV_COLOR_MEDIUM_AQUAMARINE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMAQUAMARINE" )==0 ){
		return MLV_COLOR_MEDIUMAQUAMARINE;
	} 
	if( strcmp( color_name, "MLV_COLOR_AQUAMARINE" )==0 ){
		return MLV_COLOR_AQUAMARINE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_GREEN" )==0 ){
		return MLV_COLOR_DARK_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKGREEN" )==0 ){
		return MLV_COLOR_DARKGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_OLIVE_GREEN" )==0 ){
		return MLV_COLOR_DARK_OLIVE_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKOLIVEGREEN" )==0 ){
		return MLV_COLOR_DARKOLIVEGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_SEA_GREEN" )==0 ){
		return MLV_COLOR_DARK_SEA_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSEAGREEN" )==0 ){
		return MLV_COLOR_DARKSEAGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_SEA_GREEN" )==0 ){
		return MLV_COLOR_SEA_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_SEAGREEN" )==0 ){
		return MLV_COLOR_SEAGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUM_SEA_GREEN" )==0 ){
		return MLV_COLOR_MEDIUM_SEA_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMSEAGREEN" )==0 ){
		return MLV_COLOR_MEDIUMSEAGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_SEA_GREEN" )==0 ){
		return MLV_COLOR_LIGHT_SEA_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSEAGREEN" )==0 ){
		return MLV_COLOR_LIGHTSEAGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALE_GREEN" )==0 ){
		return MLV_COLOR_PALE_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALEGREEN" )==0 ){
		return MLV_COLOR_PALEGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_SPRING_GREEN" )==0 ){
		return MLV_COLOR_SPRING_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_SPRINGGREEN" )==0 ){
		return MLV_COLOR_SPRINGGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_LAWN_GREEN" )==0 ){
		return MLV_COLOR_LAWN_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_LAWNGREEN" )==0 ){
		return MLV_COLOR_LAWNGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREEN" )==0 ){
		return MLV_COLOR_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_CHARTREUSE" )==0 ){
		return MLV_COLOR_CHARTREUSE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUM_SPRING_GREEN" )==0 ){
		return MLV_COLOR_MEDIUM_SPRING_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMSPRINGGREEN" )==0 ){
		return MLV_COLOR_MEDIUMSPRINGGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREEN_YELLOW" )==0 ){
		return MLV_COLOR_GREEN_YELLOW;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREENYELLOW" )==0 ){
		return MLV_COLOR_GREENYELLOW;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIME_GREEN" )==0 ){
		return MLV_COLOR_LIME_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIMEGREEN" )==0 ){
		return MLV_COLOR_LIMEGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_YELLOW_GREEN" )==0 ){
		return MLV_COLOR_YELLOW_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_YELLOWGREEN" )==0 ){
		return MLV_COLOR_YELLOWGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_FOREST_GREEN" )==0 ){
		return MLV_COLOR_FOREST_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_FORESTGREEN" )==0 ){
		return MLV_COLOR_FORESTGREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_OLIVE_DRAB" )==0 ){
		return MLV_COLOR_OLIVE_DRAB;
	} 
	if( strcmp( color_name, "MLV_COLOR_OLIVEDRAB" )==0 ){
		return MLV_COLOR_OLIVEDRAB;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_KHAKI" )==0 ){
		return MLV_COLOR_DARK_KHAKI;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKKHAKI" )==0 ){
		return MLV_COLOR_DARKKHAKI;
	} 
	if( strcmp( color_name, "MLV_COLOR_KHAKI" )==0 ){
		return MLV_COLOR_KHAKI;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALE_GOLDENROD" )==0 ){
		return MLV_COLOR_PALE_GOLDENROD;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALEGOLDENROD" )==0 ){
		return MLV_COLOR_PALEGOLDENROD;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_GOLDENROD_YELLOW" )==0 ){
		return MLV_COLOR_LIGHT_GOLDENROD_YELLOW;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTGOLDENRODYELLOW" )==0 ){
		return MLV_COLOR_LIGHTGOLDENRODYELLOW;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_YELLOW" )==0 ){
		return MLV_COLOR_LIGHT_YELLOW;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTYELLOW" )==0 ){
		return MLV_COLOR_LIGHTYELLOW;
	} 
	if( strcmp( color_name, "MLV_COLOR_YELLOW" )==0 ){
		return MLV_COLOR_YELLOW;
	} 
	if( strcmp( color_name, "MLV_COLOR_GOLD" )==0 ){
		return MLV_COLOR_GOLD;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_GOLDENROD" )==0 ){
		return MLV_COLOR_LIGHT_GOLDENROD;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTGOLDENROD" )==0 ){
		return MLV_COLOR_LIGHTGOLDENROD;
	} 
	if( strcmp( color_name, "MLV_COLOR_GOLDENROD" )==0 ){
		return MLV_COLOR_GOLDENROD;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_GOLDENROD" )==0 ){
		return MLV_COLOR_DARK_GOLDENROD;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKGOLDENROD" )==0 ){
		return MLV_COLOR_DARKGOLDENROD;
	} 
	if( strcmp( color_name, "MLV_COLOR_ROSY_BROWN" )==0 ){
		return MLV_COLOR_ROSY_BROWN;
	} 
	if( strcmp( color_name, "MLV_COLOR_ROSYBROWN" )==0 ){
		return MLV_COLOR_ROSYBROWN;
	} 
	if( strcmp( color_name, "MLV_COLOR_INDIAN_RED" )==0 ){
		return MLV_COLOR_INDIAN_RED;
	} 
	if( strcmp( color_name, "MLV_COLOR_INDIANRED" )==0 ){
		return MLV_COLOR_INDIANRED;
	} 
	if( strcmp( color_name, "MLV_COLOR_SADDLE_BROWN" )==0 ){
		return MLV_COLOR_SADDLE_BROWN;
	} 
	if( strcmp( color_name, "MLV_COLOR_SADDLEBROWN" )==0 ){
		return MLV_COLOR_SADDLEBROWN;
	} 
	if( strcmp( color_name, "MLV_COLOR_SIENNA" )==0 ){
		return MLV_COLOR_SIENNA;
	} 
	if( strcmp( color_name, "MLV_COLOR_PERU" )==0 ){
		return MLV_COLOR_PERU;
	} 
	if( strcmp( color_name, "MLV_COLOR_BURLYWOOD" )==0 ){
		return MLV_COLOR_BURLYWOOD;
	} 
	if( strcmp( color_name, "MLV_COLOR_BEIGE" )==0 ){
		return MLV_COLOR_BEIGE;
	} 
	if( strcmp( color_name, "MLV_COLOR_WHEAT" )==0 ){
		return MLV_COLOR_WHEAT;
	} 
	if( strcmp( color_name, "MLV_COLOR_SANDY_BROWN" )==0 ){
		return MLV_COLOR_SANDY_BROWN;
	} 
	if( strcmp( color_name, "MLV_COLOR_SANDYBROWN" )==0 ){
		return MLV_COLOR_SANDYBROWN;
	} 
	if( strcmp( color_name, "MLV_COLOR_TAN" )==0 ){
		return MLV_COLOR_TAN;
	} 
	if( strcmp( color_name, "MLV_COLOR_CHOCOLATE" )==0 ){
		return MLV_COLOR_CHOCOLATE;
	} 
	if( strcmp( color_name, "MLV_COLOR_FIREBRICK" )==0 ){
		return MLV_COLOR_FIREBRICK;
	} 
	if( strcmp( color_name, "MLV_COLOR_BROWN" )==0 ){
		return MLV_COLOR_BROWN;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_SALMON" )==0 ){
		return MLV_COLOR_DARK_SALMON;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSALMON" )==0 ){
		return MLV_COLOR_DARKSALMON;
	} 
	if( strcmp( color_name, "MLV_COLOR_SALMON" )==0 ){
		return MLV_COLOR_SALMON;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_SALMON" )==0 ){
		return MLV_COLOR_LIGHT_SALMON;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSALMON" )==0 ){
		return MLV_COLOR_LIGHTSALMON;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORANGE" )==0 ){
		return MLV_COLOR_ORANGE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_ORANGE" )==0 ){
		return MLV_COLOR_DARK_ORANGE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKORANGE" )==0 ){
		return MLV_COLOR_DARKORANGE;
	} 
	if( strcmp( color_name, "MLV_COLOR_CORAL" )==0 ){
		return MLV_COLOR_CORAL;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_CORAL" )==0 ){
		return MLV_COLOR_LIGHT_CORAL;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTCORAL" )==0 ){
		return MLV_COLOR_LIGHTCORAL;
	} 
	if( strcmp( color_name, "MLV_COLOR_TOMATO" )==0 ){
		return MLV_COLOR_TOMATO;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORANGE_RED" )==0 ){
		return MLV_COLOR_ORANGE_RED;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORANGERED" )==0 ){
		return MLV_COLOR_ORANGERED;
	} 
	if( strcmp( color_name, "MLV_COLOR_RED" )==0 ){
		return MLV_COLOR_RED;
	} 
	if( strcmp( color_name, "MLV_COLOR_HOT_PINK" )==0 ){
		return MLV_COLOR_HOT_PINK;
	} 
	if( strcmp( color_name, "MLV_COLOR_HOTPINK" )==0 ){
		return MLV_COLOR_HOTPINK;
	} 
	if( strcmp( color_name, "MLV_COLOR_DEEP_PINK" )==0 ){
		return MLV_COLOR_DEEP_PINK;
	} 
	if( strcmp( color_name, "MLV_COLOR_DEEPPINK" )==0 ){
		return MLV_COLOR_DEEPPINK;
	} 
	if( strcmp( color_name, "MLV_COLOR_PINK" )==0 ){
		return MLV_COLOR_PINK;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_PINK" )==0 ){
		return MLV_COLOR_LIGHT_PINK;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTPINK" )==0 ){
		return MLV_COLOR_LIGHTPINK;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALE_VIOLET_RED" )==0 ){
		return MLV_COLOR_PALE_VIOLET_RED;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALEVIOLETRED" )==0 ){
		return MLV_COLOR_PALEVIOLETRED;
	} 
	if( strcmp( color_name, "MLV_COLOR_MAROON" )==0 ){
		return MLV_COLOR_MAROON;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUM_VIOLET_RED" )==0 ){
		return MLV_COLOR_MEDIUM_VIOLET_RED;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMVIOLETRED" )==0 ){
		return MLV_COLOR_MEDIUMVIOLETRED;
	} 
	if( strcmp( color_name, "MLV_COLOR_VIOLET_RED" )==0 ){
		return MLV_COLOR_VIOLET_RED;
	} 
	if( strcmp( color_name, "MLV_COLOR_VIOLETRED" )==0 ){
		return MLV_COLOR_VIOLETRED;
	} 
	if( strcmp( color_name, "MLV_COLOR_MAGENTA" )==0 ){
		return MLV_COLOR_MAGENTA;
	} 
	if( strcmp( color_name, "MLV_COLOR_VIOLET" )==0 ){
		return MLV_COLOR_VIOLET;
	} 
	if( strcmp( color_name, "MLV_COLOR_PLUM" )==0 ){
		return MLV_COLOR_PLUM;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORCHID" )==0 ){
		return MLV_COLOR_ORCHID;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUM_ORCHID" )==0 ){
		return MLV_COLOR_MEDIUM_ORCHID;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMORCHID" )==0 ){
		return MLV_COLOR_MEDIUMORCHID;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_ORCHID" )==0 ){
		return MLV_COLOR_DARK_ORCHID;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKORCHID" )==0 ){
		return MLV_COLOR_DARKORCHID;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_VIOLET" )==0 ){
		return MLV_COLOR_DARK_VIOLET;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKVIOLET" )==0 ){
		return MLV_COLOR_DARKVIOLET;
	} 
	if( strcmp( color_name, "MLV_COLOR_BLUE_VIOLET" )==0 ){
		return MLV_COLOR_BLUE_VIOLET;
	} 
	if( strcmp( color_name, "MLV_COLOR_BLUEVIOLET" )==0 ){
		return MLV_COLOR_BLUEVIOLET;
	} 
	if( strcmp( color_name, "MLV_COLOR_PURPLE" )==0 ){
		return MLV_COLOR_PURPLE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUM_PURPLE" )==0 ){
		return MLV_COLOR_MEDIUM_PURPLE;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMPURPLE" )==0 ){
		return MLV_COLOR_MEDIUMPURPLE;
	} 
	if( strcmp( color_name, "MLV_COLOR_THISTLE" )==0 ){
		return MLV_COLOR_THISTLE;
	} 
	if( strcmp( color_name, "MLV_COLOR_SNOW1" )==0 ){
		return MLV_COLOR_SNOW1;
	} 
	if( strcmp( color_name, "MLV_COLOR_SNOW2" )==0 ){
		return MLV_COLOR_SNOW2;
	} 
	if( strcmp( color_name, "MLV_COLOR_SNOW3" )==0 ){
		return MLV_COLOR_SNOW3;
	} 
	if( strcmp( color_name, "MLV_COLOR_SNOW4" )==0 ){
		return MLV_COLOR_SNOW4;
	} 
	if( strcmp( color_name, "MLV_COLOR_SEASHELL1" )==0 ){
		return MLV_COLOR_SEASHELL1;
	} 
	if( strcmp( color_name, "MLV_COLOR_SEASHELL2" )==0 ){
		return MLV_COLOR_SEASHELL2;
	} 
	if( strcmp( color_name, "MLV_COLOR_SEASHELL3" )==0 ){
		return MLV_COLOR_SEASHELL3;
	} 
	if( strcmp( color_name, "MLV_COLOR_SEASHELL4" )==0 ){
		return MLV_COLOR_SEASHELL4;
	} 
	if( strcmp( color_name, "MLV_COLOR_ANTIQUEWHITE1" )==0 ){
		return MLV_COLOR_ANTIQUEWHITE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_ANTIQUEWHITE2" )==0 ){
		return MLV_COLOR_ANTIQUEWHITE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_ANTIQUEWHITE3" )==0 ){
		return MLV_COLOR_ANTIQUEWHITE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_ANTIQUEWHITE4" )==0 ){
		return MLV_COLOR_ANTIQUEWHITE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_BISQUE1" )==0 ){
		return MLV_COLOR_BISQUE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_BISQUE2" )==0 ){
		return MLV_COLOR_BISQUE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_BISQUE3" )==0 ){
		return MLV_COLOR_BISQUE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_BISQUE4" )==0 ){
		return MLV_COLOR_BISQUE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_PEACHPUFF1" )==0 ){
		return MLV_COLOR_PEACHPUFF1;
	} 
	if( strcmp( color_name, "MLV_COLOR_PEACHPUFF2" )==0 ){
		return MLV_COLOR_PEACHPUFF2;
	} 
	if( strcmp( color_name, "MLV_COLOR_PEACHPUFF3" )==0 ){
		return MLV_COLOR_PEACHPUFF3;
	} 
	if( strcmp( color_name, "MLV_COLOR_PEACHPUFF4" )==0 ){
		return MLV_COLOR_PEACHPUFF4;
	} 
	if( strcmp( color_name, "MLV_COLOR_NAVAJOWHITE1" )==0 ){
		return MLV_COLOR_NAVAJOWHITE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_NAVAJOWHITE2" )==0 ){
		return MLV_COLOR_NAVAJOWHITE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_NAVAJOWHITE3" )==0 ){
		return MLV_COLOR_NAVAJOWHITE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_NAVAJOWHITE4" )==0 ){
		return MLV_COLOR_NAVAJOWHITE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_LEMONCHIFFON1" )==0 ){
		return MLV_COLOR_LEMONCHIFFON1;
	} 
	if( strcmp( color_name, "MLV_COLOR_LEMONCHIFFON2" )==0 ){
		return MLV_COLOR_LEMONCHIFFON2;
	} 
	if( strcmp( color_name, "MLV_COLOR_LEMONCHIFFON3" )==0 ){
		return MLV_COLOR_LEMONCHIFFON3;
	} 
	if( strcmp( color_name, "MLV_COLOR_LEMONCHIFFON4" )==0 ){
		return MLV_COLOR_LEMONCHIFFON4;
	} 
	if( strcmp( color_name, "MLV_COLOR_CORNSILK1" )==0 ){
		return MLV_COLOR_CORNSILK1;
	} 
	if( strcmp( color_name, "MLV_COLOR_CORNSILK2" )==0 ){
		return MLV_COLOR_CORNSILK2;
	} 
	if( strcmp( color_name, "MLV_COLOR_CORNSILK3" )==0 ){
		return MLV_COLOR_CORNSILK3;
	} 
	if( strcmp( color_name, "MLV_COLOR_CORNSILK4" )==0 ){
		return MLV_COLOR_CORNSILK4;
	} 
	if( strcmp( color_name, "MLV_COLOR_IVORY1" )==0 ){
		return MLV_COLOR_IVORY1;
	} 
	if( strcmp( color_name, "MLV_COLOR_IVORY2" )==0 ){
		return MLV_COLOR_IVORY2;
	} 
	if( strcmp( color_name, "MLV_COLOR_IVORY3" )==0 ){
		return MLV_COLOR_IVORY3;
	} 
	if( strcmp( color_name, "MLV_COLOR_IVORY4" )==0 ){
		return MLV_COLOR_IVORY4;
	} 
	if( strcmp( color_name, "MLV_COLOR_HONEYDEW1" )==0 ){
		return MLV_COLOR_HONEYDEW1;
	} 
	if( strcmp( color_name, "MLV_COLOR_HONEYDEW2" )==0 ){
		return MLV_COLOR_HONEYDEW2;
	} 
	if( strcmp( color_name, "MLV_COLOR_HONEYDEW3" )==0 ){
		return MLV_COLOR_HONEYDEW3;
	} 
	if( strcmp( color_name, "MLV_COLOR_HONEYDEW4" )==0 ){
		return MLV_COLOR_HONEYDEW4;
	} 
	if( strcmp( color_name, "MLV_COLOR_LAVENDERBLUSH1" )==0 ){
		return MLV_COLOR_LAVENDERBLUSH1;
	} 
	if( strcmp( color_name, "MLV_COLOR_LAVENDERBLUSH2" )==0 ){
		return MLV_COLOR_LAVENDERBLUSH2;
	} 
	if( strcmp( color_name, "MLV_COLOR_LAVENDERBLUSH3" )==0 ){
		return MLV_COLOR_LAVENDERBLUSH3;
	} 
	if( strcmp( color_name, "MLV_COLOR_LAVENDERBLUSH4" )==0 ){
		return MLV_COLOR_LAVENDERBLUSH4;
	} 
	if( strcmp( color_name, "MLV_COLOR_MISTYROSE1" )==0 ){
		return MLV_COLOR_MISTYROSE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_MISTYROSE2" )==0 ){
		return MLV_COLOR_MISTYROSE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_MISTYROSE3" )==0 ){
		return MLV_COLOR_MISTYROSE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_MISTYROSE4" )==0 ){
		return MLV_COLOR_MISTYROSE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_AZURE1" )==0 ){
		return MLV_COLOR_AZURE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_AZURE2" )==0 ){
		return MLV_COLOR_AZURE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_AZURE3" )==0 ){
		return MLV_COLOR_AZURE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_AZURE4" )==0 ){
		return MLV_COLOR_AZURE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATEBLUE1" )==0 ){
		return MLV_COLOR_SLATEBLUE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATEBLUE2" )==0 ){
		return MLV_COLOR_SLATEBLUE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATEBLUE3" )==0 ){
		return MLV_COLOR_SLATEBLUE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATEBLUE4" )==0 ){
		return MLV_COLOR_SLATEBLUE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_ROYALBLUE1" )==0 ){
		return MLV_COLOR_ROYALBLUE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_ROYALBLUE2" )==0 ){
		return MLV_COLOR_ROYALBLUE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_ROYALBLUE3" )==0 ){
		return MLV_COLOR_ROYALBLUE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_ROYALBLUE4" )==0 ){
		return MLV_COLOR_ROYALBLUE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_BLUE1" )==0 ){
		return MLV_COLOR_BLUE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_BLUE2" )==0 ){
		return MLV_COLOR_BLUE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_BLUE3" )==0 ){
		return MLV_COLOR_BLUE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_BLUE4" )==0 ){
		return MLV_COLOR_BLUE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_DODGERBLUE1" )==0 ){
		return MLV_COLOR_DODGERBLUE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_DODGERBLUE2" )==0 ){
		return MLV_COLOR_DODGERBLUE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_DODGERBLUE3" )==0 ){
		return MLV_COLOR_DODGERBLUE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_DODGERBLUE4" )==0 ){
		return MLV_COLOR_DODGERBLUE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_STEELBLUE1" )==0 ){
		return MLV_COLOR_STEELBLUE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_STEELBLUE2" )==0 ){
		return MLV_COLOR_STEELBLUE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_STEELBLUE3" )==0 ){
		return MLV_COLOR_STEELBLUE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_STEELBLUE4" )==0 ){
		return MLV_COLOR_STEELBLUE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_DEEPSKYBLUE1" )==0 ){
		return MLV_COLOR_DEEPSKYBLUE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_DEEPSKYBLUE2" )==0 ){
		return MLV_COLOR_DEEPSKYBLUE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_DEEPSKYBLUE3" )==0 ){
		return MLV_COLOR_DEEPSKYBLUE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_DEEPSKYBLUE4" )==0 ){
		return MLV_COLOR_DEEPSKYBLUE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_SKYBLUE1" )==0 ){
		return MLV_COLOR_SKYBLUE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_SKYBLUE2" )==0 ){
		return MLV_COLOR_SKYBLUE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_SKYBLUE3" )==0 ){
		return MLV_COLOR_SKYBLUE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_SKYBLUE4" )==0 ){
		return MLV_COLOR_SKYBLUE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSKYBLUE1" )==0 ){
		return MLV_COLOR_LIGHTSKYBLUE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSKYBLUE2" )==0 ){
		return MLV_COLOR_LIGHTSKYBLUE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSKYBLUE3" )==0 ){
		return MLV_COLOR_LIGHTSKYBLUE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSKYBLUE4" )==0 ){
		return MLV_COLOR_LIGHTSKYBLUE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATEGRAY1" )==0 ){
		return MLV_COLOR_SLATEGRAY1;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATEGRAY2" )==0 ){
		return MLV_COLOR_SLATEGRAY2;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATEGRAY3" )==0 ){
		return MLV_COLOR_SLATEGRAY3;
	} 
	if( strcmp( color_name, "MLV_COLOR_SLATEGRAY4" )==0 ){
		return MLV_COLOR_SLATEGRAY4;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSTEELBLUE1" )==0 ){
		return MLV_COLOR_LIGHTSTEELBLUE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSTEELBLUE2" )==0 ){
		return MLV_COLOR_LIGHTSTEELBLUE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSTEELBLUE3" )==0 ){
		return MLV_COLOR_LIGHTSTEELBLUE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSTEELBLUE4" )==0 ){
		return MLV_COLOR_LIGHTSTEELBLUE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTBLUE1" )==0 ){
		return MLV_COLOR_LIGHTBLUE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTBLUE2" )==0 ){
		return MLV_COLOR_LIGHTBLUE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTBLUE3" )==0 ){
		return MLV_COLOR_LIGHTBLUE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTBLUE4" )==0 ){
		return MLV_COLOR_LIGHTBLUE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTCYAN1" )==0 ){
		return MLV_COLOR_LIGHTCYAN1;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTCYAN2" )==0 ){
		return MLV_COLOR_LIGHTCYAN2;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTCYAN3" )==0 ){
		return MLV_COLOR_LIGHTCYAN3;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTCYAN4" )==0 ){
		return MLV_COLOR_LIGHTCYAN4;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALETURQUOISE1" )==0 ){
		return MLV_COLOR_PALETURQUOISE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALETURQUOISE2" )==0 ){
		return MLV_COLOR_PALETURQUOISE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALETURQUOISE3" )==0 ){
		return MLV_COLOR_PALETURQUOISE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALETURQUOISE4" )==0 ){
		return MLV_COLOR_PALETURQUOISE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_CADETBLUE1" )==0 ){
		return MLV_COLOR_CADETBLUE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_CADETBLUE2" )==0 ){
		return MLV_COLOR_CADETBLUE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_CADETBLUE3" )==0 ){
		return MLV_COLOR_CADETBLUE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_CADETBLUE4" )==0 ){
		return MLV_COLOR_CADETBLUE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_TURQUOISE1" )==0 ){
		return MLV_COLOR_TURQUOISE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_TURQUOISE2" )==0 ){
		return MLV_COLOR_TURQUOISE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_TURQUOISE3" )==0 ){
		return MLV_COLOR_TURQUOISE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_TURQUOISE4" )==0 ){
		return MLV_COLOR_TURQUOISE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_CYAN1" )==0 ){
		return MLV_COLOR_CYAN1;
	} 
	if( strcmp( color_name, "MLV_COLOR_CYAN2" )==0 ){
		return MLV_COLOR_CYAN2;
	} 
	if( strcmp( color_name, "MLV_COLOR_CYAN3" )==0 ){
		return MLV_COLOR_CYAN3;
	} 
	if( strcmp( color_name, "MLV_COLOR_CYAN4" )==0 ){
		return MLV_COLOR_CYAN4;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSLATEGRAY1" )==0 ){
		return MLV_COLOR_DARKSLATEGRAY1;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSLATEGRAY2" )==0 ){
		return MLV_COLOR_DARKSLATEGRAY2;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSLATEGRAY3" )==0 ){
		return MLV_COLOR_DARKSLATEGRAY3;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSLATEGRAY4" )==0 ){
		return MLV_COLOR_DARKSLATEGRAY4;
	} 
	if( strcmp( color_name, "MLV_COLOR_AQUAMARINE1" )==0 ){
		return MLV_COLOR_AQUAMARINE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_AQUAMARINE2" )==0 ){
		return MLV_COLOR_AQUAMARINE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_AQUAMARINE3" )==0 ){
		return MLV_COLOR_AQUAMARINE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_AQUAMARINE4" )==0 ){
		return MLV_COLOR_AQUAMARINE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSEAGREEN1" )==0 ){
		return MLV_COLOR_DARKSEAGREEN1;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSEAGREEN2" )==0 ){
		return MLV_COLOR_DARKSEAGREEN2;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSEAGREEN3" )==0 ){
		return MLV_COLOR_DARKSEAGREEN3;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKSEAGREEN4" )==0 ){
		return MLV_COLOR_DARKSEAGREEN4;
	} 
	if( strcmp( color_name, "MLV_COLOR_SEAGREEN1" )==0 ){
		return MLV_COLOR_SEAGREEN1;
	} 
	if( strcmp( color_name, "MLV_COLOR_SEAGREEN2" )==0 ){
		return MLV_COLOR_SEAGREEN2;
	} 
	if( strcmp( color_name, "MLV_COLOR_SEAGREEN3" )==0 ){
		return MLV_COLOR_SEAGREEN3;
	} 
	if( strcmp( color_name, "MLV_COLOR_SEAGREEN4" )==0 ){
		return MLV_COLOR_SEAGREEN4;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALEGREEN1" )==0 ){
		return MLV_COLOR_PALEGREEN1;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALEGREEN2" )==0 ){
		return MLV_COLOR_PALEGREEN2;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALEGREEN3" )==0 ){
		return MLV_COLOR_PALEGREEN3;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALEGREEN4" )==0 ){
		return MLV_COLOR_PALEGREEN4;
	} 
	if( strcmp( color_name, "MLV_COLOR_SPRINGGREEN1" )==0 ){
		return MLV_COLOR_SPRINGGREEN1;
	} 
	if( strcmp( color_name, "MLV_COLOR_SPRINGGREEN2" )==0 ){
		return MLV_COLOR_SPRINGGREEN2;
	} 
	if( strcmp( color_name, "MLV_COLOR_SPRINGGREEN3" )==0 ){
		return MLV_COLOR_SPRINGGREEN3;
	} 
	if( strcmp( color_name, "MLV_COLOR_SPRINGGREEN4" )==0 ){
		return MLV_COLOR_SPRINGGREEN4;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREEN1" )==0 ){
		return MLV_COLOR_GREEN1;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREEN2" )==0 ){
		return MLV_COLOR_GREEN2;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREEN3" )==0 ){
		return MLV_COLOR_GREEN3;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREEN4" )==0 ){
		return MLV_COLOR_GREEN4;
	} 
	if( strcmp( color_name, "MLV_COLOR_CHARTREUSE1" )==0 ){
		return MLV_COLOR_CHARTREUSE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_CHARTREUSE2" )==0 ){
		return MLV_COLOR_CHARTREUSE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_CHARTREUSE3" )==0 ){
		return MLV_COLOR_CHARTREUSE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_CHARTREUSE4" )==0 ){
		return MLV_COLOR_CHARTREUSE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_OLIVEDRAB1" )==0 ){
		return MLV_COLOR_OLIVEDRAB1;
	} 
	if( strcmp( color_name, "MLV_COLOR_OLIVEDRAB2" )==0 ){
		return MLV_COLOR_OLIVEDRAB2;
	} 
	if( strcmp( color_name, "MLV_COLOR_OLIVEDRAB3" )==0 ){
		return MLV_COLOR_OLIVEDRAB3;
	} 
	if( strcmp( color_name, "MLV_COLOR_OLIVEDRAB4" )==0 ){
		return MLV_COLOR_OLIVEDRAB4;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKOLIVEGREEN1" )==0 ){
		return MLV_COLOR_DARKOLIVEGREEN1;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKOLIVEGREEN2" )==0 ){
		return MLV_COLOR_DARKOLIVEGREEN2;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKOLIVEGREEN3" )==0 ){
		return MLV_COLOR_DARKOLIVEGREEN3;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKOLIVEGREEN4" )==0 ){
		return MLV_COLOR_DARKOLIVEGREEN4;
	} 
	if( strcmp( color_name, "MLV_COLOR_KHAKI1" )==0 ){
		return MLV_COLOR_KHAKI1;
	} 
	if( strcmp( color_name, "MLV_COLOR_KHAKI2" )==0 ){
		return MLV_COLOR_KHAKI2;
	} 
	if( strcmp( color_name, "MLV_COLOR_KHAKI3" )==0 ){
		return MLV_COLOR_KHAKI3;
	} 
	if( strcmp( color_name, "MLV_COLOR_KHAKI4" )==0 ){
		return MLV_COLOR_KHAKI4;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTGOLDENROD1" )==0 ){
		return MLV_COLOR_LIGHTGOLDENROD1;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTGOLDENROD2" )==0 ){
		return MLV_COLOR_LIGHTGOLDENROD2;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTGOLDENROD3" )==0 ){
		return MLV_COLOR_LIGHTGOLDENROD3;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTGOLDENROD4" )==0 ){
		return MLV_COLOR_LIGHTGOLDENROD4;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTYELLOW1" )==0 ){
		return MLV_COLOR_LIGHTYELLOW1;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTYELLOW2" )==0 ){
		return MLV_COLOR_LIGHTYELLOW2;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTYELLOW3" )==0 ){
		return MLV_COLOR_LIGHTYELLOW3;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTYELLOW4" )==0 ){
		return MLV_COLOR_LIGHTYELLOW4;
	} 
	if( strcmp( color_name, "MLV_COLOR_YELLOW1" )==0 ){
		return MLV_COLOR_YELLOW1;
	} 
	if( strcmp( color_name, "MLV_COLOR_YELLOW2" )==0 ){
		return MLV_COLOR_YELLOW2;
	} 
	if( strcmp( color_name, "MLV_COLOR_YELLOW3" )==0 ){
		return MLV_COLOR_YELLOW3;
	} 
	if( strcmp( color_name, "MLV_COLOR_YELLOW4" )==0 ){
		return MLV_COLOR_YELLOW4;
	} 
	if( strcmp( color_name, "MLV_COLOR_GOLD1" )==0 ){
		return MLV_COLOR_GOLD1;
	} 
	if( strcmp( color_name, "MLV_COLOR_GOLD2" )==0 ){
		return MLV_COLOR_GOLD2;
	} 
	if( strcmp( color_name, "MLV_COLOR_GOLD3" )==0 ){
		return MLV_COLOR_GOLD3;
	} 
	if( strcmp( color_name, "MLV_COLOR_GOLD4" )==0 ){
		return MLV_COLOR_GOLD4;
	} 
	if( strcmp( color_name, "MLV_COLOR_GOLDENROD1" )==0 ){
		return MLV_COLOR_GOLDENROD1;
	} 
	if( strcmp( color_name, "MLV_COLOR_GOLDENROD2" )==0 ){
		return MLV_COLOR_GOLDENROD2;
	} 
	if( strcmp( color_name, "MLV_COLOR_GOLDENROD3" )==0 ){
		return MLV_COLOR_GOLDENROD3;
	} 
	if( strcmp( color_name, "MLV_COLOR_GOLDENROD4" )==0 ){
		return MLV_COLOR_GOLDENROD4;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKGOLDENROD1" )==0 ){
		return MLV_COLOR_DARKGOLDENROD1;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKGOLDENROD2" )==0 ){
		return MLV_COLOR_DARKGOLDENROD2;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKGOLDENROD3" )==0 ){
		return MLV_COLOR_DARKGOLDENROD3;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKGOLDENROD4" )==0 ){
		return MLV_COLOR_DARKGOLDENROD4;
	} 
	if( strcmp( color_name, "MLV_COLOR_ROSYBROWN1" )==0 ){
		return MLV_COLOR_ROSYBROWN1;
	} 
	if( strcmp( color_name, "MLV_COLOR_ROSYBROWN2" )==0 ){
		return MLV_COLOR_ROSYBROWN2;
	} 
	if( strcmp( color_name, "MLV_COLOR_ROSYBROWN3" )==0 ){
		return MLV_COLOR_ROSYBROWN3;
	} 
	if( strcmp( color_name, "MLV_COLOR_ROSYBROWN4" )==0 ){
		return MLV_COLOR_ROSYBROWN4;
	} 
	if( strcmp( color_name, "MLV_COLOR_INDIANRED1" )==0 ){
		return MLV_COLOR_INDIANRED1;
	} 
	if( strcmp( color_name, "MLV_COLOR_INDIANRED2" )==0 ){
		return MLV_COLOR_INDIANRED2;
	} 
	if( strcmp( color_name, "MLV_COLOR_INDIANRED3" )==0 ){
		return MLV_COLOR_INDIANRED3;
	} 
	if( strcmp( color_name, "MLV_COLOR_INDIANRED4" )==0 ){
		return MLV_COLOR_INDIANRED4;
	} 
	if( strcmp( color_name, "MLV_COLOR_SIENNA1" )==0 ){
		return MLV_COLOR_SIENNA1;
	} 
	if( strcmp( color_name, "MLV_COLOR_SIENNA2" )==0 ){
		return MLV_COLOR_SIENNA2;
	} 
	if( strcmp( color_name, "MLV_COLOR_SIENNA3" )==0 ){
		return MLV_COLOR_SIENNA3;
	} 
	if( strcmp( color_name, "MLV_COLOR_SIENNA4" )==0 ){
		return MLV_COLOR_SIENNA4;
	} 
	if( strcmp( color_name, "MLV_COLOR_BURLYWOOD1" )==0 ){
		return MLV_COLOR_BURLYWOOD1;
	} 
	if( strcmp( color_name, "MLV_COLOR_BURLYWOOD2" )==0 ){
		return MLV_COLOR_BURLYWOOD2;
	} 
	if( strcmp( color_name, "MLV_COLOR_BURLYWOOD3" )==0 ){
		return MLV_COLOR_BURLYWOOD3;
	} 
	if( strcmp( color_name, "MLV_COLOR_BURLYWOOD4" )==0 ){
		return MLV_COLOR_BURLYWOOD4;
	} 
	if( strcmp( color_name, "MLV_COLOR_WHEAT1" )==0 ){
		return MLV_COLOR_WHEAT1;
	} 
	if( strcmp( color_name, "MLV_COLOR_WHEAT2" )==0 ){
		return MLV_COLOR_WHEAT2;
	} 
	if( strcmp( color_name, "MLV_COLOR_WHEAT3" )==0 ){
		return MLV_COLOR_WHEAT3;
	} 
	if( strcmp( color_name, "MLV_COLOR_WHEAT4" )==0 ){
		return MLV_COLOR_WHEAT4;
	} 
	if( strcmp( color_name, "MLV_COLOR_TAN1" )==0 ){
		return MLV_COLOR_TAN1;
	} 
	if( strcmp( color_name, "MLV_COLOR_TAN2" )==0 ){
		return MLV_COLOR_TAN2;
	} 
	if( strcmp( color_name, "MLV_COLOR_TAN3" )==0 ){
		return MLV_COLOR_TAN3;
	} 
	if( strcmp( color_name, "MLV_COLOR_TAN4" )==0 ){
		return MLV_COLOR_TAN4;
	} 
	if( strcmp( color_name, "MLV_COLOR_CHOCOLATE1" )==0 ){
		return MLV_COLOR_CHOCOLATE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_CHOCOLATE2" )==0 ){
		return MLV_COLOR_CHOCOLATE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_CHOCOLATE3" )==0 ){
		return MLV_COLOR_CHOCOLATE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_CHOCOLATE4" )==0 ){
		return MLV_COLOR_CHOCOLATE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_FIREBRICK1" )==0 ){
		return MLV_COLOR_FIREBRICK1;
	} 
	if( strcmp( color_name, "MLV_COLOR_FIREBRICK2" )==0 ){
		return MLV_COLOR_FIREBRICK2;
	} 
	if( strcmp( color_name, "MLV_COLOR_FIREBRICK3" )==0 ){
		return MLV_COLOR_FIREBRICK3;
	} 
	if( strcmp( color_name, "MLV_COLOR_FIREBRICK4" )==0 ){
		return MLV_COLOR_FIREBRICK4;
	} 
	if( strcmp( color_name, "MLV_COLOR_BROWN1" )==0 ){
		return MLV_COLOR_BROWN1;
	} 
	if( strcmp( color_name, "MLV_COLOR_BROWN2" )==0 ){
		return MLV_COLOR_BROWN2;
	} 
	if( strcmp( color_name, "MLV_COLOR_BROWN3" )==0 ){
		return MLV_COLOR_BROWN3;
	} 
	if( strcmp( color_name, "MLV_COLOR_BROWN4" )==0 ){
		return MLV_COLOR_BROWN4;
	} 
	if( strcmp( color_name, "MLV_COLOR_SALMON1" )==0 ){
		return MLV_COLOR_SALMON1;
	} 
	if( strcmp( color_name, "MLV_COLOR_SALMON2" )==0 ){
		return MLV_COLOR_SALMON2;
	} 
	if( strcmp( color_name, "MLV_COLOR_SALMON3" )==0 ){
		return MLV_COLOR_SALMON3;
	} 
	if( strcmp( color_name, "MLV_COLOR_SALMON4" )==0 ){
		return MLV_COLOR_SALMON4;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSALMON1" )==0 ){
		return MLV_COLOR_LIGHTSALMON1;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSALMON2" )==0 ){
		return MLV_COLOR_LIGHTSALMON2;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSALMON3" )==0 ){
		return MLV_COLOR_LIGHTSALMON3;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTSALMON4" )==0 ){
		return MLV_COLOR_LIGHTSALMON4;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORANGE1" )==0 ){
		return MLV_COLOR_ORANGE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORANGE2" )==0 ){
		return MLV_COLOR_ORANGE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORANGE3" )==0 ){
		return MLV_COLOR_ORANGE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORANGE4" )==0 ){
		return MLV_COLOR_ORANGE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKORANGE1" )==0 ){
		return MLV_COLOR_DARKORANGE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKORANGE2" )==0 ){
		return MLV_COLOR_DARKORANGE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKORANGE3" )==0 ){
		return MLV_COLOR_DARKORANGE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKORANGE4" )==0 ){
		return MLV_COLOR_DARKORANGE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_CORAL1" )==0 ){
		return MLV_COLOR_CORAL1;
	} 
	if( strcmp( color_name, "MLV_COLOR_CORAL2" )==0 ){
		return MLV_COLOR_CORAL2;
	} 
	if( strcmp( color_name, "MLV_COLOR_CORAL3" )==0 ){
		return MLV_COLOR_CORAL3;
	} 
	if( strcmp( color_name, "MLV_COLOR_CORAL4" )==0 ){
		return MLV_COLOR_CORAL4;
	} 
	if( strcmp( color_name, "MLV_COLOR_TOMATO1" )==0 ){
		return MLV_COLOR_TOMATO1;
	} 
	if( strcmp( color_name, "MLV_COLOR_TOMATO2" )==0 ){
		return MLV_COLOR_TOMATO2;
	} 
	if( strcmp( color_name, "MLV_COLOR_TOMATO3" )==0 ){
		return MLV_COLOR_TOMATO3;
	} 
	if( strcmp( color_name, "MLV_COLOR_TOMATO4" )==0 ){
		return MLV_COLOR_TOMATO4;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORANGERED1" )==0 ){
		return MLV_COLOR_ORANGERED1;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORANGERED2" )==0 ){
		return MLV_COLOR_ORANGERED2;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORANGERED3" )==0 ){
		return MLV_COLOR_ORANGERED3;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORANGERED4" )==0 ){
		return MLV_COLOR_ORANGERED4;
	} 
	if( strcmp( color_name, "MLV_COLOR_RED1" )==0 ){
		return MLV_COLOR_RED1;
	} 
	if( strcmp( color_name, "MLV_COLOR_RED2" )==0 ){
		return MLV_COLOR_RED2;
	} 
	if( strcmp( color_name, "MLV_COLOR_RED3" )==0 ){
		return MLV_COLOR_RED3;
	} 
	if( strcmp( color_name, "MLV_COLOR_RED4" )==0 ){
		return MLV_COLOR_RED4;
	} 
	if( strcmp( color_name, "MLV_COLOR_DEEPPINK1" )==0 ){
		return MLV_COLOR_DEEPPINK1;
	} 
	if( strcmp( color_name, "MLV_COLOR_DEEPPINK2" )==0 ){
		return MLV_COLOR_DEEPPINK2;
	} 
	if( strcmp( color_name, "MLV_COLOR_DEEPPINK3" )==0 ){
		return MLV_COLOR_DEEPPINK3;
	} 
	if( strcmp( color_name, "MLV_COLOR_DEEPPINK4" )==0 ){
		return MLV_COLOR_DEEPPINK4;
	} 
	if( strcmp( color_name, "MLV_COLOR_HOTPINK1" )==0 ){
		return MLV_COLOR_HOTPINK1;
	} 
	if( strcmp( color_name, "MLV_COLOR_HOTPINK2" )==0 ){
		return MLV_COLOR_HOTPINK2;
	} 
	if( strcmp( color_name, "MLV_COLOR_HOTPINK3" )==0 ){
		return MLV_COLOR_HOTPINK3;
	} 
	if( strcmp( color_name, "MLV_COLOR_HOTPINK4" )==0 ){
		return MLV_COLOR_HOTPINK4;
	} 
	if( strcmp( color_name, "MLV_COLOR_PINK1" )==0 ){
		return MLV_COLOR_PINK1;
	} 
	if( strcmp( color_name, "MLV_COLOR_PINK2" )==0 ){
		return MLV_COLOR_PINK2;
	} 
	if( strcmp( color_name, "MLV_COLOR_PINK3" )==0 ){
		return MLV_COLOR_PINK3;
	} 
	if( strcmp( color_name, "MLV_COLOR_PINK4" )==0 ){
		return MLV_COLOR_PINK4;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTPINK1" )==0 ){
		return MLV_COLOR_LIGHTPINK1;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTPINK2" )==0 ){
		return MLV_COLOR_LIGHTPINK2;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTPINK3" )==0 ){
		return MLV_COLOR_LIGHTPINK3;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTPINK4" )==0 ){
		return MLV_COLOR_LIGHTPINK4;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALEVIOLETRED1" )==0 ){
		return MLV_COLOR_PALEVIOLETRED1;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALEVIOLETRED2" )==0 ){
		return MLV_COLOR_PALEVIOLETRED2;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALEVIOLETRED3" )==0 ){
		return MLV_COLOR_PALEVIOLETRED3;
	} 
	if( strcmp( color_name, "MLV_COLOR_PALEVIOLETRED4" )==0 ){
		return MLV_COLOR_PALEVIOLETRED4;
	} 
	if( strcmp( color_name, "MLV_COLOR_MAROON1" )==0 ){
		return MLV_COLOR_MAROON1;
	} 
	if( strcmp( color_name, "MLV_COLOR_MAROON2" )==0 ){
		return MLV_COLOR_MAROON2;
	} 
	if( strcmp( color_name, "MLV_COLOR_MAROON3" )==0 ){
		return MLV_COLOR_MAROON3;
	} 
	if( strcmp( color_name, "MLV_COLOR_MAROON4" )==0 ){
		return MLV_COLOR_MAROON4;
	} 
	if( strcmp( color_name, "MLV_COLOR_VIOLETRED1" )==0 ){
		return MLV_COLOR_VIOLETRED1;
	} 
	if( strcmp( color_name, "MLV_COLOR_VIOLETRED2" )==0 ){
		return MLV_COLOR_VIOLETRED2;
	} 
	if( strcmp( color_name, "MLV_COLOR_VIOLETRED3" )==0 ){
		return MLV_COLOR_VIOLETRED3;
	} 
	if( strcmp( color_name, "MLV_COLOR_VIOLETRED4" )==0 ){
		return MLV_COLOR_VIOLETRED4;
	} 
	if( strcmp( color_name, "MLV_COLOR_MAGENTA1" )==0 ){
		return MLV_COLOR_MAGENTA1;
	} 
	if( strcmp( color_name, "MLV_COLOR_MAGENTA2" )==0 ){
		return MLV_COLOR_MAGENTA2;
	} 
	if( strcmp( color_name, "MLV_COLOR_MAGENTA3" )==0 ){
		return MLV_COLOR_MAGENTA3;
	} 
	if( strcmp( color_name, "MLV_COLOR_MAGENTA4" )==0 ){
		return MLV_COLOR_MAGENTA4;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORCHID1" )==0 ){
		return MLV_COLOR_ORCHID1;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORCHID2" )==0 ){
		return MLV_COLOR_ORCHID2;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORCHID3" )==0 ){
		return MLV_COLOR_ORCHID3;
	} 
	if( strcmp( color_name, "MLV_COLOR_ORCHID4" )==0 ){
		return MLV_COLOR_ORCHID4;
	} 
	if( strcmp( color_name, "MLV_COLOR_PLUM1" )==0 ){
		return MLV_COLOR_PLUM1;
	} 
	if( strcmp( color_name, "MLV_COLOR_PLUM2" )==0 ){
		return MLV_COLOR_PLUM2;
	} 
	if( strcmp( color_name, "MLV_COLOR_PLUM3" )==0 ){
		return MLV_COLOR_PLUM3;
	} 
	if( strcmp( color_name, "MLV_COLOR_PLUM4" )==0 ){
		return MLV_COLOR_PLUM4;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMORCHID1" )==0 ){
		return MLV_COLOR_MEDIUMORCHID1;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMORCHID2" )==0 ){
		return MLV_COLOR_MEDIUMORCHID2;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMORCHID3" )==0 ){
		return MLV_COLOR_MEDIUMORCHID3;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMORCHID4" )==0 ){
		return MLV_COLOR_MEDIUMORCHID4;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKORCHID1" )==0 ){
		return MLV_COLOR_DARKORCHID1;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKORCHID2" )==0 ){
		return MLV_COLOR_DARKORCHID2;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKORCHID3" )==0 ){
		return MLV_COLOR_DARKORCHID3;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKORCHID4" )==0 ){
		return MLV_COLOR_DARKORCHID4;
	} 
	if( strcmp( color_name, "MLV_COLOR_PURPLE1" )==0 ){
		return MLV_COLOR_PURPLE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_PURPLE2" )==0 ){
		return MLV_COLOR_PURPLE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_PURPLE3" )==0 ){
		return MLV_COLOR_PURPLE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_PURPLE4" )==0 ){
		return MLV_COLOR_PURPLE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMPURPLE1" )==0 ){
		return MLV_COLOR_MEDIUMPURPLE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMPURPLE2" )==0 ){
		return MLV_COLOR_MEDIUMPURPLE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMPURPLE3" )==0 ){
		return MLV_COLOR_MEDIUMPURPLE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_MEDIUMPURPLE4" )==0 ){
		return MLV_COLOR_MEDIUMPURPLE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_THISTLE1" )==0 ){
		return MLV_COLOR_THISTLE1;
	} 
	if( strcmp( color_name, "MLV_COLOR_THISTLE2" )==0 ){
		return MLV_COLOR_THISTLE2;
	} 
	if( strcmp( color_name, "MLV_COLOR_THISTLE3" )==0 ){
		return MLV_COLOR_THISTLE3;
	} 
	if( strcmp( color_name, "MLV_COLOR_THISTLE4" )==0 ){
		return MLV_COLOR_THISTLE4;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY0" )==0 ){
		return MLV_COLOR_GRAY0;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY0" )==0 ){
		return MLV_COLOR_GREY0;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY1" )==0 ){
		return MLV_COLOR_GRAY1;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY1" )==0 ){
		return MLV_COLOR_GREY1;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY2" )==0 ){
		return MLV_COLOR_GRAY2;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY2" )==0 ){
		return MLV_COLOR_GREY2;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY3" )==0 ){
		return MLV_COLOR_GRAY3;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY3" )==0 ){
		return MLV_COLOR_GREY3;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY4" )==0 ){
		return MLV_COLOR_GRAY4;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY4" )==0 ){
		return MLV_COLOR_GREY4;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY5" )==0 ){
		return MLV_COLOR_GRAY5;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY5" )==0 ){
		return MLV_COLOR_GREY5;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY6" )==0 ){
		return MLV_COLOR_GRAY6;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY6" )==0 ){
		return MLV_COLOR_GREY6;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY7" )==0 ){
		return MLV_COLOR_GRAY7;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY7" )==0 ){
		return MLV_COLOR_GREY7;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY8" )==0 ){
		return MLV_COLOR_GRAY8;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY8" )==0 ){
		return MLV_COLOR_GREY8;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY9" )==0 ){
		return MLV_COLOR_GRAY9;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY9" )==0 ){
		return MLV_COLOR_GREY9;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY10" )==0 ){
		return MLV_COLOR_GRAY10;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY10" )==0 ){
		return MLV_COLOR_GREY10;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY11" )==0 ){
		return MLV_COLOR_GRAY11;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY11" )==0 ){
		return MLV_COLOR_GREY11;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY12" )==0 ){
		return MLV_COLOR_GRAY12;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY12" )==0 ){
		return MLV_COLOR_GREY12;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY13" )==0 ){
		return MLV_COLOR_GRAY13;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY13" )==0 ){
		return MLV_COLOR_GREY13;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY14" )==0 ){
		return MLV_COLOR_GRAY14;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY14" )==0 ){
		return MLV_COLOR_GREY14;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY15" )==0 ){
		return MLV_COLOR_GRAY15;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY15" )==0 ){
		return MLV_COLOR_GREY15;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY16" )==0 ){
		return MLV_COLOR_GRAY16;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY16" )==0 ){
		return MLV_COLOR_GREY16;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY17" )==0 ){
		return MLV_COLOR_GRAY17;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY17" )==0 ){
		return MLV_COLOR_GREY17;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY18" )==0 ){
		return MLV_COLOR_GRAY18;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY18" )==0 ){
		return MLV_COLOR_GREY18;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY19" )==0 ){
		return MLV_COLOR_GRAY19;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY19" )==0 ){
		return MLV_COLOR_GREY19;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY20" )==0 ){
		return MLV_COLOR_GRAY20;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY20" )==0 ){
		return MLV_COLOR_GREY20;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY21" )==0 ){
		return MLV_COLOR_GRAY21;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY21" )==0 ){
		return MLV_COLOR_GREY21;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY22" )==0 ){
		return MLV_COLOR_GRAY22;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY22" )==0 ){
		return MLV_COLOR_GREY22;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY23" )==0 ){
		return MLV_COLOR_GRAY23;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY23" )==0 ){
		return MLV_COLOR_GREY23;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY24" )==0 ){
		return MLV_COLOR_GRAY24;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY24" )==0 ){
		return MLV_COLOR_GREY24;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY25" )==0 ){
		return MLV_COLOR_GRAY25;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY25" )==0 ){
		return MLV_COLOR_GREY25;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY26" )==0 ){
		return MLV_COLOR_GRAY26;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY26" )==0 ){
		return MLV_COLOR_GREY26;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY27" )==0 ){
		return MLV_COLOR_GRAY27;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY27" )==0 ){
		return MLV_COLOR_GREY27;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY28" )==0 ){
		return MLV_COLOR_GRAY28;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY28" )==0 ){
		return MLV_COLOR_GREY28;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY29" )==0 ){
		return MLV_COLOR_GRAY29;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY29" )==0 ){
		return MLV_COLOR_GREY29;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY30" )==0 ){
		return MLV_COLOR_GRAY30;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY30" )==0 ){
		return MLV_COLOR_GREY30;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY31" )==0 ){
		return MLV_COLOR_GRAY31;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY31" )==0 ){
		return MLV_COLOR_GREY31;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY32" )==0 ){
		return MLV_COLOR_GRAY32;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY32" )==0 ){
		return MLV_COLOR_GREY32;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY33" )==0 ){
		return MLV_COLOR_GRAY33;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY33" )==0 ){
		return MLV_COLOR_GREY33;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY34" )==0 ){
		return MLV_COLOR_GRAY34;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY34" )==0 ){
		return MLV_COLOR_GREY34;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY35" )==0 ){
		return MLV_COLOR_GRAY35;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY35" )==0 ){
		return MLV_COLOR_GREY35;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY36" )==0 ){
		return MLV_COLOR_GRAY36;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY36" )==0 ){
		return MLV_COLOR_GREY36;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY37" )==0 ){
		return MLV_COLOR_GRAY37;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY37" )==0 ){
		return MLV_COLOR_GREY37;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY38" )==0 ){
		return MLV_COLOR_GRAY38;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY38" )==0 ){
		return MLV_COLOR_GREY38;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY39" )==0 ){
		return MLV_COLOR_GRAY39;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY39" )==0 ){
		return MLV_COLOR_GREY39;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY40" )==0 ){
		return MLV_COLOR_GRAY40;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY40" )==0 ){
		return MLV_COLOR_GREY40;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY41" )==0 ){
		return MLV_COLOR_GRAY41;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY41" )==0 ){
		return MLV_COLOR_GREY41;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY42" )==0 ){
		return MLV_COLOR_GRAY42;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY42" )==0 ){
		return MLV_COLOR_GREY42;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY43" )==0 ){
		return MLV_COLOR_GRAY43;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY43" )==0 ){
		return MLV_COLOR_GREY43;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY44" )==0 ){
		return MLV_COLOR_GRAY44;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY44" )==0 ){
		return MLV_COLOR_GREY44;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY45" )==0 ){
		return MLV_COLOR_GRAY45;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY45" )==0 ){
		return MLV_COLOR_GREY45;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY46" )==0 ){
		return MLV_COLOR_GRAY46;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY46" )==0 ){
		return MLV_COLOR_GREY46;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY47" )==0 ){
		return MLV_COLOR_GRAY47;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY47" )==0 ){
		return MLV_COLOR_GREY47;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY48" )==0 ){
		return MLV_COLOR_GRAY48;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY48" )==0 ){
		return MLV_COLOR_GREY48;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY49" )==0 ){
		return MLV_COLOR_GRAY49;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY49" )==0 ){
		return MLV_COLOR_GREY49;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY50" )==0 ){
		return MLV_COLOR_GRAY50;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY50" )==0 ){
		return MLV_COLOR_GREY50;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY51" )==0 ){
		return MLV_COLOR_GRAY51;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY51" )==0 ){
		return MLV_COLOR_GREY51;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY52" )==0 ){
		return MLV_COLOR_GRAY52;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY52" )==0 ){
		return MLV_COLOR_GREY52;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY53" )==0 ){
		return MLV_COLOR_GRAY53;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY53" )==0 ){
		return MLV_COLOR_GREY53;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY54" )==0 ){
		return MLV_COLOR_GRAY54;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY54" )==0 ){
		return MLV_COLOR_GREY54;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY55" )==0 ){
		return MLV_COLOR_GRAY55;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY55" )==0 ){
		return MLV_COLOR_GREY55;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY56" )==0 ){
		return MLV_COLOR_GRAY56;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY56" )==0 ){
		return MLV_COLOR_GREY56;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY57" )==0 ){
		return MLV_COLOR_GRAY57;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY57" )==0 ){
		return MLV_COLOR_GREY57;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY58" )==0 ){
		return MLV_COLOR_GRAY58;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY58" )==0 ){
		return MLV_COLOR_GREY58;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY59" )==0 ){
		return MLV_COLOR_GRAY59;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY59" )==0 ){
		return MLV_COLOR_GREY59;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY60" )==0 ){
		return MLV_COLOR_GRAY60;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY60" )==0 ){
		return MLV_COLOR_GREY60;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY61" )==0 ){
		return MLV_COLOR_GRAY61;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY61" )==0 ){
		return MLV_COLOR_GREY61;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY62" )==0 ){
		return MLV_COLOR_GRAY62;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY62" )==0 ){
		return MLV_COLOR_GREY62;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY63" )==0 ){
		return MLV_COLOR_GRAY63;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY63" )==0 ){
		return MLV_COLOR_GREY63;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY64" )==0 ){
		return MLV_COLOR_GRAY64;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY64" )==0 ){
		return MLV_COLOR_GREY64;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY65" )==0 ){
		return MLV_COLOR_GRAY65;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY65" )==0 ){
		return MLV_COLOR_GREY65;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY66" )==0 ){
		return MLV_COLOR_GRAY66;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY66" )==0 ){
		return MLV_COLOR_GREY66;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY67" )==0 ){
		return MLV_COLOR_GRAY67;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY67" )==0 ){
		return MLV_COLOR_GREY67;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY68" )==0 ){
		return MLV_COLOR_GRAY68;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY68" )==0 ){
		return MLV_COLOR_GREY68;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY69" )==0 ){
		return MLV_COLOR_GRAY69;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY69" )==0 ){
		return MLV_COLOR_GREY69;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY70" )==0 ){
		return MLV_COLOR_GRAY70;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY70" )==0 ){
		return MLV_COLOR_GREY70;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY71" )==0 ){
		return MLV_COLOR_GRAY71;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY71" )==0 ){
		return MLV_COLOR_GREY71;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY72" )==0 ){
		return MLV_COLOR_GRAY72;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY72" )==0 ){
		return MLV_COLOR_GREY72;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY73" )==0 ){
		return MLV_COLOR_GRAY73;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY73" )==0 ){
		return MLV_COLOR_GREY73;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY74" )==0 ){
		return MLV_COLOR_GRAY74;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY74" )==0 ){
		return MLV_COLOR_GREY74;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY75" )==0 ){
		return MLV_COLOR_GRAY75;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY75" )==0 ){
		return MLV_COLOR_GREY75;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY76" )==0 ){
		return MLV_COLOR_GRAY76;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY76" )==0 ){
		return MLV_COLOR_GREY76;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY77" )==0 ){
		return MLV_COLOR_GRAY77;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY77" )==0 ){
		return MLV_COLOR_GREY77;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY78" )==0 ){
		return MLV_COLOR_GRAY78;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY78" )==0 ){
		return MLV_COLOR_GREY78;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY79" )==0 ){
		return MLV_COLOR_GRAY79;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY79" )==0 ){
		return MLV_COLOR_GREY79;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY80" )==0 ){
		return MLV_COLOR_GRAY80;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY80" )==0 ){
		return MLV_COLOR_GREY80;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY81" )==0 ){
		return MLV_COLOR_GRAY81;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY81" )==0 ){
		return MLV_COLOR_GREY81;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY82" )==0 ){
		return MLV_COLOR_GRAY82;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY82" )==0 ){
		return MLV_COLOR_GREY82;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY83" )==0 ){
		return MLV_COLOR_GRAY83;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY83" )==0 ){
		return MLV_COLOR_GREY83;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY84" )==0 ){
		return MLV_COLOR_GRAY84;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY84" )==0 ){
		return MLV_COLOR_GREY84;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY85" )==0 ){
		return MLV_COLOR_GRAY85;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY85" )==0 ){
		return MLV_COLOR_GREY85;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY86" )==0 ){
		return MLV_COLOR_GRAY86;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY86" )==0 ){
		return MLV_COLOR_GREY86;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY87" )==0 ){
		return MLV_COLOR_GRAY87;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY87" )==0 ){
		return MLV_COLOR_GREY87;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY88" )==0 ){
		return MLV_COLOR_GRAY88;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY88" )==0 ){
		return MLV_COLOR_GREY88;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY89" )==0 ){
		return MLV_COLOR_GRAY89;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY89" )==0 ){
		return MLV_COLOR_GREY89;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY90" )==0 ){
		return MLV_COLOR_GRAY90;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY90" )==0 ){
		return MLV_COLOR_GREY90;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY91" )==0 ){
		return MLV_COLOR_GRAY91;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY91" )==0 ){
		return MLV_COLOR_GREY91;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY92" )==0 ){
		return MLV_COLOR_GRAY92;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY92" )==0 ){
		return MLV_COLOR_GREY92;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY93" )==0 ){
		return MLV_COLOR_GRAY93;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY93" )==0 ){
		return MLV_COLOR_GREY93;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY94" )==0 ){
		return MLV_COLOR_GRAY94;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY94" )==0 ){
		return MLV_COLOR_GREY94;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY95" )==0 ){
		return MLV_COLOR_GRAY95;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY95" )==0 ){
		return MLV_COLOR_GREY95;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY96" )==0 ){
		return MLV_COLOR_GRAY96;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY96" )==0 ){
		return MLV_COLOR_GREY96;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY97" )==0 ){
		return MLV_COLOR_GRAY97;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY97" )==0 ){
		return MLV_COLOR_GREY97;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY98" )==0 ){
		return MLV_COLOR_GRAY98;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY98" )==0 ){
		return MLV_COLOR_GREY98;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY99" )==0 ){
		return MLV_COLOR_GRAY99;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY99" )==0 ){
		return MLV_COLOR_GREY99;
	} 
	if( strcmp( color_name, "MLV_COLOR_GRAY100" )==0 ){
		return MLV_COLOR_GRAY100;
	} 
	if( strcmp( color_name, "MLV_COLOR_GREY100" )==0 ){
		return MLV_COLOR_GREY100;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_GREY" )==0 ){
		return MLV_COLOR_DARK_GREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKGREY" )==0 ){
		return MLV_COLOR_DARKGREY;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_GRAY" )==0 ){
		return MLV_COLOR_DARK_GRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKGRAY" )==0 ){
		return MLV_COLOR_DARKGRAY;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_BLUE" )==0 ){
		return MLV_COLOR_DARK_BLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKBLUE" )==0 ){
		return MLV_COLOR_DARKBLUE;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_CYAN" )==0 ){
		return MLV_COLOR_DARK_CYAN;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKCYAN" )==0 ){
		return MLV_COLOR_DARKCYAN;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_MAGENTA" )==0 ){
		return MLV_COLOR_DARK_MAGENTA;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKMAGENTA" )==0 ){
		return MLV_COLOR_DARKMAGENTA;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARK_RED" )==0 ){
		return MLV_COLOR_DARK_RED;
	} 
	if( strcmp( color_name, "MLV_COLOR_DARKRED" )==0 ){
		return MLV_COLOR_DARKRED;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHT_GREEN" )==0 ){
		return MLV_COLOR_LIGHT_GREEN;
	} 
	if( strcmp( color_name, "MLV_COLOR_LIGHTGREEN" )==0 ){
		return MLV_COLOR_LIGHTGREEN;
	}
	ERROR("Unexpected color name.");
	return -1;
}

