#pragma once

#include <GLAD/glad.h>

class RenderBuffer {
private:
	unsigned int rendererID;
public:
	RenderBuffer();
	~RenderBuffer();

	void bind() const;
	void unBind() const;

	inline unsigned int getRendererID() {
		return rendererID;
	}
};