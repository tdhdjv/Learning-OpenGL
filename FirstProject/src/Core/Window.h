#pragma once

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
	Window(int width, int height, const char* name);
	~Window();

	void createWindow();
	void swapBuffer();
	inline GLFWwindow* getGLFWWindow() const { return glfwWindow; };
	inline bool shouldClose() { return glfwWindowShouldClose(glfwWindow); };
private:
	int width;
	int height;
	const char* name;
	GLFWwindow* glfwWindow;
};