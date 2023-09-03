#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_DisplayMode DM;

    if (SDL_GetDesktopDisplayMode(0, &DM) != 0) {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
    }

    SDL_Window *window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);


    /*
        ==== Basic Rectangle ====

        SDL_Rect header;
        header.x = 0;
        header.y = 0;
        header.h = 60;
        header.w = SDL_GetWindowSurface(window)->w;
    */

    bool running = true;

    while (running) {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 19, 19, 19, 255);
        SDL_RenderClear(renderer);

        /*
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(renderer, &header);
        */
	    
		SDL_RenderPresent(renderer);

       while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						running = false;
						break;
					}
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						std::cout << "The left mouse button is currently down" << std::endl;
					}
					break;
				default:
					break;
			}
       }
    }

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

    return 0;
}