#include "VertexBuffer.h"
#include "ErrorCheck.h"

VertexBuffer::VertexBuffer(const float* vertices, unsigned int size) {
    GLCall(glGenBuffers(1, &rendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &rendererID));
}

void VertexBuffer::bind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
}

void VertexBuffer::unBind() const{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}