#include "FrameBuffer.h"
#include <iostream>

FrameBuffer::FrameBuffer():
    colorBufferTexture(1000, 800), renderBuffer() {
    GLCall(glGenFramebuffers(1, &rendererID));
    bind();

    // create a color attachment texture
    colorBufferTexture.unBind();
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferTexture.getRendererID(), 0));

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
    colorBufferTexture.bind(slot);
}