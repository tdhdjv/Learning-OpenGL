#include "Input.h"
#include "Application.h"

bool Input::isKeyPressed(KeyCode keycode) {
	auto* window = Application::getInstance().getWindow().getGLFWWindow();
	auto status = glfwGetKey(window, static_cast<int32_t>(keycode));
	return status == GLFW_PRESS;
}