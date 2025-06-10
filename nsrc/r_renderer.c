#include "r_renderer.h"

// mesh

static void r_mesh_load_indices(uint32_array_t *array, char line[64]) {
    int gate = 0, offset = 0;
    for (int i = 0; i < 64; i++) {
        if (line[i] == ' ') gate = 1;
        else if (line[i] == '/' && gate == 1) {
            int size = (i + offset) - i;
            char *sub = (char*) malloc(size + 1);
            strncpy(sub, &line[i - offset], size);
            sub[size] = '\0';
            uint32_t value = strtoul(sub, NULL, 0);
            d_uint32_array_insert(array, value - 1);
            free(sub);
            gate = 0; offset = 0;
        } else if (gate == 1) offset = 1;
    }
}

void r_mesh_load_material(material_t material, char *filepath) {
    FILE *file = fopen(filepath, "r");

    ASSERT(file != NULL, "Failed to open the file: %s\n", filepath);

    char line[64];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Ns", 2) == 0) {
            sscanf(line, "Ns %f", &material.shininess);
        } else if (strncmp(line, "Ka", 2) == 0) {
            sscanf(line, "Ka %f %f %f", &material.ambient.x, &material.ambient.y, &material.ambient.z);
        } else if (strncmp(line, "Kd", 2) == 0) {
            sscanf(line, "Kd %f %f %f", &material.diffuse.x, &material.diffuse.y, &material.diffuse.z);
        } else if (strncmp(line, "Ks", 2) == 0) {
            sscanf(line, "Ks %f %f %f", &material.specular.x, &material.specular.y, &material.specular.z);
        } else if (strncmp(line, "Ke", 2) == 0) {
            sscanf(line, "Ke %f %f %f", &material.emissibity.x, &material.emissibity.y, &material.emissibity.z);
        } else if (strncmp(line, "Ni", 2) == 0) {
            sscanf(line, "Ni %f", &material.density);
        } else if (strncmp(line, "d", 1) == 0) {
            sscanf(line, "d %f", &material.transparency);
        } else if (strncmp(line, "illum", 5) == 0) {
            sscanf(line, "illum %d", &material.illumination);
        }
    }
    fclose(file);
}

void r_mesh_load(mesh_t *mesh, char *filepath) {
    FILE *file = fopen(filepath, "r");

    ASSERT(file != NULL, "Failed to open the file: %s\n", filepath);

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
            r_mesh_load_indices(&mesh -> indices, line);
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
