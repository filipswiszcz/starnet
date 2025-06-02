#ifndef __D_ARRAY_H__
#define __D_ARRAY_H__

#include <stdlib.h>

typedef struct float_array {
    float *values;
    size_t size, capacity;
} float_array_t;

void d_float_array_insert(float_array_t *array, float value);

typedef struct uint32_array {
    uint32_t *values;
    size_t size, capacity;
} uint32_array_t;

void d_uint32_array_insert(uint32_array_t *array, uint32_t value);

typedef struct vertex vertex_t;

typedef struct vertex_array {
    vertex_t *values;
    size_t size, capacity;
} vertex_array_t;

void d_vertex_array_insert(vertex_array_t *array, vertex_t value);

#endif // !__D_ARRAY_H__