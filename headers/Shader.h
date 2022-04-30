//
// Created by xionghao on 2022/3/14.
//

#ifndef OPENGL_DEMO_SHADER_H
#define OPENGL_DEMO_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
public:

    Shader() = default;

    unsigned int ID;
    Shader(const char *vertexPath, const char *fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, GLfloat *value) const;
    void setMat4(const std::string &name, glm::mat4 mat) const;
    void setVec3(const std::string &name, float v1, float v2, float v3) const;
    void setVec3(const std::string &name, glm::vec3 v) const;
};

#endif //OPENGL_DEMO_SHADER_H
