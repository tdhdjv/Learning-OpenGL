#include "MeshFactory.h"
#include "Model3D.h"
#include <iostream>
#include <vector>

MeshData createCubeMesh() {
    std::vector<Vertex3D> vertices = {
        {{-0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f }, { 0.0f,  0.0f, -1.0f }, { 1.0f , 0.0f, 0.0f }},
        {{ 0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f }, { 0.0f,  0.0f, -1.0f }, { 1.0f , 0.0f, 0.0f }},
        {{ 0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f }, { 0.0f,  0.0f, -1.0f }, { 1.0f , 0.0f, 0.0f }},
        {{-0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f }, { 0.0f,  0.0f, -1.0f }, { 1.0f , 0.0f, 0.0f }},

        {{-0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }, { 0.0f,  0.0f,  1.0f }, { -1.0f , 0.0f, 0.0f }},
        {{ 0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }, { 0.0f,  0.0f,  1.0f }, { -1.0f , 0.0f, 0.0f }},
        {{ 0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f }, { 0.0f,  0.0f,  1.0f }, { -1.0f , 0.0f, 0.0f }},
        {{-0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f }, { 0.0f,  0.0f,  1.0f }, { -1.0f , 0.0f, 0.0f }},

        {{-0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f }, {-1.0f,  0.0f,  0.0f }, { 0.0f , 0.0f, -1.0f }},
        {{-0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f }, {-1.0f,  0.0f,  0.0f }, { 0.0f , 0.0f, -1.0f }},
        {{-0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f }, {-1.0f,  0.0f,  0.0f }, { 0.0f , 0.0f, -1.0f }},
        {{-0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }, {-1.0f,  0.0f,  0.0f }, { 0.0f , 0.0f, -1.0f }},

        {{ 0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }, { 1.0f,  0.0f,  0.0f }, { 0.0f , 0.0f, 1.0f }},
        {{ 0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f }, { 1.0f,  0.0f,  0.0f }, { 0.0f , 0.0f, 1.0f }},
        {{ 0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f }, { 1.0f,  0.0f,  0.0f }, { 0.0f , 0.0f, 1.0f }},
        {{ 0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f }, { 1.0f,  0.0f,  0.0f }, { 0.0f , 0.0f, 1.0f }},

        {{-0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f }, { 0.0f, -1.0f,  0.0f }, { 1.0f , 0.0f, 0.0f }},
        {{ 0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f }, { 0.0f, -1.0f,  0.0f }, { 1.0f , 0.0f, 0.0f }},
        {{ 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f }, { 0.0f, -1.0f,  0.0f }, { 1.0f , 0.0f, 0.0f }},
        {{-0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f }, { 0.0f, -1.0f,  0.0f }, { 1.0f , 0.0f, 0.0f }},

        {{-0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f }, { 0.0f,  1.0f,  0.0f }, { 1.0f , 0.0f, 0.0f }},
        {{ 0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f }, { 0.0f,  1.0f,  0.0f }, { 1.0f , 0.0f, 0.0f }},
        {{ 0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f }, { 0.0f,  1.0f,  0.0f }, { 1.0f , 0.0f, 0.0f }},
        {{-0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f }, { 0.0f,  1.0f,  0.0f }, { 1.0f , 0.0f, 0.0f }}
    };
    std::vector<Triangle> triangles = {
        {0, 1, 2},
        {2, 3, 0},

        {4, 5, 6},
        {6, 7, 4},

        {8, 9, 10},
        {10, 11, 8},

        {12, 13, 14},
        {14, 15, 12},

        {16, 17, 18},
        {18, 19, 16},

        {20, 21, 22},
        {22, 23, 20},
    };
    return MeshData(vertex3DToVertexData(vertices), triangles, Vertex3D::layout);
}

MeshData generateSides(const glm::vec3 up, const glm::vec3 front, const unsigned int subdivision) {
    glm::vec3 normalUp = glm::normalize(up);
    glm::vec3 normalFront = glm::normalize(front);
    glm::vec3 normalRight = glm::normalize(cross(up, front));

    const int subdivisionPlusOne = subdivision + 1;
    const int subdivisionPlusTwo = subdivision + 2;
    std::vector<Vertex3D> vertices;
    vertices.reserve(subdivisionPlusTwo * subdivisionPlusTwo);
    glm::vec3 previousPos;
    for (float t = 0.0; t <= 1.0; t += 1.0f / subdivisionPlusOne) {
        previousPos = glm::normalize(normalFront * (t - 0.5f) + normalRight * -((float)(1.0 / subdivisionPlusOne) + 0.5f) + normalUp * 0.5f);
        for (float u = 0.0; u <= 1.0; u += 1.0f / subdivisionPlusOne) {
            glm::vec3 position = normalUp * 0.5f;
            glm::vec2 uv = glm::vec2(u, t);
            position += normalFront * (t - 0.5f) + normalRight * (u - 0.5f);
            position = glm::normalize(position);
            vertices.push_back({ position * 0.5f, uv, position, glm::normalize(position - previousPos) });
            previousPos = position;
        }
    }
    std::vector<Triangle> triangles;
    triangles.reserve(2 * (subdivisionPlusOne * subdivisionPlusOne));

    for (int i = 0; i < subdivisionPlusOne; i++) {
        for (int j = 0; j < subdivisionPlusOne; j++) {
            unsigned int a = i + j * subdivisionPlusTwo;
            unsigned int b = (i + 1) + j * subdivisionPlusTwo;
            unsigned int c = i + (j + 1) * subdivisionPlusTwo;
            unsigned int d = (i + 1) + (j + 1) * subdivisionPlusTwo;

            triangles.emplace_back( a, b, c );
            triangles.emplace_back( c, b, d );
        }
    }
    std::vector<float> vertexData = vertex3DToVertexData(vertices);
    MeshData meshData = MeshData(vertexData, triangles, Vertex3D::layout);
    return meshData;
}

MeshData createCubesphereMesh(const unsigned int subdivisions) {

    MeshData meshData = { std::vector<float>(), std::vector<Triangle>(), Vertex3D::layout };

    meshData += generateSides({  0.0,  1.0,  0.0 }, {  0.0,  0.0,  1.0 }, subdivisions);
    meshData += generateSides({  0.0, -1.0,  0.0 }, {  0.0,  0.0, -1.0 }, subdivisions);
    meshData += generateSides({  1.0,  0.0,  0.0 }, {  0.0, -1.0,  0.0 }, subdivisions);
    meshData += generateSides({ -1.0,  0.0,  0.0 }, {  0.0,  1.0,  0.0 }, subdivisions);
    meshData += generateSides({  0.0,  0.0,  1.0 }, { -1.0,  0.0,  0.0 }, subdivisions);
    meshData += generateSides({  0.0,  0.0, -1.0 }, {  1.0,  0.0,  0.0 }, subdivisions);

    return meshData;
}

MeshData createQuad3D(unsigned int subdivisions, glm::vec3 up, glm::vec3 front) {
    glm::vec3 normalUp = glm::normalize(up);
    glm::vec3 normalFront = glm::normalize(front);
    glm::vec3 normalRight = glm::normalize(cross(up, front));

    const int subdivisionPlusOne = subdivisions + 1;
    const int subdivisionPlusTwo = subdivisions + 2;

    std::vector<Vertex3D> vertices;
    vertices.reserve(subdivisionPlusTwo * subdivisionPlusTwo);

    for (float t = 0.0; t <= 1.0; t += 1.0f / subdivisionPlusOne) {
        for (float u = 0.0; u <= 1.0; u += 1.0f / subdivisionPlusOne) {
            glm::vec3 position = normalFront * (t - 0.5f) + normalRight * (u - 0.5f);
            glm::vec2 uv = glm::vec2(t, u);
            vertices.push_back({ position * 0.5f, uv, normalUp, normalFront });
        }
    }
    std::vector<Triangle> triangles;
    triangles.reserve(2 * (subdivisionPlusOne * subdivisionPlusOne));

    for (int i = 0; i < subdivisionPlusOne; i++) {
        for (int j = 0; j < subdivisionPlusOne; j++) {
            unsigned int a = i + j * subdivisionPlusTwo;
            unsigned int b = (i + 1) + j * subdivisionPlusTwo;
            unsigned int c = i + (j + 1) * subdivisionPlusTwo;
            unsigned int d = (i + 1) + (j + 1) * subdivisionPlusTwo;

            triangles.emplace_back(a, b, c);
            triangles.emplace_back(c, b, d);
        }
    }
    return MeshData(vertex3DToVertexData(vertices), triangles, Vertex3D::layout);
}

MeshData createQuad2D() {
    std::vector<float> vertexData {
         // positions   // texCoords
        -1.0f,  1.0f,     0.0f, 1.0f,
        -1.0f, -1.0f,     0.0f, 0.0f,
         1.0f, -1.0f,     1.0f, 0.0f,
         1.0f,  1.0f,     1.0f, 1.0f
    };

    std::vector<Triangle> triangles = {
        { 2, 1, 0 },
        { 3, 2, 0 }
    };
    std::shared_ptr<VertexBufferLayout> layout = std::make_shared<VertexBufferLayout>();
    layout->push<float>(2);
    layout->push<float>(2);
    return MeshData(vertexData, triangles, layout);
};