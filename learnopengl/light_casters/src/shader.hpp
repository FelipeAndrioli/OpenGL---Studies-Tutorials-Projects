#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Shader {
    public:
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath);
        unsigned int ID;
        void use();
        void end();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec2(const std::string &name, float x, float y) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w) const;
        void setMat2(const std::string &name, const glm::mat2 &mat2) const;
        void setMat3(const std::string &name, const glm::mat3 &mat3) const;
        void setMat4(const std::string &name, const glm::mat4 &mat4) const;
    private:
        void checkCompileErrors(unsigned int shader, std::string type);
};

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

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat2) const {
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat2[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat3) const {
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat3[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat4) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat4[0][0]);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR" << "\n" << infoLog << std::endl;
        }
    }
}

#endif
