#ifndef PATH_H_
#define PATH_H_

#include <stdint.h>
#include <math.h>

#include "array.h"
#include "image.h"

typedef struct point
{
	uint32_t x;
	uint32_t y;
} point_t;

double TOLERANCE=10;

bool locate_edge(image_t *img, point_t start, point_t *border);
double color_dist(pixel_t c1, pixel_t c2);

array_t *identify_edges(image_t *img)
{
	array_t *edges = malloc(sizeof(array_t));
	edges->ptr = malloc(0);
	edges->size = 0;
	point_t start;
	for (start.x = 0; start.x < img->width; start.x++)
	{
		for (start.y = 0; start.y < img->height; start.y++)
		{
			point_t border;
			bool edge_found = locate_edge(img, start, &border);
			if (edge_found)
			{
				array_t *path = trace_path(border)
				edges->size++;
				edges->ptr = realloc(ptr, sizeof(array_t*) * edges->size);
				((array_t *) edges->ptr)[edges->size - 1] = path;
				
			}
		}
	}
}

bool locate_edge(image_t *img, point_t start, point_t *border)
{
	// dont hit the edge of image
	
}

// assumes same bit depth
double color_dist(pixel_t c1, pixel_t c2)
{
	return sqrt(pow(c1.red - c2.red, 2) + pow(c1.blue - c2.blue, 2) + pow(c1.green - c2.green, 2));
}

#endif
