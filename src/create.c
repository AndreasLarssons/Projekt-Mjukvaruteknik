/*
 * create.c
 *
 *  Created on: 9 maj 2014
 *      Author: andreas
 */
#include "create.h"
#include "main.h"

void fire_bullet(bullet * bullet, int player_x, int player_y, Uint8 *keystates) {

	if (keystates[SDLK_SPACE]) {
		bullet->rect.x = player_x;
		bullet->rect.y = player_y;
		bullet->alive = TRUE;
		printf("Bullets fire\n");
	}

}

SDL_Rect create_rect(int x, int y, int width, int height) {
	SDL_Rect rect = { x, y, width, height };
	return rect;
}

int check_bullet_slot(bullet bullets[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (bullets[i].alive == FALSE) {
			return i;
		}
	}
	return -1;
}

bullet create_bullet(SDL_Surface *surface, int player_x, int player_y) {
	bullet bullet;
	SDL_Rect rect = { player_x, player_y, 25, 25 };
	bullet.alive = FALSE;
	bullet.bullet = surface;
	bullet.rect = rect;
	return bullet;
}
void create_stars(star stars[], SDL_Surface *surface, int size) {
	int i;
	for (i = 0; i < size; i++) {
		stars[i].rect = create_rect(i * 70, 0, 5, 5);
		stars[i].velocity = rand() % 5 + 1;
		stars[i].star_pic = surface;
	}
}
