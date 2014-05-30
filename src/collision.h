/*
 * collision.h
 *
 *  Created on: 7 maj 2014
 *      Author: andreas
 */

#ifndef COLLISION_H_
#define COLLISION_H_
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "helperfunc.h"
extern SDL_Rect create_hitbox();

//This function checks if two rectangles is overlapping.
extern int hit_test();

//This function can be used to check if a bullet or player has hit a asteroid.
extern void collision();

//This function checks if a bullet has hit a asteroid.
extern void bullet_collision();

#endif /* COLLISION_H_ */
