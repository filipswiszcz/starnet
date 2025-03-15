#include <math.h>
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

#include "util/matrix.h"

static struct {
    GLFWwindow *window;

    struct {
        vec3 pos;
        vec3 targpos, uppos;
        float yaw, pitch;
    } camera;

} context;