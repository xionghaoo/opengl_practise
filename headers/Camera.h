//
// Created by xionghao on 2022/3/18.
//

#ifndef OPENGL_TEST_CAMERA_H
#define OPENGL_TEST_CAMERA_H

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

// 鼠标移动的方向
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// 默认值
const float PITCH = 0.0f;
// 朝向Z轴负方向
const float YAW = -90.0f;
// 透视视角
const float FOV = 45.0f;
const float SENSITIVITY = 0.1f;
const float SPEED = 2.5f;
const float ZOOM = 45.0f;

/**
 * 摄像机
 */
class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 Fov;
    glm::vec3 WorldUp;

    // 欧拉角，用于三维旋转
    // 偏航角
    float Yaw;
    // 俯仰角
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW,
        float pitch = PITCH
    ): Position(position), WorldUp(up), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
        Front = glm::vec3(0.0f, 0.0f, -1.0f);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    };

    glm::mat4 GetViewMatrix() {
        // 生成观察矩阵，
        return glm::lookAt(Position, Position + Front, Up);
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
        float speed = SPEED * deltaTime;
        switch (direction) {
            case Camera_Movement::FORWARD:
                Position += Front * speed;
                break;;
            case Camera_Movement::BACKWARD:
                Position -= Front * speed;
                break;
            case Camera_Movement::LEFT:
                Position -= Right * speed;
                break;
            case Camera_Movement::RIGHT:
                Position += Right * speed;
                break;
        }
    }

    // 鼠标移动处理
    void ProcessMouseMove(double xoffset, double yoffset) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;
        Pitch += yoffset;
        Yaw += xoffset;
        // 限制俯仰角，避免发生屏幕翻转
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
        updateCameraVectors();
    }

    // 鼠标滚动处理
    void ProcessMouseScroll(float yoffset) {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f) {
            Zoom = 1.0f;
        } else if(Zoom > 45.0f) {
            Zoom = 45.0f;
        }
    }

private:
    void updateCameraVectors() {
        // 计算摄像头方向向量(单位向量)
        glm::vec3 front;
        front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
        front.y = sin(glm::radians(Pitch));
        front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
        Front = glm::normalize(front);

        // 叉乘得到摄像机右向量和上向量
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Front, Right));
    }

};


#endif //OPENGL_TEST_CAMERA_H
