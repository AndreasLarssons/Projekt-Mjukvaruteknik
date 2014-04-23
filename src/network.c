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

	// Connects to localhost at port 9999 (client)
	IPaddress ip;
	TCPsocket tcpsock;

	if(SDLNet_ResolveHost(&ip, "172.20.10.9", 9999) == -1){
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		exit(1);
	}

	tcpsock = SDLNet_TCP_Open(&ip);
	while(!tcpsock){
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		tcpsock = SDLNet_TCP_Open(&ip);
		//exit(2);
	}

	while(1){
		if(SDLNet_TCP_Recv(tcpsock, msg, MAX_LENGTH) <= 0){
			// An error could have occured
		}
		else{
			printf("\n%s\n", msg);
			SDLNet_TCP_Send(tcpsock, trollmsg, 12);
		}

	}

	return 0;
}
