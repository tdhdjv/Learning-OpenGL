#include "Scene.h"

Scene::Scene(): 
	shader3D("FirstProject/res/shaders/Shader3D.vert", "FirstProject/res/shaders/Shader3D.frag"),
	postProcessShaders(),
	otherShaders(),
	models(), 
	FBO(1000, 800), 
	skyBox(),
	camera()
{
	postProcessShaders.emplace_back("FirstProject/res/shaders/NoFilter.vert", "FirstProject/res/shaders/NoFilter.frag");
}

void Scene::render() {
	shader3D.setUniformMat4f("view", camera.getViewMat());
	shader3D.setUniformMat4f("projection", camera.getProjectionMat());
	for (std::shared_ptr<Model3D>& model : models) {
		model->render(shader3D);
	}
}

void Scene::addModel(const std::shared_ptr<Model3D> model)
{
	models.emplace_back(model);
}

void Scene::setShader3D(const Shader& shader)
{
	shader3D = shader;
}

void Scene::addPostProcess(const Shader& shader)
{
	postProcessShaders.push_back(shader);
}

void Scene::addOtherShaders(const Shader& shader)
{
	otherShaders.push_back(shader);
}
