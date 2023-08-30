#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_DisplayMode DM;
    if (SDL_GetDesktopDisplayMode(0, &DM) != 0)
    {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        return 1;
    }

    int width = DM.w;
    int height = DM.h;
    int refreshrate = DM.refresh_rate;

    SDL_Window *window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 560, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_SetWindowAlwaysOnTop(window, SDL_TRUE);
    SDL_SetWindowBordered(window, SDL_TRUE);

    SDL_Rect header;
    header.x = 0;
    header.y = 0;
    header.h = 60;
    header.w = SDL_GetWindowSurface(window)->w;

    SDL_Rect select;
    select.x = 20;
    select.y = 300;
    select.h = 60;
    select.w = (SDL_GetWindowSurface(window)->w - 40);

    bool running = true;
    int targetFPS = 165;

    while (running)
    {
        SDL_Event event;

        SDL_Delay(1000 / targetFPS);
        SDL_SetRenderDrawColor(renderer, 19, 19, 19, 255);

        SDL_RenderClear(renderer);

        // Header
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &header);

        // Select
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &select);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (event.button.x > select.x && event.button.x < select.x + select.w && event.button.y > select.y && event.button.y < select.y + select.h)
                    {
                        std::cout << "Inside of select button" << endl;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    select.x += 10;
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    select.x -= 10;
                }
                if (event.key.keysym.sym == SDLK_UP)
                {
                    select.y -= 10;
                }
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    select.y += 10;
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