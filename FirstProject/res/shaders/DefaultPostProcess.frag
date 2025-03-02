#version 330 core

//outputs the FragColor value to the color attachment 0
out vec4 FragColor;

in vec2 texturePos;

uniform sampler2D colorBuffer;
uniform sampler2D bloomBuffer;
//uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

uniform float gamma = 2.2;

void main() {
    vec3 color = texture2D(colorBuffer, texturePos).rgb + texture2D(bloomBuffer, texturePos).rgb;

    // reinhard tone mapping
    vec3 mapped = color / (color + vec3(1.0));
    // gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));

    FragColor = vec4(mapped, 1.0);
}