#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

typedef struct vec3 {
    float x, y;
} vec3;

static struct {
    GLFWwindow *window;

    struct {
        vec3 pos;
        vec3 targpos, uppos;
        float yaw, pitch;
    } camera;

} context;