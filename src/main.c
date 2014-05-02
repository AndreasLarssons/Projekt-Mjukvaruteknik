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
#define TRUE 1
#define FALSE 0
#define WIDTH 1366
#define HEIGHT 768
#define DEPTH 32
#define VELOCITY 10

typedef int bool;

SDL_Rect players[4];

void draw();
void update();
void close_window();
void move_player();

void draw(SDL_Surface *screen) {
	draw_screen(screen);
	//draw_rect(screen, player);
	//draw_rect(screen, other_player);
	draw_rect(screen, &players[0]);
	draw_rect(screen, &players[1]);
	draw_rect(screen, &players[2]);
	draw_rect(screen, &players[3]);
	//printf("\n%d %d\n", other_player->x, other_player->y);

}

void update(SDL_Rect *player, bool *is_running, thread_data *thread_recv_info, int lastupdatetime) {
	move_player(player, thread_recv_info, lastupdatetime);
}

void close_window(bool *is_running) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			*is_running = FALSE;
		}
	}
}

void move_player(SDL_Rect *player, thread_data *thread_recv_info, int lastupdatetime){
	Uint8 *keystates = SDL_GetKeyState( NULL);
	if (keystates[SDLK_UP]) {
		//player->y -= 3;
		//cord_trans(player->x, player->y, thread_recv_info);
		players[thread_recv_info->id].y -= VELOCITY * lastupdatetime;
		//cord_trans(players[thread_recv_info->id].x, players[thread_recv_info->id].y, thread_recv_info);
	}
	if (keystates[SDLK_DOWN]) {
		//player->y += 3;
		//cord_trans(player->x, player->y, thread_recv_info);
		players[thread_recv_info->id].y += VELOCITY * lastupdatetime;;
		//cord_trans(players[thread_recv_info->id].x, players[thread_recv_info->id].y, thread_recv_info);
	}
	if (keystates[SDLK_RIGHT]) {
		//player->x += 3;
		//cord_trans(player->x, player->y, thread_recv_info);
		players[thread_recv_info->id].x += VELOCITY * lastupdatetime;;
		//cord_trans(players[thread_recv_info->id].x, players[thread_recv_info->id].y, thread_recv_info);
	}
	if (keystates[SDLK_LEFT]) {
		//player->x -= 3;
		//cord_trans(player->x, player->y, thread_recv_info);
		players[thread_recv_info->id].x -= VELOCITY * lastupdatetime;;
		//cord_trans(players[thread_recv_info->id].x, players[thread_recv_info->id].y, thread_recv_info);
	}

}

int main(int argc, char **arg) {
	srand(time(NULL));
	SDL_Surface *screen;
	bool is_running = TRUE;
	screen = NULL;
	const int FPS = 1000 / 100;
	Uint32 lastUpdateTime;
	int x = 1366 / 2 - 50;
	int y = 768 / 2 - 50;
	SDL_Rect player = create_rect(x, y, 100, 100);


	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return 0;
	}
	if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF))) {
		SDL_Quit();
		return 1;
	}

	thread_data thread_recv_info;
	thread_recv_info.x = x;
	thread_recv_info.y = y;
	thread_recv_info.ready = 0;

	//thread_recv_info.other_player = create_rect(x, y+100, 100, 100);
	SDL_Thread *net_thread_recv = NULL;
	SDL_Thread *net_thread_trans = NULL;

	players[0] = create_rect(x, y, 100, 100);
	players[1] = create_rect(x, y, 100, 100);
	players[2] = create_rect(x, y, 100, 100);
	players[3] = create_rect(x, y, 100, 100);

	net_thread_recv = SDL_CreateThread(network_recv, &thread_recv_info);

	while(thread_recv_info.ready != 1);
	net_thread_trans = SDL_CreateThread(network_trans, &thread_recv_info);

	if(net_thread_recv == NULL){
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
		return -1;
	}
	Uint32 current_time = SDL_GetTicks() / 25;
	while (is_running) {
		Uint32 difference = current_time - lastUpdateTime;
		lastUpdateTime = current_time;
		current_time = SDL_GetTicks() / 25;
		SDL_FreeSurface(screen);
//		while (difference >= FPS) {
//			difference -= FPS;
//			update(&player, &is_running, &thread_recv_info);
//			lastUpdateTime = current_time;
//		}
		update(&player, &is_running, &thread_recv_info, current_time - lastUpdateTime);
		draw(screen);
		close_window(&is_running);

		SDL_BlitSurface(screen, NULL, screen, NULL);
		SDL_Flip(screen);

	}

	return 0;
}
