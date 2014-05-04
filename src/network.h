/*
 * network.h
 *
 *  Created on: Apr 23, 2014
 *      Author: isak
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <SDL/SDL_net.h>
#include "helperfunc.h"

typedef struct thread_data{
	TCPsocket tcpsock;
	int id, x, y, ready;
	node *root;
}thread_data;

extern int network_recv();
extern void cord_trans();
extern int network_trans();
extern SDL_Rect players[4];

#endif /* NETWORK_H_ */
