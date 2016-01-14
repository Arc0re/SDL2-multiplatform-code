#include <SDL.h>
#include <stdio.h>

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define WIN_TITLE "SDL multiplatfrom code"

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	SDL_Init(SDL_INIT_VIDEO); // We don't need the other "modules"

	window = SDL_CreateWindow(WIN_TITLE,
							  SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED,
							  WIN_WIDTH, WIN_HEIGHT,
							  SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

	// Always check
	if(window == NULL){
		printf("Cannot create window: %s\n", SDL_GetError());
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Especially here
	if(renderer == NULL){
		printf("Cannot create renderer: %s\n", SDL_GetError());
	}

	while(1){
		SDL_Event event;

		// Without a simple loop to catch this event, it'll freeze on OSX.
		// It'll not even "show" a window with borders.
		if(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				break;
			}
		}

		SDL_RenderClear(renderer); // Flush
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); // Change bg color, just to test
		SDL_RenderPresent(renderer);
	}

	// No leaks
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
