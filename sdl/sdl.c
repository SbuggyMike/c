#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main (int argc, char* args[]){
	SDL_Window* window = NULL;

	SDL_Surface* screen_surface = NULL;

	if (SDL_Init (SDL_INIT_VIDEO) < 0)
		printf ("Error\n");
	else
	{
		window = SDL_CreateWindow ("Bulla", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf ("Error. SDL Error:%s\n", SDL_GetError());
		}
		else
		{
			screen_surface = SDL_GetWindowSurface(window);
			SDL_FillRect (screen_surface, NULL, SDL_MapRGB (screen_surface->format, 0xFF, 0xFF, 0xFF));

			SDL_Delay (2000);
		}
	}

	SDL_DestroyWindow (window);
	SDL_Quit();
	return 0;
}


