#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// global variables
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

// function declarations
bool init();
bool loadMedia();
void closer();

bool init(){
	bool success = true;

	if (SDL_Init (SDL_INIT_VIDEO) < 0){
		printf ("Error\n");
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow ("Bulla", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf ("Error. SDL Error:%s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia(){
	bool success = true;
	
	gHelloWorld = SDL_LoadBMP ("Bart-long-auction-clydesdale-04.bmp");
	if (gHelloWorld == NULL){
		printf ("Error\n");
		success = false;
	}	

	return success;
}

void closer(){
	SDL_FreeSurface (gHelloWorld);
	gHelloWorld = NULL;
	SDL_DestroyWindow (gWindow);
	gWindow = NULL;
	SDL_Quit();
}

int main(){
	if (!init()){
		printf ("There was a problem.\n");
	}
	else {
		if (!loadMedia()){
			printf ("There was a different problem.\n");
		}
		else{
			SDL_BlitSurface (gHelloWorld, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface (gWindow);
			SDL_Delay (2000);
		}
	}
	closer();

	return 0;
}
