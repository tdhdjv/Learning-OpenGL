#include <GLAD/glad.h>
#include <iostream>

#include "ErrorCheck.h"
#include "Renderer.h"
#include "../GameObjects/MeshFactory.h"

Renderer::Renderer(): lightMesh(std::make_unique<Mesh>(createCubesphereMesh(32))) {
    lightMesh->setScale(glm::vec3(0.3f));
}

void Renderer::render(Shader& shader, Mesh& mesh) {
    mesh.bind();
    shader.bind();
    shader.setUniformMat4f("model", mesh.getModelMat());
    
    // render
    unsigned int count = mesh.getIndexCount();
    GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));
}

void Renderer::renderPointLight(Shader& shader, PointLight pointLight) {
    lightMesh->setPosition(pointLight.position);
    shader.setUniformMat4f("model", lightMesh->getModelMat());
    shader.setUniform3f("lightColor", pointLight.color.r, pointLight.color.g, pointLight.color.b);
    lightMesh->bind();

    shader.bind();

    // render
    unsigned int count = lightMesh->getIndexCount();
    GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));

    lightMesh->unBind();

}