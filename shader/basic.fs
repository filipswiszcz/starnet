#version 410 core

in vec3 modif_vertices;
in vec3 modif_normals;

out vec4 colors;

uniform vec3 light_pos;
uniform vec3 view_pos;
uniform vec3 light_color;
uniform vec3 object_color;

void main() {
    // vec3 light = ()
    float ambient_strength = 0.1f;
    vec3 ambient = ambient_strength * light_color;

    vec3 norm = normalize(modif_normals);
    vec3 direct = normalize(light_pos - modif_vertices);

    float diff = max(dot(norm, direct), 0.0f);
    vec3 diffuse = diff * light_color;

    // float specular_strength = 0.5f;
    // vec3 view_direct = normalize(view_pos - modif_vertices);
    // vec3 reflect_direct = reflect(-direct, norm);
    
    // float spec = pow(max(dot(view_direct, reflect_direct), 0.0f), 32);
    // vec3 specular = specular_strength * spec * light_color;

    vec3 result = (ambient + diffuse) * object_color;
    colors = vec4(result, 1.0f);
    // colors = vec4(0.22f, 0.92f, 0.95f, 1.0f);
}