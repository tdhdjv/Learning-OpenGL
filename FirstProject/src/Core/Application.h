#pragma once

#include <memory.h>
#include "Scene.h"
#include "Window.h"

class Application {
public:
	Application(const char* name);
	~Application();
	void run();
	inline const Window& getWindow() const { return window; }
	inline const static Application& getInstance() { return *instance; };
private:
	Window window;
	std::unique_ptr<Scene> scene;
	
	static Application* instance;
};