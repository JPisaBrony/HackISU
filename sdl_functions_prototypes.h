#ifndef SDL_FUNCTION_PROTOTYPES
#define SDL_FUNCTION_PROTOTYPES

int init();
SDL_Surface* loadImage(char* filename);
SDL_Surface* loadImageForDisplay(char* filename);
struct image* createImageInfo(SDL_Surface *src);
struct pixel_t getPixelFromImage(struct image *img, int x, int y);

#endif
