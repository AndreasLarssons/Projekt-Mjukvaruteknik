/*
 * network.h
 *
 *  Created on: Apr 23, 2014
 *      Author: isak
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <SDL/SDL_net.h>

typedef struct thread_data{
	TCPsocket tcpsock;
	int thread_id;
	SDL_Rect other_player;
}thread_data;

extern int network_recv();
extern void cord_trans();
extern SDL_Rect players[4];

#endif /* NETWORK_H_ */
