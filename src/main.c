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

typedef int bool;

void draw();
void update();
void close_window();
void move_player();

void draw(SDL_Surface *screen, SDL_Rect *player) {
	draw_screen(screen);
	draw_rect(screen, player);
}

void update(SDL_Rect *player, bool *is_running) {
	move_player(player);
}

void close_window(bool *is_running) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			*is_running = FALSE;
		}
	}
}

void move_player(SDL_Rect *player){
	Uint8 *keystates = SDL_GetKeyState( NULL);
		if (keystates[SDLK_UP]) {
			player->y -= 3;
		}
		if (keystates[SDLK_DOWN]) {
			player->y += 3;
		}
		if (keystates[SDLK_RIGHT]) {
			player->x += 3;
		}
		if (keystates[SDLK_LEFT]) {
			player->x -= 3;
		}
}

int main(int argc, char **arg) {
	srand(time(NULL));
	SDL_Surface *screen;
	bool is_running = TRUE;
	screen = NULL;
	const int FPS = 1000 / 60;
	Uint32 lastUpdateTime = SDL_GetTicks();
	int x = 1366 / 2 - 50;
	int y = 768 / 2 - 50;
	SDL_Rect player = create_rect(x, y, 100, 100);
	//SDL_Rect rectangles[10];

	//SDL_Rect *rectangles;
	//rectangles = (SDL_Rect *) malloc(sizeof(SDL_Rect));
//	int numbOfRect = 0;
	//*rectangles = create_rect(x+50, y+50, 100, 100);
//	for (; numbOfRect < 100; numbOfRect++) {
//		rectangles = (SDL_Rect *) realloc(rectangles,
//				(numbOfRect + 1) * sizeof(SDL_Rect));
//		*(rectangles + numbOfRect) = create_rect(rand() % WIDTH + 1,
//				rand() % HEIGHT + 1, 100, 100);
//	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return 0;
	}
	if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF))) {
		SDL_Quit();
		return 1;
	}

	SDL_Thread *net_thread_recv = NULL;

	net_thread_recv = SDL_CreateThread(network_recv, NULL);
	if(net_thread_recv == NULL){
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
		return -1;
	}


	while (is_running) {
		Uint32 current_time = SDL_GetTicks();
		Uint32 difference = current_time - lastUpdateTime;
		SDL_FreeSurface(screen);
		while (difference >= FPS) {
			difference -= FPS;
			update(&player, &is_running);
			lastUpdateTime = current_time;
		}
		draw(screen, &player);
		close_window(&is_running);
//		int i;
//		for (i = 0; i < numbOfRect; i++) {
//			draw_rect(screen, rectangles + i);
//		}
		SDL_BlitSurface(screen, NULL, screen, NULL);
		SDL_Flip(screen);

	}

	return 0;
}
