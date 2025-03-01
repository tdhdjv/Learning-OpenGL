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
	FrameBuffer();
	FrameBuffer(const FrameBuffer&) = delete;
	~FrameBuffer();

	void bind() const;
	void writeToFBO(const FrameBuffer& otherFBO) const;
	void unBind() const;

	void bindColorBufferTexture(unsigned int slot) const;

	inline int const getRendererID() const { return rendererID; }
};

class SamplingFrameBuffer {
private:
	unsigned int rendererID;
	unsigned int colorBufferTexture;
	SamplingRenderBuffer renderBuffer;

public:
	SamplingFrameBuffer();
	~SamplingFrameBuffer();

	void bind() const;
	void writeToFBO(const FrameBuffer& otherFBO) const;
	void unBind() const;

	void bindColorBufferTexture(unsigned int slot) const;
};


class OcculsionFrameBuffer {
private:
	unsigned int rendererID;
	unsigned int depthMap;
public:
	OcculsionFrameBuffer();
	OcculsionFrameBuffer(const OcculsionFrameBuffer&) = delete;
	~OcculsionFrameBuffer();

	void bind() const;
	void writeToFBO(const FrameBuffer& otherFBO) const;
	void unBind() const;
	void bindDepthTexture(unsigned int slot) const;
};