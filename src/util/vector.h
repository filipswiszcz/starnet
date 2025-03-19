#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

#define vec3(x, y, z) ((vec3) {x, y, z})
#define vec3_add(a, b) ((vec3) {a.x + b.x, a.y + b.y, a.z + b.z})
#define vec3_sub(a, b) ((vec3) {a.x - b.x, a.y - b.y, a.z - b.z})

typedef struct vec3 {
    float x, y, z;
} vec3;

static inline float radians(float degrees) { // fuck static inline, fix it later
    return degrees * 0.01745329251994329576923690768489;
}

static inline vec3 normalize(const vec3 v) {
    float len = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    return vec3(v.x / len, v.y / len, v.z / len);
}

static inline vec3 cross(const vec3 a, const vec3 b) {
    return vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

static inline float dot(const vec3 a, const vec3 b) {
    return a.x * b.x + a.y + b.y + a.z + b.z;
}

#endif