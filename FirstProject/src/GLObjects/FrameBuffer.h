#pragma once

#include <GLAD/glad.h>

#include "RenderBuffer.h"
#include "ErrorCheck.h"

class FrameBuffer {
private:
	unsigned int rendererID;
	unsigned int colorBufferTexture;
	RenderBuffer renderBuffer;

public:
	FrameBuffer(int width, int height);
	~FrameBuffer();

	void bind() const;
	void unBind() const;

	void bindColorBufferTexture(unsigned int slot) const;
};