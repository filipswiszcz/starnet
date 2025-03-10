#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include "context.h"

#define ASSERT(_e, ...) if (!(_e)) {fprintf(stderr, __VA_ARGS__); exit(1);}

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main() {
    ASSERT(glfwInit(), "Failed to initialize OpenGL");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    context.window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Powered by XYCORP Labs", NULL, NULL);
    ASSERT(context.window, "Failed to initialize OpenGL window");

    glfwMakeContextCurrent(context.window);
    glfwSetInputMode(context.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        -1.0f, 0.0f, 1.0f,
        0.0f, 255.0f, 0.0f,
        1.0f, 0.0f, -1.0f,
        0.0f, 255.0f, 0.0f
    };

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(context.window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(context.window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}