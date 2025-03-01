#include <GLAD/glad.h>
#include <vector>
#include <iostream>

#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertexData, const std::vector<Triangle>& triangles, const std::shared_ptr<VertexBufferLayout> layout)
    :VAO(std::make_unique<VertexArray>()),
    vertexBuffer(std::make_unique<VertexBuffer>(vertexData.data(), sizeof(float)* vertexData.size())),
    indexBuffer(std::make_unique<IndexBuffer>(triangleToIndex(triangles).data(), sizeof(unsigned int) * 3 * triangles.size())),
    meshData(std::make_unique<MeshData>(vertexData, triangles, layout)),
    position(0.0),
    scale(1.0),
    modelMat(1.0) 
{

    VAO->setBuffer(*vertexBuffer, *indexBuffer, *layout);
}

Mesh::Mesh(const MeshData& meshData): Mesh(meshData.vertexData, meshData.triangles, meshData.layout) {}

void Mesh::bind() const {
    VAO->bind();
}

void Mesh::unBind() const {
    VAO->unBind();
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
