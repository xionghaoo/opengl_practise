//
// Created by xionghao on 2022/5/2.
//

#ifndef OPENGL_PRACTISE_MATERIAL_H
#define OPENGL_PRACTISE_MATERIAL_H
#include "Base.h"
#include "Shader.h"

class Material : public Base {
public:
    void initial() override;
    void run(float d, float d1, float d2) override;
private:
    Shader lightShader;
    Shader cubeShader;
    unsigned int VBO = 0, cubeVAO = 0;
    unsigned int lightCubeVAO = 0;

    glm::vec3 lightPos = glm::vec3 (1.2f, 1.0f, 2.0f);
};


#endif //OPENGL_PRACTISE_MATERIAL_H
