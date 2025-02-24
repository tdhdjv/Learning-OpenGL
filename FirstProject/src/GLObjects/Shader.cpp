#include <GLAD/glad.h>

#include <iostream>
#include <sstream>
#include <fstream>

#include "Shader.h"
#include "ErrorCheck.h"

Shader::Shader(const std::string &vertexFilePath, const std::string &fragmentFilePath) {
    this->vertexFilePath = vertexFilePath;
    this->fragmentFilePath = fragmentFilePath;
    createShader(vertexFilePath, fragmentFilePath);
}

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath, const std::string& geometryFilePath) {
    this->vertexFilePath = vertexFilePath;
    this->fragmentFilePath = fragmentFilePath;
    this->geometryFilePath = geometryFilePath;

    rendererID = glCreateProgram();

    vertexShader = compileShader(GL_VERTEX_SHADER, vertexFilePath);
    geometryShader = compileShader(GL_GEOMETRY_SHADER, geometryFilePath);
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentFilePath);

    GLCall(glAttachShader(rendererID, vertexShader));
    GLCall(glAttachShader(rendererID, geometryShader));
    GLCall(glAttachShader(rendererID, fragmentShader));
    GLCall(glLinkProgram(rendererID));

    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(geometryShader));
    GLCall(glDeleteShader(fragmentShader));
}

Shader::~Shader() {
    GLCall(glDeleteProgram(rendererID));
}

void Shader::bind() const{
    GLCall(glUseProgram(rendererID));
}

void Shader::unBind() const {
    GLCall(glUseProgram(0));
}

std::string Shader::parseShader(const std::string &filepath) const {
    std::string line;
    std::string source;
    std::ifstream is;
    is.open(filepath);
    if(is.is_open()) {
        while(std::getline(is, line)) {
            source += line + "\n";
        }
    }
    else {
        std::cout << "NOT a valid filepath" << std::endl;
    }
    is.close();
    return source;
}


void Shader::setUniform3f(const std::string name, float f1, float f2, float f3) {
    GLCall(glUniform3f(getUniformLocation(name), f1, f2, f3));
}

void Shader::setUniform3fv(const std::string name, glm::vec3 vec3Array[], unsigned int count) {
    GLCall(glUniform3fv(getUniformLocation(name), count, &vec3Array[0][0]));
}

void Shader::setUniform1i(const std::string name, int i1) {
    GLCall(glUniform1i(getUniformLocation(name), i1));
}

void Shader::setUniform1f(const std::string name, float f1) {
    GLCall(glUniform1f(getUniformLocation(name), f1));
}

void Shader::setUniform2f(const std::string name, float f1, float f2) {
    GLCall(glUniform2f(getUniformLocation(name), f1, f2));
}


void Shader::setUniformMat4f(const std::string name, glm::mat4 matrix) {
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}


void Shader::setUniformDirectionalLights(const std::vector<DirectionalLight> dirLights) {
    GLCall(glUniform1i(getUniformLocation("dirLightCount"), dirLights.size()));
    for (unsigned int i = 0; i < dirLights.size(); i++) {
        DirectionalLight light = dirLights[i];
        std::stringstream oss1;
        oss1 << "dirLights[" << i << "].direction";
        std::stringstream oss2;
        oss2 << "dirLights[" << i << "].color";
        GLCall(glUniform3f(getUniformLocation(oss1.str()), light.direction.x, light.direction.y, light.direction.z));
        GLCall(glUniform3f(getUniformLocation(oss2.str()), light.color.r, light.color.g, light.color.b));
    }
}

void Shader::setUniformPointLights(const std::vector<PointLight> pointLights) {
    GLCall(glUniform1i(getUniformLocation("pointLightCount"), pointLights.size()));
    for (unsigned int i = 0; i < pointLights.size(); i++) {
        PointLight light = pointLights[i];
        std::stringstream oss1;
        oss1 << "pointLights[" << i << "].position";
        std::stringstream oss2;
        oss2 << "pointLights[" << i << "].color";
        GLCall(glUniform3f(getUniformLocation(oss1.str()), light.position.x, light.position.y, light.position.z));
        GLCall(glUniform3f(getUniformLocation(oss2.str()), light.color.r, light.color.g, light.color.b));
    }
}

int Shader::compileShader(const unsigned int type, const std::string &filePath) const{
    unsigned int shader;
    shader = glCreateShader(type);
    std::string source = parseShader(filePath);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char message[1024];
        glGetShaderInfoLog(shader, 1024, &length, message);
        std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "Vertex": "Fragment") << " Shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(shader);

        return 0;
    }

    return shader;
}

void Shader::createShader(const std::string &vertexFilePath, const std::string &fragmentFilePath) {
    rendererID = glCreateProgram();

    vertexShader = compileShader(GL_VERTEX_SHADER, vertexFilePath);
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentFilePath);
    
    GLCall(glAttachShader(rendererID, vertexShader));
    GLCall(glAttachShader(rendererID, fragmentShader));
    GLCall(glLinkProgram(rendererID));

    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));
}

int Shader::getUniformLocation(const std::string name) {
    int location = glGetUniformLocation(rendererID, name.c_str());
    if(location == -1) {
        std::cout << "<Warning!> Uniform named '" << name << "' is Unused or doesn't exist" << std::endl;
    }
    return location;
}