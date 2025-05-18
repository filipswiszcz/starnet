#ifndef __R_SHADER_H__
#define __R_SHADER_H__

#include <stdio.h>
#include <stdint.h>

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

#include "common.h" // change it later

typedef struct {
    uint32_t ids[2]; // [0] = vert, [1] = frag
    uint32_t program;
} shader_t;

void r_create_program(shader_t *shader, char *frag_path, char *vert_path);

#endif // !__R_SHADER_H__