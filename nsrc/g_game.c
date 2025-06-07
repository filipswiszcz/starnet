#include "d_util.h"
#include "g_game.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define WINDOW_NAME "SOLAR (Build v0.0.8)"

void g_mouse_input() {}

void g_keyboard_input() {}

float TIME_OF_LAST_FRAME = 0.0f;
int FRAMES_PER_SECOND = 0;

void g_game_frames() {
    float current_time = (float) glfwGetTime();
    FRAMES_PER_SECOND++;
    if (current_time - TIME_OF_LAST_FRAME >= 1.0) {
        char subtitle[16], title[64];
        strcpy(title, WINDOW_NAME);
        sprintf(subtitle, " [%d FPS]", (int) FRAMES_PER_SECOND);
        strcat(title, subtitle);
        glfwSetWindowTitle(context.window, title);
        FRAMES_PER_SECOND = 0;
        TIME_OF_LAST_FRAME = 1.0f;
    }
}

void g_game_init() {
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //..
}

void g_game_loop() {
    while (!glfwWindowShouldClose(context.window)) {
        // inputs

        // frames updater
        g_game_frames();

        // background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(context.window);
        glfwPollEvents();
    }
}

void g_game_stop() {
    glfwTerminate();
}
