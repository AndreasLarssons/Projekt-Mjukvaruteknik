/*
 * create.h
 *
 * Created on: 28 apr 2014
 * Author: andreas
 */

#ifndef CREATE_H_
#define CREATE_H_
#include <SDL/SDL.h>
#include "main.h"
struct astroid {
	int id;
	SDL_Rect rect;
	int velocity;

}typedef astroid;

extern bullet create_bullet();

//This function returns an available bullet's position in the array.
extern int check_bullet_slot();


extern void fire_bullet();

//This function returns a rectangle with specified position, width and height.
extern SDL_Rect create_rect();

//This function fill the star array with stars with a unique position and random velocity.
extern void create_stars();

#endif /* CREATE_H_ */
