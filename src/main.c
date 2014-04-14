/*
 * Projekt.c
 */

#include <stdio.h>
#include <SDL/SDL.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

typedef struct object
{
	SDL_Surface *screen;
	SDL_Surface *rectangle;
	SDL_Rect *position;
} t_object;

int create_Rect(t_object *t_obj) {
	t_obj->rectangle = NULL;
	//the color of the screen
	if (SDL_FillRect(t_obj->screen, NULL,
			SDL_MapRGB(t_obj->screen->format, 255, 255, 255)) == -1) {
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		return (1);
	}
	//the size of the rectangle
	if ((t_obj->rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 110, 90, 32, 0, 0,
			0, 0)) == NULL) {
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		return (1);
	}
	//The color of the rectangle
	if (SDL_FillRect(t_obj->rectangle, NULL,
			SDL_MapRGB(t_obj->screen->format, 0, 0, 0)) == -1)
	{
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		return (1);
	}

	if (SDL_BlitSurface(t_obj->rectangle, NULL, t_obj->screen, t_obj->position)
			== -1) {
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		return (1);
	}

	if (SDL_Flip(t_obj->screen) == -1) {
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		return (1);
	}
	return (0);
}

int moving_Rect(t_object *t_obj) {
	int move;
	SDL_Event event;
	//move = 1;

	while (move) {
		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
			move = 0;
		else if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				move = 0;
			}
			if (event.key.keysym.sym == SDLK_RIGHT) {
				t_obj->position->x += 20;
			}
			if (event.key.keysym.sym == SDLK_LEFT) {
				t_obj->position->x -= 20;
			}

			if (event.key.keysym.sym == SDLK_UP) {
				t_obj->position->y -= 20;
			}

			if (event.key.keysym.sym == SDLK_DOWN) {
				t_obj->position->y += 20;
			}
		}
		create_Rect(t_obj);
	}
	return 0;
}

int init(t_object *t_obj) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		return (1);
	}
	//Screen
	if ((t_obj->screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE)) == NULL) {
		fprintf(stderr, "Error: %s", SDL_GetError());
		return (1);
	}

	SDL_WM_SetCaption("Astroid", NULL);

	if (SDL_FillRect(t_obj->screen, NULL,
			SDL_MapRGB(t_obj->screen->format,255, 32, 45)) == -1) //255, 32, 45
			{
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		return (1);
	}

	if (SDL_Flip(t_obj->screen) == -1) {
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		return (1);
	}

	t_obj->position->x = 0;
	t_obj->position->y = 0;

	if (moving_Rect(t_obj)) {
		fprintf(stderr, "Error: %s\n", SDL_GetError());
		return (1);
	}
	SDL_FreeSurface(t_obj->rectangle);
	return (0);
}

int main() {
	t_object t_obj;
	t_obj.screen = NULL;
	if (init(&t_obj))
		return (1);
	return (0);
}

