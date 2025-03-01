#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;

out vec3 FragPos;
out vec4 LightSpacePos;
out vec3 Normal;
out vec3 Tangent;
out vec3 BiTangent;
out vec2 vertex_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightTransform;

void main()
{
    FragPos = vec3(model * vec4(position, 1.0));
    LightSpacePos = lightTransform * vec4(FragPos, 1.0);
    Normal = normalize(mat3(transpose(inverse(model))) * normal);
    Tangent = normalize(mat3(transpose(inverse(model))) * tangent);
    BiTangent = cross(Normal, Tangent);
    vertex_uv = uv;
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}