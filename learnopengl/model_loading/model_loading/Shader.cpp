#include <iostream>
#include <glad/glad.h>
#include <glm.hpp>

#include "Shader.h"

#include <sstream>
#include <fstream>
#include <string>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath) {
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

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vShaderCode, NULL);
    glCompileShader(vertex_shader);
    checkCompileErrors(vertex_shader, "VERTEX");

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fShaderCode, NULL);
    glCompileShader(fragment_shader);
    checkCompileErrors(fragment_shader, "FRAGMENT");

    unsigned int geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);

    if (geometryShaderPath != nullptr) {
        const char* gShaderCode = geometryShaderCode.c_str();
        glShaderSource(geometry_shader, 1, &gShaderCode, NULL);
        glCompileShader(geometry_shader);
        checkCompileErrors(geometry_shader, "GEOMETRY");
    }

    ID = glCreateProgram();

    glAttachShader(ID, vertex_shader);
    glAttachShader(ID, fragment_shader);

    if (geometryShaderPath != nullptr) {
        glAttachShader(ID, geometry_shader);
    }

    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    if (geometryShaderPath != nullptr) {
        glDeleteShader(geometry_shader);
    }
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::end() {
    glDeleteProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
