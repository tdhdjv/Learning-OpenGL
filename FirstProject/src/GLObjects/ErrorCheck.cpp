#include "ErrorCheck.h"
#include <iostream>

void GLClear() {
    while(glGetError());
}

bool GLCheckError(const char* file, unsigned int line) {
    unsigned int error;
    bool isError = true;
    while((error = glGetError()) != GL_NO_ERROR) {
        std::cout << "[OpenGL Error: "<< GLParse(error) << "] at " << file << " line: " << line << std::endl;
        isError = false;
    }
    return isError;

}

const char* GLParse(unsigned int error) {
    switch(error) {
        case GL_INVALID_ENUM:
            return "Invalid enum";
        case GL_INVALID_VALUE:
            return "Invalid value";
        case GL_INVALID_OPERATION:
            return "Invalid operation";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "Invalid framebuffer operation";
        case GL_OUT_OF_MEMORY:
            return "Out of memory";
        case GL_STACK_UNDERFLOW:
            return "Stack underflow";
        case GL_STACK_OVERFLOW:
            return "Stack overflow";
        default:
            return "Unknow Error";
    }
}
