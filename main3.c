#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// event pooling
SDL_Event event;
// main window
SDL_Window *window = NULL;
// main screen
SDL_Surface *screen = NULL;

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800


int init()
{
    // initilze SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    
    // create main window
    window = window = SDL_CreateWindow("Hack ISU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    
    // check pointers
    if(window == NULL)
        exit(1);
    
    // create main surface
    screen = SDL_GetWindowSurface(window);
    
    // check pointers
    if(screen == NULL)
        exit(2);
}

SDL_Surface* loadImage(char* filename)
{
    // optmized image
    SDL_Surface *opt_img = NULL;
    // image surface
    SDL_Surface *img = IMG_Load(filename);
    // check pointers
    if(img == NULL)
    {
        printf("can't load loadImage");
        exit(3);
    }
    // convert to screen format
    opt_img = SDL_ConvertSurface(img, screen->format, NULL);
    // free old surface
    SDL_FreeSurface(img);
    // return optimized img
    return opt_img;
}

int main()
{
    // initilize
    init();

    SDL_Surface* img = loadImage("twi.png");
   
    // while running
    while(1)
    {
        // pool for events
        while(SDL_PollEvent(&event))
        {
            // if window is closed
            if(event.type == SDL_QUIT)
            {
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
