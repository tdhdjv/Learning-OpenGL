#version 330 core

out vec4 FragColor;

float near = 0.1;
float far = 100.0;

in vec2 texturePos;

uniform sampler2D colorBuffer;

uniform float gamma = 2.2;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main() {
    vec3 color = texture2D(colorBuffer, texturePos).rgb;
    // reinhard tone mapping
    vec3 mapped = color / (color + vec3(1.0));
    // gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    float depth = LinearizeDepth(texture2D(colorBuffer, texturePos).r)/10.0;
    //mapped = vec3(depth);
    FragColor = vec4(mapped, 1.0);
}