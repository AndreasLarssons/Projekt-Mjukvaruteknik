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

//This function applies a background color to the screen.
extern void draw_screen();

//This function fills a rectangular with the color black.
extern SDL_Rect draw_rect();
//extern SDL_Surface * rotate();

//This function draws the specified player's score in the bottom right of that player's rectangular.
extern void draw_score();

//This function updates all asteroids positions.
extern void update_asteroids();


void apply_surface();
extern player players[4];


#endif /* DRAW_H_ */
