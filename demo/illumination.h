//
// Created by xionghao on 2022/4/29.
//

#ifndef OPENGL_PRACTISE_ILLUMINATION_H
#define OPENGL_PRACTISE_ILLUMINATION_H

#include "Shader.h"
#include "Base.h"

class Illumination : Base {
public:
    Illumination() = default;

    void initial() override;
    void run(float, float, float) override;
private:
    Shader lightingShader;
    Shader cubeShader;
    unsigned int VBO = 0, cubeVAO = 0;
    unsigned int lightCubeVAO = 0;

    glm::vec3 lightPos = glm::vec3 (1.0f, 1.0f, 3.0f);
};


#endif //OPENGL_PRACTISE_ILLUMINATION_H
