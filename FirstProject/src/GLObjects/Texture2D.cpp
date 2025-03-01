#include "GLAD/glad.h"

#include "../vendor/std_image/std_image.h"
#include <iostream>

#include "ErrorCheck.h"
#include "Texture2D.h"

Texture2D::Texture2D(const char* filepath, unsigned int format) {
    GLCall(glGenTextures(1, &rendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
    
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    // set texture filtering parameters
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    unsigned char* data = stbi_load(filepath, &width, &height, &channel, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    }
    else {
        std::cout << "Failed to load an image from: " << filepath << std::endl;
    }
    stbi_image_free(data);
}

Texture2D::~Texture2D() {
    GLCall(glDeleteTextures(1, &rendererID));
}

void Texture2D::bind(unsigned int slot /* = 0 */) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, rendererID));
}

void Texture2D::unBind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

unsigned int Texture2D::getRendererID() {
    return rendererID;
}