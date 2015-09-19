#ifndef SDL_FUNCTIONS
#define SDL_FUNCTIONS

#include "sdl_functions.h"
#include "globals.h"
#include "image.h"

#include <SDL2/SDL_image.h>

int init(SDL_Window **window_ptr, SDL_Surface **screen_ptr)
{
    // initilze SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // create main window
    *window_ptr = *window_ptr = SDL_CreateWindow("Hack ISU", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);

    // check pointers
    if(*window_ptr == NULL)
        exit(1);

    // create main surface
    *screen_ptr = SDL_GetWindowSurface(*window_ptr);

    // check pointers
    if(*screen_ptr == NULL)
        exit(2);
}

SDL_Surface* loadImage(char* filename)
{
    // image surface
    SDL_Surface *img = IMG_Load(filename);
    // check pointers
    if(img == NULL)
    {
        printf("can't load '%s': %s\n", filename, IMG_GetError());
        exit(3);
    }
    return img;
}

SDL_Surface* loadImageForDisplay(char* filename, SDL_Surface *screen)
{
    // optmized image
    SDL_Surface *opt_img = NULL;
    // load image
    SDL_Surface *img = loadImage(filename);
    // convert to screen format
    opt_img = SDL_ConvertSurface(img, screen->format, 0);
    // free old surface
    SDL_FreeSurface(img);
    // return optimized img
    return opt_img;
}

struct image* createImageInfo(SDL_Surface *src)
{
    image_t *img = malloc(sizeof(image_t));
    img->pixels = (Uint32*)src->pixels;
    img->format = src->format;
    img->bitdepth = src->format->BitsPerPixel;
    img->width = src->w;
    img->height = src->h;
    return img;
}

struct pixel_t getPixelFromImage(struct image *img, int x, int y)
{
    pixel_t pix;
    Uint32 *pixel = img->pixels;
    int index = y * img->width + x;
    pix.red = pixel[index] & (Uint8)img->format->Rmask;
    pix.blue = pixel[index] & (Uint8)img->format->Gmask;
    pix.green = pixel[index] & (Uint8)img->format->Bmask;
    pix.alpha = pixel[index] & (Uint8)img->format->Amask;
    return pix;
}

void setImagePixelAtLocation(struct image *img, int x, int y, Uint32 newpixel)
{
    Uint32 *pixel = (Uint32*)img->pixels;

    pixel[(y * img->width) + x] = newpixel;
}

void setSurfacePixelAtLocation(SDL_Surface *surf, int x, int y, Uint32 newpixel)
{
    Uint32 *pixel = (Uint32*)surf->pixels;

    pixel[(y * surf->w) + x] = newpixel;
}

SDL_Surface* createSurfaceFromImage(struct image *img)
{
    SDL_Surface *surf = SDL_CreateRGBSurface(
            0,
            img->width,
            img->height,
            img->bitdepth,
            0,
            0,
            0,
            0);

    int i, j;
    for(i = 0; i < img->width; i++)
    {
        for(j = 0; j < img->height; j++)
        {
            setSurfacePixelAtLocation(surf, i, j, img->pixels[(j * img->width) + i]);
        }
    }

    return surf;
}

void saveImage(struct image *img, char* outfile)
{
    SDL_Surface *surf = createSurfaceFromImage(img);
    IMG_SavePNG(surf, outfile);
    SDL_FreeSurface(surf);
}

#endif
