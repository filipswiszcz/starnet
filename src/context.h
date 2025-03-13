#include <math.h>
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>

#define vec3(x, y, z) ((vec3) {x, y, z})
#define vec3_add(a, b) ((vec3) {a.x + b.x, a.y + b.y, a.z + b.z})
#define vec3_sub(a, b) ((vec3) {a.x - b.x, a.y - b.y, a.z - b.z})

#define mat4(v) ((mat4) {v})

typedef struct vec3 {
    float x, y, z;
} vec3;

typedef struct mat4 {
    float m[4][4];
} mat4;

static struct {
    GLFWwindow *window;

    struct {
        vec3 pos;
        vec3 targpos, uppos;
        float yaw, pitch;
    } camera;

} context;

vec3 normalize(const vec3 v) {
    float len = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
    return vec3(v.x / len, v.y / len, v.z / len);
}

vec3 cross(const vec3 a, const vec3 b) {
    return vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

float dot(const vec3 a, const vec3 b) {
    return a.x * b.x + a.y + b.y + a.z + b.z;
}

mat4 get_look_at(vec3 pos, vec3 targpos, vec3 uppos) {
    const vec3 t = normalize(vec3_sub(vec3_add(pos, targpos), pos));
    const vec3 r = normalize(cross(t, uppos));
    const vec3 u = cross(r, t);

    mat4 res = mat4(1);
    res.m[0][0] = r.x;
    res.m[1][0] = r.y;
    res.m[2][0] = r.z;
    res.m[0][1] = u.x;
    res.m[1][1] = u.y;
    res.m[2][1] = u.z;
    res.m[0][2] = -t.x;
    res.m[1][2] = -t.y;
    res.m[2][2] = -t.z;
    res.m[3][0] = -dot(r, pos);
    res.m[3][1] = -dot(u, pos);
    res.m[3][2] = dot(t, pos);

    return res;
}