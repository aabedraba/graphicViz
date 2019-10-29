cmake_minimum_required(VERSION 2.8)
project(Practica3aGrafica C CXX)

# prefer newer versions of OpenGL
set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(SRCS
        pr3a.cpp igvPunto3D.h igvPunto3D.cpp igvMallaTriangulos.h igvMallaTriangulos.cpp igvMallaTriangulos.cpp igvInterfaz.h
        igvInterfaz.cpp igvEscena3D.h igvEscena3D.cpp igvCamara.h igvCamara.cpp)

add_executable(Practica3aGrafica
        ${SRCS})

target_link_libraries(Practica3aGrafica
        OpenGL::OpenGL
        OpenGL::GLU
        ${GLUT_LIBRARIES})