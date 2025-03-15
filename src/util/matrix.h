#include "vector.h"

#define mat4(v) ((mat4) {v})

typedef struct mat4 {
    float m[4][4];
} mat4;

mat4 perspective(float fovy, float aspect, float znear, float zfar) {
    float rad = fovy;
    float tan_half_fovy = tan(rad / 2);

    mat4 res = mat4(0);
    res.m[0][0] = 1 / (aspect * tan_half_fovy);
    res.m[1][1] = 1 / (tan_half_fovy);
    res.m[2][2] = -(zfar + znear) / (zfar - znear);
    res.m[2][3] = -1;
    res.m[3][2] = -(2 * zfar * znear);

    return res;
}

mat4 translate(mat4 m, vec3 v) {
    mat4 res = m;
    res.m[3][0] = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0];
    res.m[3][1] = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1];
    res.m[3][2] = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2];
    res.m[3][3] = m.m[0][3] * v.x + m.m[1][3] * v.y + m.m[2][3] * v.z + m.m[3][3];
    return res;
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