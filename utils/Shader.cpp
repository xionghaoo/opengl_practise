//
// Created by xionghao on 2022/3/14.
//

#include "Shader.h"

void compileShader(unsigned int &, int, const char *);

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexStr, fragmentStr;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    std::string project_path("/Users/destiny/projects/opengl/opengl_practise/");

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(project_path + vertexPath, std::ios::in);
        fShaderFile.open(project_path + fragmentPath, std::ios::in);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexStr = vShaderStream.str();
        fragmentStr = fShaderStream.str();
    } catch (std::ifstream::failure &e) {
        std::cout << "着色器文件读取失败: " << e.what() << std::endl;
        return;
    }
    const char *vertexCode = vertexStr.c_str();
    const char *fragmentCode = fragmentStr.c_str();

    ID = glCreateProgram();
    unsigned int vertexShader;
    compileShader(vertexShader, GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader;
    compileShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentCode);
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // 检查着色器是否链接成功
    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "Program link error: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// 编译着色器代码
void compileShader(unsigned int &shader, int shaderType, const char *shaderCode) {
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    std::cout << "compileShader completed: " << shader << std::endl;
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, GLfloat *value) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
}

void Shader::setVec3(const std::string &name, float v1, float v2, float v3) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(glm::vec3(v1, v2, v3)));
}

void Shader::setVec3(const std::string &name, glm::vec3 v) const {
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(v));
}

void Shader::setMat4(const std::string &name, glm::mat4 mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
