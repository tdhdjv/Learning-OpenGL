#pragma once

#include "Mesh.h"
#include "GLM/glm.hpp"

MeshData createCubeMesh();

MeshData createCubesphereMesh(unsigned int subdivisions);

MeshData createQuad3D(unsigned int subdivisions, glm::vec3 up, glm::vec3 front);

MeshData createQuad2D();