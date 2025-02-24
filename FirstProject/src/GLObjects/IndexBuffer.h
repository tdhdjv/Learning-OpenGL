#pragma once
#include <vector>
#include <iostream>

#include "GLAD/glad.h"

class IndexBuffer {
private:
    unsigned int rendererID;
    unsigned int count;
    std::vector<unsigned int> indices;

public:
    IndexBuffer(const unsigned int* indices, unsigned int size);
    ~IndexBuffer();

    void bind() const;
    void unBind() const;

    inline unsigned int getCount() const { return count; }
};