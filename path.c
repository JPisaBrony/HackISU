#include "path.h"

double TOLERANCE=10;

bool locate_edge_dir(image_t *img, point_t start, point_t *border, int16_t inc, bool is_horz);
bool locate_edge(image_t *img, point_t start, point_t *border);
double color_dist(pixel_t c1, pixel_t c2);

array_t *identify_edges(image_t *img)
{
	array_t *edges = arr_alloc(sizeof(array_t*), 0);
	point_t start;
	for (start.x = 0; start.x < img->width; start.x++)
	{
		for (start.y = 0; start.y < img->height; start.y++)
		{
			point_t border;
			bool edge_found = locate_edge(img, start, &border);
			if (edge_found)
			{
				array_t path = trace_path(border);
				arr_resize(edges, edges->length + 1);
				((array_t *)edges->elems)[i] = path;
			}
		}
	}
	return edges;
}

bool locate_edge(image_t *img, point_t start, point_t *border)
{
	return	locate_edge_dir(img, start, border, 1, true) ||
		locate_edge_dir(img, start, border, -1, true) ||
		locate_edge_dir(img, start, border, 1, false) ||
		locate_edge_dir(img, start, border, -1, false);
}

bool locate_edge_dir(image_t *img, point_t start, point_t *border, int16_t inc, bool is_horz);
	point_t pos = start;
	uint32_t *val = (is_horz) ? &(pos.x) : &(pos.y);
	uint32_t *startval = (is_horz) ? &(start.x) : &(start.y);
	pixel_t curpixel;
	pixel_t lastpixel;
	bool contiguous = true;
	do
	{
		lastpixel = curpixel;
		curpixel = getPixelFromImage(img, pos.x, pos.y);
		if (*val != *startval)
		{
			contiguous = color_dist(curpixel, lastpixel) < TOLERANCE;
		}
		*val += inc;
	}
	while (pos.x < img->width && pos.y < img->height && contiguous);
	if (!contiguous)
	{
		*val -= inc;
		*border = pos;
		return true;
	}
	else
	{
		return false;
	}
}

// assumes same bit depth
double color_dist(pixel_t c1, pixel_t c2)
{
	return sqrt(pow(c1.red - c2.red, 2) + pow(c1.blue - c2.blue, 2) + pow(c1.green - c2.green, 2));
}

