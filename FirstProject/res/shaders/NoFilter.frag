#version 330 core

out vec4 FragColor;

in vec2 texturePos;

uniform sampler2D colorBuffer;

void main() {
    FragColor = texture2D(colorBuffer, texturePos);
}