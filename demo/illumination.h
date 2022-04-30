//
// Created by xionghao on 2022/4/29.
//

#ifndef OPENGL_PRACTISE_ILLUMINATION_H
#define OPENGL_PRACTISE_ILLUMINATION_H

#include "../utils/Camera.h"
#include "../utils/Shader.h"

class Illumination {
public:
    Illumination() = default;

    void initial();
    void run(float, float, float);
private:
    Shader lightingShader;
    Shader cubeShader;
    unsigned int VBO, cubeVAO;
    unsigned int lightCubeVAO;

    const float SCREEN_WIDTH = 1280.0f;
    const float SCREEN_HEIGHT = 720.0f;

    Camera camera = Camera(glm::vec3(0.0f, 1.0f, 5.0f));

    glm::vec3 lightPos = glm::vec3 (1.0f, 1.0f, 3.0f);
};


#endif //OPENGL_PRACTISE_ILLUMINATION_H
