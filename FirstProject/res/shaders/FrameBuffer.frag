#version 330 core

out vec4 FragColor;

in vec2 TexturePos;

uniform sampler2D screenTexture;
uniform vec2 resolution;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main() {
    vec4 color1 = vec4(0.0);
    vec2 offset1 = vec2(1.0)/resolution;
    for(int i = -4; i < 5; i++) {
        float w1 = weight[abs(i)];
        for(int j = -4; j < 5; j++) {
            float w2 = weight[abs(j)];
            color1 += texture(screenTexture, TexturePos+vec2(offset1.x*i, offset1.y*j)) * w1 * w2;
        }
    }
    vec4 color2 = vec4(0.0);
    vec2 offset2 = vec2(2.0)/resolution;
    for(int i = -4; i < 5; i++) {
        float w1 = weight[abs(i)];
        for(int j = -4; j < 5; j++) {
            float w2 = weight[abs(j)];
            color2 += texture(screenTexture, TexturePos+vec2(offset2.x*i, offset2.y*j)) * w1 * w2;
        }
    }
    float DoG = smoothstep(0.04, 0.05, length(color1-color2));
    FragColor = texture(screenTexture, TexturePos);
}