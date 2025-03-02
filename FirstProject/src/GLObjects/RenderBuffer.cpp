#include "RenderBuffer.h"

#include "ErrorCheck.h"
#include "../Core/Application.h"

RenderBuffer::RenderBuffer() {
	GLCall(glGenRenderbuffers(1, &rendererID));
	bind();

	//TODO: Maybe that in a parameter inorder to be able to define the internal format
	int width = Application::getInstance().getWindow().getWidth();
	int height = Application::getInstance().getWindow().getHeight();
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
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