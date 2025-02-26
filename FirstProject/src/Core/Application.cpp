#include "Application.h"

#include <memory>
#include <GLFW/glfw3.h>

#include "../GameObjects/MeshFactory.h"
#include "../GLObjects/Texture2D.h"

Application* Application::instance = nullptr;

Application::Application(const char* name):window(1000, 800, name){
	window.createWindow();
	scene = std::make_unique<Scene>();

	if (instance == nullptr) {
		instance = this;
	}
	else if (instance != this) {
		std::cout << "[Warning] Another Instance of an application was Created!!!!" << std::endl;
	}

	std::shared_ptr<Texture2D> alebdoBox = std::make_shared < Texture2D>("FirstProject/res/image/shiny wood/albedo.png", GL_RGB);
	std::shared_ptr<Texture2D> metallicMapBox = std::make_shared < Texture2D>("FirstProject/res/image/shiny wood/metallic.png", GL_RED);
	std::shared_ptr<Texture2D> smoothnessMapBox = std::make_shared < Texture2D>("FirstProject/res/image/shiny wood/roughness.jpg", GL_RED);
	std::shared_ptr<Texture2D> normalMapBox = std::make_shared < Texture2D>("FirstProject/res/image/toy_box/toy_box_normal.png", GL_RGB);
	std::shared_ptr<Texture2D> depthMapBox = std::make_shared < Texture2D>("FirstProject/res/image/toy_box/toy_box_disp.png", GL_RGBA);
	
	std::shared_ptr<Texture2D> alebdoRough = std::make_shared < Texture2D>("FirstProject/res/image/rough/albedo.png", GL_RGB);
	std::shared_ptr<Texture2D> metallicMapRough = std::make_shared < Texture2D>("FirstProject/res/image/rough/metallic.png", GL_RED);
	std::shared_ptr<Texture2D> smoothnessMapRough = std::make_shared < Texture2D>("FirstProject/res/image/rough/roughness.png", GL_RED);
	std::shared_ptr<Texture2D> normalMapRough = std::make_shared < Texture2D>("FirstProject/res/image/rough/normal.png", GL_RGB);
	std::shared_ptr<Texture2D> depthMapRough = std::make_shared < Texture2D>("FirstProject/res/image/rough/displacement.png", GL_RED);
	
	std::shared_ptr<Texture2D> alebdoCir = std::make_shared < Texture2D>("FirstProject/res/image/circuitry/albedo.png", GL_RGB);
	std::shared_ptr<Texture2D> metallicMapCir = std::make_shared < Texture2D>("FirstProject/res/image/circuitry/metallic.png", GL_RED);
	std::shared_ptr<Texture2D> smoothnessMapCir = std::make_shared < Texture2D>("FirstProject/res/image/circuitry/roughness.png", GL_RED);
	std::shared_ptr<Texture2D> normalMapCir = std::make_shared < Texture2D>("FirstProject/res/image/circuitry/normal.png", GL_RGB);
	std::shared_ptr<Texture2D> depthMapCir = std::make_shared < Texture2D>("FirstProject/res/image/shiny wood/displacement.png", GL_RED);

	std::shared_ptr<Mesh> mesh1 = std::make_shared<Mesh>(createCubeMesh());
	mesh1->setPosition({ 0, 0, 5 });
	std::shared_ptr<Mesh> mesh2 = std::make_shared<Mesh>(createCubesphereMesh(32));
	mesh2->setPosition({ 0, 0, 3 });
	std::shared_ptr<Mesh> mesh3 = std::make_shared<Mesh>(createQuad3D(0, { 0, 0, -1 }, {0, 1, 0}));
	mesh3->setPosition({ 0, 0, 1 });
	std::shared_ptr<Material> materialBox = std::make_shared<Material>(
		alebdoBox,
		metallicMapBox,
		smoothnessMapBox,
		normalMapBox,
		depthMapBox
	);
	std::shared_ptr<Material> materialRough = std::make_shared<Material>(
		alebdoRough,
		metallicMapRough,
		smoothnessMapRough,
		normalMapRough,
		depthMapRough
	);


	std::shared_ptr<Material> materialCir = std::make_shared<Material>(
		alebdoCir,
		metallicMapCir,
		smoothnessMapCir,
		normalMapCir,
		depthMapCir
	);

	std::shared_ptr<Model3D> model1 = std::make_shared<Model3D>(mesh1, materialBox);
	std::shared_ptr<Model3D> model2 = std::make_shared<Model3D>(mesh2, materialRough);
	std::shared_ptr<Model3D> model3 = std::make_shared<Model3D>(mesh3, materialCir);

	scene->addModel(model1);
	scene->addModel(model2);
	scene->addModel(model3);

	scene->addDirectionalLight({ {0.0, 1.0, -1.0}, {10.0, 10.0, 10.0} });
	scene->addPointLight({ {0.0, 0.0, 0.0}, {10.0, 10.0, 10.0} });
}

Application::~Application() {
}

void Application::run() {
	float dt;
	float previousTime = glfwGetTime();
	while (!window.shouldClose()) {
		float currentTime = glfwGetTime();
		dt = currentTime - previousTime;
		previousTime = currentTime;

		//updates
		scene->update(dt);

		//rendering
		scene->render();

		glfwPollEvents();
		window.swapBuffer();
	}
}