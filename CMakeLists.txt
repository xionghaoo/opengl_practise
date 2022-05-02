cmake_minimum_required(VERSION 3.22)
project(opengl_practise)

set(CMAKE_CXX_STANDARD 14)
set(ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

set(GLFW_HOME "/usr/local/Cellar/glfw/3.3.6")
set(GLAD_HOME "/usr/local/include/glad")

# 设置头文件目录
include_directories("${GLFW_HOME}/include")
include_directories("${GLAD_HOME}/include")

# 添加 GLFW3 预编译库
add_library(glfw SHARED IMPORTED)
SET_TARGET_PROPERTIES(glfw PROPERTIES IMPORTED_LOCATION "${GLFW_HOME}/lib/libglfw.3.dylib")

# 添加imgui
set(LIB_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(imgui_Includes "${LIB_FOLDER}/imgui/")
add_library(imgui STATIC
        ${LIB_FOLDER}/imgui/imgui.cpp
        ${LIB_FOLDER}/imgui/imgui_draw.cpp
        ${LIB_FOLDER}/imgui/imgui_demo.cpp
        ${LIB_FOLDER}/imgui/imgui_tables.cpp
        ${LIB_FOLDER}/imgui/imgui_widgets.cpp)


# glm opengl 线性代数库
include_directories(lib/include lib/imgui/backends utils ${imgui_Includes})

#add_executable(
#        opengl_practise
#        main.cpp
#        "lib/glad.c"
#        lib/include/stb_image.h
#        ${LIB_FOLDER}/imgui/backends/imgui_impl_opengl3.cpp
#        ${LIB_FOLDER}/imgui/backends/imgui_impl_glfw.cpp
#        utils/Shader.cpp
#        utils/Camera.cpp
#        # demo部分
#        demo/illumination.cpp
#)

add_executable(
        opengl_practise
        main.cpp
        "lib/glad.c"
        lib/include/stb_image.h
        ${LIB_FOLDER}/imgui/backends/imgui_impl_opengl3.cpp
        ${LIB_FOLDER}/imgui/backends/imgui_impl_glfw.cpp
        utils/Shader.cpp
        utils/Camera.cpp
        # demo部分
        demo/Material.cpp
        demo/Material.h
        demo/Base.h
)

# 链接 GLFW GLAD OpenGL
target_link_libraries(opengl_practise glfw "-framework OpenGL" imgui)
