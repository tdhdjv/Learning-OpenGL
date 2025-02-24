#include "RenderBuffer.h"

#include "ErrorCheck.h"

RenderBuffer::RenderBuffer() {
	GLCall(glGenRenderbuffers(1, &rendererID));
	bind();

	//TODO: Maybe that in a parameter inorder to be able to define the internal format
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1000, 800);
}

RenderBuffer::~RenderBuffer() {
	GLCall(glDeleteRenderbuffers(1, &rendererID));
}

void RenderBuffer::bind() const {
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, rendererID));
}

void RenderBuffer::unBind() const {
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}