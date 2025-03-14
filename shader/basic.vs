#version 410 core

layout (location = 0) in vec3 vertices;
layout (location = 1) in vec3 colors;

out vec3 pcolors;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = model * view * projection * vec4(vertices.x, vertices.y, vertices.z, 1.0f);
    pcolors = vec3(colors.x, colors.y, colors.z);
}