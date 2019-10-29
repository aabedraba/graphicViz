#include <cstdlib>
#include <stdio.h>
#include <math.h>

#include "igvMallaTriangulos.h"

// Metodos constructores 

igvMallaTriangulos::igvMallaTriangulos(long int _num_vertices, float *_vertices, long int _num_triangulos, unsigned int *_triangulos) {
	mostrarA = true;
	mostrarB = false;
	anguloX = anguloY = anguloZ = 0;
    num_vertices = _num_vertices;
    num_triangulos = _num_triangulos;
    vertices = new float[_num_triangulos*3];
    triangulos = new unsigned int[_num_triangulos*3];
    for (int i = 0; i < _num_vertices*3; ++i)
        vertices[i] = _vertices[i];
    for (int i = 0; i < _num_triangulos*3; ++i)
        triangulos[i] = _triangulos[i];

	/* Apartado D: a�adir el c�lculo de las normales */

}

igvMallaTriangulos::~igvMallaTriangulos() {
	/* Apartado A: destruir la malla de tri�ngulos */
    delete[] normales;
    delete[] triangulos;
    delete[] vertices;
}


// Metodos publicos 

void igvMallaTriangulos::visualizar(void) {
    glPushMatrix();
    glRotatef(getAnguloY(), 0, 1, 0);
    glRotatef(getAnguloZ(), 0, 0, 1);
    glRotatef(getAnguloX(), 1, 0, 0);

	/* Apartado A: visualizaci�n tri�ngulo a tri�ngulo */
	if (mostrarA) {
        GLfloat verde[] = {0, 1, 0, 1.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, verde);
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < num_triangulos; i++) {
            glVertex3f(vertices[3 * triangulos[i * 3]], vertices[3 * triangulos[i * 3] + 1],
                       vertices[3 * triangulos[i * 3] + 2]);
            glVertex3f(vertices[3 * triangulos[i * 3 + 1]], vertices[3 * triangulos[i * 3 + 1] + 1],
                       vertices[3 * triangulos[i * 3 + 1] + 2]);
            glVertex3f(vertices[3 * triangulos[i * 3 + 2]], vertices[3 * triangulos[i * 3 + 2] + 1],
                       vertices[3 * triangulos[i * 3 + 2] + 2]);
        }
        glEnd();
    }

	/* Apartado B: Visualizaci�n con array de v�rtices y en apartado D a�adir array de normales */
	if(mostrarB) {
        GLfloat gris[] = {0.3, 0.3, 0.3, 1.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, gris);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, triangulos);
        glDisableClientState(GL_VERTEX_ARRAY);
    }

}

void igvMallaTriangulos::setMostarA(bool mostarA) {
    igvMallaTriangulos::mostrarA = mostarA;
}

void igvMallaTriangulos::setMostrarB(bool mostrarB) {
    igvMallaTriangulos::mostrarB = mostrarB;
}

void igvMallaTriangulos::rotarX(float _angulo) {
    anguloX += _angulo;
    if (anguloX >= 360) {
        anguloX -= 360;
    }else if (anguloX < 0) {
        anguloX += 360;
    }
}

void igvMallaTriangulos::rotarY(float _angulo) {
    anguloY += _angulo;
    if (anguloY >= 360) {
        anguloY -= 360;
    }else if (anguloY < 0) {
        anguloY += 360;
    }
}

void igvMallaTriangulos::rotarZ(float _angulo) {
    anguloZ += _angulo;
    if (anguloZ >= 360) {
        anguloZ -= 360;
    }else if (anguloZ < 0) {
        anguloZ += 360;
    }
}

float igvMallaTriangulos::getAnguloX() const {
    return anguloX;
}

float igvMallaTriangulos::getAnguloY() const {
    return anguloY;
}

float igvMallaTriangulos::getAnguloZ() const {
    return anguloZ;
}

