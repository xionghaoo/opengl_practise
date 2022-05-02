//
// Created by xionghao on 2022/5/2.
//

#ifndef OPENGL_PRACTISE_BASE_H
#define OPENGL_PRACTISE_BASE_H
#include "Camera.h"

class Base {
public:
    constexpr static const float SCREEN_WIDTH = 1280.0f;
    constexpr static const float SCREEN_HEIGHT = 720.0f;
    Camera camera = Camera(glm::vec3(0.0f, 1.0f, 5.0f));

protected:
    virtual void initial() = 0;
    virtual void run(float, float, float) = 0;
};

#endif //OPENGL_PRACTISE_BASE_H
