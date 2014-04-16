/*
 * Projekt.c
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "draw.h"
#define TRUE 1
#define FALSE 0
#define WIDTH 1366
#define HEIGHT 768
#define DEPTH 32

typedef int bool;

int main(int argc, char **arg) {
	SDL_Surface *screen;
	SDL_Event event;
	bool is_running = TRUE;
	screen = NULL;
	Uint8 *keystates = SDL_GetKeyState( NULL);
	const int FPS = 1000 / 60;
	Uint32 lastUpdateTime = SDL_GetTicks();
	int x = 1366 / 2 - 50;
	int y = 768 / 2 - 50;
	SDL_Rect player = create_rect(x,y,100,100);
	SDL_Rect rectangles[10];
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return 0;
	}
	if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE))) {
		SDL_Quit();
		return 1;
	}
	while (is_running) {

		Uint32 current_time = SDL_GetTicks();
		Uint32 difference = current_time - lastUpdateTime;
		SDL_FreeSurface(screen);
		while (difference >= FPS) {

			difference -= FPS;

			if (keystates[SDLK_UP]) {
				player.y -= 3;
			}
			if (keystates[SDLK_DOWN]) {
				player.y += 3;
			}
			if (keystates[SDLK_RIGHT]) {
				player.x += 3;
			}
			if (keystates[SDLK_LEFT]) {
				player.x -= 3;
			}
			lastUpdateTime = current_time;

		}
		draw_screen(screen);
		draw_rect(screen, &player);

		SDL_BlitSurface(screen, NULL, screen, NULL);
		SDL_Flip(screen);
		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				is_running = FALSE;
			}

		}
	}

	return 0;
}
