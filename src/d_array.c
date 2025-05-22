#include "d_array.h"

// float dynamic array

void float_array_insert(float_array_t *array, float value) {
    if (array -> size >= array -> capacity) {
        if (array -> capacity == 0) array -> capacity = 256;
        else array -> capacity *= 2;
        array -> values = (float*) realloc(array -> values, array -> capacity * sizeof(*array -> values));
    }
    array -> values[array -> size++] = value;
}

// uint32_t dynamic array

void uint32_array_insert(uint32_array_t *array, uint32_t value) {
    if (array -> size >= array -> capacity) {
        if (array -> capacity == 0) array -> capacity = 256;
        else array -> capacity *= 2;
        array -> values = (uint32_t*) realloc(array -> values, array -> capacity * sizeof(*array -> values));
    }
    array -> values[array -> size++] = value;
}