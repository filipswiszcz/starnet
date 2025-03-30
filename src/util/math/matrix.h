#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

#include "util/math/vector.h"

#define mat4(v) ((mat4) {.m = { \
    {v, 0, 0, 0}, \
    {0, v, 0, 0}, \
    {0, 0, v, 0}, \
    {0, 0, 0, v} \
}})

typedef struct mat4 {
    float m[4][4];
} mat4;

void __mat4_read(mat4 m);

mat4 perspective(float fovy, float aspect, float znear, float zfar);

mat4 translate(mat4 m, vec3 v);

mat4 get_look_at(vec3 pos, vec3 targpos, vec3 uppos);

#endif /* MATRIX_H */