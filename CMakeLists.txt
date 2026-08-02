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

FetchContent_MakeAvailable(glfw)

# Actual compiling
add_executable(MineAscii)

find_package(OpenGL REQUIRED)

target_sources(MineAscii PRIVATE
    src/main.c src/asciibuffer.c
    external/glad/src/glad.c
)

target_include_directories(MineAscii PRIVATE
    "include" "external/glad/include"
)

target_link_libraries(MineAscii PRIVATE glfw OpenGL::GL)
