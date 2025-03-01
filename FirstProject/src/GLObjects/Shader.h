#pragma once
#include <string>

#include "../GameObjects/Light.h"
#include "glm/glm.hpp"
#include "glm/matrix.hpp"

class Shader {
private:
    unsigned int rendererID;
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int geometryShader;

    std::string vertexFilePath;
    std::string fragmentFilePath;
    std::string geometryFilePath;

public:
    Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
    Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath, const std::string& geometryShader);
    Shader(const Shader&) = delete;
    ~Shader();
    
    void bind() const;

    void unBind() const;

    void setUniform3f(const std::string name, float f1, float f2, float f3) const;
    void setUniform3fv(const std::string name, glm::vec3 vec3Array[], unsigned int count) const;
    void setUniformMat4f(const std::string name, glm::mat4 matrix) const;
    void setUniform1i(const std::string name, int i1) const;
    void setUniform1f(const std::string name, float f1) const;
    void setUniform2f(const std::string name, float f1, float f2) const;
    void setUniformDirectionalLights(const std::vector<DirectionalLight> dirLights) const;
    void setUniformPointLights(const std::vector<PointLight> pointLights) const;

private:
    std::string parseShader(const std::string &filepath) const;
    int compileShader(const unsigned int type, const std::string &filePath) const;
    void createShader(const std::string &vertexFilePath, const std::string &fragmentFilePath);
    int getUniformLocation(const std::string name) const;
};