/*
 * helperfunc.c
 *
 * Created on: 28 apr 2014
 * Author: andreas
 */
#include "helperfunc.h"
#include "draw.h"
#include <stdlib.h>
#define VELOCITY 10

void create_linked_list(node *root) {
	root = malloc(sizeof(node));
	root->next = NULL;
}

void fill_list(node **root, float x, float y, int size) {
	int i;
	for (i = 0; i < size; i++) {
		add_item_beginning(root, x, y, i);
		if (i == 0) {
			(*root)->next = NULL;
		}
	}
}

void add_item_beginning(node ** root, float x, float y, int id) {
	node * new_node;
	astroid * new_astroid;
	new_node = malloc(sizeof(node));
	new_astroid = malloc(sizeof(astroid));
	new_astroid->id = id;
// new_astroid->image = image;
	new_astroid->velocity = VELOCITY;
	new_astroid->rect.x = x;
	new_astroid->rect.y = y;
	new_node->astroid = *new_astroid;
	new_node->next = *root;
	*root = new_node;
}

int search_id(node * root, int id) {
	node * current = root;
	int pos;
	while (current != NULL) {
		if (current->astroid.id == id) {
			return pos;
		}
		current = current->next;
		pos++;
		//printf("%d\n", pos);
	}
	return -1;

}
node *search_node(node * root, int id) {
	node * current = root;
	int i;
	for (i = 0; i < 11; i++) {
		if (current != NULL) {
			if (current->astroid.id == id) {
				return current;

			}
			current = current->next;
		}

	}
	return NULL;
	//printf("HÄR!\n");

}

int remove_id(node ** root, int id) {
	node * current = *root;
	node * temp_node = NULL;
	int pos = search_id(*root, id);
	int i;
	//printf("%d\n", id);
	if (pos > 0) {
		for (i = 0; i < pos - 1; i++) {
			if (current == NULL) {
				printf("ERROR IN LINKED ARRAY!\n");
				return -1;
			}
			current = current->next;
		}
		temp_node = current->next;
		current->next = temp_node->next;
		free(temp_node);
	} else if (pos == 0) {
		if (*root != NULL) {
			*root = (*root)->next;
			//free(current);
		}
	}
	return 0;
}

void fill_astroid_rect(node *root, int w, int h) {
	node * iterate = root;
	int i;
	for (i = 0; i < 10; i++) {
		iterate->astroid.rect = create_rect(-50, -50, w, h);
		iterate->astroid.velocity = 0;
		iterate = iterate->next;
	}
}

void set_asteroids(node *root) {
	node * iterate = root;
	int i;
	for (i = 0; i < 11; i++) {
		if (iterate != NULL) {
			if (i != 0) {
				iterate->astroid.rect.x = i * 150;
				iterate->astroid.rect.y = rand() % 5 + 1;
				iterate->astroid.velocity = rand() % 2 + 1;
				iterate = iterate->next;
			}
		}
	}
}
