#include "util/math/matrix.h"

void __mat4_read(mat4 m) {
    for (int i = 0; i < 4; i++) {
        printf("[");
        for (int j = 0; j < 4; j++) {
            printf("%7.2f", m.m[i][j]);
            if (j < 3) printf(" ");
        }
        printf("]\n");
    }
    printf("\n");
}

mat4 perspective(float fovy, float aspect, float znear, float zfar) {
    float rad = fovy;
    float tan_half_fovy = tan(rad / 2);

    mat4 res = mat4(0);
    res.m[0][0] = 1.0f / (aspect * tan_half_fovy);
    res.m[1][1] = 1.0f / (tan_half_fovy);
    res.m[2][2] = -(zfar + znear) / (zfar - znear);
    res.m[2][3] = -1.0f;
    res.m[3][2] = -(2.0f * zfar * znear) / (zfar - znear);
    res.m[3][3] = 0.0f;

    return res;
}

mat4 translate(mat4 m, vec3 v) {
    mat4 res = m;
    res.m[3][0] += v.x;
    res.m[3][1] += v.y;
    res.m[3][2] += v.z;
    return res;
}

mat4 get_look_at(vec3 pos, vec3 targpos, vec3 uppos) {
    const vec3 t = normalize(vec3_sub(targpos, pos));
    const vec3 r = normalize(cross(t, uppos));
    const vec3 u = normalize(cross(r, t));

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
    res.m[3][3] = 1.0f;

    return res;
}