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
    int index = (y * img->width) + x;
    pix.red = pixel[index] & (Uint8)img->format->Rmask;
    pix.blue = pixel[index] & (Uint8)img->format->Bmask;
    pix.green = pixel[index] & (Uint8)img->format->Gmask;
    pix.alpha = pixel[index] & (Uint8)img->format->Amask;
    return pix;
}

Uint32 getPixelFromSurface(SDL_Surface *surf, int x, int y)
{
    Uint32 *pixel = (Uint32*)surf->pixels;

    return pixel[(y * surf->w) + x];
}

struct colorArray* getColorValues(SDL_Surface *surf)
{
    int i, j, k;

    int size = surf->w * surf->h;
    Uint32 colors[size];
    for(i = 0; i < size; i++)
        colors[i] = 0;

    Uint32 pix;
    int currentSize = 0;
    int flag = 0;

    for(i = 0; i < surf->w; i++)
    {
        for(j = 0; j < surf->h; j++)
        {
            pix = getPixelFromSurface(surf, i, j);
            flag = 0;
            for(k = 0; k < currentSize+1; k++)
            {
                if(pix == colors[k])
                {
                    flag = 0;
                    break;
                }
                else if(pix != colors[k])
                    flag = 1;
            }
            if(flag == 1) {
                colors[currentSize] = pix;
                currentSize++;
            }
        }
    }
    
    struct colorArray *ca = malloc(sizeof(struct colorArray));
    ca->array = colors;
    ca->size = currentSize;

    return ca;
}

char* getNameValueFromColor(int pixel)
{
    char* value = "can't find color";
    
    if(pixel == 0xFFFFFF)
        value = "white";
    else if(pixel == 0x000000)
        value = "black";
    else if(pixel >= 0x0000FF && pixel <= 0x669999)
        value = "blue";
    else if(pixel >= 0xFF0000 && pixel <= 0x330000)
        value = "red";
    else if(pixel >= 0x001100 && pixel <= 0x00FFFF)
        value = "green";
    else if(pixel >= 0x6600CC && pixel <= 0x990099)
        value = "purple";
    else if(pixel >= 0xCCCC00 && pixel <= 0xFFFF00)
        value = "yellow";

    return value;
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
