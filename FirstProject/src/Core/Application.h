#pragma once

#include <memory.h>
#include "Scene.h"
#include "Window.h"

class Application {
public:
	Application(const char* name);
	~Application();
	void run();

private:
	Window window;
	std::unique_ptr<Scene> scene;
};