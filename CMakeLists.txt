cmake_minimum_required(VERSION 2.8)

project(bf)

add_definitions(-Wall)
add_definitions(-Wextra)
add_definitions(-Wformat=2)
add_definitions(-Wstrict-aliasing=2)
add_definitions(-Wcast-align)
add_definitions(-Wwrite-strings)
add_definitions(-Wformat-nonliteral)
add_definitions(-Wconversion)
add_definitions(-Wfloat-equal)
add_definitions(-Wpointer-arith)
add_definitions(-Wswitch-enum)


add_executable(bf main.c)

