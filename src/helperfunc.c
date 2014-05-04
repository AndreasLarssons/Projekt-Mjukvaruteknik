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
		printf("%d\n", pos);
	}
	return -1;

}
node *search_node(node * root, int id) {
	node * current = root;
	int i;
	for (i = 0; i < 10; i++){
		if (current->astroid.id == id) {
			return current;

		}
		current = current->next;
	}
	return NULL;

}

int remove_id(node ** root, int id) {
	node * current = *root;
	node * temp_node = NULL;
	int pos = search_id(*root, id);
	int i;
	for (i = 0; i < pos - 1; i++) {
		if (current->next == NULL) {
			return -1;
		}
		current = current->next;
	}
	temp_node = current->next;
	current->next = temp_node->next;
	free(temp_node);
	return 0;
}

void fill_astroid_rect(node *root, int w, int h){
	node * iterate = root;
	int i;
	for (i = 0; i < 10; i++){
		iterate->astroid.rect = create_rect(0, 0, w, h);
		iterate = iterate->next;
	}
}
