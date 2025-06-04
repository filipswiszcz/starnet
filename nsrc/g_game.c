#include "d_util.h"
#include "g_game.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define WINDOW_NAME "SOLAR (Build v0.0.8) - Powered by XYCINDA Labs"

void g_gameloop() {
   ASSERT(glfwInit(), "Failed to initialize OpenGL");

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

   //..
}
