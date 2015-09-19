#include "image.h"
#include "array.h"

image_t *img_alloc(size_t width, size_t height, size_t bitdepth)
{
	/*image_t *img = malloc(sizeof(image_t));
	img->pixels = malloc(sizeof(array_t));
	img->pixels->ptr = malloc(sizeof(array_t *) * height);
	img->pixels->size = height;
	for (size_t i = 0; i < height; i++)
	{
		img->pixels->ptr[i] = malloc(sizeof(array_t));
		img->pixels->ptr[i]->ptr = malloc(sizeof(pixel_t *) * width);
		img->pixels->ptr[i]->size = width;
		for (size_t j = 0; j < width; j++)
		{
			img->pixels->ptr[i]->ptr[j] = malloc(sizeof(pixel_t));
		}
	}
	img->bitdepth = bitdepth;
	img->width = width;
	img->height = height;*/
}

pixel_t *img_pixel(const image_t *img, size_t x, size_t y)
{
//	return img->pixels->ptr[y]->ptr[x];
	return NULL;
}

void img_free(image_t *img)
{
	/*for (size_t i = 0; i < img->height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			free(img->pixels->ptr[i]->ptr[j]);
		}
		free(img->pixels->ptr[i]->ptr);
		free(img->pixels->ptr[i];
	}
	free(img->pixels->ptr);
	free(img->pixels);
	free(img);*/
}
