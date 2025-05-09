#include "util/dyn_array.h"

void varray_add(varray_t *arr, vertex_t val) {
    do {
        if (arr -> k >= arr -> capacity) {
            if (arr -> capacity == 0) arr -> capacity = 64;
            else arr -> capacity *= 2;
            arr -> values = (vertex_t*) realloc(arr -> values, arr -> capacity * sizeof(*arr -> values));
        }
        arr -> values[arr -> k++] = val;
    } while (0);
}

void farray_add(farray_t *arr, float val) {
    do {
        if (arr -> k >= arr -> capacity) {
            if (arr -> capacity == 0) arr -> capacity = 64;
            else arr -> capacity *= 2;
            arr -> values = (float*) realloc(arr -> values, arr -> capacity * sizeof(*arr -> values));
        }
        arr -> values[arr -> k++] = val;
    } while (0);
}

void iarray_add(iarray_t *arr, int val) {
    do {
        if (arr -> k >= arr -> capacity) {
            if (arr -> capacity == 0) arr -> capacity = 64;
            else arr -> capacity *= 2;
            arr -> values = (int*) realloc(arr -> values, arr -> capacity * sizeof(*arr -> values));
        }
        arr -> values[arr -> k++] = val;
    } while (0);
}