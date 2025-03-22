#ifndef RES_LOAD_H
#define RES_LOAD_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <regex.h>

#include "object/mesh.h"

void mesh_load(mesh_t *mesh, const char *filepath);

void _mesh_get_indices(iarray_t *arr, char ln[64]);

void _mesh_get_material(material_t material, const char *filepath);

#endif /* RES_LOAD_H */