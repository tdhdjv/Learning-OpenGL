#pragma once

#include <GLAD/glad.h>
#include <iostream>

#include "RenderBuffer.h"
#include "ErrorCheck.h"

template <unsigned int N>
class FrameBuffer {
private:
	unsigned int rendererID;
	unsigned int colorBufferTexture[N];

	const unsigned int width;
	const unsigned int height;
	RenderBuffer renderBuffer;

public:
	FrameBuffer(const bool multisample, const int width, const int height);
	FrameBuffer(const FrameBuffer&) = delete;
	~FrameBuffer();

	void bind() const;
	void writeToFBO(const FrameBuffer& otherFBO) const;
	void unBind() const;

	void bindColorBufferTexture(unsigned int slot, unsigned int attachment) const;

	inline int const getRendererID() const { return rendererID; }
};



//TODO implement multisampling
template<unsigned int N>
FrameBuffer<N>::FrameBuffer(const bool multisample, const int width, const int height) : width(width), height(height) {
    GLCall(glGenFramebuffers(1, &rendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));

    GLCall(glGenTextures(N, colorBufferTexture));
    unsigned int attachments[N];
    for (int i = 0; i < N; i++) {
        GLCall(glBindTexture(GL_TEXTURE_2D, colorBufferTexture[i]));
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // create a color attachment texture
        GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBufferTexture[i], 0));
        attachments[i] = GL_COLOR_ATTACHMENT0 + i;
    }

    // create a renderbuffer object for depth and stencil attachment
    renderBuffer.unBind();
    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer.getRendererID()));
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    GLCall(glDrawBuffers(N, attachments));

    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
}

template<unsigned int N>
FrameBuffer<N>::~FrameBuffer() {
    GLCall(glDeleteTextures(N, colorBufferTexture));
    GLCall(glDeleteFramebuffers(1, &rendererID));
}

template<unsigned int N>
void FrameBuffer<N>::bind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));
}

template<unsigned int N>
void FrameBuffer<N>::writeToFBO(const FrameBuffer& otherFBO) const {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, rendererID);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, otherFBO.rendererID);
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

template<unsigned int N>
void FrameBuffer<N>::unBind() const {
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

template<unsigned int N>
void FrameBuffer<N>::bindColorBufferTexture(unsigned int slot, unsigned int attachment) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, colorBufferTexture[attachment]);
}