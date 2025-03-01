#pragma once

#include "../GLObjects/VertexLayout.h"
#include <GLM/vec3.hpp>
#include <GLM/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

struct PointLight {
	glm::vec3 position;
	glm::vec3 color;
};

struct DirectionalLight {
private:
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 transform;
public:
	glm::vec3 direction;
	glm::vec3 color;

	DirectionalLight(const glm::vec3& direction, const glm::vec3& color) :direction(direction), color(color) {
		float near_plane = 0.01f, far_plane = 20.0f;
		projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		view = glm::lookAt(2.0f*glm::normalize(direction), {0, 0, 0}, {0, 1, 0});
		transform = projection * view;
	}

	inline const glm::mat4 getView() const { return view; }

	inline const glm::mat4 getProjection() const { return projection; }

	inline const glm::mat4 getTransform() const { return transform; }
};
