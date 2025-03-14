#version 410 core

in vec3 pcolors;

out vec4 colors;

void main() {
    colors = vec4(pcolors.x, pcolors.y, pcolors.z, 1.0f);
}