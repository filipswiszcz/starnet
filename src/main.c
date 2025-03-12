#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include "util/shload.h"
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

    // shaders

    char *vshcode, *fshcode;
    shread("shader/basic.vs", &vshcode);
    shread("shader/basic.fs", &fshcode);

    uint32_t vshader = shcompile(GL_VERTEX_SHADER, vshcode);
    uint32_t fshader = shcompile(GL_FRAGMENT_SHADER, fshcode);

    uint32_t prog = shlink(vshader, fshader);

    // end of shaders

    float vertices[] = {
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,

        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f
    };

    float colors[] = {
        0.0f, 255.0f, 0.0f,
        0.0f, 255.0f, 0.0f,
        0.0f, 255.0f, 0.0f,
        0.0f, 255.0f, 0.0f,

        0.0f, 255.0f, 0.0f,
        0.0f, 255.0f, 0.0f,
        0.0f, 255.0f, 0.0f,
        0.0f, 255.0f, 0.0f,
    };

    uint32_t indices[] = {
        0, 1, 2,
        2, 3, 0,

        0, 3, 7,
        7, 4, 0,

        2, 6, 7,
        7, 3, 2,

        1, 5, 6,
        6, 2, 1,

        4, 7, 6,
        6, 5, 4,

        5, 1, 0,
        0, 4, 5
    };

    unsigned int vao, vbo, cvbo, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &cvbo);
    glBindBuffer(GL_ARRAY_BUFFER, cvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof colors, colors, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    uint32_t loc = glGetUniformLocation(prog, "transform");

    while (!glfwWindowShouldClose(context.window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(prog);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, NULL);

        glfwSwapBuffers(context.window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return 0;
}