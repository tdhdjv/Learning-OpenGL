#pragma once

class RenderBuffer {
private:
	unsigned int rendererID;
public:
	RenderBuffer();
	RenderBuffer(const RenderBuffer&) = delete;
	~RenderBuffer();

	void bind() const;
	void unBind() const;

	inline unsigned int getRendererID() {
		return rendererID;
	}
};

class SamplingRenderBuffer {
private:
	unsigned int rendererID;
public:
	SamplingRenderBuffer();
	SamplingRenderBuffer(const SamplingRenderBuffer&) = delete;
	~SamplingRenderBuffer();

	void bind() const;
	void unBind() const;

	inline unsigned int getRendererID() {
		return rendererID;
	}
};