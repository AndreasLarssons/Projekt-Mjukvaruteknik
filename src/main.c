/*
 * Projekt.c
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <SDL/SDL_thread.h>
#include "draw.h"
#include "network.h"
#include "helperfunc.h"
#include <SDL/SDL_rotozoom.h>
#include <math.h>
#include "main.h"
#define TRUE 1
#define FALSE 0
#define WIDTH 1366
#define HEIGHT 768
#define DEPTH 32
#define VELOCITY 10
#define PI 3.14159265

typedef int bool;

void draw(SDL_Surface *screen, node * root) {
	draw_screen(screen);
	int i;
//	for(i = 0; i < 4; i++){
//		draw_rect(screen, &players[i]);
//	}
	for (i = 0; i < 4; i++) {
		SDL_Surface *rotated = rotozoomSurface(ship, players[i].angle, 1, SMOOTHING_ON);
//		players[0].x -= (rotated->w / 2) - (ship->w / 2);
//		players[0].y -= (rotated->h / 2) - (ship->h / 2);
		SDL_Rect rect = { 200, 200, 0, 0 };
		rect = players[i].rect;
		rect.x -= (rotated->w / 2) - (ship->w / 2);
		rect.y -= (rotated->h / 2) - (ship->h / 2);
		SDL_BlitSurface(rotated, NULL, screen, &rect);
		SDL_FreeSurface(rotated);
		if (players[i].angle == 360) {
			players[i].angle = 0;
		} else if (players[i].angle < 0) {
			players[i].angle = angle * -1;
			players[i].angle = 360 - angle;
		}
	}
	node * tmp = root;
	for (i = 0; i < 10; i++) {
		draw_rect(screen, &tmp->astroid.rect);
		tmp = tmp->next;
	}

	//printf("\n%d %d\n", other_player->x, other_player->y);

}

void update(SDL_Rect *player, SDL_Surface *screen, bool *is_running,
		thread_data *thread_recv_info, int lastupdatetime) {
	move_player(player, screen, ship, angle, *thread_recv_info, lastupdatetime);

}

void close_window(bool *is_running) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			*is_running = FALSE;
		}
	}
}

void move_player(SDL_Rect *player, SDL_Surface *screen,
		thread_data thread_recv_info, int lastupdatetime) {
	Uint8 *keystates = SDL_GetKeyState( NULL);
	//printf("%d\n" , thread_recv_info.id);
	if (keystates[SDLK_UP]) {
		//player->y -= 3;
		//cord_trans(player->x, player->y, thread_recv_info);
		//
		//cord_trans(players[thread_recv_info->id].x, players[thread_recv_info->id].y, thread_recv_info);
		//printf("%d \n", thread_recv_info.id);
		players[thread_recv_info.id].rect.x += sin(players[thread_recv_info.id].angle * PI / 180) * 8;

		players[thread_recv_info.id].rect.y += cos(players[thread_recv_info.id].angle  * PI / 180) * 8;

	}
	if (keystates[SDLK_DOWN]) {
		//player->y += 3;
		//cord_trans(player->x, player->y, thread_recv_info);
		//players[thread_recv_info->id].y += VELOCITY * lastupdatetime;
		//cord_trans(players[thread_recv_info->id].x, players[thread_recv_info->id].y, thread_recv_info);

		players[thread_recv_info.id].rect.x -= sin(players[thread_recv_info.id].angle  * PI / 180) * 8;
		players[thread_recv_info.id].rect.y -= cos(players[thread_recv_info.id].angle  * PI / 180) * 8;

	}
	if (keystates[SDLK_RIGHT]) {
		//player->x += 3;
		//cord_trans(player->x, player->y, thread_recv_info);
		//players[thread_recv_info->id].x += VELOCITY * lastupdatetime;
		//cord_trans(players[thread_recv_info->id].x, players[thread_recv_info->id].y, thread_recv_info);

		players[thread_recv_info.id].angle += 2;

	}
	if (keystates[SDLK_LEFT]) {
		//player->x -= 3;
		//cord_trans(player->x, player->y, thread_recv_info);
		//players[thread_recv_info->id].x -= VELOCITY * lastupdatetime;
		//cord_trans(players[thread_recv_info->id].x, players[thread_recv_info->id].y, thread_recv_info);

		players[thread_recv_info.id].angle -= 2;
	}

}

int main(int argc, char **arg) {
	srand(time(NULL));
	SDL_Surface *screen;
	bool is_running = TRUE;
	screen = NULL;
	angle = 0;
	const int FPS = 1000 / 100;
	Uint32 lastUpdateTime;
	int x = 1366 / 2 - 50;
	int y = 768 / 2 - 50;
	node *root;
	create_linked_list(root);
	fill_list(&root, 0, 0, 10);
	fill_astroid_rect(root, 10, 10);

	//ship = IMG_Load("Spaceship.png");
	ship = IMG_Load("Spaceship.png");
	if (!ship) {
		printf("Cannot load file");
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return 0;
	}
	if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH,
	SDL_HWSURFACE | SDL_DOUBLEBUF))) {
		SDL_Quit();
		return 1;
	}

	thread_data thread_recv_info;
	thread_recv_info.x = x;
	thread_recv_info.y = y;
	thread_recv_info.ready = 0;
	thread_recv_info.root = root;

	//thread_recv_info.other_player = create_rect(x, y+100, 100, 100);
	SDL_Thread *net_thread_recv = NULL;
	SDL_Thread *net_thread_trans = NULL;
	int i;
	for (i = 0; i < 4; i++){
		players[i].rect = create_rect(x, y, 100, 100);
		players[i].angle = 0;
	}

	net_thread_recv = SDL_CreateThread(network_recv, &thread_recv_info);

	while (thread_recv_info.ready != 1)
		;
	net_thread_trans = SDL_CreateThread(network_trans, &thread_recv_info);

	if (net_thread_recv == NULL) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
		return -1;
	}

	Uint32 current_time = SDL_GetTicks() / 25;
	while (is_running) {
		lastUpdateTime = current_time;
		current_time = SDL_GetTicks() / 25;
		SDL_FreeSurface(screen);
		update(&players[thread_recv_info.id].rect, &is_running, screen,
				&thread_recv_info, (int) (current_time - lastUpdateTime));
		draw(screen, root);
		close_window(&is_running);
		SDL_Flip(screen);

	}

	return 0;
}
