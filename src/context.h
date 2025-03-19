#ifndef CONTEXT_H
#define CONTEXT_H

#include <math.h>
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

#include "util/matrix.h"

// xycida

static struct {
    GLFWwindow *window;

    struct {
        vec3 pos;
        vec3 targpos, uppos;
        float yaw, pitch;
    } camera;

    // viewer
        // speed of movement, distances to other objects
        // camera attached to viewer

    // renderer
        // scenes
            // objects
                // things
                    // meshes, textures, colors
                    // other properties (weight, size)
                // characters
                    // bones
                    // draw
                // particles
                    // sim
                    // draw

} context;

#endif /* CONTEXT_H */