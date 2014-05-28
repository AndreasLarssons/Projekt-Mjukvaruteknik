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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "menu.h"
#include <SDL/SDL_mixer.h>

#define STARS 20

char ip_addr[20];
char port_num[20];

void draw(SDL_Surface *screen, node * root, bullet bullets[],
		thread_data thread_recv_info, SDL_Surface *astroid, TTF_Font *font,
		star stars[]) {
	draw_screen(screen);
	int i, j;
	for (i = 0; i < STARS; i++) {
		if (stars[i].rect.y > HEIGHT) {
			stars[i].rect.y = 0;
		}
		stars[i].rect.y += stars[i].velocity;
		SDL_BlitSurface(stars[i].star_pic, NULL, screen, &stars[i].rect);
	}

	for (i = 0; i < 4; i++) {
		if (players[i].lives != 0) {
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
			draw_life(screen, font, &i);
		}
	}

	update_asteroids(root);
	node * tmp = root;
	for (i = 0; i < 11; i++) {
		if (tmp != NULL) {
			if (i != 0) {
				if (tmp->astroid.velocity != 0) {
					SDL_BlitSurface(astroid, NULL, screen, &tmp->astroid.rect);
				}
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
		SDL_Surface *bullet_pic, int allow_movement) {
	move_player(player, screen, *thread_recv_info, bullets, cooldown,
			bullet_pic, allow_movement);
}

void close_window(bool *is_running) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			*is_running = FALSE;
		}
		if (event.key.keysym.sym == SDLK_ESCAPE){
			*is_running = FALSE;
		}
	}
}

void move_player(SDL_Rect *player, SDL_Surface *screen,
		thread_data thread_recv_info, bullet bullets[], int *cooldown,
		SDL_Surface *bullet_pic, int allow_movement) {
	if (allow_movement != 0) {
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
}

int main(int argc, char **arg) {
	printf("Write server IP\n");
	gets(ip_addr);
	printf("Write your PORT\n");
	gets(port_num);
	startMenu();
	return 0;
}
int game() {
	srand(time(NULL));
	SDL_Surface *screen, *bullet_pic, *astroid, *star_pic;
	bool is_running = TRUE;
	screen = NULL;
	angle = 0;
	int i, j;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return 0;
	}
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH,
			SDL_HWSURFACE | SDL_DOUBLEBUF);




	int allow_movement = 1, invincible_bool = TRUE, invincible_cooldown = 0;

	int x = 1366 / 2 - 50;
	int y = 768 / 2 - 50;
	bullet bullets[5];
	node *root;
	create_linked_list(root);
	fill_list(&root, 0, 0, 11);
	fill_astroid_rect(root, 10, 10);
	int cooldown = 0;
	star stars[STARS];

	ship = IMG_Load("Ship.png");
	bullet_pic = IMG_Load("Bullet.png");
	astroid = IMG_Load("Astroid.png");
	star_pic = IMG_Load("Star.png");
	if (!ship) {
		printf("Cannot load file");
	}
	TTF_Font *font = TTF_OpenFont("SourceSansPro-Black.otf", 18);

	FPSmanager manager = { 0 };
	SDL_initFramerate(&manager);
	SDL_setFramerate(&manager, 60);

	thread_data thread_recv_info;
	thread_recv_info.x = x;
	thread_recv_info.y = y;
	thread_recv_info.ready = 0;
	thread_recv_info.root = root;
	thread_recv_info.error = 0;

	SDL_Thread *net_thread_recv = NULL;
	SDL_Thread *net_thread_trans = NULL;

	for (i = 0; i < 4; i++) {
		players[i].rect = create_rect(-50, -50, 40, 40);
		players[i].angle = 0;
		players[i].score = 0;
		players[i].lives = 3;
	}
	create_stars(stars, star_pic, STARS);
	net_thread_recv = SDL_CreateThread(network_recv, &thread_recv_info);
	int timer = 0;
	SDL_Color colorWhite = { 0xFF, 0xFF, 0xFF };
	while (thread_recv_info.ready != 1) {
		timer++;
		SDL_Delay(10);
		if (timer == 400) {
			break;
		}
	}
	if (timer == 400) {
		SDL_KillThread(net_thread_recv);
		return 0;
	}

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

	while (is_running) {
		if (players[thread_recv_info.id].lives != 0) {
			update(&players[thread_recv_info.id].rect, screen, &is_running,
					&thread_recv_info, bullets, &cooldown, bullet_pic,
					allow_movement);
			if (invincible_bool == FALSE) {
				collision(&players[thread_recv_info.id].rect, root,
						&thread_recv_info, NULL, NULL, &allow_movement,
						&invincible_bool);
			}
			// Checks if any bullets has made contact with any asteroids
			bullet_collision(bullets, root, 4, &thread_recv_info);
			// Checks if the player has any immortality active and if he does the timer will count down.
			if (invincible_cooldown < 200 && invincible_bool == TRUE) {
				invincible_cooldown += 1;
				printf("invincible_cooldown: %d\n", invincible_cooldown);
			} else {
				invincible_bool = FALSE;
				invincible_cooldown = 0;
			}
		}
		draw(screen, root, bullets, thread_recv_info, astroid, font, stars);
		close_window(&is_running);

		SDL_framerateDelay(&manager);
		SDL_Flip(screen);

	}
	SDL_KillThread(net_thread_recv);
	SDL_KillThread(net_thread_trans);
	return 1;
}
