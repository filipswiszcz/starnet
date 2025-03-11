#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

void rfile(char *shader, char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Failed to open file"); return;
    }

    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    rewind(file);

    char *cont = (char*) malloc(fsize + 1);
    fread(cont, 1, fsize, file);
    cont[fsize] = '\0';

    shader = strdup(cont);

    free(cont);
    fclose(file);
}

uint32_t shcompile(char* code, uint32_t type) {
    uint32_t shader = glCreateShader(type);
    const char* src = code;

    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    char info[256];
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        glGetShaderInfoLog(shader, 256, NULL, info);
    }

    return shader;
}

uint32_t shlink(uint32_t vsh, uint32_t fsh) {}