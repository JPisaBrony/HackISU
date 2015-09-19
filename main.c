#include "globals.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "image.h"

#include "sdl_functions.h"

int main()
{
    // initilize
    SDL_Window *window = NULL;
    SDL_Surface *screen = NULL;
    SDL_Event event;

    init(&window, &screen);

    SDL_Surface* img = loadImageForDisplay("twi.png", screen);
    struct image *img2 = createImageInfo(img);
    
    printf("Pixels: %d, BitDepth: %d, Width: %d, Height: %d\n", img2->pixels, img2->bitdepth, img2->width, img2->height);
    struct pixel_t p = getPixelFromImage(img2, 0, 0);
    printf("Red: %d, Blue: %d, Green: %d, Alpha: %d\n", p.red, p.blue, p.green, p.alpha);
    
    // while running
    while(1)
    {
        // pool for events
        while(SDL_PollEvent(&event))
        {
            // if window is closed
            if(event.type == SDL_QUIT)
            {
                SDL_FreeSurface(img);
                SDL_Quit();
                return 0;
            }
        }
        // apply image to screen
        SDL_BlitSurface(img, NULL, screen, NULL);
        // update screen
        SDL_UpdateWindowSurface(window);
    }

    SDL_Quit();
    return 0;
}
