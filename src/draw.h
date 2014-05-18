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
#include "main.h"
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_ttf.h>

extern void draw_screen();
extern SDL_Rect draw_rect();
extern SDL_Rect create_rect();
//extern SDL_Surface * rotate();
extern void rotate();
extern void update_rect();
extern void draw_score();
extern void update_asteroids();
void apply_surface();
extern player players[4];


#endif /* DRAW_H_ */
