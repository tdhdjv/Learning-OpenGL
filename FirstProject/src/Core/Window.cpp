#include "Window.h"
#include "../GLObjects/ErrorCheck.h"
#include <iostream>

Window::Window(int width, int height, const char* name):
	width(width), height(height), name(name), glfwWindow(nullptr) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window::~Window() {
	glfwTerminate();
}

void Window::createWindow() {
	glfwWindow = glfwCreateWindow(width, height, name, NULL, NULL);
	if (glfwWindow == NULL) {
		glfwTerminate();
		std::cout << "Failed to create Window" << std::endl;
		return;
	}
	glfwMakeContextCurrent(glfwWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
}

void Window::swapBuffer() {
	glfwSwapBuffers(glfwWindow);
}