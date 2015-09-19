#include "headers_and_globals.h"
#include <stdio.h>
#include "path.h"

int main(int argc, char **argv)
{
	SDL_Init(0);

	image_t *img = createImageInfo(loadImage(argv[1]));

	SDL_Quit();
	
	
	array_t *edges = identify_edges(img);

	printf("length: %d\n", array_t->length);
}
