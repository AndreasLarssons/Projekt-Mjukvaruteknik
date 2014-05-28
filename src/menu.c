#include "menu.h"
#include "draw.h"
void applySurface(int x, int y, SDL_Rect *clip, SDL_Surface* source,
		SDL_Surface* destination) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, destination, &offset);
}

SDL_Surface *loadImage(const char *filename) {
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load(filename);

	if (loadedImage != NULL) {
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
		if (optimizedImage != NULL) {
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0xFF,
					0xFF);
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}
	}
	return optimizedImage;
}

void display_text(int x, int y, TTF_Font *font, SDL_Surface *text,
		SDL_Surface *destination) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(text, NULL, destination, &offset);
}

void startMenu() {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Surface *screen = NULL;
	int position = MAIN_MENU;
	bool quit = FALSE;

	SDL_Surface *message[MAX_MESSAGES];
	int messageWidth[MAX_MESSAGES];
	int messageHeight[MAX_MESSAGES];
	int messageCounter;

	SDL_Surface *renderedText[MAX_MESSAGES];
	SDL_Surface *background = NULL;
	SDL_Event event;
	TTF_Font *fontAsteroid28 = NULL;
	TTF_Font *fontAsteroid48 = NULL;

	fontAsteroid28 = TTF_OpenFont("asteroid.ttf", 28);
	fontAsteroid48 = TTF_OpenFont("asteroid.ttf", 48);
	TTF_Font *fontSpaceAge28 = NULL;
	TTF_Font *fontSpaceAge48 = NULL;
	fontSpaceAge28 = TTF_OpenFont("spaceAge.ttf", 28);
	fontSpaceAge48 = TTF_OpenFont("spaceAge.ttf", 48);
	SDL_Color colorWhite = { 0xFF, 0xFF, 0xFF };
	SDL_Color colorRed = { 0xFF, 0x00, 0x00 };
	SDL_Color colorMediumTurquoise = { 72, 209, 204 };

	screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH,
	SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Asteroids", NULL);
	background = loadImage("Intro.jpg");
	renderedText[0] = TTF_RenderText_Blended(fontAsteroid48, "Pear To Pear",
			colorWhite);
	renderedText[1] = TTF_RenderText_Blended(fontAsteroid28, "PLAY",
			colorWhite);
	renderedText[2] = TTF_RenderText_Blended(fontAsteroid28, "PLAY", colorRed);
	renderedText[3] = TTF_RenderText_Blended(fontAsteroid28, "CREDITS",
			colorWhite);
	renderedText[4] = TTF_RenderText_Blended(fontAsteroid28, "CREDITS",
			colorRed);
	renderedText[5] = TTF_RenderText_Blended(fontAsteroid28, "QUIT",
			colorWhite);
	renderedText[6] = TTF_RenderText_Blended(fontAsteroid28, "QUIT", colorRed);
	renderedText[7] = TTF_RenderText_Blended(fontSpaceAge48, "CREDITS",
			colorWhite);
	renderedText[8] = TTF_RenderText_Blended(fontSpaceAge28,
			"GAME, NETWORK AND GRAPHIC DESIGNER", colorMediumTurquoise);
	renderedText[9] = TTF_RenderText_Blended(fontSpaceAge28, "ANDREAS LARSSON",
			colorWhite);
	renderedText[10] = TTF_RenderText_Blended(fontSpaceAge28, "ISAK GUSTAFSSON",
			colorWhite);
	renderedText[11] = TTF_RenderText_Blended(fontSpaceAge28, "MENU DESIGNER",
			colorMediumTurquoise);
	renderedText[12] = TTF_RenderText_Blended(fontSpaceAge28,
			"JOEL YAO HÅKANSSON", colorWhite);
	renderedText[13] = TTF_RenderText_Blended(fontSpaceAge28,
			"GAMEPLAY DESIGNER", colorMediumTurquoise);
	renderedText[14] = TTF_RenderText_Blended(fontSpaceAge28, "DENNIS DRAGOS",
			colorWhite);
	renderedText[15] = TTF_RenderText_Blended(fontSpaceAge28, "GUSTAV SVEDIN",
			colorWhite);
	message[1] = renderedText[1];
	message[2] = renderedText[3];
	message[3] = renderedText[5];
	while (quit == FALSE) {
		SDL_Flip(screen);
		int mouseX = event.motion.x;
		int mouseY = event.motion.y;
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_MOUSEMOTION) {
				if (position == MAIN_MENU) {
					if (mouseX > WIDTH / 2 - messageWidth[1] / 2
							&& mouseX < WIDTH / 2 + messageWidth[1] / 2
							&& mouseY > HEIGHT / 2 - 3 * messageHeight[1] / 2
							&& mouseY < HEIGHT / 2 - messageHeight[1] / 2) {
						message[1] = renderedText[2];
					} else {
						message[1] = renderedText[1];
					}

					if (mouseX > WIDTH / 2 - messageWidth[2] / 2
							&& mouseX < WIDTH / 2 + messageWidth[2] / 2
							&& mouseY > HEIGHT / 2 - messageHeight[2] / 2
							&& mouseY < HEIGHT / 2 + messageHeight[2] / 2) {
						message[2] = renderedText[4];
					} else {
						message[2] = renderedText[3];
					}

					if (mouseX > WIDTH / 2 - messageWidth[3] / 2
							&& mouseX < WIDTH / 2 + messageWidth[3] / 2
							&& mouseY > HEIGHT / 2 + messageHeight[3] / 2
							&& mouseY < HEIGHT / 2 + 3 * messageHeight[3] / 2) {
						message[3] = renderedText[6];
					} else {
						message[3] = renderedText[5];
					}
				}
			} else if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (position == MAIN_MENU) {
						if (mouseX > WIDTH / 2 - messageWidth[1] / 2
								&& mouseX < WIDTH / 2 + messageWidth[1] / 2
								&& mouseY
										> HEIGHT / 2 - 3 * messageHeight[1] / 2
								&& mouseY < HEIGHT / 2 - messageHeight[1] / 2) {
							position = GAME;
						} else if (mouseX > WIDTH / 2 - messageWidth[2] / 2
								&& mouseX < WIDTH / 2 + messageWidth[2] / 2
								&& mouseY > HEIGHT / 2 - messageHeight[2] / 2
								&& mouseY < HEIGHT / 2 + messageHeight[2] / 2) {
							position = CREDITS;
						} else if (mouseX > WIDTH / 2 - messageWidth[3] / 2
								&& mouseX < WIDTH / 2 + messageWidth[3] / 2
								&& mouseY > HEIGHT / 2 + messageHeight[3] / 2
								&& mouseY
										< HEIGHT / 2
												+ 3 * messageHeight[3] / 2) {
							quit = TRUE;
						}
					}
				}
			} else if (event.type == SDL_KEYDOWN) {
				if (position == MAIN_MENU) {
					if (event.key.keysym.sym == SDLK_p) {
						position = GAME;
					} else if (event.key.keysym.sym == SDLK_c) {
						position = CREDITS;
					} else if (event.key.keysym.sym == SDLK_q) {
						quit = TRUE;
					}
				} else if (position == GAME) {
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						message[0] = renderedText[0];
						message[1] = renderedText[1];
						message[2] = renderedText[3];
						message[3] = renderedText[5];
						position = MAIN_MENU;
					}
				} else if (position == CREDITS) {
					if (event.key.keysym.sym == SDLK_e
							|| event.key.keysym.sym == SDLK_ESCAPE) {
						message[0] = renderedText[0];
						message[1] = renderedText[1];
						message[2] = renderedText[3];
						message[3] = renderedText[5];
						position = MAIN_MENU;
					}
				}
			} else if (event.type == SDL_QUIT) {
				quit = TRUE;
			}
		}
		switch (position) {
		int data;
		case MAIN_MENU:
			SDL_FillRect(screen, NULL,
					SDL_MapRGB(screen->format, 0x00, 0x00, 0xFF));
			message[0] = renderedText[0];
			TTF_SizeText(fontAsteroid48, "Pear To Pear", &messageWidth[0],
					&messageHeight[0]);
			TTF_SizeText(fontAsteroid28, "PLAY", &messageWidth[1],
					&messageHeight[1]);
			TTF_SizeText(fontAsteroid28, "CREDITS", &messageWidth[2],
					&messageHeight[2]);
			TTF_SizeText(fontAsteroid28, "QUIT", &messageWidth[3],
					&messageHeight[3]);
			applySurface(0, 0, NULL, background, screen);
			applySurface(WIDTH / 2 - messageWidth[0] / 2,
			HEIGHT / 4 - messageHeight[0] / 2, NULL, message[0], screen);
			applySurface(WIDTH / 2 - messageWidth[1] / 2,
			HEIGHT / 2 - 3 * messageHeight[1] / 2, NULL, message[1], screen);
			applySurface(WIDTH / 2 - messageWidth[2] / 2,
			HEIGHT / 2 - messageHeight[2] / 2, NULL, message[2], screen);
			applySurface(WIDTH / 2 - messageWidth[3] / 2,
			HEIGHT / 2 + messageHeight[3] / 2, NULL, message[3], screen);
			break;
		case GAME:
			data = game();
			if (data != 1) {
				SDL_Surface *text = TTF_RenderText_Solid(fontSpaceAge28,
						"Connection Failed", colorWhite);
				display_text(500, 600, fontSpaceAge28, text, screen);
				SDL_Flip(screen);
				SDL_Delay(1000);
				position = MAIN_MENU;
			} else {
				SDL_Surface *text = TTF_RenderText_Solid(fontSpaceAge28,
						"Why no play?", colorWhite);
				display_text(500, 600, fontSpaceAge28, text, screen);
				SDL_Flip(screen);
				SDL_Delay(1000);
				position = MAIN_MENU;
			}
			break;
		case CREDITS:
			SDL_FillRect(screen, NULL,
					SDL_MapRGB(screen->format, 0x00, 0x00, 0xFF));
			TTF_SizeText(fontSpaceAge48, "CREDITS", &messageWidth[0],
					&messageHeight[0]);
			TTF_SizeText(fontAsteroid28,
					"GAMEPLAY, NETWORK AND GRAPHIC DESIGNER", &messageWidth[1],
					&messageHeight[1]);
			TTF_SizeText(fontAsteroid28, "ANDREAS LARSSON", &messageWidth[2],
					&messageHeight[2]);
			TTF_SizeText(fontAsteroid28, "ISAK GUSTAFSON", &messageWidth[3],
					&messageHeight[3]);
			TTF_SizeText(fontAsteroid28, "MENU DESIGNER", &messageWidth[4],
					&messageHeight[4]);
			TTF_SizeText(fontAsteroid28, "JOEL YAO HÅKANSSON", &messageWidth[5],
					&messageHeight[5]);
			TTF_SizeText(fontAsteroid28, "GAMEPLAY DESIGNER", &messageWidth[6],
					&messageHeight[6]);
			TTF_SizeText(fontAsteroid28, "GUSTAV SVEDIN", &messageWidth[7],
					&messageHeight[7]);
			TTF_SizeText(fontAsteroid28, "DENNIS DRAGOS", &messageWidth[8],
					&messageHeight[8]);
			applySurface(0, 0, NULL, background, screen);
			for (messageCounter = 0; messageCounter < 9; messageCounter++) {
				message[messageCounter] = renderedText[messageCounter + 7];
				applySurface(WIDTH / 2 - messageWidth[messageCounter] / 2,
						(1 + 2 * messageCounter)
								* messageHeight[messageCounter],
						NULL, message[messageCounter], screen);
			}
			break;
		}
	}
	for (messageCounter = 0; messageCounter < MAX_MESSAGES; messageCounter++) {
		SDL_FreeSurface(renderedText[messageCounter]);
	}
	SDL_FreeSurface(background);
	TTF_CloseFont(fontAsteroid28);
	TTF_CloseFont(fontAsteroid48);
	TTF_CloseFont(fontSpaceAge28);
	TTF_CloseFont(fontSpaceAge48);
	TTF_Quit();
	SDL_Quit();
}
