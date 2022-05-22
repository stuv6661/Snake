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

#include "MLV_keyboard.h"
#include "MLV_event.h"
#include "MLV_time.h"

#ifndef MEMORY_DEBUG
#include <SDL/SDL.h>
#else
#include "memory_debug.h"
#endif

#include "warning_error.h"

#include "memory_management.h"


void MLV_wait_keyboard( MLV_Keyboard_button* sym, MLV_Keyboard_modifier* mod, int* unicode ){
	MLV_Button_state state;

	// We remove all existing event from the queue
	MLV_flush_event_queue();

	//We wait for a new keyboard event
	while(
		(
			MLV_wait_event(
					sym, mod, unicode,
					NULL, NULL,
					NULL, NULL, NULL,
					&state
			) != MLV_KEY
		) ||
		( state != MLV_PRESSED )
	);
}

int MLV_wait_keyboard_or_seconds( MLV_Keyboard_button* sym, MLV_Keyboard_modifier* mod, int* unicode, int seconds ){
	MLV_Button_state state;

	// We remove all existing event from the queue
	MLV_flush_event_queue();

	int time = MLV_get_time();

	MLV_Keyboard_button tmp_sym;
	MLV_Keyboard_modifier tmp_mod;
	int tmp_unicode;

	//We wait for a new keyboard event
	int resultat = 0;
	while(
		(
			(
				resultat = (
					MLV_wait_event_or_seconds(
						&tmp_sym, &tmp_mod, &tmp_unicode,
						NULL, NULL,
						NULL, NULL, NULL,
						&state,
						seconds - (MLV_get_time() - time)/1000
					) != MLV_KEY
				)
			) ||
			( state != MLV_PRESSED )
		) && (
			(MLV_get_time() - time) < seconds*1000
		)
	);

	if( ! resultat && state == MLV_PRESSED ){
		if( sym ) *sym = tmp_sym;
		if( mod ) *mod = tmp_mod;
		if( unicode ) *unicode = tmp_unicode;
	}

	return resultat;
}

MLV_Keyboard_button MLV_convert_string_to_keyboard_button( const char* key_string ){

	if(strcmp(key_string,"MLV_KEYBOARD_UNKNOWN") == 0){
		return MLV_KEYBOARD_UNKNOWN;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_FIRST") == 0){
		return MLV_KEYBOARD_FIRST;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_BACKSPACE") == 0){
		return MLV_KEYBOARD_BACKSPACE;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_TAB") == 0){
		return MLV_KEYBOARD_TAB;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_CLEAR") == 0){
		return MLV_KEYBOARD_CLEAR;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_RETURN") == 0){
		return MLV_KEYBOARD_RETURN;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_PAUSE") == 0){
		return MLV_KEYBOARD_PAUSE;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_ESCAPE") == 0){
		return MLV_KEYBOARD_ESCAPE;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_SPACE") == 0){
		return MLV_KEYBOARD_SPACE;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_EXCLAIM") == 0){
		return MLV_KEYBOARD_EXCLAIM;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_QUOTEDBL") == 0){
		return MLV_KEYBOARD_QUOTEDBL;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_HASH") == 0){
		return MLV_KEYBOARD_HASH;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_DOLLAR") == 0){
		return MLV_KEYBOARD_DOLLAR;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_AMPERSAND") == 0){
		return MLV_KEYBOARD_AMPERSAND;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_QUOTE") == 0){
		return MLV_KEYBOARD_QUOTE;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_LEFTPAREN") == 0){
		return MLV_KEYBOARD_LEFTPAREN;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_RIGHTPAREN") == 0){
		return MLV_KEYBOARD_RIGHTPAREN;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_ASTERISK") == 0){
		return MLV_KEYBOARD_ASTERISK;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_PLUS") == 0){
		return MLV_KEYBOARD_PLUS;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_COMMA") == 0){
		return MLV_KEYBOARD_COMMA;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_MINUS") == 0){
		return MLV_KEYBOARD_MINUS;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_PERIOD") == 0){
		return MLV_KEYBOARD_PERIOD;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_SLASH") == 0){
		return MLV_KEYBOARD_SLASH;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_0") == 0){
		return MLV_KEYBOARD_0;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_1") == 0){
		return MLV_KEYBOARD_1;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_2") == 0){
		return MLV_KEYBOARD_2;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_3") == 0){
		return MLV_KEYBOARD_3;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_4") == 0){
		return MLV_KEYBOARD_4;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_5") == 0){
		return MLV_KEYBOARD_5;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_6") == 0){
		return MLV_KEYBOARD_6;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_7") == 0){
		return MLV_KEYBOARD_7;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_8") == 0){
		return MLV_KEYBOARD_8;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_9") == 0){
		return MLV_KEYBOARD_9;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_COLON") == 0){
		return MLV_KEYBOARD_COLON;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_SEMICOLON") == 0){
		return MLV_KEYBOARD_SEMICOLON;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_LESS") == 0){
		return MLV_KEYBOARD_LESS;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_EQUALS") == 0){
		return MLV_KEYBOARD_EQUALS;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_GREATER") == 0){
		return MLV_KEYBOARD_GREATER;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_QUESTION") == 0){
		return MLV_KEYBOARD_QUESTION;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_AT") == 0){
		return MLV_KEYBOARD_AT;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_LEFTBRACKET") == 0){
		return MLV_KEYBOARD_LEFTBRACKET;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_BACKSLASH") == 0){
		return MLV_KEYBOARD_BACKSLASH;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_RIGHTBRACKET") == 0){
		return MLV_KEYBOARD_RIGHTBRACKET;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_CARET") == 0){
		return MLV_KEYBOARD_CARET;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_UNDERSCORE") == 0){
		return MLV_KEYBOARD_UNDERSCORE;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_BACKQUOTE") == 0){
		return MLV_KEYBOARD_BACKQUOTE;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_a") == 0){
		return MLV_KEYBOARD_a;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_b") == 0){
		return MLV_KEYBOARD_b;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_c") == 0){
		return MLV_KEYBOARD_c;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_d") == 0){
		return MLV_KEYBOARD_d;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_e") == 0){
		return MLV_KEYBOARD_e;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_f") == 0){
		return MLV_KEYBOARD_f;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_g") == 0){
		return MLV_KEYBOARD_g;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_h") == 0){
		return MLV_KEYBOARD_h;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_i") == 0){
		return MLV_KEYBOARD_i;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_j") == 0){
		return MLV_KEYBOARD_j;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_k") == 0){
		return MLV_KEYBOARD_k;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_l") == 0){
		return MLV_KEYBOARD_l;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_m") == 0){
		return MLV_KEYBOARD_m;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_n") == 0){
		return MLV_KEYBOARD_n;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_o") == 0){
		return MLV_KEYBOARD_o;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_p") == 0){
		return MLV_KEYBOARD_p;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_q") == 0){
		return MLV_KEYBOARD_q;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_r") == 0){
		return MLV_KEYBOARD_r;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_s") == 0){
		return MLV_KEYBOARD_s;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_t") == 0){
		return MLV_KEYBOARD_t;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_u") == 0){
		return MLV_KEYBOARD_u;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_v") == 0){
		return MLV_KEYBOARD_v;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_w") == 0){
		return MLV_KEYBOARD_w;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_x") == 0){
		return MLV_KEYBOARD_x;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_y") == 0){
		return MLV_KEYBOARD_y;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_z") == 0){
		return MLV_KEYBOARD_z;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_DELETE") == 0){
		return MLV_KEYBOARD_DELETE;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_0") == 0){
		return MLV_KEYBOARD_WORLD_0;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_1") == 0){
		return MLV_KEYBOARD_WORLD_1;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_2") == 0){
		return MLV_KEYBOARD_WORLD_2;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_3") == 0){
		return MLV_KEYBOARD_WORLD_3;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_4") == 0){
		return MLV_KEYBOARD_WORLD_4;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_5") == 0){
		return MLV_KEYBOARD_WORLD_5;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_6") == 0){
		return MLV_KEYBOARD_WORLD_6;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_7") == 0){
		return MLV_KEYBOARD_WORLD_7;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_8") == 0){
		return MLV_KEYBOARD_WORLD_8;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_9") == 0){
		return MLV_KEYBOARD_WORLD_9;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_10") == 0){
		return MLV_KEYBOARD_WORLD_10;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_11") == 0){
		return MLV_KEYBOARD_WORLD_11;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_12") == 0){
		return MLV_KEYBOARD_WORLD_12;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_13") == 0){
		return MLV_KEYBOARD_WORLD_13;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_14") == 0){
		return MLV_KEYBOARD_WORLD_14;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_15") == 0){
		return MLV_KEYBOARD_WORLD_15;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_16") == 0){
		return MLV_KEYBOARD_WORLD_16;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_17") == 0){
		return MLV_KEYBOARD_WORLD_17;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_18") == 0){
		return MLV_KEYBOARD_WORLD_18;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_19") == 0){
		return MLV_KEYBOARD_WORLD_19;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_20") == 0){
		return MLV_KEYBOARD_WORLD_20;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_21") == 0){
		return MLV_KEYBOARD_WORLD_21;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_22") == 0){
		return MLV_KEYBOARD_WORLD_22;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_23") == 0){
		return MLV_KEYBOARD_WORLD_23;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_24") == 0){
		return MLV_KEYBOARD_WORLD_24;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_25") == 0){
		return MLV_KEYBOARD_WORLD_25;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_26") == 0){
		return MLV_KEYBOARD_WORLD_26;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_27") == 0){
		return MLV_KEYBOARD_WORLD_27;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_28") == 0){
		return MLV_KEYBOARD_WORLD_28;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_29") == 0){
		return MLV_KEYBOARD_WORLD_29;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_30") == 0){
		return MLV_KEYBOARD_WORLD_30;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_31") == 0){
		return MLV_KEYBOARD_WORLD_31;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_32") == 0){
		return MLV_KEYBOARD_WORLD_32;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_33") == 0){
		return MLV_KEYBOARD_WORLD_33;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_34") == 0){
		return MLV_KEYBOARD_WORLD_34;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_35") == 0){
		return MLV_KEYBOARD_WORLD_35;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_36") == 0){
		return MLV_KEYBOARD_WORLD_36;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_37") == 0){
		return MLV_KEYBOARD_WORLD_37;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_38") == 0){
		return MLV_KEYBOARD_WORLD_38;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_39") == 0){
		return MLV_KEYBOARD_WORLD_39;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_40") == 0){
		return MLV_KEYBOARD_WORLD_40;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_41") == 0){
		return MLV_KEYBOARD_WORLD_41;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_42") == 0){
		return MLV_KEYBOARD_WORLD_42;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_43") == 0){
		return MLV_KEYBOARD_WORLD_43;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_44") == 0){
		return MLV_KEYBOARD_WORLD_44;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_45") == 0){
		return MLV_KEYBOARD_WORLD_45;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_46") == 0){
		return MLV_KEYBOARD_WORLD_46;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_47") == 0){
		return MLV_KEYBOARD_WORLD_47;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_48") == 0){
		return MLV_KEYBOARD_WORLD_48;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_49") == 0){
		return MLV_KEYBOARD_WORLD_49;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_50") == 0){
		return MLV_KEYBOARD_WORLD_50;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_51") == 0){
		return MLV_KEYBOARD_WORLD_51;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_52") == 0){
		return MLV_KEYBOARD_WORLD_52;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_53") == 0){
		return MLV_KEYBOARD_WORLD_53;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_54") == 0){
		return MLV_KEYBOARD_WORLD_54;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_55") == 0){
		return MLV_KEYBOARD_WORLD_55;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_56") == 0){
		return MLV_KEYBOARD_WORLD_56;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_57") == 0){
		return MLV_KEYBOARD_WORLD_57;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_58") == 0){
		return MLV_KEYBOARD_WORLD_58;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_59") == 0){
		return MLV_KEYBOARD_WORLD_59;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_60") == 0){
		return MLV_KEYBOARD_WORLD_60;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_61") == 0){
		return MLV_KEYBOARD_WORLD_61;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_62") == 0){
		return MLV_KEYBOARD_WORLD_62;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_63") == 0){
		return MLV_KEYBOARD_WORLD_63;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_64") == 0){
		return MLV_KEYBOARD_WORLD_64;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_65") == 0){
		return MLV_KEYBOARD_WORLD_65;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_66") == 0){
		return MLV_KEYBOARD_WORLD_66;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_67") == 0){
		return MLV_KEYBOARD_WORLD_67;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_68") == 0){
		return MLV_KEYBOARD_WORLD_68;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_69") == 0){
		return MLV_KEYBOARD_WORLD_69;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_70") == 0){
		return MLV_KEYBOARD_WORLD_70;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_71") == 0){
		return MLV_KEYBOARD_WORLD_71;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_72") == 0){
		return MLV_KEYBOARD_WORLD_72;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_73") == 0){
		return MLV_KEYBOARD_WORLD_73;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_74") == 0){
		return MLV_KEYBOARD_WORLD_74;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_75") == 0){
		return MLV_KEYBOARD_WORLD_75;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_76") == 0){
		return MLV_KEYBOARD_WORLD_76;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_77") == 0){
		return MLV_KEYBOARD_WORLD_77;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_78") == 0){
		return MLV_KEYBOARD_WORLD_78;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_79") == 0){
		return MLV_KEYBOARD_WORLD_79;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_80") == 0){
		return MLV_KEYBOARD_WORLD_80;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_81") == 0){
		return MLV_KEYBOARD_WORLD_81;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_82") == 0){
		return MLV_KEYBOARD_WORLD_82;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_83") == 0){
		return MLV_KEYBOARD_WORLD_83;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_84") == 0){
		return MLV_KEYBOARD_WORLD_84;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_85") == 0){
		return MLV_KEYBOARD_WORLD_85;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_86") == 0){
		return MLV_KEYBOARD_WORLD_86;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_87") == 0){
		return MLV_KEYBOARD_WORLD_87;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_88") == 0){
		return MLV_KEYBOARD_WORLD_88;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_89") == 0){
		return MLV_KEYBOARD_WORLD_89;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_90") == 0){
		return MLV_KEYBOARD_WORLD_90;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_91") == 0){
		return MLV_KEYBOARD_WORLD_91;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_92") == 0){
		return MLV_KEYBOARD_WORLD_92;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_93") == 0){
		return MLV_KEYBOARD_WORLD_93;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_94") == 0){
		return MLV_KEYBOARD_WORLD_94;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_WORLD_95") == 0){
		return MLV_KEYBOARD_WORLD_95;
	}

	if(strcmp(key_string,"MLV_KEYBOARD_KP0") == 0){
		return MLV_KEYBOARD_KP0;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP1") == 0){
		return MLV_KEYBOARD_KP1;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP2") == 0){
		return MLV_KEYBOARD_KP2;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP3") == 0){
		return MLV_KEYBOARD_KP3;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP4") == 0){
		return MLV_KEYBOARD_KP4;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP5") == 0){
		return MLV_KEYBOARD_KP5;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP6") == 0){
		return MLV_KEYBOARD_KP6;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP7") == 0){
		return MLV_KEYBOARD_KP7;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP8") == 0){
		return MLV_KEYBOARD_KP8;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP9") == 0){
		return MLV_KEYBOARD_KP9;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP_PERIOD") == 0){
		return MLV_KEYBOARD_KP_PERIOD;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP_DIVIDE") == 0){
		return MLV_KEYBOARD_KP_DIVIDE;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP_MULTIPLY") == 0){
		return MLV_KEYBOARD_KP_MULTIPLY;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP_MINUS") == 0){
		return MLV_KEYBOARD_KP_MINUS;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP_PLUS") == 0){
		return MLV_KEYBOARD_KP_PLUS;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP_ENTER") == 0){
		return MLV_KEYBOARD_KP_ENTER;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_KP_EQUALS") == 0){
		return MLV_KEYBOARD_KP_EQUALS;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_UP") == 0){
		return MLV_KEYBOARD_UP;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_DOWN") == 0){
		return MLV_KEYBOARD_DOWN;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_RIGHT") == 0){
		return MLV_KEYBOARD_RIGHT;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_LEFT") == 0){
		return MLV_KEYBOARD_LEFT;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_INSERT") == 0){
		return MLV_KEYBOARD_INSERT;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_HOME") == 0){
		return MLV_KEYBOARD_HOME;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_END") == 0){
		return MLV_KEYBOARD_END;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_PAGEUP") == 0){
		return MLV_KEYBOARD_PAGEUP;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_PAGEDOWN") == 0){
		return MLV_KEYBOARD_PAGEDOWN;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F1") == 0){
		return MLV_KEYBOARD_F1;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F2") == 0){
		return MLV_KEYBOARD_F2;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F3") == 0){
		return MLV_KEYBOARD_F3;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F4") == 0){
		return MLV_KEYBOARD_F4;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F5") == 0){
		return MLV_KEYBOARD_F5;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F6") == 0){
		return MLV_KEYBOARD_F6;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F7") == 0){
		return MLV_KEYBOARD_F7;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F8") == 0){
		return MLV_KEYBOARD_F8;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F9") == 0){
		return MLV_KEYBOARD_F9;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F10") == 0){
		return MLV_KEYBOARD_F10;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F11") == 0){
		return MLV_KEYBOARD_F11;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F12") == 0){
		return MLV_KEYBOARD_F12;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F13") == 0){
		return MLV_KEYBOARD_F13;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F14") == 0){
		return MLV_KEYBOARD_F14;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_F15") == 0){
		return MLV_KEYBOARD_F15;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_NUMLOCK") == 0){
		return MLV_KEYBOARD_NUMLOCK;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_CAPSLOCK") == 0){
		return MLV_KEYBOARD_CAPSLOCK;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_SCROLLOCK") == 0){
		return MLV_KEYBOARD_SCROLLOCK;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_RSHIFT") == 0){
		return MLV_KEYBOARD_RSHIFT;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_LSHIFT") == 0){
		return MLV_KEYBOARD_LSHIFT;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_RCTRL") == 0){
		return MLV_KEYBOARD_RCTRL;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_LCTRL") == 0){
		return MLV_KEYBOARD_LCTRL;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_RALT") == 0){
		return MLV_KEYBOARD_RALT;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_LALT") == 0){
		return MLV_KEYBOARD_LALT;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_RMETA") == 0){
		return MLV_KEYBOARD_RMETA;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_LMETA") == 0){
		return MLV_KEYBOARD_LMETA;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_LSUPER") == 0){
		return MLV_KEYBOARD_LSUPER;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_RSUPER") == 0){
		return MLV_KEYBOARD_RSUPER;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_MODE") == 0){
		return MLV_KEYBOARD_MODE;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_COMPOSE") == 0){
		return MLV_KEYBOARD_COMPOSE;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_HELP") == 0){
		return MLV_KEYBOARD_HELP;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_PRINT") == 0){
		return MLV_KEYBOARD_PRINT;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_SYSREQ") == 0){
		return MLV_KEYBOARD_SYSREQ;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_BREAK") == 0){
		return MLV_KEYBOARD_BREAK;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_MENU") == 0){
		return MLV_KEYBOARD_MENU;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_POWER") == 0){
		return MLV_KEYBOARD_POWER;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_EURO") == 0){
		return MLV_KEYBOARD_EURO;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_UNDO") == 0){
		return MLV_KEYBOARD_UNDO;
	}
	if(strcmp(key_string,"MLV_KEYBOARD_LAST") == 0){
		return MLV_KEYBOARD_LAST;
	}
	ERROR( "Keyboard type unexpected" );
	return 0;
}

const char* MLV_convert_keyboard_button_to_string( MLV_Keyboard_button key_code ){
	switch( key_code ){	
		case MLV_KEYBOARD_UNKNOWN :
			return "MLV_KEYBOARD_UNKNOWN";
		case MLV_KEYBOARD_BACKSPACE :
			return "MLV_KEYBOARD_BACKSPACE";
		case MLV_KEYBOARD_TAB :
			return "MLV_KEYBOARD_TAB";
		case MLV_KEYBOARD_CLEAR :
			return "MLV_KEYBOARD_CLEAR";
		case MLV_KEYBOARD_RETURN :
			return "MLV_KEYBOARD_RETURN";
		case MLV_KEYBOARD_PAUSE :
			return "MLV_KEYBOARD_PAUSE";
		case MLV_KEYBOARD_ESCAPE :
			return "MLV_KEYBOARD_ESCAPE";
		case MLV_KEYBOARD_SPACE :
			return "MLV_KEYBOARD_SPACE";
		case MLV_KEYBOARD_EXCLAIM :
			return "MLV_KEYBOARD_EXCLAIM";
		case MLV_KEYBOARD_QUOTEDBL :
			return "MLV_KEYBOARD_QUOTEDBL";
		case MLV_KEYBOARD_HASH :
			return "MLV_KEYBOARD_HASH";
		case MLV_KEYBOARD_DOLLAR :
			return "MLV_KEYBOARD_DOLLAR";
		case MLV_KEYBOARD_AMPERSAND :
			return "MLV_KEYBOARD_AMPERSAND";
		case MLV_KEYBOARD_QUOTE :
			return "MLV_KEYBOARD_QUOTE";
		case MLV_KEYBOARD_LEFTPAREN :
			return "MLV_KEYBOARD_LEFTPAREN";
		case MLV_KEYBOARD_RIGHTPAREN :
			return "MLV_KEYBOARD_RIGHTPAREN";
		case MLV_KEYBOARD_ASTERISK :
			return "MLV_KEYBOARD_ASTERISK";
		case MLV_KEYBOARD_PLUS :
			return "MLV_KEYBOARD_PLUS";
		case MLV_KEYBOARD_COMMA :
			return "MLV_KEYBOARD_COMMA";
		case MLV_KEYBOARD_MINUS :
			return "MLV_KEYBOARD_MINUS";
		case MLV_KEYBOARD_PERIOD :
			return "MLV_KEYBOARD_PERIOD";
		case MLV_KEYBOARD_SLASH :
			return "MLV_KEYBOARD_SLASH";
		case MLV_KEYBOARD_0 :
			return "MLV_KEYBOARD_0";
		case MLV_KEYBOARD_1 :
			return "MLV_KEYBOARD_1";
		case MLV_KEYBOARD_2 :
			return "MLV_KEYBOARD_2";
		case MLV_KEYBOARD_3 :
			return "MLV_KEYBOARD_3";
		case MLV_KEYBOARD_4 :
			return "MLV_KEYBOARD_4";
		case MLV_KEYBOARD_5 :
			return "MLV_KEYBOARD_5";
		case MLV_KEYBOARD_6 :
			return "MLV_KEYBOARD_6";
		case MLV_KEYBOARD_7 :
			return "MLV_KEYBOARD_7";
		case MLV_KEYBOARD_8 :
			return "MLV_KEYBOARD_8";
		case MLV_KEYBOARD_9 :
			return "MLV_KEYBOARD_9";
		case MLV_KEYBOARD_COLON :
			return "MLV_KEYBOARD_COLON";
		case MLV_KEYBOARD_SEMICOLON :
			return "MLV_KEYBOARD_SEMICOLON";
		case MLV_KEYBOARD_LESS :
			return "MLV_KEYBOARD_LESS";
		case MLV_KEYBOARD_EQUALS :
			return "MLV_KEYBOARD_EQUALS";
		case MLV_KEYBOARD_GREATER :
			return "MLV_KEYBOARD_GREATER";
		case MLV_KEYBOARD_QUESTION :
			return "MLV_KEYBOARD_QUESTION";
		case MLV_KEYBOARD_AT :
			return "MLV_KEYBOARD_AT";
		case MLV_KEYBOARD_LEFTBRACKET :
			return "MLV_KEYBOARD_LEFTBRACKET";
		case MLV_KEYBOARD_BACKSLASH :
			return "MLV_KEYBOARD_BACKSLASH";
		case MLV_KEYBOARD_RIGHTBRACKET :
			return "MLV_KEYBOARD_RIGHTBRACKET";
		case MLV_KEYBOARD_CARET :
			return "MLV_KEYBOARD_CARET";
		case MLV_KEYBOARD_UNDERSCORE :
			return "MLV_KEYBOARD_UNDERSCORE";
		case MLV_KEYBOARD_BACKQUOTE :
			return "MLV_KEYBOARD_BACKQUOTE";
		case MLV_KEYBOARD_a :
			return "MLV_KEYBOARD_a";
		case MLV_KEYBOARD_b :
			return "MLV_KEYBOARD_b";
		case MLV_KEYBOARD_c :
			return "MLV_KEYBOARD_c";
		case MLV_KEYBOARD_d :
			return "MLV_KEYBOARD_d";
		case MLV_KEYBOARD_e :
			return "MLV_KEYBOARD_e";
		case MLV_KEYBOARD_f :
			return "MLV_KEYBOARD_f";
		case MLV_KEYBOARD_g :
			return "MLV_KEYBOARD_g";
		case MLV_KEYBOARD_h :
			return "MLV_KEYBOARD_h";
		case MLV_KEYBOARD_i :
			return "MLV_KEYBOARD_i";
		case MLV_KEYBOARD_j :
			return "MLV_KEYBOARD_j";
		case MLV_KEYBOARD_k :
			return "MLV_KEYBOARD_k";
		case MLV_KEYBOARD_l :
			return "MLV_KEYBOARD_l";
		case MLV_KEYBOARD_m :
			return "MLV_KEYBOARD_m";
		case MLV_KEYBOARD_n :
			return "MLV_KEYBOARD_n";
		case MLV_KEYBOARD_o :
			return "MLV_KEYBOARD_o";
		case MLV_KEYBOARD_p :
			return "MLV_KEYBOARD_p";
		case MLV_KEYBOARD_q :
			return "MLV_KEYBOARD_q";
		case MLV_KEYBOARD_r :
			return "MLV_KEYBOARD_r";
		case MLV_KEYBOARD_s :
			return "MLV_KEYBOARD_s";
		case MLV_KEYBOARD_t :
			return "MLV_KEYBOARD_t";
		case MLV_KEYBOARD_u :
			return "MLV_KEYBOARD_u";
		case MLV_KEYBOARD_v :
			return "MLV_KEYBOARD_v";
		case MLV_KEYBOARD_w :
			return "MLV_KEYBOARD_w";
		case MLV_KEYBOARD_x :
			return "MLV_KEYBOARD_x";
		case MLV_KEYBOARD_y :
			return "MLV_KEYBOARD_y";
		case MLV_KEYBOARD_z :
			return "MLV_KEYBOARD_z";
		case MLV_KEYBOARD_DELETE :
			return "MLV_KEYBOARD_DELETE";
		case MLV_KEYBOARD_WORLD_0 :
			return "MLV_KEYBOARD_WORLD_0";
		case MLV_KEYBOARD_WORLD_1 :
			return "MLV_KEYBOARD_WORLD_1";
		case MLV_KEYBOARD_WORLD_2 :
			return "MLV_KEYBOARD_WORLD_2";
		case MLV_KEYBOARD_WORLD_3 :
			return "MLV_KEYBOARD_WORLD_3";
		case MLV_KEYBOARD_WORLD_4 :
			return "MLV_KEYBOARD_WORLD_4";
		case MLV_KEYBOARD_WORLD_5 :
			return "MLV_KEYBOARD_WORLD_5";
		case MLV_KEYBOARD_WORLD_6 :
			return "MLV_KEYBOARD_WORLD_6";
		case MLV_KEYBOARD_WORLD_7 :
			return "MLV_KEYBOARD_WORLD_7";
		case MLV_KEYBOARD_WORLD_8 :
			return "MLV_KEYBOARD_WORLD_8";
		case MLV_KEYBOARD_WORLD_9 :
			return "MLV_KEYBOARD_WORLD_9";
		case MLV_KEYBOARD_WORLD_10 :
			return "MLV_KEYBOARD_WORLD_10";
		case MLV_KEYBOARD_WORLD_11 :
			return "MLV_KEYBOARD_WORLD_11";
		case MLV_KEYBOARD_WORLD_12 :
			return "MLV_KEYBOARD_WORLD_12";
		case MLV_KEYBOARD_WORLD_13 :
			return "MLV_KEYBOARD_WORLD_13";
		case MLV_KEYBOARD_WORLD_14 :
			return "MLV_KEYBOARD_WORLD_14";
		case MLV_KEYBOARD_WORLD_15 :
			return "MLV_KEYBOARD_WORLD_15";
		case MLV_KEYBOARD_WORLD_16 :
			return "MLV_KEYBOARD_WORLD_16";
		case MLV_KEYBOARD_WORLD_17 :
			return "MLV_KEYBOARD_WORLD_17";
		case MLV_KEYBOARD_WORLD_18 :
			return "MLV_KEYBOARD_WORLD_18";
		case MLV_KEYBOARD_WORLD_19 :
			return "MLV_KEYBOARD_WORLD_19";
		case MLV_KEYBOARD_WORLD_20 :
			return "MLV_KEYBOARD_WORLD_20";
		case MLV_KEYBOARD_WORLD_21 :
			return "MLV_KEYBOARD_WORLD_21";
		case MLV_KEYBOARD_WORLD_22 :
			return "MLV_KEYBOARD_WORLD_22";
		case MLV_KEYBOARD_WORLD_23 :
			return "MLV_KEYBOARD_WORLD_23";
		case MLV_KEYBOARD_WORLD_24 :
			return "MLV_KEYBOARD_WORLD_24";
		case MLV_KEYBOARD_WORLD_25 :
			return "MLV_KEYBOARD_WORLD_25";
		case MLV_KEYBOARD_WORLD_26 :
			return "MLV_KEYBOARD_WORLD_26";
		case MLV_KEYBOARD_WORLD_27 :
			return "MLV_KEYBOARD_WORLD_27";
		case MLV_KEYBOARD_WORLD_28 :
			return "MLV_KEYBOARD_WORLD_28";
		case MLV_KEYBOARD_WORLD_29 :
			return "MLV_KEYBOARD_WORLD_29";
		case MLV_KEYBOARD_WORLD_30 :
			return "MLV_KEYBOARD_WORLD_30";
		case MLV_KEYBOARD_WORLD_31 :
			return "MLV_KEYBOARD_WORLD_31";
		case MLV_KEYBOARD_WORLD_32 :
			return "MLV_KEYBOARD_WORLD_32";
		case MLV_KEYBOARD_WORLD_33 :
			return "MLV_KEYBOARD_WORLD_33";
		case MLV_KEYBOARD_WORLD_34 :
			return "MLV_KEYBOARD_WORLD_34";
		case MLV_KEYBOARD_WORLD_35 :
			return "MLV_KEYBOARD_WORLD_35";
		case MLV_KEYBOARD_WORLD_36 :
			return "MLV_KEYBOARD_WORLD_36";
		case MLV_KEYBOARD_WORLD_37 :
			return "MLV_KEYBOARD_WORLD_37";
		case MLV_KEYBOARD_WORLD_38 :
			return "MLV_KEYBOARD_WORLD_38";
		case MLV_KEYBOARD_WORLD_39 :
			return "MLV_KEYBOARD_WORLD_39";
		case MLV_KEYBOARD_WORLD_40 :
			return "MLV_KEYBOARD_WORLD_40";
		case MLV_KEYBOARD_WORLD_41 :
			return "MLV_KEYBOARD_WORLD_41";
		case MLV_KEYBOARD_WORLD_42 :
			return "MLV_KEYBOARD_WORLD_42";
		case MLV_KEYBOARD_WORLD_43 :
			return "MLV_KEYBOARD_WORLD_43";
		case MLV_KEYBOARD_WORLD_44 :
			return "MLV_KEYBOARD_WORLD_44";
		case MLV_KEYBOARD_WORLD_45 :
			return "MLV_KEYBOARD_WORLD_45";
		case MLV_KEYBOARD_WORLD_46 :
			return "MLV_KEYBOARD_WORLD_46";
		case MLV_KEYBOARD_WORLD_47 :
			return "MLV_KEYBOARD_WORLD_47";
		case MLV_KEYBOARD_WORLD_48 :
			return "MLV_KEYBOARD_WORLD_48";
		case MLV_KEYBOARD_WORLD_49 :
			return "MLV_KEYBOARD_WORLD_49";
		case MLV_KEYBOARD_WORLD_50 :
			return "MLV_KEYBOARD_WORLD_50";
		case MLV_KEYBOARD_WORLD_51 :
			return "MLV_KEYBOARD_WORLD_51";
		case MLV_KEYBOARD_WORLD_52 :
			return "MLV_KEYBOARD_WORLD_52";
		case MLV_KEYBOARD_WORLD_53 :
			return "MLV_KEYBOARD_WORLD_53";
		case MLV_KEYBOARD_WORLD_54 :
			return "MLV_KEYBOARD_WORLD_54";
		case MLV_KEYBOARD_WORLD_55 :
			return "MLV_KEYBOARD_WORLD_55";
		case MLV_KEYBOARD_WORLD_56 :
			return "MLV_KEYBOARD_WORLD_56";
		case MLV_KEYBOARD_WORLD_57 :
			return "MLV_KEYBOARD_WORLD_57";
		case MLV_KEYBOARD_WORLD_58 :
			return "MLV_KEYBOARD_WORLD_58";
		case MLV_KEYBOARD_WORLD_59 :
			return "MLV_KEYBOARD_WORLD_59";
		case MLV_KEYBOARD_WORLD_60 :
			return "MLV_KEYBOARD_WORLD_60";
		case MLV_KEYBOARD_WORLD_61 :
			return "MLV_KEYBOARD_WORLD_61";
		case MLV_KEYBOARD_WORLD_62 :
			return "MLV_KEYBOARD_WORLD_62";
		case MLV_KEYBOARD_WORLD_63 :
			return "MLV_KEYBOARD_WORLD_63";
		case MLV_KEYBOARD_WORLD_64 :
			return "MLV_KEYBOARD_WORLD_64";
		case MLV_KEYBOARD_WORLD_65 :
			return "MLV_KEYBOARD_WORLD_65";
		case MLV_KEYBOARD_WORLD_66 :
			return "MLV_KEYBOARD_WORLD_66";
		case MLV_KEYBOARD_WORLD_67 :
			return "MLV_KEYBOARD_WORLD_67";
		case MLV_KEYBOARD_WORLD_68 :
			return "MLV_KEYBOARD_WORLD_68";
		case MLV_KEYBOARD_WORLD_69 :
			return "MLV_KEYBOARD_WORLD_69";
		case MLV_KEYBOARD_WORLD_70 :
			return "MLV_KEYBOARD_WORLD_70";
		case MLV_KEYBOARD_WORLD_71 :
			return "MLV_KEYBOARD_WORLD_71";
		case MLV_KEYBOARD_WORLD_72 :
			return "MLV_KEYBOARD_WORLD_72";
		case MLV_KEYBOARD_WORLD_73 :
			return "MLV_KEYBOARD_WORLD_73";
		case MLV_KEYBOARD_WORLD_74 :
			return "MLV_KEYBOARD_WORLD_74";
		case MLV_KEYBOARD_WORLD_75 :
			return "MLV_KEYBOARD_WORLD_75";
		case MLV_KEYBOARD_WORLD_76 :
			return "MLV_KEYBOARD_WORLD_76";
		case MLV_KEYBOARD_WORLD_77 :
			return "MLV_KEYBOARD_WORLD_77";
		case MLV_KEYBOARD_WORLD_78 :
			return "MLV_KEYBOARD_WORLD_78";
		case MLV_KEYBOARD_WORLD_79 :
			return "MLV_KEYBOARD_WORLD_79";
		case MLV_KEYBOARD_WORLD_80 :
			return "MLV_KEYBOARD_WORLD_80";
		case MLV_KEYBOARD_WORLD_81 :
			return "MLV_KEYBOARD_WORLD_81";
		case MLV_KEYBOARD_WORLD_82 :
			return "MLV_KEYBOARD_WORLD_82";
		case MLV_KEYBOARD_WORLD_83 :
			return "MLV_KEYBOARD_WORLD_83";
		case MLV_KEYBOARD_WORLD_84 :
			return "MLV_KEYBOARD_WORLD_84";
		case MLV_KEYBOARD_WORLD_85 :
			return "MLV_KEYBOARD_WORLD_85";
		case MLV_KEYBOARD_WORLD_86 :
			return "MLV_KEYBOARD_WORLD_86";
		case MLV_KEYBOARD_WORLD_87 :
			return "MLV_KEYBOARD_WORLD_87";
		case MLV_KEYBOARD_WORLD_88 :
			return "MLV_KEYBOARD_WORLD_88";
		case MLV_KEYBOARD_WORLD_89 :
			return "MLV_KEYBOARD_WORLD_89";
		case MLV_KEYBOARD_WORLD_90 :
			return "MLV_KEYBOARD_WORLD_90";
		case MLV_KEYBOARD_WORLD_91 :
			return "MLV_KEYBOARD_WORLD_91";
		case MLV_KEYBOARD_WORLD_92 :
			return "MLV_KEYBOARD_WORLD_92";
		case MLV_KEYBOARD_WORLD_93 :
			return "MLV_KEYBOARD_WORLD_93";
		case MLV_KEYBOARD_WORLD_94 :
			return "MLV_KEYBOARD_WORLD_94";
		case MLV_KEYBOARD_WORLD_95 :
			return "MLV_KEYBOARD_WORLD_95";
		case MLV_KEYBOARD_KP0 :
			return "MLV_KEYBOARD_KP0";
		case MLV_KEYBOARD_KP1 :
			return "MLV_KEYBOARD_KP1";
		case MLV_KEYBOARD_KP2 :
			return "MLV_KEYBOARD_KP2";
		case MLV_KEYBOARD_KP3 :
			return "MLV_KEYBOARD_KP3";
		case MLV_KEYBOARD_KP4 :
			return "MLV_KEYBOARD_KP4";
		case MLV_KEYBOARD_KP5 :
			return "MLV_KEYBOARD_KP5";
		case MLV_KEYBOARD_KP6 :
			return "MLV_KEYBOARD_KP6";
		case MLV_KEYBOARD_KP7 :
			return "MLV_KEYBOARD_KP7";
		case MLV_KEYBOARD_KP8 :
			return "MLV_KEYBOARD_KP8";
		case MLV_KEYBOARD_KP9 :
			return "MLV_KEYBOARD_KP9";
		case MLV_KEYBOARD_KP_PERIOD :
			return "MLV_KEYBOARD_KP_PERIOD";
		case MLV_KEYBOARD_KP_DIVIDE :
			return "MLV_KEYBOARD_KP_DIVIDE";
		case MLV_KEYBOARD_KP_MULTIPLY :
			return "MLV_KEYBOARD_KP_MULTIPLY";
		case MLV_KEYBOARD_KP_MINUS :
			return "MLV_KEYBOARD_KP_MINUS";
		case MLV_KEYBOARD_KP_PLUS :
			return "MLV_KEYBOARD_KP_PLUS";
		case MLV_KEYBOARD_KP_ENTER :
			return "MLV_KEYBOARD_KP_ENTER";
		case MLV_KEYBOARD_KP_EQUALS :
			return "MLV_KEYBOARD_KP_EQUALS";
		case MLV_KEYBOARD_UP :
			return "MLV_KEYBOARD_UP";
		case MLV_KEYBOARD_DOWN :
			return "MLV_KEYBOARD_DOWN";
		case MLV_KEYBOARD_RIGHT :
			return "MLV_KEYBOARD_RIGHT";
		case MLV_KEYBOARD_LEFT :
			return "MLV_KEYBOARD_LEFT";
		case MLV_KEYBOARD_INSERT :
			return "MLV_KEYBOARD_INSERT";
		case MLV_KEYBOARD_HOME :
			return "MLV_KEYBOARD_HOME";
		case MLV_KEYBOARD_END :
			return "MLV_KEYBOARD_END";
		case MLV_KEYBOARD_PAGEUP :
			return "MLV_KEYBOARD_PAGEUP";
		case MLV_KEYBOARD_PAGEDOWN :
			return "MLV_KEYBOARD_PAGEDOWN";
		case MLV_KEYBOARD_F1 :
			return "MLV_KEYBOARD_F1";
		case MLV_KEYBOARD_F2 :
			return "MLV_KEYBOARD_F2";
		case MLV_KEYBOARD_F3 :
			return "MLV_KEYBOARD_F3";
		case MLV_KEYBOARD_F4 :
			return "MLV_KEYBOARD_F4";
		case MLV_KEYBOARD_F5 :
			return "MLV_KEYBOARD_F5";
		case MLV_KEYBOARD_F6 :
			return "MLV_KEYBOARD_F6";
		case MLV_KEYBOARD_F7 :
			return "MLV_KEYBOARD_F7";
		case MLV_KEYBOARD_F8 :
			return "MLV_KEYBOARD_F8";
		case MLV_KEYBOARD_F9 :
			return "MLV_KEYBOARD_F9";
		case MLV_KEYBOARD_F10 :
			return "MLV_KEYBOARD_F10";
		case MLV_KEYBOARD_F11 :
			return "MLV_KEYBOARD_F11";
		case MLV_KEYBOARD_F12 :
			return "MLV_KEYBOARD_F12";
		case MLV_KEYBOARD_F13 :
			return "MLV_KEYBOARD_F13";
		case MLV_KEYBOARD_F14 :
			return "MLV_KEYBOARD_F14";
		case MLV_KEYBOARD_F15 :
			return "MLV_KEYBOARD_F15";
		case MLV_KEYBOARD_NUMLOCK :
			return "MLV_KEYBOARD_NUMLOCK";
		case MLV_KEYBOARD_CAPSLOCK :
			return "MLV_KEYBOARD_CAPSLOCK";
		case MLV_KEYBOARD_SCROLLOCK :
			return "MLV_KEYBOARD_SCROLLOCK";
		case MLV_KEYBOARD_RSHIFT :
			return "MLV_KEYBOARD_RSHIFT";
		case MLV_KEYBOARD_LSHIFT :
			return "MLV_KEYBOARD_LSHIFT";
		case MLV_KEYBOARD_RCTRL :
			return "MLV_KEYBOARD_RCTRL";
		case MLV_KEYBOARD_LCTRL :
			return "MLV_KEYBOARD_LCTRL";
		case MLV_KEYBOARD_RALT :
			return "MLV_KEYBOARD_RALT";
		case MLV_KEYBOARD_LALT :
			return "MLV_KEYBOARD_LALT";
		case MLV_KEYBOARD_RMETA :
			return "MLV_KEYBOARD_RMETA";
		case MLV_KEYBOARD_LMETA :
			return "MLV_KEYBOARD_LMETA";
		case MLV_KEYBOARD_LSUPER :
			return "MLV_KEYBOARD_LSUPER";
		case MLV_KEYBOARD_RSUPER :
			return "MLV_KEYBOARD_RSUPER";
		case MLV_KEYBOARD_MODE :
			return "MLV_KEYBOARD_MODE";
		case MLV_KEYBOARD_COMPOSE :
			return "MLV_KEYBOARD_COMPOSE";
		case MLV_KEYBOARD_HELP :
			return "MLV_KEYBOARD_HELP";
		case MLV_KEYBOARD_PRINT :
			return "MLV_KEYBOARD_PRINT";
		case MLV_KEYBOARD_SYSREQ :
			return "MLV_KEYBOARD_SYSREQ";
		case MLV_KEYBOARD_BREAK :
			return "MLV_KEYBOARD_BREAK";
		case MLV_KEYBOARD_MENU :
			return "MLV_KEYBOARD_MENU";
		case MLV_KEYBOARD_POWER :
			return "MLV_KEYBOARD_POWER";
		case MLV_KEYBOARD_EURO :
			return "MLV_KEYBOARD_EURO";
		case MLV_KEYBOARD_UNDO :
			return "MLV_KEYBOARD_UNDO";
		case MLV_KEYBOARD_LAST :
			return "MLV_KEYBOARD_LAST";
		default :
			ERROR("Keyboard code unexpected");
	}
}

char* MLV_convert_keyboard_mod_to_string( MLV_Keyboard_modifier keymod_code ){
	int text_size = 0;
	char* text;
	char* result;
	int nb = 0;
	
	if( keymod_code == MLV_KEYBOARD_KMOD_NONE ){
		text = "MLV_KEYBOARD_KMOD_NONE";
		result = MLV_MALLOC( strlen(text)+1, char );
		sprintf( result, "%s", text );
		return result;
	}

	if( keymod_code & MLV_KEYBOARD_KMOD_NONE ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_NONE" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_LSHIFT ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_LSHIFT" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_RSHIFT ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_RSHIFT" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_LCTRL ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_LCTRL" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_RCTRL ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_RCTRL" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_LALT ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_LALT" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_RALT ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_RALT" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_LMETA ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_LMETA" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_RMETA ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_RMETA" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_NUM ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_NUM" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_CAPS ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_CAPS" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_MODE ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_MODE" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_RESERVED ){
		if( nb>0 ){
			text_size += 3;
		}
		text_size += strlen( "MLV_KEYBOARD_KMOD_RESERVED" );
		nb += 1;
	}

	text = MLV_MALLOC( text_size+1, char );
	text[text_size] = '\0';
	result = text;

	nb = 0;
	if( keymod_code & MLV_KEYBOARD_KMOD_NONE ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_NONE" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_LSHIFT ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_LSHIFT" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_RSHIFT ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_RSHIFT" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_LCTRL ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_LCTRL" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_RCTRL ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_RCTRL" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_LALT ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_LALT" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_RALT ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_RALT" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_LMETA ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_LMETA" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_RMETA ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_RMETA" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_NUM ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_NUM" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_CAPS ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_CAPS" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_MODE ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_MODE" );
		nb += 1;
	}
	if( keymod_code & MLV_KEYBOARD_KMOD_RESERVED ){
		if( nb>0 ){
			text += sprintf( text, " | " );
		}
		text += sprintf( text, "MLV_KEYBOARD_KMOD_RESERVED" );
		nb += 1;
	}
	return result;
}


MLV_Button_state MLV_get_keyboard_state( MLV_Keyboard_button keyboard_code ){
	SDL_PumpEvents();
	Uint8* keyboard_states = SDL_GetKeyState( NULL );
	if( keyboard_states[ keyboard_code ] ) return MLV_PRESSED;
	return MLV_RELEASED;
}

int MLV_left_shift_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & MLV_KEYBOARD_KMOD_LSHIFT;
}

int MLV_right_shift_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & MLV_KEYBOARD_KMOD_RSHIFT;
}

int MLV_shift_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & ( MLV_KEYBOARD_KMOD_LSHIFT | MLV_KEYBOARD_KMOD_RSHIFT );
}

int MLV_left_ctrl_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & MLV_KEYBOARD_KMOD_LCTRL;
}

int MLV_right_ctrl_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & MLV_KEYBOARD_KMOD_RCTRL;
}

int MLV_ctrl_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & ( MLV_KEYBOARD_KMOD_LCTRL | MLV_KEYBOARD_KMOD_RCTRL );
}

int MLV_left_alt_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & MLV_KEYBOARD_KMOD_LALT;
}

int MLV_right_alt_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & MLV_KEYBOARD_KMOD_RALT;
}

int MLV_alt_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & ( MLV_KEYBOARD_KMOD_LALT | MLV_KEYBOARD_KMOD_RALT );
}

int MLV_left_meta_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & MLV_KEYBOARD_KMOD_LMETA;
}

int MLV_right_meta_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & MLV_KEYBOARD_KMOD_RMETA;
}

int MLV_meta_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & ( MLV_KEYBOARD_KMOD_LMETA | MLV_KEYBOARD_KMOD_RMETA );
}

int MLV_num_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & MLV_KEYBOARD_KMOD_NUM;
}

int MLV_caps_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & MLV_KEYBOARD_KMOD_CAPS;
}

int MLV_mode_key_was_pressed(
	MLV_Keyboard_modifier modifier_code
){
	return modifier_code & MLV_KEYBOARD_KMOD_MODE;
}


