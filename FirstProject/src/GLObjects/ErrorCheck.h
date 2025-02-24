#pragma once
#include <GLAD/glad.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClear();\
    x;\
    ASSERT(GLCheckError(__FILE__, __LINE__));\

void GLClear();

bool GLCheckError(const char* file, unsigned int line);

const char* GLParse(unsigned int error);
