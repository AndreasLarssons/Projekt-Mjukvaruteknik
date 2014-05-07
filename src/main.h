/*
 * main.h
 *
 *  Created on: 7 maj 2014
 *      Author: andreas
 */

#ifndef MAIN_H_
#define MAIN_H_

struct player{
	SDL_Rect rect;
	double angle;

} typedef player;
player players[4];
//SDL_Rect players[4];
SDL_Surface *ship;
double angle;

void draw();
void update();
void close_window();
void move_player();


#endif /* MAIN_H_ */
