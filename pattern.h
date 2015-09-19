#ifndef PATTERN_H_
#define PATTERN_H_

#include <stdint.h>

#include "pixel.h"

// image must be an array_t that holds array_ts that holds pixel_ts
//
//
pixel_t get_color(array_t *image, size_t bitdepth);

#endif
