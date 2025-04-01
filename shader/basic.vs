#version 410 core

layout (location = 0) in vec3 vertices;
// layout (location = 1) in vec2 textures;
// layout (location = 2) in vec3 colors;

// out vec2 modif_textures;
// out vec3 modif_colors;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(vertices.x, vertices.y, vertices.z, 1.0f);
    // modif_textures = vec2(textures.x, 1.0f - textures.y);
    // modif_colors = colors;
}