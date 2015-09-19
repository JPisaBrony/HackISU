#include "pattern.h"

typedef struct lab_pixel_t
{
	double L;
	double a;
	double b;
} lab_pixel_t;

typdef struct xyz_pixel_t
{
	double x;
	double y;
	double z;
} xyz_pixel_t;

xyz_pixel_t rgb2xyz(pixel_t pixel);
lab_pixel_t xyz2lab(xyz_pixel_t pixel);

xyz_pixel_t lab2xyz(lab_pixel_t pixel);
pixel_t xyz2rgb(xyz_pixel_t pixel)

double running_avg(double last_avg, double x, double n)

pixel_t get_color(array_t *image, size_t bitdepth)
{
	uint32_t pixel_num = 0;
	lab_pixel_t *avg = NULL;
	for (size_t i = 0; i < image->size; i++)
	{
		array_t *row = ((array_t *) image->ptr);
		for (size_t j = 0; j < row->size; j++)
		{
			pixel_num++;
			pixel_t rgb = ((pixel_t *) row->ptr)[j];
			xyz_pixel_t xyz = rgb_to_xyz(rgb);
			lab_pixel_t lab = xyz_to_lab(xyz);
			if (avg == NULL)
			{
				avg = malloc(sizeof(lab_pixel_t));
				*avg = lab;
			}
			else
			{
				avg->L = running_avg(avg->L, lab->L, pixel_num);
				avg->a = running_avg(avg->a, lab->a, pixel_num);
				avg->b = running_avg(avg->b, lab->b, pixel_num);
			}
		}
	}
	xyz_pixel_t xyz_avg = lab_to_xyz(*avg);
	return xyz_to_rgb(xyz_avg);
}
