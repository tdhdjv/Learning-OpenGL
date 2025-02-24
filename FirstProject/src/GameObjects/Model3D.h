#pragma once

#include <GLM/glm.hpp>
#include "../GameObjects/Mesh.h"
#include "../GLObjects/VertexLayout.h"
#include "../GLObjects/Texture.h"

struct Material {
	Texture albedoMap;
	Texture metallicMap;
	Texture roughnessMap;
	Texture normalMap;
	Texture displacementMap;
};

struct Vertex3D {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	glm::vec3 tangent;

	static const VertexBufferLayout layout;
};

inline std::vector<float> vertex3DToVertexData(const std::vector<Vertex3D>& vertices) {
    std::vector<float> vertexData(vertices.size() * 11);
    for (int i = 0; i < vertices.size(); i++) {
		Vertex3D vertex = vertices[i];
		vertexData[i * 11]	   = vertex.position.x;
		vertexData[i * 11 + 1] = vertex.position.y;
		vertexData[i * 11 + 2] = vertex.position.z;
		vertexData[i * 11 + 3] = vertex.uv.x;
		vertexData[i * 11 + 4] = vertex.uv.y;
		vertexData[i * 11 + 5] = vertex.normal.x;
		vertexData[i * 11 + 6] = vertex.normal.y;
		vertexData[i * 11 + 7] = vertex.normal.z;
		vertexData[i * 11 + 8] = vertex.tangent.x;
		vertexData[i * 11 + 9] = vertex.tangent.y;
		vertexData[i * 11 + 10] = vertex.tangent.z;
    }
    return vertexData;
}

class Model {
private:
	const Mesh& mesh;
	const Material& material;

	Model(const Mesh& mesh, const Material& material);
};