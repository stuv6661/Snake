/*
 *   This file is part of the MLV Library.
 *
 *   Copyright (C) 2010,2011,2012 Adrien Boussicault, Marc Zipstein
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

#include "sdlkeyboardtochar.h"

#include "memory_management.h"

int sldKeyIsACharacter( SDLKey key){
    int result = 1;

    switch( key ) {
        case SDLK_TAB :  result = 1; break;
        case SDLK_SPACE :  result = 1; break;
        case SDLK_EXCLAIM :  result = 1; break;
        case SDLK_QUOTEDBL :  result = 1; break;
        case SDLK_HASH :  result = 1; break;
        case SDLK_DOLLAR :  result = 1; break;
        case SDLK_AMPERSAND :  result = 1; break;
        case SDLK_QUOTE :  result = 1; break;
        case SDLK_LEFTPAREN :  result = 1; break;
        case SDLK_RIGHTPAREN :  result = 1; break;
        case SDLK_ASTERISK :  result = 1; break;
        case SDLK_PLUS :  result = 1; break;
        case SDLK_COMMA :  result = 1; break;
        case SDLK_MINUS :  result = 1; break;
        case SDLK_PERIOD :  result = 1; break;
        case SDLK_SLASH :  result = 1; break;
        case SDLK_0 :  result = 1; break;
        case SDLK_1 :  result = 1; break;
        case SDLK_2 :  result = 1; break;
        case SDLK_3 :  result = 1; break;
        case SDLK_4 :  result = 1; break;
        case SDLK_5 :  result = 1; break;
        case SDLK_6 :  result = 1; break;
        case SDLK_7 :  result = 1; break;
        case SDLK_8 :  result = 1; break;
        case SDLK_9 :  result = 1; break;
        case SDLK_COLON :  result = 1; break;
        case SDLK_SEMICOLON :  result = 1; break;
        case SDLK_LESS :  result = 1; break;
        case SDLK_EQUALS :  result = 1; break;
        case SDLK_GREATER :  result = 1; break;
        case SDLK_QUESTION :  result = 1; break;
        case SDLK_AT :  result = 1; break;
        case SDLK_LEFTBRACKET :  result = 1; break;
        case SDLK_BACKSLASH :  result = 1; break;
        case SDLK_RIGHTBRACKET :  result = 1; break;
        case SDLK_CARET :  result = 1; break;
        case SDLK_UNDERSCORE :  result = 1; break;
        case SDLK_BACKQUOTE :  result = 1; break;
        case SDLK_a :  result = 1; break;
        case SDLK_b :  result = 1; break;
        case SDLK_c :  result = 1; break;
        case SDLK_d :  result = 1; break;
        case SDLK_e :  result = 1; break;
        case SDLK_f :  result = 1; break;
        case SDLK_g :  result = 1; break;
        case SDLK_h :  result = 1; break;
        case SDLK_i :  result = 1; break;
        case SDLK_j :  result = 1; break;
        case SDLK_k :  result = 1; break;
        case SDLK_l :  result = 1; break;
        case SDLK_m :  result = 1; break;
        case SDLK_n :  result = 1; break;
        case SDLK_o :  result = 1; break;
        case SDLK_p :  result = 1; break;
        case SDLK_q :  result = 1; break;
        case SDLK_r :  result = 1; break;
        case SDLK_s :  result = 1; break;
        case SDLK_t :  result = 1; break;
        case SDLK_u :  result = 1; break;
        case SDLK_v :  result = 1; break;
        case SDLK_w :  result = 1; break;
        case SDLK_x :  result = 1; break;
        case SDLK_y :  result = 1; break;
        case SDLK_z :  result = 1; break;
        case SDLK_KP_PERIOD :  result = 1; break;
        case SDLK_KP_DIVIDE :  result = 1; break;
        case SDLK_KP_MULTIPLY :  result = 1; break;
        case SDLK_KP_MINUS :  result = 1; break;
        case SDLK_KP_PLUS :  result = 1; break;
        case SDLK_KP_EQUALS :  result = 1; break;
        default: result = 0;
    }
    return result;
}


int converSdlKeyToChar( SDLKey key, SDLMod mod, char* character ){
    int result = 0;
/*
 *     if( mod & KMOD_NUM ) printf( "NUMLOCK " );
 *         if( mod & KMOD_CAPS ) printf( "CAPSLOCK " );
 *             if( mod & KMOD_LCTRL ) printf( "LCTRL " );
 *                 if( mod & KMOD_RCTRL ) printf( "RCTRL " );
 *                     if( mod & KMOD_RSHIFT ) printf( "RSHIFT " );
 *                         if( mod & KMOD_LSHIFT ) printf( "LSHIFT " );
 *                             if( mod & KMOD_RALT ) printf( "RALT " );
 *                                 if( mod & KMOD_LALT ) printf( "LALT " );
 *                                     if( mod & KMOD_CTRL ) printf( "CTRL " );
 *                                         if( mod & KMOD_SHIFT ) printf( "SHIFT " );
 *                                             if( mod & KMOD_ALT ) printf( "ALT " );
 *                                             */

    switch( key ) {
        case SDLK_TAB :     (*character) = '\t'; break;
        case SDLK_SPACE :   (*character) = ' '; break;
        case SDLK_EXCLAIM :     (*character) = '!'; break;
        case SDLK_QUOTEDBL :    (*character) = '"'; break;
        case SDLK_HASH :    (*character) = '#'; break;
        case SDLK_DOLLAR :  (*character) = '$'; break;
        case SDLK_AMPERSAND :   (*character) = '&'; break;
        case SDLK_QUOTE :   (*character) = '\''; break;
        case SDLK_LEFTPAREN :   (*character) = '('; break;
        case SDLK_RIGHTPAREN :  (*character) = ')'; break;
        case SDLK_ASTERISK :    (*character) = '*'; break;
        case SDLK_PLUS :    (*character) = '+'; break;
        case SDLK_COMMA :   (*character) = ','; break;
        case SDLK_MINUS :   (*character) = '-'; break;
        case SDLK_PERIOD :  (*character) = '.'; break;
        case SDLK_SLASH :   (*character) = '/'; break;
        case SDLK_0 :   (*character) = '0'; break;
        case SDLK_1 :   (*character) = '1'; break;
        case SDLK_2 :   (*character) = '2'; break;
        case SDLK_3 :   (*character) = '3'; break;
        case SDLK_4 :   (*character) = '4'; break;
        case SDLK_5 :   (*character) = '5'; break;
        case SDLK_6 :   (*character) = '6'; break;
        case SDLK_7 :   (*character) = '7'; break;
        case SDLK_8 :   (*character) = '8'; break;
        case SDLK_9 :   (*character) = '9'; break;
        case SDLK_COLON :   (*character) = ':'; break;
        case SDLK_SEMICOLON :   (*character) = ';'; break;
        case SDLK_LESS :    (*character) = '<'; break;
        case SDLK_EQUALS :  (*character) = '='; break;
        case SDLK_GREATER :     (*character) = '>'; break;
        case SDLK_QUESTION :    (*character) = '?'; break;
        case SDLK_AT :  (*character) = '@'; break;
        case SDLK_LEFTBRACKET :     (*character) = '['; break;
        case SDLK_BACKSLASH :   (*character) = '\\'; break;
        case SDLK_RIGHTBRACKET :    (*character) = ']'; break;
        case SDLK_CARET :   (*character) = '^'; break;
        case SDLK_UNDERSCORE :  (*character) = '_'; break;
        case SDLK_BACKQUOTE :   (*character) = '`'; break;
        case SDLK_a :   (*character) = 'a'; break;
        case SDLK_b :   (*character) = 'b'; break;
        case SDLK_c :   (*character) = 'c'; break;
        case SDLK_d :   (*character) = 'd'; break;
        case SDLK_e :   (*character) = 'e'; break;
        case SDLK_f :   (*character) = 'f'; break;
        case SDLK_g :   (*character) = 'g'; break;
        case SDLK_h :   (*character) = 'h'; break;
        case SDLK_i :   (*character) = 'i'; break;
        case SDLK_j :   (*character) = 'j'; break;
        case SDLK_k :   (*character) = 'k'; break;
        case SDLK_l :   (*character) = 'l'; break;
        case SDLK_m :   (*character) = 'm'; break;
        case SDLK_n :   (*character) = 'n'; break;
        case SDLK_o :   (*character) = 'o'; break;
        case SDLK_p :   (*character) = 'p'; break;
        case SDLK_q :   (*character) = 'q'; break;
        case SDLK_r :   (*character) = 'r'; break;
        case SDLK_s :   (*character) = 's'; break;
        case SDLK_t :   (*character) = 't'; break;
        case SDLK_u :   (*character) = 'u'; break;
        case SDLK_v :   (*character) = 'v'; break;
        case SDLK_w :   (*character) = 'w'; break;
        case SDLK_x :   (*character) = 'x'; break;
        case SDLK_y :   (*character) = 'y'; break;
        case SDLK_z :   (*character) = 'z'; break;
        case SDLK_KP_PERIOD :   (*character) = '.'; break;
        case SDLK_KP_DIVIDE :   (*character) = '/'; break;
        case SDLK_KP_MULTIPLY :     (*character) = '*'; break;
        case SDLK_KP_MINUS :    (*character) = '-'; break;
        case SDLK_KP_PLUS :     (*character) = '+'; break;
        case SDLK_KP_EQUALS :   (*character) = '='; break;
        default: result = 1;
    }
    return result;
}

