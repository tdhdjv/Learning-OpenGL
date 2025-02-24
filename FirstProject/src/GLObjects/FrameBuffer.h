#pragma once

#include <GLAD/glad.h>

#include "Texture.h"
#include "RenderBuffer.h"
#include "ErrorCheck.h"

class FrameBuffer {
private:
	unsigned int rendererID;
	Texture colorBufferTexture;
	RenderBuffer renderBuffer;

public:
	FrameBuffer();
	~FrameBuffer();

	void bind() const;
	void unBind() const;

	void bindColorBufferTexture(unsigned int slot) const;
};