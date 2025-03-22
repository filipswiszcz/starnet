#ifndef MESH_H
#define MESH_H

#include <stdint.h>

#include "util/dyn_array.h"
#include "util/vector.h"

typedef struct material material_t;

struct material {
    char *name;
    float shininess;
    vec3 ambient, diffuse, specular, emissibity;
    float density, transparency;
    int illumination;
};

typedef struct mesh mesh_t;

struct mesh {
    uint16_t id;
    farray_t vertices;
    iarray_t indices;
    material_t material;
};

struct {
    vec3 scale;
    vec3 rot_origin;
    // quat
    vec3 translation;
} transformation;

typedef struct instance instance_t;

struct {
    uint16_t mesh_id;
    uint16_t transform_id;
} instance;

#endif /* MESH_H */