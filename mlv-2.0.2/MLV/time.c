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

#include "MLV_time.h"

#include "platform.h"

#ifndef MEMORY_DEBUG
#if defined( OS_WINDOWS )
#	include <SDL/SDL.h>
#	include <SDL/SDL_framerate.h>
#elif defined( OS_APPLE )
#	include <SDL/SDL.h>
#	include <SDL/SDL_framerate.h>
#else
#	include <SDL/SDL.h>
#	include <SDL/SDL_framerate.h>
#endif
#else
#include "memory_debug.h"
#endif

#include <time.h>

#include "warning_error.h"
#include "memory_management.h"

#include "data_structure.h"

extern DataMLV* MLV_data;


void MLV_wait_milliseconds(int milliseconds){
	SDL_Delay( milliseconds );
}

void MLV_wait_seconds(int seconds){
	SDL_Delay( seconds * 1000 );
}

int MLV_get_time(){
	return SDL_GetTicks();
}

int MLV_get_date(
	int* seconds, int* minutes, int* hours,
	int* day, int* month, int* year,
	int* day_of_the_week
){
	time_t current_time;
    time(&current_time);
    struct tm * timeinfo = localtime (&current_time);

	if( seconds ){
		*seconds = timeinfo->tm_sec;
	}
	if( minutes ){
		*minutes = timeinfo->tm_min;
	}
	if( hours ){
		*hours = timeinfo->tm_hour;
	}
	if( day ){
		*day = timeinfo->tm_mday;
	}
	if( month ){
		*month = timeinfo->tm_mon;
	}
	if( year ){
		*year = timeinfo->tm_year+1900;
	}
	if( day_of_the_week ){
		*day_of_the_week = timeinfo->tm_wday;
	}
	return timeinfo->tm_isdst;
}

void MLV_change_frame_rate( int rate ){
	SDL_setFramerate( &(MLV_data->frame_rate_manager), rate );
}

int MLV_get_frame_rate( ){
	return( SDL_getFramerate( &(MLV_data->frame_rate_manager) ) );
}

void MLV_delay_according_to_frame_rate( ){
	SDL_framerateDelay( &(MLV_data->frame_rate_manager) );
}


