#include "SDL/SDL.h"

int main( int argc, char* args[] )
{
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );
    printf("HEJ");
    //Quit SDL
    SDL_Quit();

    return 0;
}
