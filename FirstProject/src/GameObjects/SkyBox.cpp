#include <iostream>

#include "SkyBox.h"
#include "../GLObjects/ErrorCheck.h"
#include "../GameObjects/MeshFactory.h"
#include "../vendor/std_image/std_image.h"

SkyBox::SkyBox(const std::string right, const std::string left, const std::string top, const std::string bottom, const std::string front, const std::string back)
    :shader(std::make_unique<Shader>("FirstProject/res/shaders/SkyBox.vert", "FirstProject/res/shaders/SkyBox.frag")),
    skyBoxMesh(std::make_unique<Mesh>(createCubeMesh())),
    textureID(0)
{
    const const std::string faces[6] = { right, left, top, bottom, front, back };

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrComponents;
    for (unsigned int i = 0; i < 6; i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glActiveTexture(GL_TEXTURE9);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}

SkyBox::~SkyBox() {

}

void SkyBox::render(const Camera& camera) {
    shader->bind();
    shader->setUniform1i("skybox", 9);

    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_BACK);

    //removes the 4th row, column of the matrix to remove the translation
    glm::mat4 noTransView = glm::mat4(glm::mat3(camera.getViewMat()));
    shader->setUniformMat4f("view", noTransView);
    shader->setUniformMat4f("projection", camera.getProjectionMat());

    skyBoxMesh->bind();

    unsigned int count = skyBoxMesh->getIndexCount();
    GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));

    glDepthFunc(GL_LESS);
    glCullFace(GL_FRONT);
}
