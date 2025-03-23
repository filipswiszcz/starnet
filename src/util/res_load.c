#include "util/res_load.h"

void mesh_load(mesh_t *mesh, const char *filepath) {
    FILE *file = fopen(filepath, "r");
    // assert

    char ln[64];
    while (fgets(ln, sizeof(ln), file)) {
        if (strncmp(ln, "v ", 2) == 0) {
            float x, y, z;
            sscanf(ln, "v %f %f %f", &x, &y, &z);
            farray_add(&mesh -> vertices, x);
            farray_add(&mesh -> vertices, y);
            farray_add(&mesh -> vertices, z);
        } else if (strncmp(ln, "f", 1) == 0) {
            _mesh_get_indices(&mesh -> indices, ln);
        } else if (strncmp(ln, "mtllib", 6) == 0) {
            char path[256];
            sscanf(ln, "mtllib %s", path);
            _mesh_get_material(mesh -> material, path);
        }
    }

    fclose(file);
}

void _mesh_get_indices(iarray_t *arr, char ln[64]) {
    int g = 0, c = 0;
    for (int i = 0; i < 64; i++) {
        if (ln[i] == '/' && g == 0) g = 1;
        else if (ln[i] == '/' && g == 1) {
            int l = (i + c) - i;
            char *sub = (char*) malloc(l + 1);
            strncpy(sub, &ln[i - c], l);
            sub[l] = '\0';
            uint32_t val = strtoul(sub, NULL, 0);
            iarray_add(arr, val);
            free(sub);
            g = 0; c = 0;
        } else if (g == 1) c += 1;
    }
}

void _mesh_get_material(material_t material, const char *filepath) {
    FILE *file = fopen(filepath, "r");
    // assert

    char ln[64];
    while (fgets(ln, sizeof(ln), file)) {
        if (strncmp(ln, "Ns", 2) == 0) {
            sscanf(ln, "Ns %f", &material.shininess);
        } else if (strncmp(ln, "Ka", 2) == 0) {
            sscanf(ln, "Ka %f %f %f", &material.ambient.x, &material.ambient.y, &material.ambient.z);
        }

    }
    fclose(file);
}