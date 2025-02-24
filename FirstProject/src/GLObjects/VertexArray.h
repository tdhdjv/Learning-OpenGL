#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexLayout.h"

class VertexArray {
private:
    unsigned int rendererID;
public:
    VertexArray();
    ~VertexArray();
    void setBuffer(const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer, const VertexBufferLayout& layout) const;
    void bind() const;
    void unBind() const;
};