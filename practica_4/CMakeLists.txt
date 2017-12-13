cmake_minimum_required(VERSION 2.8.9)
project(Practica4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)


find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(X11 REQUIRED)

include_directories(include ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS} ${X11_INCLUDE_DIR})
file(GLOB SOURCES "src/*.cpp")

message("OpenGL dir: " ${OPENGL_INCLUDE_DIR})
message("Glut dir: " ${GLUT_INCLUDE_DIRS})
message("X11 dir: " ${X11_INCLUDE_DIR})

add_executable(practica4 ${SOURCES})
target_link_libraries(practica4 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${X11_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
