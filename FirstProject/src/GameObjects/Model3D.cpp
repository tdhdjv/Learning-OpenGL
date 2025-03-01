#include "Model3D.h"

#include "../GLObjects/ErrorCheck.h"

const std::shared_ptr<VertexBufferLayout> Vertex3D::layout = []{
	std::shared_ptr<VertexBufferLayout> layout = std::make_shared<VertexBufferLayout>();
	layout->push<float>(3);
	layout->push<float>(2);
	layout->push<float>(3);
	layout->push<float>(3);
	return layout;
}();

Model3D::Model3D(const std::shared_ptr<Mesh> mesh, const std::shared_ptr<Material> material):mesh(mesh), material(material) {}

void Model3D::render(const Shader& shader) const {
	mesh->bind();
	shader.bind();

	//set the uniforms
	shader.setUniformMat4f("model", mesh->getModelMat());

	//set material
	material->bindTextures(0);

	int count = mesh->getIndexCount();
	GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));
}
