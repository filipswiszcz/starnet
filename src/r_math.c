#include "r_math.h"

// vec

float r_radians(float degrees) {
    return degrees * 0.01745329251994329576923690768489;
}

vec3_t r_normalize(const vec3_t v) {
    float l = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    if (l < 0.00001f) return vec3(0.0f, 0.0f, 0.0f);
    return vec3(v.x / l, v.y / l, v.z / l);
}

vec3_t r_cross(const vec3_t a, const vec3_t b) {
    return vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

float r_dot(const vec3_t a, const vec3_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// mat

void __r_mat4_read(mat4_t m) {
    for (int i = 0; i < 4; i++) {
        printf("[");
        for (int j = 0; j < 4; j++) {
            printf("%7.2f", m.m[i][j]);
            if (j < 3) printf(" ");
        }
        printf("]\n");
    }
    printf("\n");
}