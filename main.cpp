#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
//#include "demo/illumination.h"
#include "demo/Material.h"

//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <iostream>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

void process_input(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);

float lastX = Base::SCREEN_WIDTH / 2;
float lastY = Base::SCREEN_HEIGHT / 2;

bool firstMouse = true;

//Illumination illumination;
Material material;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**) {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    glfwInit();
    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    GLFWwindow *window = glfwCreateWindow(Base::SCREEN_WIDTH, Base::SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);
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
    glfwSwapInterval(1); // Enable vsync

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // 加载字体
    ImFont* font = io.Fonts->AddFontFromFileTTF("/Users/destiny/projects/opengl/opengl_practise/assets/QingNiaoHuaGuangXingKai-2.ttf", 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
    io.Fonts->GetGlyphRangesChineseSimplifiedCommon(); // 这个是只加载常用汉字，是参考的维基百科上的2500个汉字，但是现在的常用汉字是3500个，所以少了1000个
    // io.Fonts->GetGlyphRangesChineseFull(); // 这个是加载字体中所有的汉字

    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    char buf[1024] = "This is Buffer";
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;

    material.initial();

//    Model ourModel(FileSystem::getPath("resources/objects/backpack/backpack.obj"));

    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        process_input(window);
        glfwPollEvents();
        // 设置背景颜色
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        material.run(r, g, b);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 向ImGui窗口添加内容
        ImGui::Text(u8"灯光颜色调节");
//        if (ImGui::Button("Save")) {
//            cout << "save: " << buf << ", " << f << endl;
//        }
//        ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
        ImGui::SliderFloat("red", &r, 0.0f, 1.0f);
        ImGui::SliderFloat("green", &g, 0.0f, 1.0f);
        ImGui::SliderFloat("blue", &b, 0.0f, 1.0f);

        // Rendering ImGui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
//        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
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

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    material.camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    cout << "x = " << xposIn << ", y = " << yposIn << endl;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    // 因为观察者坐标系和鼠标坐标系y轴是反的，所以计算偏移时要带上负号
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    material.camera.ProcessMouseMovement(xoffset, yoffset);
}