#include "draw.h"
#include "main.h"
void draw_screen(SDL_Surface *screen) {

	Uint32 color = SDL_MapRGB(screen->format, 0, 125, 255);
	SDL_FillRect(screen, NULL, color);

}

SDL_Rect draw_rect(SDL_Surface *screen, SDL_Rect *rect) {

	SDL_FillRect(screen, rect, SDL_MapRGB(screen->format, 0, 0, 0));
	return *rect;
}
SDL_Rect create_rect(int x, int y, int width, int height) {
	SDL_Rect rect = { x, y, width, height };
	return rect;
}
SDL_Surface *load_image(char *filename) {
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename);

	if (loadedImage != NULL) {
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}

void draw_bullet(SDL_Rect *bullet, bool *alive, SDL_Surface *shot,
		SDL_Surface *screen) {
	if (*alive) {
		apply_surface(bullet->x, bullet->y, shot, screen);
	}
}

void apply_surface(int x, int y, SDL_Surface *ship, SDL_Surface *screen) {
	SDL_Rect temp;
	temp.x = x;
	temp.y = y;
	SDL_BlitSurface(ship, NULL, screen, &temp);
}

//void apply_surface(SDL_Surface *ship, SDL_Surface *screen, SDL_Rect *player) {
//
//	SDL_BlitSurface(ship, NULL, screen, player);
//}

//SDL_Surface *rotate (SDL_Surface *s, SDL_Surface *pic, double angle, double zoom)
//{
//  SDL_Surface *tmp;
//  SDL_Rect tmpRect;
//  int w, h;
//  tmpRect = pic->clip_rect;
//  rotozoomSurfaceSize (players[0].w,  players[0].h, angle, zoom, &w, &h);
//  if ( (w < 1366) && (h < 768) )
//    {
//      tmp = rotozoomSurface (pic, angle, zoom, SMOOTHING_ON);
//      players[0] = tmp->clip_rect;
//
//      players[0].x = (1366 - players[0].w) / 2;
//      players[0].y = (786 - players[0].h) / 2;
//
//      //update_rect(s, tmp);
//      SDL_FreeSurface (tmp);
//      return NULL;
//    }
//  return NULL;
//  printf("%d, %d\n", w, h);
//}

//void rotate(SDL_Surface *ship, double angle) {
//	//SDL_FreeSurface( ship );
//	printf("%f", angle);
//	ship = rotozoomSurface(ship, angle,1,SMOOTHING_ON);
//	printf("%d, %d \n", ship->w, ship->h);
//}
//
//void update_rect(SDL_Surface *screen, SDL_Surface *pic) {
//	SDL_Rect rect;
//	//players[0] = pic->clip_rect;
//	players[0].x = (1366 - players[0].w) / 2;
//	players[0].y = (786 - players[0].h) / 2;
//	SDL_BlitSurface(pic, NULL, screen, &players[0]);
//	SDL_UpdateRect(screen, 0, 0, 1366, 768);
//}

