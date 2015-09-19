#include "path.h"

double TOLERANCE=10;
size_t EDGE_SEARCH_DIST = 2;


bool locate_edge_dir(image_t *img, point_t start, point_t *border, int16_t inc, bool is_horz);
bool locate_edge(image_t *img, point_t start, point_t *border, bool *is_horz);
double color_dist(pixel_t c1, pixel_t c2);
array_t *trace_path(image_t *img, point_t start);

array_t *identify_edges(image_t *img)
{
	array_t *edges = arr_alloc(sizeof(array_t*), 0);
	point_t start;
	for (start.x = 0; start.x < img->width; start.x++)
	{
		for (start.y = 0; start.y < img->height; start.y++)
		{
			point_t border;
			bool is_horz; // whether edge type is horizontal
			bool edge_found = locate_edge(img, start, &border, &is_horz);
			if (edge_found)
			{
				array_t path = trace_path(img, border, is_horz);
				arr_resize(edges, edges->length + 1);
				((array_t **)edges->elems)[i] = path;
			}
		}
	}
	return edges;
}

bool locate_edge(image_t *img, point_t start, point_t *border, bool *is_horz)
{
	return	(*is_horz = false && locate_edge_dir(img, start, border, 1, true)) ||
		locate_edge_dir(img, start, border, -1, true) ||
		(*is_horz = true && locate_edge_dir(img, start, border, 1, false)) ||
		locate_edge_dir(img, start, border, -1, false);
}

bool locate_edge_dir(image_t *img, point_t start, point_t *border, int16_t inc, bool is_horz)
{
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

bool is_edge(image_t *img, point_t base, point_t check)
{
	pixel_t c1 = getPixelFromImage(img, base.x, base.y);
	pixel_t c2 = getPixelFromImage(img, check.x, check.y);
	if (color_dist(c1, c2) < TOLERANCE)
	{
		uint32_t left = (check.x < 1) ? 0 : check.x - 1;
		uint32_t right = ((img->width - 1) - check.x < 1) ? img->width : check.x + 2;
		uint32_t up = (check.y < 1) ? 0 : check.y - 1;
		uint32_t down = ((img->height - 1) - check.y < 1) ? img->height : check.y + 2;
		point_t bound;
		for (bound.x = left; bound.x < right; bound.x++)
		{
			for (bound.y = up; bound.y < down; bound.y++)
			{
				if (bound.y == check.y && bound.x == check.x) continue;
				if (color_dist(getPixelFromImage(img, bound.x, bound.y), c2) >= TOLERANCE)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool next_edge_point(image_t *img, array_t *visited, size_t visited_cnt, point_t *cur_point)
{
	uint32_t left = (cur_point->x < EDGE_SEARCH_DIST) ? 0 : cur_point->x - EDGE_SEARCH_DIST;
	uint32_t right = ((img->width - 1) - cur_point->x < EDGE_SEARCH_DIST) ? img->width : cur_point->x + EDGE_SEARCH_DIST + 1;
	uint32_t up = (cur_point->y < EDGE_SEARCH_DIST) ? 0 : cur_point->y - EDGE_SEARCH_DIST;
	uint32_t down = ((img->height - 1) - cur_point->y < EDGE_SEARCH_DIST) ? img->height : cur_point->y + EDGE_SEARCH_DIST + 1;
	point_t check;
	array_t *potential = arr_alloc(sizeof(point_t), EDGE_SEARCH_DIST * EDGE_SEARCH_DIST -1);
	size_t pot_count = 0;
	for (check.x = left; check.x < right; check.x++)
	{
		for (check.y = up; check.y < down; check.y++)
		{
			if (check.x == cur_point.x && check.y == cur_point.y) continue;
			if (!is_edge(img, getPixelFromImage(img, check.x, check.y), *cur_point)) continue;
			
			if (visited_cnt > 1)
			{
				bool already_visited = false;
				// if already visited, skip:
				for (size_t i = visited_cnt - 1; i > 0; i++) // reverse because last visited are in last
				{
					point_t vis = ((point_t *) visited->elems)[i];
					if (check.x == vis.x && check.y == vis.y)
					{
						already_visited = true;
						break;
					}
				}
				if (already_visited) continue;
			}
			((point_t *) potential->elems)[pot_count++] = check;
		}
	}
	double close_dist = 1000;
	point_t next;
	arr_resize(potential, pot_count);
	for (size_t i = 0; i < potential->length; i++)
	{
		point_t p = ((point_t *) potential->elems)[i];
		if (sqrt(pow(p.x - cur_point->x, 2) + pow(p.y - cur_point->y, 2)) < close_dist)
		{
			next = p;
		}
	}
	if (pot_count != 0) *cur_point = next;
	arr_free(potential);
	return (pot_count != 0);
}

array_t *trace_path(image_t *img, point_t start, bool is_horz)
{
	size_t count = 0;
	array_t *edge_points = arr_alloc(sizeof(point_t), 20);
	point_t cur = start;
	edge_points->items[count++] = start;
	while (next_edge_point(img, edge_points, count, &cur))
	{
		if (count == edge_points->length)
		{
			arr_resize(edge_points, edge_points->length + 20);
		}
		((point_t *) edge_points->elems)[count++] = cur;
	}
	arr_resize(edge_points, count);
	return edge_points;
}
