#pragma once
#include "GLAD/glad.h"

class VertexBuffer {
private:
    unsigned int rendererID;
public:
    VertexBuffer(const float* vertices, unsigned int size);
    VertexBuffer(const VertexBuffer&) = delete;
    ~VertexBuffer();

    void bind() const;
    void unBind() const;
};