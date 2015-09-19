#ifndef PATH_H_
#define PATH_H_

#include <stdint.h>

#include "array.h"

typedef struct point
{
	uint32_t x;
	uint32_t y;
} point_t;

bool locate_edge(pixel_t start, pixel_t *edge);

array_t *identify_edges(array_t *image)
{
	array_t *edges = malloc(sizeof(array_t));
	edges->ptr = malloc(0);
	edges->size = 0;
	for (size_t i = 0; i < image->size; i++)
	{
		array_t *row = ((array_t *) image->ptr);
		for (size_t j = 0; j < row->size; j++)
		{
			pixel_t pix = ((pixel_t *) row->ptr)[j];
			pixel_t border;
			bool edge_found = locate_edge(pix, &border);
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

bool locate_edge(pixel_t start, pixel_t *edge)
{
	
}

#endif
