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
#include "main.h"

typedef struct thread_data{
	TCPsocket tcpsock;
	int id, x, y, ready;
	int *error;
	node *root;
}thread_data;

extern int network_recv();
extern void cord_trans();
extern int network_trans();
extern void bullet_trans();
extern player players[4];
extern bullet bullets_other[4][4];

#endif /* NETWORK_H_ */
