# Ad Maiorem Dei Gloriam!
cmake_minimum_required(VERSION 3.12)

project(MineAscii)

add_executable(MineAscii)

target_sources(MineAscii PRIVATE
    src/main.c src/framebuffer.c
)

target_include_directories(MineAscii PRIVATE
    include
)


