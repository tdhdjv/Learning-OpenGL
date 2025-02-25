#include <GLAD/glad.h>
#include <vector>
#include <iostream>

#include "Mesh.h"
#include "Constructs.h"

Mesh::Mesh(const std::vector<float>& vertexData, const std::vector<Triangle>& triangles, const VertexBufferLayout& layout)
    :VAO(),
    vertexBuffer(vertexData.data(), sizeof(float)* vertexData.size()),
    indexBuffer(triangleToIndex(triangles).data(), sizeof(unsigned int) * 3 * triangles.size()),
    meshData(vertexData, triangles, layout),
    position(0.0),
    scale(1.0),
    modelMat(1.0) 
{

    VAO.setBuffer(vertexBuffer, indexBuffer, layout);
}

Mesh::Mesh(const MeshData& meshData): Mesh(meshData.vertexData, meshData.triangles, meshData.layout) {}

void Mesh::bind() const {
    VAO.bind();
}

void Mesh::unBind() const {
    VAO.unBind();
}

void Mesh::setPosition(const glm::vec3 position) {
    this->position = position;
    modelMat = glm::scale(glm::translate(glm::mat4(1.0), position), scale);
}

void Mesh::setScale(const glm::vec3 scale)
{
    this->scale = scale;
    modelMat = glm::scale(glm::translate(glm::mat4(1.0), position), scale);
}
