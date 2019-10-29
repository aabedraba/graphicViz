#ifndef __IGVMALLATRIANGULOS
#define __IGVMALLATRIANGULOS

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glut.h>

#endif

#include <string>

class igvMallaTriangulos {
protected:
    // Atributos

    long int num_vertices; // n�mero de v�rtices de la malla de tri�ngulos
    float *vertices; // array con las (num_vertices * 3) coordenadas de los v�rtices
    float *normales; // array con las (num_vertices * 3) coordenadas de la normal a cada v�rtice (s�lo para la generaci�n de la esfera)

    long int num_triangulos; // n�mero de tri�ngulos de la malla de tri�ngulos
    unsigned int *triangulos; // array con los (num_triangulos * 3) �ndices a los v�rtices de cada tri�ngulo

    bool mostrarA;
    bool mostrarB;

    // Apartado C: A�adir aqu� los atributos con los �ngulos de rotaci�n en X, Y y Z.
    float anguloX;
    float anguloY;
    float anguloZ;


public:
    igvMallaTriangulos(long int _num_vertices, float *_vertices, long int _num_triangulos, unsigned int *_triangulos);

    ~igvMallaTriangulos();

    void setMostarA(bool mostarA);
    void setMostrarB(bool mostrarB);
    // metodo con las llamadas OpenGL para visualizar la malla de tri�ngulos
    void visualizar();

    // Apartado C: m�todos para incrementar los �ngulos en X, y Z
    void rotarX(float _angulo);
    void rotarY(float _angulo);
    void rotarZ(float _angulo);

    // Apartado C: m�todos para obtener los valores de los �ngulos en X, y y Z
    float getAnguloX() const;
    float getAnguloY() const;
    float getAnguloZ() const;
};

#endif
