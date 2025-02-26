#include "Scene.h"
#include "../GameObjects/MeshFactory.h"

Scene::Scene(): 
	shader3D(std::make_unique<Shader>("FirstProject/res/shaders/Shader3D.vert", "FirstProject/res/shaders/Shader3D.frag")),
	postProcessShaders(),
	otherShaders(),
	models(), 
	FBO(1000, 800), 
	skyBox(	
		"FirstProject/res/image/skybox/right.jpg",
		"FirstProject/res/image/skybox/left.jpg",
		"FirstProject/res/image/skybox/top.jpg",
		"FirstProject/res/image/skybox/bottom.jpg",
		"FirstProject/res/image/skybox/front.jpg",
		"FirstProject/res/image/skybox/back.jpg"
	),
	camera(),
	quad(createQuad2D())
{
	postProcessShaders.emplace_back(std::make_unique<Shader>("FirstProject/res/shaders/NoFilter.vert", "FirstProject/res/shaders/NoFilter.frag"));

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));

	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_FRONT));

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Scene::update(float dt) {
	camera.update(dt);
}

void Scene::render() {
	FBO.bind();
	GLCall(glClearColor(0.4f, 0.6f, 0.7f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

	//model render
	shader3D->setUniform3f("viewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	shader3D->setUniformMat4f("view", camera.getViewMat());
	shader3D->setUniformMat4f("projection", camera.getProjectionMat());
	shader3D->setUniform1i("albedoMap", 0);
	shader3D->setUniform1i("metallicMap", 1);
	shader3D->setUniform1i("roughnessMap", 2);
	shader3D->setUniform1i("normalMap", 3);
	shader3D->setUniform1i("depthMap", 4);

	for (std::shared_ptr<Model3D>& model : models) {
		model->render(*shader3D);
	}

	//skybox
	skyBox.render(camera);

	//Post-Process

	FBO.unBind();
	FBO.bindColorBufferTexture(10);
	
	GLCall(glDisable(GL_DEPTH_TEST));
	GLCall(glDisable(GL_CULL_FACE));
	
	GLCall(glClearColor(0.4f, 0.6f, 0.7f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
	
	for (std::shared_ptr<Shader> shader : postProcessShaders) {
		shader->bind();
		shader->setUniform1i("colorBuffer", 10);
		quad.bind();

		int count = quad.getIndexCount();
		GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));
	}

	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glEnable(GL_DEPTH_TEST));
}

void Scene::addModel(const std::shared_ptr<Model3D> model)
{
	models.emplace_back(model);
}

void Scene::addDirectionalLight(const DirectionalLight& directionalLight)
{
	directionalLights.push_back(directionalLight);
	shader3D->setUniformDirectionalLights(directionalLights);
}

void Scene::addPointLight(const PointLight& pointLight)
{
	pointLights.push_back(pointLight);
	shader3D->setUniformPointLights(pointLights);
}

void Scene::setShader3D(std::shared_ptr<Shader> shader)
{
	shader3D = shader;
}

void Scene::addPostProcess(std::shared_ptr<Shader> shader)
{
	postProcessShaders.push_back(shader);
}

void Scene::addOtherShaders(std::shared_ptr<Shader> shader)
{
	otherShaders.push_back(shader);
}
