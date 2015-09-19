#include "array.h"

#include <stdlib.h>
#include <limits.h>

array_t *arr_alloc(size_t elem_size, size_t length)
{
	array_t *arr = malloc(sizeof(array_t));
	arr->length = length;
	arr->elems = malloc(elem_size * length);
	arr->elem_size = elem_size;
	return arr;
}

void arr_alloc_elems(array_t *arr, size_t elem_deref_size)
{
	for (size_t i = 0; i < arr->length; i++)
	{
		((void **) arr->elems)[i] = malloc(elem_deref_size);
	}
}

void arr_resize(array_t *arr, size_t length)
{
	arr->elems = realloc(arr->elems, elem_size * length);
	arr->length = length;
}

void arr_resize_safe(array_t *arr, size_t length)
{
	for (size_t i = length; i < arr->length; i++)
	{
		free(((void **) arr->elems)[i]);
	}
	arr_resize(arr, length);
}

void arr_free_elems(array_t *arr)
{
	for (size_t i = length; i < arr->length; i++)
	{
		free(((void **) arr->elems)[i]);
	}
}

void arr_free(array_t *arr)
{
	free(arr->elems);
	free(arr);
}


