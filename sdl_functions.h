#ifndef SDL_FUNCTION_PROTOTYPES
#define SDL_FUNCTION_PROTOTYPES

#include <SDL2/SDL.h>

int init(SDL_Window **window_ptr, SDL_Surface **screen_ptr);
SDL_Surface* loadImage(char* filename);
SDL_Surface* loadImageForDisplay(char* filename, SDL_Surface *screen);
struct image* createImageInfo(SDL_Surface *src);
struct pixel_t getPixelFromImage(struct image *img, int x, int y);

#endif
