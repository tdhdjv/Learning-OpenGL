#version 330 core

out vec4 FragColor;

float near = 0.1;
float far = 100.0;

uniform vec3 viewPos;
uniform sampler2D albedoMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{          
    viewPos;   
    texture2D(albedoMap, vec2(0.0));
    texture2D(metallicMap, vec2(0.0));
    texture2D(roughnessMap, vec2(0.0));
    texture2D(normalMap, vec2(0.0));
    texture2D(depthMap, vec2(0.0));
    float depth = LinearizeDepth(gl_FragCoord.z) / 10.0; // divide by far for demonstration
    FragColor = vec4(vec3(depth), 1.0);
}