#include "globals.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "image.h"
#include "array.h"

#include "sdl_functions.h"

int main(int argc, char* args[])
{
    // check if there is a file supplied
    //if(argc < 2)
    //{
    //    printf("No file supplied\n");
    //    return 0;
    //}
    
    // initilize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    // create blank surface
    SDL_Surface *screen = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    // load image
    SDL_Surface* img = loadImageForDisplay(args[1], screen);
    // create image structure from surface
    struct image *img2 = createImageInfo(img);
    
    struct colorArray *ca = getColorValues(img);
    
    int i;

    for(i = 0; i < ca->size; i++)
        printf("Colors: %d\n", ca->array[i]);

    /*
    // identify edges
    array_t *edges = identify_edges(img2);
    // print length
	printf("length: %zu\n", edges->length);
    // free up memory
	free(img);
    */
    /*
    // create image structure from surface
    struct image *img2 = createImageInfo(img);
    // print info about structure
    printf("Pixels: %d, Format: %d, BitDepth: %d, Width: %d, Height: %d\n", img2->pixels, img2->format, img2->bitdepth, img2->width, img2->height);
    struct pixel_t p = getPixelFromImage(img2, 0, 0);
    printf("Red: %d, Blue: %d, Green: %d, Alpha: %d\n", p.red, p.blue, p.green, p.alpha);

    // add a black square to image
    int i, j;
    for(i = 0; i < 300; i++)
        for(j = 0; j < 300; j++)
            setImagePixelAtLocation(img2, i, j, 0x000000);

    // save the image from the
    saveImage(img2, "out.png");
    */
    // quit
    SDL_Quit();
    return 0;
}
