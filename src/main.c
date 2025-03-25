#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include "util/res_load.h"
#include "util/shload.h"
#include "context.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define WINDOW_NAME "STARNET (BUILD v0.0.2) - Powered by XYCORP Labs"

int IS_FIRST_PLAY = 1;

void mouse_input(GLFWwindow *window) {
    double mouse_x, mouse_y;
    glfwGetCursorPos(context.window, &mouse_x, &mouse_y);

    if (IS_FIRST_PLAY) {
        // set mouse x
        // set mouse y
        IS_FIRST_PLAY = 0;
    }

    float offset_x = mouse_x - context.camera.mouse_x;
    float offset_y = context.camera.mouse_y - mouse_y;

    context.camera.mouse_x = mouse_x;
    context.camera.mouse_y = mouse_y;

    offset_x *= context.camera.sensitivity;
    offset_y *= context.camera.sensitivity;

    
}

int main() {
    ASSERT(glfwInit(), "Failed to initialize OpenGL");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    context.window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
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

    // unsigned int vao, vbo;
    // glGenVertexArrays(1, &vao);
    // glGenBuffers(1, &vbo);

    // glBindVertexArray(vao);
    
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    // glBindVertexArray(0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // TODO
    // render a lot of meshes and later a lot of instances, check performances (does it really fucking works?)
    mesh_t mesh = {0};
    mesh_load(&mesh, "assets/default/cube.obj");

    mat4 projection = perspective(radians(45.0f), (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(prog, "projection"), 1, GL_FALSE, &projection.m[0][0]);

    // camera
    context.camera.pos = vec3(0.0f, 1.0f, 3.0f);
    context.camera.targpos = vec3(0.0f, 0.0f, -1.0f);
    context.camera.uppos = vec3(0.0f, 1.0f, 0.0f);
    // end of camera

    while (!glfwWindowShouldClose(context.window)) {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(prog);

        mat4 view = get_look_at(context.camera.pos, vec3_add(context.camera.pos, context.camera.targpos), context.camera.uppos);
        glUniformMatrix4fv(glGetUniformLocation(prog, "view"), 1, GL_FALSE, &view.m[0][0]);

        // glBindVertexArray(vao);
        
        mat4 model = mat4(1.0f);
        // model = translate(model, positions[1]);
        glUniformMatrix4fv(glGetUniformLocation(prog, "model"), 1, GL_FALSE, &model.m[0][0]);

        glfwSwapBuffers(context.window);
        glfwPollEvents();
    }

    // glDeleteVertexArrays(1, &vao);
    // glDeleteBuffers(1, &vbo);
    glDeleteProgram(prog);
    glfwTerminate();

    return 0;
}