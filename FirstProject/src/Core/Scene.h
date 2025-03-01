#pragma once

#include <vector>
#include <memory>

#include "../GameObjects/Camera.h"
#include "../GameObjects/Model3D.h"
#include "../GameObjects/Light.h"
#include "../GameObjects/SkyBox.h"
#include "../GLObjects/FrameBuffer.h"

class Scene {
public:
	Scene();

	void update(float dt);
	void render();

	void addModel(const std::shared_ptr<Model3D> model);
	void addDirectionalLight(const DirectionalLight& directionalLight);
	void addPointLight(const PointLight& pointLight);
	void setShader3D(const std::shared_ptr<Shader> shader);
	void addPostProcess(const std::shared_ptr<Shader> shader);
	void addOtherShaders(const std::shared_ptr<Shader> shader);

private:
	std::shared_ptr<Shader> shader3D;
	std::shared_ptr<Shader> occulsionShader;
	std::vector<std::shared_ptr<Shader>> postProcessShaders;
	std::vector< std::shared_ptr<Shader>> otherShaders;
	std::vector<std::shared_ptr<Model3D>> models;

	std::vector<PointLight> pointLights;
	std::vector<DirectionalLight> directionalLights;

	SamplingFrameBuffer samplingFBO;
	OcculsionFrameBuffer occulsionFBO;
	FrameBuffer FBO;
	SkyBox skyBox;

	Camera camera;

	Mesh quad;

	//temporary
	float gamma = 0.5;
};