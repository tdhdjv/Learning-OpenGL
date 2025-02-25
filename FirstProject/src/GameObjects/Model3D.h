#pragma once

#include <GLM/glm.hpp>
#include "../GameObjects/Mesh.h"
#include "../GLObjects/VertexLayout.h"
#include "../GLObjects/Texture2D.h"


struct Material {
	const std::shared_ptr<Texture2D> albedoMap;
	const std::shared_ptr<Texture2D> metallicMap;
	const std::shared_ptr<Texture2D> roughnessMap;
	const std::shared_ptr<Texture2D> normalMap;
	const std::shared_ptr<Texture2D> displacementMap;

	Material(std::shared_ptr<Texture2D> albedo, std::shared_ptr<Texture2D> metallic, std::shared_ptr<Texture2D> roughness,
		std::shared_ptr<Texture2D> normal, std::shared_ptr<Texture2D>displacement)
		: albedoMap(albedo),
		metallicMap(metallic),
		roughnessMap(roughness),
		normalMap(normal),
		displacementMap(displacement)
	{}

	void bindTextures(int starting_slot) const {
		albedoMap->bind(starting_slot);
		metallicMap->bind(starting_slot+1);
		roughnessMap->bind(starting_slot+2);
		normalMap->bind(starting_slot+3);
		displacementMap->bind(starting_slot+4);
	}
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

class Model3D {
private:

	//Using a shared pointers since multiple models can have the same mesh/material
	const std::shared_ptr<Mesh> mesh;
	const std::shared_ptr<Material> material;

public:
	Model3D(const std::shared_ptr<Mesh> mesh, const std::shared_ptr<Material> material);
	void render(const Shader& shader) const;
};