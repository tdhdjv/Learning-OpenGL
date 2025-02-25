#pragma once

#include <vector>
#include <memory>

#include "../GameObjects/Camera.h"
#include "../GameObjects/Model3D.h"
#include "../GameObjects/SkyBox.h"
#include "../GLObjects/FrameBuffer.h"

class Scene {
public:
	Scene();

	void render();

	void addModel(const std::shared_ptr<Model3D> model);
	void setShader3D(const Shader& shader);
	void addPostProcess(const Shader& shader);
	void addOtherShaders(const Shader& shader);

private:
	Shader shader3D;
	std::vector<Shader> postProcessShaders;
	std::vector<Shader> otherShaders;
	std::vector<std::shared_ptr<Model3D>> models;

	FrameBuffer FBO;
	SkyBox skyBox;

	Camera camera;
};