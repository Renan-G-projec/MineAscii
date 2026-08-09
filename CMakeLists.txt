# Ad Maiorem Dei Gloriam!
cmake_minimum_required(VERSION 3.12)

project(MineAscii C)

# Fetching the contents
include(FetchContent)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG master
)

set(CGLM_SHARED OFF)
set(CGLM_STATIC ON)

FetchContent_Declare(
    cglm
    GIT_REPOSITORY https://github.com/recp/cglm.git
    GIT_TAG master
)

FetchContent_MakeAvailable(glfw cglm)

# Actual compiling
add_executable(MineAscii)

find_package(OpenGL REQUIRED)

target_sources(MineAscii PRIVATE
    src/main.c
    src/engine.c 

    # Graphics
    src/graphics/asciibuffer.c 
    src/graphics/shader.c 
    src/graphics/vao.c 
    src/graphics/vbo.c 
    src/graphics/ebo.c 
    src/graphics/mesh.c 
    src/graphics/input.c 
    src/graphics/camera.c
    src/graphics/texture.c

    # Libraries
    external/glad/src/glad.c 
    external/stb/src/stb_image.c
)

target_include_directories(MineAscii PRIVATE
    "include" "external/glad/include" "external/stb/include"
)

target_link_libraries(MineAscii PRIVATE glfw cglm OpenGL::GL)
