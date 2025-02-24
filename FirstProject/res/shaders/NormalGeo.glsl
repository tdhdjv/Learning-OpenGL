#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

#define Magnitude 0.2

uniform mat4 projection;

void createNormalLines(int index) {
    gl_Position = projection * gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = projection * (gl_in[index].gl_Position + Magnitude * vec4(gs_in[index].normal,0.0));
    EmitVertex();
    EndPrimitive();
}

void main() {
    createNormalLines(0);
    createNormalLines(1);
    createNormalLines(2);
}