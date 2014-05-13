/*
 * collision.c
 *
 *  Created on: 7 maj 2014
 *      Author: andreas
 */
#include "collision.h"
#include "helperfunc.h"
#include "create.h"
SDL_Rect create_hitbox(SDL_Rect hitbox){
	SDL_Rect new_box;
	new_box.x = hitbox.x + 1;
	new_box.y = hitbox.y + 1;
	new_box.w = hitbox.w - 1;
	new_box.h = hitbox.h - 1;
	return new_box;
}

int hit_test(SDL_Rect source, SDL_Rect target){
	if (source.x + source.w > target.x && source.x <= target.x + target.w){
		if (source.y + source.h >= target.y && source.y <= target.y + target.h){
			return 1;
		}
		return -1;
	}
	return -1;
}

void collision (SDL_Rect player,node * root){
	int i = 0;
	node * tmp = root;
	for (i = 0; i < 10; i++){
		if (hit_test(player, tmp->astroid.rect) != -1){
			//printf("Collision + %d\n " , i);
		}
	tmp = tmp->next;
	}
//	if (hit_test(player, target) != -1){
//		printf("Collision\n");
//	}
}

void bullet_collision(bullet bullets[],node * root, int size){
	int i;
	for (i = 0; i < size; i++){
		if (bullets[i].alive == TRUE){
			collision(bullets[i].rect, root);
		}

	}
}
