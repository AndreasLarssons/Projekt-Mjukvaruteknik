/*
 * helperfunc.c
 *
 *  Created on: 19 apr 2014
 *      Author: andreas
 */
#include "helperfunc.h"

void set_fps(int fps, Uint32 *last_update_time ){

	Uint32 current_time = SDL_GetTicks();
	Uint32 difference = current_time - *last_update_time;

	while (difference >= fps) {
		difference -= fps;
	}
	*last_update_time = current_time;

}

