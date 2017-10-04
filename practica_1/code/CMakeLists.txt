cmake_minimum_required(VERSION 2.8.9)
project(Practica1_OpenGL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(practica1 ${SOURCES})

include_directories(include ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
