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

array_t *identify_edges(image_t *img);

#endif
