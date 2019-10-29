cmake_minimum_required(VERSION 2.8)
project(Practica1Grafica C CXX)

# prefer newer versions of OpenGL
set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(SRCS
        pr1.cpp igvInterfaz.cpp igvInterfaz.h)

add_executable(Practica1Grafica
        ${SRCS})

target_link_libraries(Practica1Grafica
        OpenGL::OpenGL
        OpenGL::GLU
        ${GLUT_LIBRARIES})