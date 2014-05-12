/*
 * collision.h
 *
 *  Created on: 7 maj 2014
 *      Author: andreas
 */

#ifndef COLLISION_H_
#define COLLISION_H_
#include <SDL/SDL.h>
extern SDL_Rect create_hitbox();
extern int hit_test();
extern void collision();
extern void bullet_collision();

#endif /* COLLISION_H_ */
