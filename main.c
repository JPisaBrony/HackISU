#include "globals.h"

#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "image.h"
#include "array.h"

#include "sdl_functions.h"

typedef struct color_range
{
	uint32_t upper_bound; // inclusive
	uint32_t lower_bound; // exclusive, but inclusive if 0
	char *name;
} color_range_t;

// returns an array of ptrs-to-color_range_t types.
color_range *load_config(size_t *range_count);
char *getNameValueFromColor(int pixel, color_range *options, size_t options_count);

int main(int argc, char* args[])
{
    // check if there is a file supplied
    if(argc < 2)
    {
        printf("No file supplied\n");
        return 0;
    }

    size_t range_count = 0;
    color_range_t *ranges = load_config(&range_count);
    
    // initilize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    // create blank surface
    SDL_Surface *screen = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    // load image
    SDL_Surface* img = loadImageForDisplay(args[1], screen);
    // create image structure from surface
    struct image *img2 = createImageInfo(img);
    
    struct colorArray *ca = getColorValues(img);
    
    SDL_FreeSurface(img);
    
    int i;
    char* ca2[ca->size];
    
    for(i = 0; i < ca->size; i++)
        ca2[i] = 0;

    int currentValue = 0;

    for(i = 0; i < ca->size; i++)
    {
        /*
        char* compare = getNameValueFromColor(ca2[i]);
        char* compare2 = getNameValueFromColor(ca->array[i]);
        if(strcmp(compare, compare2) == 0)
        {
            ca2[currentValue] = compare;
            currentValue++;
        }*/
        printf("Number: %d Name: %s\n", ca->array[i], getNameValueFromColor(ca->array[i]));

    }
    /*
    for(i = 0; i < currentValue; i++)
    {
        printf("Name: %s\n", ca2[i]);
    }*/
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

char* getNameValueFromColor(int pixel, color_range_t *options, size_t opt_count)
{
    char value[128];
    bool set = false;
    for (size_t i = 0; i < opt_count; i++)
    {
        color_range_t opt = options[i];
	if ((pixel > opt.lower_bound || (pixel == opt.lower_bound && pixel == 0)) && // lower bound is inclusive iff 0.
		(pixel >= opt.upper_bound))
	{
		strcpy(value, opt.name);
		set = true;
		break;
	}
    }
    if (!set)
    {
	value = "can't find color";
    }
    return value;
}

color_range_t *load_config(size_t *config)
{
	FILE *fp = fopen("config.cfg", "r");
	char name[128];
	color_range_t *ranges = malloc(sizeof(color_range_t) * 64);
	while (fscanf(fp, "%s\n", line) != NULL
}
