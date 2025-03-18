#include <stdio.h>
#include <stdint.h>

#include "util/dynarray.h"

typedef struct mesh {
    uint16_t id;
    farray_t vertices;
    iarray_t indices;
} mesh;

void mshload(mesh &mesh, const char *filepath) {
    FILE *file = fopen(filepath, "r");
    // assert

    char ln[64];
    while (fgets(ln, sizeof(ln), file)) {
        printf("%s", ln);
    }

    fclose(file);
}