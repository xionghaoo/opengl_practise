#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "include/stb_image.h"
#include "../headers/illumination.h"

using namespace std;

const float SCREEN_WIDTH = 800.0f;
const float SCREEN_HEIGHT = 600.0f;

void process_input(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Illumination illumination;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    // mac需要
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // 窗口变化事件监听
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // 用glad加载OpenGL的函数指针
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    illumination.initial();
    // 开启深度测试
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);
        // 设置背景颜色
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        illumination.run();

        // 交换缓冲区，图像渲染和显示用到了双缓冲区，前面的缓冲区始终显示渲染完成的画面
        // ，后面的缓冲区执行渲染操作
        glfwSwapBuffers(window);
        // 检查有没有触发事件
        glfwPollEvents();
    }
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        cout << "press escape" << endl;
        glfwSetWindowShouldClose(window, true);
    }
}