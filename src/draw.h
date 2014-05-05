/*
 * draw.h
 *
 *  Created on: 15 apr 2014
 *      Author: andreas
 */

#ifndef DRAW_H_
#define DRAW_H_

#include <SDL/SDL.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>

extern void draw_screen();
extern SDL_Rect draw_rect();
extern SDL_Rect create_rect();
extern void apply_surface(SDL_Surface *ship, SDL_Surface *screen, SDL_Rect *player);



#endif /* DRAW_H_ */
