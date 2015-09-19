#ifndef IMAGE_H_
#define IMAGE_H_

//#include "array.h"

typedef struct pixel_t
{
	uint8_t red;
	uint8_t blue;
	uint8_t green;
	uint8_t alpha;
} pixel_t;

typedef struct image
{
	Uint32 *pixels;
    SDL_PixelFormat *format;
	uint8_t bitdepth;
	int width;
	int height;
} image_t;

image_t *img_malloc(size_t width, size_t height, size_t bitdepth);
pixel_t *img_pixel(const image_t *img, size_t x, size_t y);
void img_free(image_t *img);

#endif
