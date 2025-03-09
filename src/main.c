#include <stdio.h>

#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        printf("a"); return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 600, "asd", NULL, NULL);
    if (!window) {
        printf("c"); return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}