#include "FrameBuffer.h"

#include "../Core/Application.h"
#include <iostream>


FrameBuffer::FrameBuffer() {

    int width = Application::getInstance().getWindow().getWidth();
    int height = Application::getInstance().getWindow().getHeight();
    GLCall(glGenTextures(1, &colorBufferTexture));
    GLCall(glBindTexture(GL_TEXTURE_2D, colorBufferTexture));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    
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
}

FrameBuffer::~FrameBuffer() {
    GLCall(glDeleteFramebuffers(1, &rendererID));
}

void FrameBuffer::bind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));
}

void FrameBuffer::writeToFBO(const FrameBuffer &otherFBO) const {
    int width = Application::getInstance().getWindow().getWidth();
    int height = Application::getInstance().getWindow().getHeight();
    glBindFramebuffer(GL_READ_FRAMEBUFFER, rendererID);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, otherFBO.rendererID);
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void FrameBuffer::unBind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::bindColorBufferTexture(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, colorBufferTexture);
}

SamplingFrameBuffer::SamplingFrameBuffer() {
    int width = Application::getInstance().getWindow().getWidth();
    int height = Application::getInstance().getWindow().getHeight();
    GLCall(glGenTextures(1, &colorBufferTexture));
    GLCall(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, colorBufferTexture));
    GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, width, height, GL_TRUE));

    GLCall(glGenFramebuffers(1, &rendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));

    // create a color attachment texture
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, colorBufferTexture, 0));

    // create a renderbuffer object for depth and stencil attachment
    renderBuffer.unBind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer.getRendererID());
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
}

SamplingFrameBuffer::~SamplingFrameBuffer() {
    GLCall(glDeleteFramebuffers(1, &rendererID));
}

void SamplingFrameBuffer::bind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));
}

void SamplingFrameBuffer::writeToFBO(const FrameBuffer& otherFBO) const {
    int width = Application::getInstance().getWindow().getWidth();
    int height = Application::getInstance().getWindow().getHeight();
    glBindFramebuffer(GL_READ_FRAMEBUFFER, rendererID);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, otherFBO.getRendererID());
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    unBind();
}

void SamplingFrameBuffer::unBind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void SamplingFrameBuffer::bindColorBufferTexture(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, colorBufferTexture);
}


OcculsionFrameBuffer::OcculsionFrameBuffer() {
    int width = 4096;
    int height = 4096;

    GLCall(glGenTextures(1, &depthMap));
    GLCall(glBindTexture(GL_TEXTURE_2D, depthMap));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
  
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLCall(glGenFramebuffers(1, &rendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));

    // create a color attachment texture
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0));
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
}

OcculsionFrameBuffer::~OcculsionFrameBuffer() {
    GLCall(glDeleteFramebuffers(1, &rendererID));
}

void OcculsionFrameBuffer::bind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));
}

void OcculsionFrameBuffer::writeToFBO(const FrameBuffer& otherFBO) const
{
    int width = Application::getInstance().getWindow().getWidth();
    int height = Application::getInstance().getWindow().getHeight();
    GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, rendererID));
    GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, otherFBO.getRendererID()));
    GLCall(glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST));
    unBind();

}

void OcculsionFrameBuffer::unBind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void OcculsionFrameBuffer::bindDepthTexture(unsigned int slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, depthMap));
}