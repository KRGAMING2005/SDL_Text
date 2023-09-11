#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_DisplayMode DM;

    if (SDL_GetDesktopDisplayMode(0, &DM) != 0)
    {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
    }

    SDL_Window *window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    TTF_Font *font = TTF_OpenFont("Roboto-Medium.ttf", 200);
    if (!font)
    {
        std::cout << "Error loading font" << std::endl;
        return 0;
    }

    SDL_Color textColor = {0x00, 0x00, 0x00, 0xFF};
    SDL_Color textBackgroundColor = {0xFF, 0xFF, 0xFF, 0xFF};
    SDL_Texture *text = NULL;
    SDL_Rect textRect;

    SDL_Color white = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Hello World!", white);

    text = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, text, NULL, NULL);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Rect header;
    header.x = 0;
    header.y = 0;
    header.h = 200;
    header.w = SDL_GetWindowSurface(window)->w;

    bool running = true;

    while (running)
    {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 19, 19, 19, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &header);
        SDL_RenderCopy(renderer, text, NULL, &header);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
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

    SDL_DestroyTexture(text);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}