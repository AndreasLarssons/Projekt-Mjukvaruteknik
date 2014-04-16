#include "draw.h"


void draw_screen(SDL_Surface *screen) {

	Uint32 color = SDL_MapRGB(screen->format, 0, 125, 255);
	SDL_FillRect(screen, NULL, color);

}

SDL_Rect draw_rect(SDL_Surface *screen, SDL_Rect *rect) {

	SDL_FillRect(screen, rect, SDL_MapRGB(screen->format, 0, 125, 125));
	return *rect;
}
SDL_Rect create_rect(int x, int y , int width, int height){
	SDL_Rect rect = {x,y,width,height};
	return rect;
}
