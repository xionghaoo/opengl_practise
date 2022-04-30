//
// Created by xionghao on 2022/4/29.
//

#ifndef OPENGL_PRACTISE_ILLUMINATION_H
#define OPENGL_PRACTISE_ILLUMINATION_H


#include "Shader.h"

class Illumination {
public:
    Illumination() = default;

    void initial();
    void run();
private:
    Shader lightingShader;
    Shader cubeShader;
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;

    const float SCREEN_WIDTH = 800.0f;
    const float SCREEN_HEIGHT = 600.0f;
};


#endif //OPENGL_PRACTISE_ILLUMINATION_H
