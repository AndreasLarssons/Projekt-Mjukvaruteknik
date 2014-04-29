/*
 * network.c
 *
 *  Created on: Apr 23, 2014
 *      Author: isak
 */

#include "network.h"
#define MAX_LENGTH 1024



int network_recv(void *data){
	SDL_Rect network_players[4];
	int tot_net_players = 0;
	char msg[MAX_LENGTH];
	char trollmsg[] = {"TROLOLOLOL!"};
	SDL_Rect other_player;

	thread_data *thread_info = (thread_data *)data;

	// Connects to localhost at port 9999 (client)
	IPaddress ip;
	//TCPsocket *tcpsock = (TCPsocket *)data;

	// Connects to Server
	if(SDLNet_ResolveHost(&ip, "130.229.175.121", 9999) == -1){
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(1);
	}

	thread_info->tcpsock = SDLNet_TCP_Open(&ip);
	while(!(thread_info->tcpsock)){
		//printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		thread_info->tcpsock = SDLNet_TCP_Open(&ip);
	}

	SDLNet_TCP_Recv(thread_info->tcpsock, msg, MAX_LENGTH);
	int i, counter = 0;
	for(i = 0; i < 5; i++){
		if(msg[i] == '#'){
			counter++;
		}
	}
	sscanf(msg, "#|%d|#", &thread_info->thread_id);
	printf("\n%d\n", thread_info->thread_id);

	// Tries to receive a message to the server, if successful it prints the message and sends back a message.
	while(1){
		if(SDLNet_TCP_Recv(thread_info->tcpsock, msg, MAX_LENGTH) <= 0){
			// An error could have occurred.
		}
		else{
			// Data has been received.
			//other_player = create

			//printf("\n%s\n", msg);
			//SDLNet_TCP_Send(*tcpsock, trollmsg, 12);
		}

	}

	return 0;
}

// # indicates that the message is containing player coordinates.
void cord_trans(int x, int y, thread_data *thread_recv_info){
	char str[20];
	sprintf(str, "#%d|%d|%d#",thread_recv_info->thread_id, x, y);
	SDLNet_TCP_Send(thread_recv_info->tcpsock, str, 20);
	//printf("\n%s\n", str);
}
