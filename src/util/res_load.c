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
            char prepath[256], path[128];
            sscanf(ln, "mtllib %s", path);
            strcpy(prepath, ASSETS_DEFAULT_DIR_PATH);
            strcat(prepath, path);
            _mesh_get_material(mesh -> material, prepath);
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
    if (file == NULL) {
        printf("no file"); return;
    }

    char ln[64];
    while (fgets(ln, sizeof(ln), file)) {
        if (strncmp(ln, "Ns", 2) == 0) {
            sscanf(ln, "Ns %f", &material.shininess);
        } else if (strncmp(ln, "Ka", 2) == 0) {
            sscanf(ln, "Ka %f %f %f", &material.ambient.x, &material.ambient.y, &material.ambient.z);
        } else if (strncmp(ln, "Kd", 2) == 0) {
            sscanf(ln, "Kd %f %f %f", &material.diffuse.x, &material.diffuse.y, &material.diffuse.z);
        } else if (strncmp(ln, "Ks", 2) == 0) {
            sscanf(ln, "Ks %f %f %f", &material.specular.x, &material.specular.y, &material.specular.z);
        } else if (strncmp(ln, "Ke", 2) == 0) {
            sscanf(ln, "Ke %f %f %f", &material.emissibity.x, &material.emissibity.y, &material.emissibity.z);
        } else if (strncmp(ln, "Ni", 2) == 0) {
            sscanf(ln, "Ni %f", &material.density);
        } else if (strncmp(ln, "d", 1) == 0) {
            sscanf(ln, "d %f", &material.transparency);
        } else if (strncmp(ln, "illum", 5) == 0) {
            sscanf(ln, "illum %d", &material.illumination);
        }
    }
    fclose(file);
}