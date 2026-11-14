#pragma once
#include "renderer.h"
#include <stdlib.h>

static inline int renderer_grow_array_impl(renderer *r, void **array, uint32_t count, uint32_t *capacity, size_t elem_size) {
    if (count < *capacity) {
        return 0; 
    }

    uint32_t new_capacity = *capacity ? *capacity * 2 : 16;
    
    void *new_array = realloc(*array, new_capacity * elem_size);
    if (!new_array) {
        return -1;
    }

    *array = new_array;
    *capacity = new_capacity;
    return 0;
}

#define RENDERER_GROW_ARRAY(r, arr, count, cap) \
    renderer_grow_array_impl((r), (void**)&(arr), (count), &(cap), sizeof(*(arr)))