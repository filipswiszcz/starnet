#include "r_renderer.h"

// mesh

void r_mesh_load(mesh_t *mesh, char *filepath) {
    FILE *file = fopen(filepath, "r");

    // assert

    char line[64];
    while (fgets(line, sizeof(line), file)) {
        vertex_t vertex;
        if (strncmp(line, "v ", 2) == 0) {
            vec3_t position;
            sscanf(line, "v %f %f %f", &position.x, &position.y, &position.z);
            vertex.position = position;
        } else if (strncmp(line, "vn", 2) == 0) {
            vec3_t normal;
            sscanf(line, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
            vertex.normal = normal;
        } else if (strncmp(line, "vt", 2) == 0) {
            vec2_t uv;
            sscanf(line, "vt %f %f", &uv.x, &uv.y);
            vertex.uv = uv;
        } else if (strncmp(line, "f", 1) == 0) {
            // load indices
        } else if (strncmp(line, "mtllib", 6) == 0) {
            char prepath[256], path[128];
            sscanf(line, "mtllib %s", path);
            // mesh -> material.name = path;
            strcpy(prepath, ASSETS_DEFAULT_DIR_PATH);
            strcat(prepath, path);
            // load material
        }
        d_vertex_array_insert(&mesh -> vertices, vertex);
    }
    
    fclose(file);
}