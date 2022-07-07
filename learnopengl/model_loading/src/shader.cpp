#include "shader.h"

#include <iostream>

//#include <glad/glad.h>
#include "../dependencies/glad/build/include/glad/glad.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath = nullptr) {
    std::string vertexShaderCode;
    std::string fragmentShaderCode;
    std::string geometryShaderCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    std::ifstream geometryShaderFile;

    vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    geometryShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);

        std::stringstream vShaderStream;
        std::stringstream fShaderStream;

        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexShaderCode = vShaderStream.str();
        fragmentShaderCode = fShaderStream.str();

        if (geometryShaderPath != nullptr) {
            geometryShaderFile.open(geometryShaderPath);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryShaderCode = gShaderStream.str();
        }

    } catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    const char* vShaderCode = vertexShaderCode.c_str();
    const char* fShaderCode = fragmentShaderCode.c_str();
    const char* gShaderCode = nullptr;

    unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glCompileShader(VertexShader);
    checkCompileErrors(VertexShader, "VERTEX");
    glCompileShader(FragmentShader);
    checkCompileErrors(FragmentShader, "FRAGMENT");
    
    glAttachShader(ID, VertexShader);
    glAttachShader(ID, FragmentShader);

    if (geometryShaderPath != nullptr) {
        gShaderCode = geometryShaderCode.c_str();
    
        unsigned int GeometryShader = 0;
        GeometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glCompileShader(GeometryShader);
        checkCompileErrors(GeometryShader, "GEOMETRY");
        glAttachShader(ID, GeometryShader);
    }

    glLinkProgram(ID);

};

void Shader::checkCompileErrors(unsigned int ID, std::string type) {
    int success;
    char infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(ID, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(ID, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(ID, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR" << "\n" << infoLog << std::endl;
        }
    }
}











