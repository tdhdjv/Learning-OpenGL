#pragma once
#include <memory.h>
#include <string>
#include "../GameObjects/Camera.h"
#include "../GameObjects/Mesh.h"
#include "../GLObjects/Shader.h"

class SkyBox {
public:
	SkyBox(const std::string right, const std::string left, const std::string top, const std::string bottom, const std::string front, const std::string back);
	~SkyBox();

	void render(const Camera& camera);

private:
	Shader shader;
	unsigned int textureID;
	std::unique_ptr<Mesh> skyBoxMesh;
};