#include "FrameBuffer.h"
#include <iostream>

FrameBuffer::FrameBuffer(int width, int height) {
    GLCall(glGenTextures(1, &colorBufferTexture));
    GLCall(glBindTexture(GL_TEXTURE_2D, colorBufferTexture));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));

    GLCall(glGenFramebuffers(1, &rendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));

    // create a color attachment texture
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferTexture, 0));

    // create a renderbuffer object for depth and stencil attachment
    renderBuffer.unBind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer.getRendererID());
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    unBind();
}

FrameBuffer::~FrameBuffer() {
    GLCall(glDeleteFramebuffers(1, &rendererID));
}

void FrameBuffer::bind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));
}

void FrameBuffer::unBind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::bindColorBufferTexture(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, colorBufferTexture);
}