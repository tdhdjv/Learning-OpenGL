#include "Application.h"

#include <memory>
#include <GLFW/glfw3.h>

#include "../GameObjects/MeshFactory.h"
#include "../GLObjects/Texture2D.h"

Application::Application(const char* name):window(1000, 800, name){
	window.createWindow();
	scene = std::make_unique<Scene>();

	std::shared_ptr<Texture2D> alebdo = std::make_shared < Texture2D>("FirstProject/res/image/shiny wood/albedo.png", GL_RGB);
	std::shared_ptr<Texture2D> metallicMap = std::make_shared < Texture2D>("FirstProject/res/image/shiny wood/metallic.png", GL_RED);
	std::shared_ptr<Texture2D> smoothnessMap = std::make_shared < Texture2D>("FirstProject/res/image/shiny wood/roughness.jpg", GL_RED);
	std::shared_ptr<Texture2D> normalMap = std::make_shared < Texture2D>("FirstProject/res/image/toy_box/toy_box_normal.png", GL_RGB);
	std::shared_ptr<Texture2D> depthMap = std::make_shared < Texture2D>("FirstProject/res/image/toy_box/toy_box_disp.png", GL_RGBA);

	std::shared_ptr<Mesh> mesh1 = std::make_shared<Mesh>(createCubeMesh());
	mesh1->setPosition({ 0, 0, 5 });
	std::shared_ptr<Mesh> mesh2 = std::make_shared<Mesh>(createCubesphereMesh(16));
	mesh2->setPosition({ 2, 0, 5 });
	std::shared_ptr<Mesh> mesh3 = std::make_shared<Mesh>(createQuad(0, { 0, 0, -1 }, {0, 1, 0}));
	mesh3->setPosition({ -2, 0, 5 });
	std::shared_ptr<Material> material = std::make_shared<Material>(alebdo, metallicMap, smoothnessMap, normalMap, depthMap);
	std::shared_ptr<Model3D> model1 = std::make_shared<Model3D>(mesh1, material);
	std::shared_ptr<Model3D> model2 = std::make_shared<Model3D>(mesh2, material);
	std::shared_ptr<Model3D> model3 = std::make_shared<Model3D>(mesh3, material);

	scene->addModel(model1);
	scene->addModel(model2);
	scene->addModel(model3);
}

Application::~Application() {
}

void Application::run() {
	while (!window.shouldClose()) {
		GLCall(glClearColor(0.4f, 0.6f, 0.7f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
		scene->render();

		glfwPollEvents();
		window.swapBuffer();
	}
}