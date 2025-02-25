#pragma once

#include <memory>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../GLObjects/VertexBuffer.h"
#include "../GLObjects/VertexArray.h"
#include "../GLObjects/VertexLayout.h"
#include "../GLObjects/IndexBuffer.h"

#include "../GLObjects/Texture2D.h"
#include "../GLObjects/Shader.h"

struct Triangle {
    unsigned int a;
    unsigned int b;
    unsigned int c;

    Triangle(unsigned int a, unsigned int b, unsigned int c)
        :a(a), b(b), c(c) {}
};

inline std::vector<unsigned int> triangleToIndex(const std::vector<Triangle>& triangles) {
    std::vector<unsigned int> indices(triangles.size() * 3);
    for (int i = 0; i < triangles.size(); i++) {
        indices[i * 3] = triangles[i].a;
        indices[i * 3 + 1] = triangles[i].b;
        indices[i * 3 + 2] = triangles[i].c;
    }
    return indices;
}

struct MeshData {
    std::vector<float> vertexData;
    std::vector<Triangle> triangles;
    const VertexBufferLayout& layout;

    MeshData(const std::vector<float> vertexData, const std::vector<Triangle> triangles, const VertexBufferLayout& layout)
        :vertexData(vertexData), triangles(triangles), layout(layout) 
    {}

    MeshData(const MeshData& meshData) :vertexData(meshData.vertexData), triangles(meshData.triangles), layout(meshData.layout) {};

    inline MeshData& operator += (const MeshData& other) {
        if (this == &other) {
            throw std::runtime_error("Self-addition is not allowed");
        }

        //offset calculation
        size_t offset = vertexData.size() / layout.getCount();

        // Append vertex data
        this->vertexData.insert(this->vertexData.end(), other.vertexData.begin(), other.vertexData.end());

        // Append triangle indices with offset
        for (const Triangle& tri : other.triangles) {
            this->triangles.emplace_back(tri.a + offset, tri.b + offset, tri.c + offset);
        }

        return *this;
    }
};

class Mesh {
private:
    const VertexArray VAO;
    const VertexBuffer vertexBuffer;
    const IndexBuffer indexBuffer;
    const MeshData meshData;

    glm::vec3 scale;
    glm::vec3 position;
    glm::mat4 modelMat;

public:
    Mesh(const std::vector<float>& vertices, const std::vector<Triangle>& triangle, const VertexBufferLayout& layout);
    Mesh(const MeshData& meshData);

    void bind() const;
    void unBind() const;

    void setPosition(const glm::vec3 position);
    void setScale(const glm::vec3 scale);

    inline const glm::mat4& getModelMat() const{ return modelMat; }
    inline const VertexArray& getVertexArray() const { return VAO; }
    inline unsigned int getIndexCount() const { return indexBuffer.getCount(); }
};