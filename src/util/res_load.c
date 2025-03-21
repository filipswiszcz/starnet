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
            
        } else if (strncmp(ln, "mtllib", 6) == 0) {

        }
    }

    fclose(file);
}