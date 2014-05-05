#include "draw.h"

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

void apply_surface(SDL_Surface *ship, SDL_Surface *screen, SDL_Rect *player) {

	SDL_BlitSurface(ship, NULL, screen, player);
}
