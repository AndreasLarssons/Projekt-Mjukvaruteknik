/*
 * main.h
 *
 *  Created on: 7 maj 2014
 *      Author: andreas
 */

#ifndef MAIN_H_
#define MAIN_H_

//SDL_Rect players[4];
SDL_Surface *ship;
double angle;
#define TRUE 1
#define FALSE 0
#define WIDTH 1366
#define HEIGHT 768
#define DEPTH 32
#define VELOCITY 10
#define PI 3.14159265

typedef int bool;


struct player{
	SDL_Rect rect;
	double angle;
	int score;

} typedef player;
struct bullet{
	SDL_Surface *bullet;
	SDL_Rect rect;
	bool alive;
	int angle;
} typedef bullet;


player players[4];
bullet bullets_other[4][4];
void draw();
void update();
void close_window();
void move_player();


#endif /* MAIN_H_ */
