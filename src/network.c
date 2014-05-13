/*
 * network.c
 *
 *  Created on: Apr 23, 2014
 *      Author: isak
 */

#include "network.h"
#define MAX_LENGTH 1024



int network_recv(void *data){
	char msg[MAX_LENGTH];
	//SDL_Rect other_player = create_rect(0, 0, 10, 10);
	int id = 0, x = 0, y = 0, slot;
	int angle = 0;

	thread_data *thread_info = (thread_data *)data;

	// Connects to localhost at port 9999 (client)
	IPaddress ip;

	// Connects to Server
	if(SDLNet_ResolveHost(&ip, "127.0.0.1", 9999) == -1){
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(1);
	}

	thread_info->tcpsock = SDLNet_TCP_Open(&ip);
	while(!(thread_info->tcpsock)){
		//printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		thread_info->tcpsock = SDLNet_TCP_Open(&ip);
	}

	SDLNet_TCP_Recv(thread_info->tcpsock, msg, MAX_LENGTH);
//	int i, counter = 0;
//	for(i = 0; i < 5; i++){
//		if(msg[i] == '#'){
//			counter++;
//		}
//	}

	while(sscanf(msg, "#|%d|#", &thread_info->id) != 1){
		SDLNet_TCP_Recv(thread_info->tcpsock, msg, MAX_LENGTH);
	}
	printf("\n%d\n", thread_info->id);
	//players[thread_info->id].x = 1366 / 2 - 50;
	//players[thread_info->id].y = 768 / 2 - 50;
	thread_info->ready = 1;

	// Tries to receive a message to the server, if successful it prints the message and sends back a message.
	node * tmp = NULL;
	while(1){
		if(SDLNet_TCP_Recv(thread_info->tcpsock, msg, MAX_LENGTH) <= 0){
			// An error could have occurred.
		}
		else{
			// Data has been received.
			if(sscanf(msg, "#%d|%d|%d|%d#", &id, &x, &y, &angle) == 4){
				if(id != thread_info->id){
					players[id].rect.x = x;
					players[id].rect.y = y;
					players[id].angle = (double) angle;
					//printf("\nid:%d x:%d y:%d\n", id, x, y);
				}
			}
			if(sscanf(msg, "*%d|%d|%d*", &id, &x, &y) == 3){

				tmp = search_node(thread_info->root, id);
				//printf("%d\n",tmp->astroid.id);
				tmp->astroid.rect.x = x;
				tmp->astroid.rect.y = y;
			}
			if(sscanf(msg, "?%d|%d|%d|%d|%d?", &id, &slot, &x, &y, &angle) == 5){
				bullets_other[id][slot].rect.x = x;
				bullets_other[id][slot].rect.y = y;
				bullets_other[id][slot].angle = angle;
				bullets_other[id][slot].alive = TRUE;
				printf("%s \n", msg);
			}
		}
	}

	return 0;
}

int network_trans(void *data){
	thread_data *thread_info = (thread_data *)data;
	while(1){
		SDL_Delay(5);
		cord_trans(thread_info->x, thread_info->y, thread_info);
	}
	return 0;
}

// # is the start and end character of the message.
void cord_trans(int x, int y, thread_data *thread_recv_info){
	char str[20];
	sprintf(str, "#%d|%d|%d|%d#",thread_recv_info->id, players[thread_recv_info->id].rect.x, players[thread_recv_info->id].rect.y
			, (int)players[thread_recv_info->id].angle);
	SDLNet_TCP_Send(thread_recv_info->tcpsock, str, 20);
	//printf("\n%s\n", str);
}

void bullet_trans(int x, int y, int angle, int slot, thread_data *thread_recv_info){
	char str[20];
	sprintf(str, "?%d|%d|%d|%d|%d?", thread_recv_info->id, slot, x, y, angle);
	SDLNet_TCP_Send(thread_recv_info->tcpsock, str, 20);
	//printf("%s\n", str);
}
