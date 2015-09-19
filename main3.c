#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Event event;

SDL_Window *window = NULL;

SDL_Surface *screen = NULL;

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800


int init()
{
    // initilze sdl
    SDL_Init(SDL_INIT_EVERYTHING);
    
    window = window = SDL_CreateWindow("Hack ISU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

    if(window == NULL)
        exit(1);

    screen = SDL_GetWindowSurface(window);

    if(screen == NULL)
        exit(2);
}

SDL_Surface* loadImage(char* filename)
{
    SDL_Surface *opt_img = NULL;

    int flags = IMG_INIT_PNG;

    if(!IMG_Init(flags) & flags)
    {
        SDL_Surface *img = IMG_Load(filename);
        if(img == NULL)
        {
            printf("can't load loadImage");
            exit(3);
        }
        opt_img = SDL_ConvertSurface(img, screen->format, NULL);
        SDL_FreeSurface(img);
    }
    
    return opt_img;
}

int main()
{
    init();

    SDL_Rect rect;
    SDL_Surface* img = loadImage("twi.jpg");
    rect.x = 0;
    rect.y = 0;
    SDL_BlitSurface(img, NULL, screen, &rect);

    while(1)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                SDL_Quit();
                return 0;
            }
        }
    }

    SDL_Quit();
    return 0;
}
