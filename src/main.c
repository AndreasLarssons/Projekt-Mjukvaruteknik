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
#include "create.h"
#include <SDL/SDL_rotozoom.h>
#include <math.h>
#include "main.h"
#include "collision.h"
#include <SDL/SDL_framerate.h>
#include <SDL/SDL_ttf.h>

void draw(SDL_Surface *screen, node * root, bullet bullets[],
		thread_data thread_recv_info, SDL_Surface *astroid, TTF_Font *font) {
	draw_screen(screen);

	int i, j;
	for (i = 0; i < 4; i++) {
		SDL_Surface *rotated = rotozoomSurface(ship, players[i].angle, 1,
				SMOOTHING_ON);
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
		draw_score(screen, font, &i);
	}

	update_asteroids(root);
	node * tmp = root;
	for (i = 0; i < 11; i++) {
		if (tmp != NULL) {
			if (i != 0) {
				SDL_BlitSurface(astroid, NULL, screen, &tmp->astroid.rect);
			}
			tmp = tmp->next;
		}
	}
	for (i = 0; i < 4; i++) {
		if (bullets[i].alive == TRUE) {
			if (bullets[i].rect.x > WIDTH - 1 || bullets[i].rect.x < 1
					|| bullets[i].rect.y > HEIGHT || bullets[i].rect.y < 1) {
				bullets[i].alive = FALSE;
			} else {

				bullets[i].rect.x -= sin(bullets[i].angle * PI / 180) * 9;
				bullets[i].rect.y -= cos(bullets[i].angle * PI / 180) * 9;
				SDL_BlitSurface(bullets[i].bullet, NULL, screen,
						&bullets[i].rect);
			}
		}
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (bullets_other[i][j].alive == TRUE) {
				if (bullets_other[i][j].rect.x > WIDTH - 1
						|| bullets_other[i][j].rect.x < 1
						|| bullets_other[i][j].rect.y > HEIGHT
						|| bullets_other[i][j].rect.y < 1) {
					bullets_other[i][j].alive = FALSE;
				} else {
					bullets_other[i][j].rect.x -= sin(
							bullets_other[i][j].angle * PI / 180) * 9;
					bullets_other[i][j].rect.y -= cos(
							bullets_other[i][j].angle * PI / 180) * 9;
					SDL_BlitSurface(bullets_other[i][j].bullet, NULL, screen,
							&bullets_other[i][j].rect);
				}
			}
		}
	}
}

void update(SDL_Rect *player, SDL_Surface *screen, bool *is_running,
		thread_data *thread_recv_info, bullet bullets[], int *cooldown,
		SDL_Surface *bullet_pic) {
	move_player(player, screen, *thread_recv_info, bullets, cooldown,
			bullet_pic);
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
		thread_data thread_recv_info, bullet bullets[], int *cooldown,
		SDL_Surface *bullet_pic) {
	Uint8 *keystates = SDL_GetKeyState(NULL);

	if (keystates[SDLK_UP]) {
		players[thread_recv_info.id].rect.x -= sin(
				players[thread_recv_info.id].angle * PI / 180) * 8;
		players[thread_recv_info.id].rect.y -= cos(
				players[thread_recv_info.id].angle * PI / 180) * 8;

	}
	if (keystates[SDLK_DOWN]) {
		players[thread_recv_info.id].rect.x += sin(
				players[thread_recv_info.id].angle * PI / 180) * 8;
		players[thread_recv_info.id].rect.y += cos(
				players[thread_recv_info.id].angle * PI / 180) * 8;
	}
	if (keystates[SDLK_RIGHT]) {
		players[thread_recv_info.id].angle -= 5;
	}
	if (keystates[SDLK_LEFT]) {
		players[thread_recv_info.id].angle += 5;
	}
	if (keystates[SDLK_SPACE]) {
		int slot = check_bullet_slot(bullets, 4);
		if (*cooldown > 40 && slot != -1) {

			bullets[slot].alive = TRUE;
			bullets[slot].rect = create_rect(
					players[thread_recv_info.id].rect.x + 10,
					players[thread_recv_info.id].rect.y - 10, 25, 25);
			bullets[slot].angle = (int) players[thread_recv_info.id].angle;
			bullets[slot].bullet = bullet_pic;
			printf("Bullets fire %d\n", slot);
			bullet_trans(bullets[slot].rect.x, bullets[slot].rect.y,
					bullets[slot].angle, slot, &thread_recv_info);
			*cooldown = 0;
		}
	}
	*cooldown += 1;
}

int main(int argc, char **arg) {
	srand(time(NULL));
	SDL_Surface *screen, *bullet_pic, *astroid;
	bool is_running = TRUE;
	screen = NULL;
	angle = 0;
	int i, j;

	int x = 1366 / 2 - 50;
	int y = 768 / 2 - 50;
	bullet bullets[5];
	node *root;
	create_linked_list(root);
	fill_list(&root, 0, 0, 11);
	fill_astroid_rect(root, 10, 10);
	int cooldown = 0;

	ship = IMG_Load("Ship.png");
	bullet_pic = IMG_Load("Bullet.png");
	astroid = IMG_Load("Astroid.png");
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
	TTF_Init();
	TTF_Font *font = TTF_OpenFont("SourceSansPro-Black.otf", 18);

	FPSmanager manager = { 0 };
	SDL_initFramerate(&manager);
	SDL_setFramerate(&manager, 60);

	thread_data thread_recv_info;
	thread_recv_info.x = x;
	thread_recv_info.y = y;
	thread_recv_info.ready = 0;
	thread_recv_info.root = root;

	SDL_Thread *net_thread_recv = NULL;
	SDL_Thread *net_thread_trans = NULL;

	for (i = 0; i < 4; i++) {
		players[i].rect = create_rect(-50, -50, 40, 40);
		players[i].angle = 0;
		players[i].score = 0;
	}

	net_thread_recv = SDL_CreateThread(network_recv, &thread_recv_info);

	while (thread_recv_info.ready != 1)
		;
	net_thread_trans = SDL_CreateThread(network_trans, &thread_recv_info);

	if (net_thread_recv == NULL) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
		return -1;
	}

	for (i = 0; i < 4; i++) {
		bullets[i].alive = FALSE;
		bullets[i].rect = create_rect(-10, -10, 25, 25);
		bullets[i].bullet = bullet_pic;
	}

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			bullets_other[i][j].alive = FALSE;
			bullets_other[i][j].rect = create_rect(-10, -10, 25, 25);
			bullets_other[i][j].bullet = bullet_pic;
		}
	}

	//remove_id(&root, 7);
	while (is_running) {
		update(&players[thread_recv_info.id].rect, screen, &is_running,
				&thread_recv_info, bullets, &cooldown, bullet_pic);
		collision(players[thread_recv_info.id].rect, root, NULL, NULL);
		bullet_collision(bullets, root, 4, &thread_recv_info);
		draw(screen, root, bullets, thread_recv_info, astroid, font);
		close_window(&is_running);
		SDL_framerateDelay(&manager);
		SDL_Flip(screen);

	}

	return 0;
}
