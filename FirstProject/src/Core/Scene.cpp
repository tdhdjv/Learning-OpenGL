#include "Scene.h"
#include "../GameObjects/MeshFactory.h"
#include "../Core/Input.h"
#include "../Core/Application.h"

Scene::Scene() :
	shader3D(std::make_unique<Shader>("FirstProject/res/shaders/Shader3D.vert", "FirstProject/res/shaders/Shader3D.frag")),
	occulsionShader(std::make_unique<Shader>("FirstProject/res/shaders/LightDepth.vert", "FirstProject/res/shaders/LightDepth.frag")),
	postProcessShaders(),
	otherShaders(),
	models(), 
	samplingFBO(),
	occulsionFBO(),
	FBO(), 
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
	postProcessShaders.emplace_back(std::make_unique<Shader>("FirstProject/res/shaders/DefaultPostProcess.vert", "FirstProject/res/shaders/DefaultPostProcess.frag"));

	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));

	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_FRONT));

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GLCall(glEnable(GL_MULTISAMPLE));
	GLCall(glEnable(GL_FRAMEBUFFER_SRGB))
}

void Scene::update(float dt) {
	if(Input::isKeyPressed(KeyCode::Equal)) {
		gamma += dt * 0.01;
	}
	if(Input::isKeyPressed(KeyCode::Minus)) {
		gamma -= dt * 0.01;
	}
	camera.update(dt);
}

void Scene::render() {
	

	//Shadowing
	occulsionFBO.bind();
	occulsionShader->bind();
	occulsionShader->setUniformMat4f("lightSpaceMatrix", directionalLights[0].getTransform());
	glViewport(0, 0, 4096, 4096);
	GLCall(glClear(GL_DEPTH_BUFFER_BIT));

	for (std::shared_ptr<Model3D>& model : models) {
		model->render(*occulsionShader);
	}
	glViewport(0, 0, Application::getInstance().getWindow().getWidth(), Application::getInstance().getWindow().getHeight());
	occulsionFBO.bindDepthTexture(5);
	
	samplingFBO.bind();
	GLCall(glClearColor(0.4f, 0.6f, 0.7f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

	//model render
	shader3D->setUniform3f("viewPos", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	shader3D->setUniformMat4f("view", camera.getViewMat());
	shader3D->setUniformMat4f("projection", camera.getProjectionMat());
	shader3D->setUniformMat4f("lightTransform", directionalLights[0].getTransform());
	shader3D->setUniform1i("albedoMap", 0);
	shader3D->setUniform1i("metallicMap", 1);
	shader3D->setUniform1i("roughnessMap", 2);
	shader3D->setUniform1i("normalMap", 3);
	shader3D->setUniform1i("depthMap", 4);
	shader3D->setUniform1i("shadowMap", 5);
	shader3D->setUniform1f("offset", gamma);

	for (std::shared_ptr<Model3D>& model : models) {
		model->render(*shader3D);
	}
	

	//skybox
	skyBox.render(camera);

	//Post-Process

	samplingFBO.writeToFBO(FBO);
	//occulsionFBO.writeToFBO(FBO);
	FBO.unBind();
	FBO.bindColorBufferTexture(8);
	//occulsionFBO.bindDepthTexture(8);
	
	GLCall(glDisable(GL_DEPTH_TEST));
	GLCall(glDisable(GL_CULL_FACE));
	
	GLCall(glClearColor(0.4f, 0.6f, 0.7f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
	
	for (std::shared_ptr<Shader> shader : postProcessShaders) {
		shader->bind();
		shader->setUniform1i("colorBuffer", 8);
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
