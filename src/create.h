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
extern int check_bullet_slot();
extern void fire_bullet();
extern SDL_Rect create_rect();
extern void create_stars();

#endif /* CREATE_H_ */
