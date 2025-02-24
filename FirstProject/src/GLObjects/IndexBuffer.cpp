#include "IndexBuffer.h"
#include "ErrorCheck.h"

IndexBuffer::IndexBuffer(const unsigned int* indices, unsigned int size) :indices(indices, indices + (size / sizeof(unsigned int))) {
    GLCall(glGenBuffers(1, &rendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
    count = size / sizeof(unsigned int);
}

IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &rendererID));
}

void IndexBuffer::bind() const{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
}

void IndexBuffer::unBind() const{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}