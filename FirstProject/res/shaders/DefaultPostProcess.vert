#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 uv;

out vec2 texturePos;

void main() {
    gl_Position = vec4(position, 1.0, 1.0);
    texturePos = uv;
}