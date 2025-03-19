#include "util/res_load.h"

void mesh_load(mesh_t *mesh, const char *filepath) {
    FILE *file = fopen(filepath, "r");
    // assert

    char ln[64];
    while (fgets(ln, sizeof(ln), file)) {
        printf("%s", ln);
    }

    fclose(file);
}