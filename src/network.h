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

//This is the function used by the network receive thread to setup a connection to the server and
//where all data from the server is received and processed.
extern int network_recv();

//This functions sends the player's data containing: id, position, angle, points and lives.
extern void cord_trans();

//This is the function used by the network transmit thread to send player data every 5ms.
extern int network_trans();

//This function is used to send data when a bullet has been fired containing: player id, bullet slot, starting position and angle.
extern void bullet_trans();

//This function is used to send data when a asteroid has been destroyed.
//The data contains: player id, asteroid id and bullet slot.
extern void trans_astroid_destroy();

extern player players[4];
extern bullet bullets_other[4][4];

#endif /* NETWORK_H_ */
