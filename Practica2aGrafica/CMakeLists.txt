cmake_minimum_required(VERSION 2.8)
project(Practica2aGrafica C CXX)

# prefer newer versions of OpenGL
set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(SRCS
        pr2a.cpp igvEscena3D.cpp igvEscena3D.h igvInterfaz.cpp igvInterfaz.h)

add_executable(Practica2aGrafica
        ${SRCS})

target_link_libraries(Practica2aGrafica
        OpenGL::OpenGL
        OpenGL::GLU
        ${GLUT_LIBRARIES})