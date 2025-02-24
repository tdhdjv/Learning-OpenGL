#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;

out VS_OUT {
    vec3 normal;
} vs_out;

uniform mat4 model;
uniform mat4 view;

void main() {

    mat3 normalMatrix = mat3(transpose(inverse(view * model)));
    vs_out.normal = normalize(normalMatrix*tangent);
    gl_Position = view * model * vec4(position, 1.0);
}