#ifndef DYN_ARRAY_H
#define DYN_ARRAY_H

#include <stdlib.h>

#include "object/mesh.h"

typedef struct varray varray_t;
typedef struct farray farray_t;
typedef struct iarray iarray_t;
typedef struct carray carray_t;

struct varray {
    vertex_t *values;
    size_t k;
    size_t capacity;
};

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

struct carray {
    char **values;
    size_t k;
    size_t capacity;
};

void varray_add(varray_t *arr, vertex_t val);

void farray_add(farray_t *arr, float val);

void iarray_add(iarray_t *arr, int val);

// void carray_add(carray_t *arr, char *val);

#endif /* DYN_ARRAY_H */