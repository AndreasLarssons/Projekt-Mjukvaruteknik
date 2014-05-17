/*
 * collision.c
 *
 *  Created on: 7 maj 2014
 *      Author: andreas
 */
#include "collision.h"
#include "helperfunc.h"
#include "create.h"
#include "network.h"
SDL_Rect create_hitbox(SDL_Rect hitbox) {
	SDL_Rect new_box;
	new_box.x = hitbox.x + 1;
	new_box.y = hitbox.y + 1;
	new_box.w = hitbox.w - 1;
	new_box.h = hitbox.h - 1;
	return new_box;
}

int hit_test(SDL_Rect source, SDL_Rect target) {
	if (source.x + source.w > target.x && source.x <= target.x + target.w) {
		if (source.y + source.h >= target.y
				&& source.y <= target.y + target.h) {
			return 1;
		}
		return -1;
	}
	return -1;
}

void collision(SDL_Rect player, node * root, thread_data *thread_info, bool *alive, int *slot) {
	int i = 0;
	node * tmp = root;
	for (i = 0; i < 11; i++) {
		if (tmp != NULL) {
			if (i != 0) {
				if (hit_test(player, tmp->astroid.rect) != -1) {
					//printf("Collision + %d\n ", i);
					if (thread_info != NULL) {
						printf("%d\n", tmp->astroid.id);
						trans_astroid_destroy(tmp, thread_info, slot);
						remove_id(&root, tmp->astroid.id);
						printf("HÄR!\n");
						*alive = FALSE;
						players[thread_info->id].score += 1;
						return;
					}
				}
				tmp = tmp->next;
			}else{
				tmp = tmp->next;
			}
		}
	}
}

void bullet_collision(bullet bullets[], node * root, int size,
		thread_data *thread_info) {
	int i;
	for (i = 0; i < size; i++) {
		if (bullets[i].alive == TRUE) {
			collision(bullets[i].rect, root, thread_info, &bullets[i].alive, &i);
		}

	}
}
