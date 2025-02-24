#pragma once

#include "../GLObjects/VertexLayout.h"
#include <GLM/vec3.hpp>
#include <GLM/vec2.hpp>
#include <vector>

struct PointLight {
	glm::vec3 position;
	glm::vec3 color;
};

struct DirectionalLight {
	glm::vec3 direction;
	glm::vec3 color;
};
