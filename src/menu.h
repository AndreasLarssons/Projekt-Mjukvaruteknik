#ifndef MENU_H_
#define MENU_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


#define FALSE 0
#define TRUE 1
#define MAX_MESSAGES 20

#define MAIN_MENU 0
#define GAME 1
#define CREDITS 2
#define WIDTH 1366
#define HEIGHT 768
#define DEPTH 32

typedef int bool;

extern void startmenu();
extern void applySurface();
extern SDL_Surface *loadImage();
extern char ip[20];
extern char port[20];
extern void display_text();

#endif

