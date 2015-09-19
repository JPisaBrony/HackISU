#ifndef ARRAY_H_
#define ARRAY_H_

#include <stddet.h>

typedef struct array_t
{
	void *elems;
	size_t length;
	size_t elem_size;
} array_t;

// allocs an array
//
// elem_size is size of an individual element
//  Ex:
//   sizeof(int *) - for an array of ptrs-to-int
//   sizeof(int) - for an array of ints
array_t *arr_alloc(size_t elem_size, size_t length);

// allocs an array's elements (only do this if arr is an array of ptrs)
//
// elem_deref_size is the size of the type type that each element of arr
// points to.
//  Ex:
//   sizeof(int) if arr is an array of ptrs-to-int
void arr_alloc_elems(array_t *arr, size_t elem_deref_size);

// resizes an array (does NOT de-alloc elems that are lost due to the length
// becoming shorter).
void arr_resize(array_t *arr, size_t length);

// resizes an array. First de-allocs any elems that are lost due to the length
// becoming shorter.
void arr_resize_safe(array_t *arr, size_t length);

// frees an array's elements
void arr_free_elems(array_t *arr);

// Frees an array.
void arr_free(array_t *arr);

#endif
