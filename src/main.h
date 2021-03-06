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
extern int game();
extern char ip_addr[20];
extern char port_num[20];
typedef int bool;

struct star{
SDL_Surface *star_pic;
SDL_Rect rect;
int velocity;
}typedef star;


struct player{
	SDL_Rect rect;
	double angle;
	int score, lives;

} typedef player;
struct bullet{
	SDL_Surface *bullet;
	SDL_Rect rect;
	bool alive;
	int angle;
} typedef bullet;


player players[4];
bullet bullets_other[4][4];

//This function draws all players, asteroids and bullets that is alive.
//It also updates the position of all asteroids and bullets that is alive.
void draw();

//This function is used to update player values.
void update();

//This function checks if the user wants to close the game window.
void close_window();

//This function checks if any of the arrowkeys or the spacebar has been pressed.
void move_player();


#endif /* MAIN_H_ */
