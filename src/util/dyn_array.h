#ifndef DYN_ARRAY_H

#include <stdlib.h>

typedef struct farray farray_t;
typedef struct iarray iarray_t;

struct farray {
    float *values;
    size_t k;
    size_t capacity;
};

struct iarray {
    int *values;
    size_t k;
    size_t capacity;
};

void farray_add(farray_t *arr, float val);

void iarray_add(iarray_t *arr, int val);

#endif /* DYN_ARRAY_H */