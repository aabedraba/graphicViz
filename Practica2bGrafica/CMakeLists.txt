cmake_minimum_required(VERSION 2.8)
project(Practica2bGrafica C CXX)

# prefer newer versions of OpenGL
set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(SRCS
        pr2b.cpp igvEscena3D.cpp igvEscena3D.h igvInterfaz.cpp igvInterfaz.h igvCamara.cpp igvCamara.h
        igvPunto3D.cpp igvPunto3D.h)

add_executable(Practica2bGrafica
        ${SRCS})

target_link_libraries(Practica2bGrafica
        OpenGL::OpenGL
        OpenGL::GLU
        ${GLUT_LIBRARIES})