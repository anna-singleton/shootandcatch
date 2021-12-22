#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include "sdl_util.h"

#define SCREENWIDTH 1600
#define SCREENHEIGHT 900

int main()
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    basicSetup(SCREENWIDTH, SCREENHEIGHT,
               (SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_TIMER),
               "your nan", &window, &renderer);

    SDL_Surface* pSurface = IMG_Load("src/triangle.png");
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pSurface);
    SDL_FreeSurface(pSurface);

    SDL_Rect testRect;
    testRect.x = 50;
    testRect.y = 50;

    SDL_QueryTexture(pTexture, NULL, NULL, &testRect.w, &testRect.h);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    char running = 1;

    while(running)
    {
        SDL_RenderClear(renderer);
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE:
                    running = 0;
                    break;
                default:
                    break;
                }
            }
        }

        SDL_RenderCopy(renderer, pTexture, NULL, &testRect);

        SDL_RenderPresent(renderer);
        SDL_Delay(60 / 1000);
    }


    safeQuit(window, renderer);
    return 0;
}
