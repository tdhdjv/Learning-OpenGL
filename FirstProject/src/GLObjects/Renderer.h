#pragma once

#include <memory>
#include "../GameObjects/Mesh.h"
#include "../GameObjects/Constructs.h"
#include "VertexArray.h"
#include "Shader.h"

class Renderer {
private:
    std::unique_ptr<Mesh> lightMesh;
public:
    Renderer();
    void render(Shader& shader, Mesh& mesh);

    void renderPointLight(Shader& shader, PointLight pointLight);
};